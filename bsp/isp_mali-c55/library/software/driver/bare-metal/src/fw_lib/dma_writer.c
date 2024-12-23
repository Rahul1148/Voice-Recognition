/*
*
* SPDX-License-Identifier: BSD-3-Clause
*
* Copyright (c) 2016-2022, Arm Limited. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice, this
*    list of conditions and the following disclaimer in the documentation and/or
*    other materials provided with the distribution.
* - Neither the name of ARM nor the names of its contributors may be used to
*    endorse or promote products derived from this software without specific prior
*    written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "acamera_logger.h"
#include "system_interrupts.h"
#include "system_stdlib.h"
#include "dma_writer_api.h"
#include "dma_writer.h"
#include "acamera_firmware_config.h"
#include "acamera.h"
#include "acamera_fw.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_DMA_WRITER
#endif

extern uint32_t acamera_get_api_context( void );

#define TAG "DMA_WRITER"

#define DEBUG_FPS 0

//#define DMA_PRINTF(a) printf a
#define DMA_PRINTF( a ) (void)0

#define FPS_CALC_FREQ_MS 1000

//
static void dma_writer_initialize_reg_ops( dma_pipe *pipe )
{
    dma_writer_reg_ops_t *primary_ops = &pipe->primary;
    dma_writer_reg_ops_t *secondary_ops = &pipe->secondary;

    primary_ops->format_read = pipe->api.p_acamera_isp_dma_writer_format_read;
    primary_ops->format_write = pipe->api.p_acamera_isp_dma_writer_format_write;
    primary_ops->bank0_base_write = pipe->api.p_acamera_isp_dma_writer_bank0_base_write;
    primary_ops->line_offset_write = pipe->api.p_acamera_isp_dma_writer_line_offset_write;
    primary_ops->write_on_write = pipe->api.p_acamera_isp_dma_writer_frame_write_on_write;
    primary_ops->active_width_write = pipe->api.p_acamera_isp_dma_writer_active_width_write;
    primary_ops->active_height_write = pipe->api.p_acamera_isp_dma_writer_active_height_write;
    primary_ops->active_width_read = pipe->api.p_acamera_isp_dma_writer_active_width_read;
    primary_ops->active_height_read = pipe->api.p_acamera_isp_dma_writer_active_height_read;

    secondary_ops->format_read = pipe->api.p_acamera_isp_dma_writer_format_read_uv;
    secondary_ops->format_write = pipe->api.p_acamera_isp_dma_writer_format_write_uv;
    secondary_ops->bank0_base_write = pipe->api.p_acamera_isp_dma_writer_bank0_base_write_uv;
    secondary_ops->line_offset_write = pipe->api.p_acamera_isp_dma_writer_line_offset_write_uv;
    secondary_ops->write_on_write = pipe->api.p_acamera_isp_dma_writer_frame_write_on_write_uv;
    secondary_ops->active_width_write = pipe->api.p_acamera_isp_dma_writer_active_width_write_uv;
    secondary_ops->active_height_write = pipe->api.p_acamera_isp_dma_writer_active_height_write_uv;
    secondary_ops->active_width_read = pipe->api.p_acamera_isp_dma_writer_active_width_read_uv;
    secondary_ops->active_height_read = pipe->api.p_acamera_isp_dma_writer_active_height_read_uv;
}

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
//
static int dma_writer_alloc_default_frame( dma_pipe *pipe )
{
    acamera_settings *settings = &pipe->settings.p_ctx->settings;
    uint32_t ctx_id = pipe->settings.p_ctx->context_id;
    tframe_t *default_frame;
    void *virt_addr;
    uint64_t dma_addr;
    int i;
    tframe_t *curr_frame = &pipe->settings.curr_frame;
    tframe_t *done_frame = &pipe->settings.done_frame;
    tframe_t *delay_frame = &pipe->settings.delay_frame;
    dma_writer_reg_ops_t *primary_ops = &pipe->primary;

    pipe->settings.default_index = 0;

    for ( i = 0; i < DMA_WRITER_DEFAULT_BUFFER_NO; i++ ) {
        default_frame = &pipe->settings.default_frame[i];
        system_memset( default_frame, 0, sizeof( *default_frame ) );

        default_frame->primary.type = primary_ops->format_read( pipe->settings.isp_base );
        default_frame->primary.status = dma_buf_empty;
        default_frame->primary.width = primary_ops->active_width_read( pipe->settings.isp_base );
        default_frame->primary.height = primary_ops->active_height_read( pipe->settings.isp_base );
        default_frame->primary.line_offset = acamera_line_offset( default_frame->primary.width,
                                                                  _get_pixel_width( default_frame->primary.type ) );
        default_frame->primary.size = default_frame->primary.height * default_frame->primary.line_offset;

        virt_addr = settings->callback_dma_alloc_coherent( ctx_id, default_frame->primary.size, &dma_addr );
        if ( !virt_addr ) {
            LOG( LOG_CRIT, "Pipe: %d unable to allocate default buffer.", pipe->type );
            return -1;
        }

        default_frame->primary.address = (uint32_t)dma_addr;
        default_frame->primary.virt_addr = virt_addr;

        LOG( LOG_INFO, "Pipe: %d Default buffer size: %d dma_addr: %lx.",
             pipe->type, default_frame->primary.size, default_frame->primary.address );

        /* For the default frames we don't use the UV plane. */
        default_frame->secondary.status = dma_buf_purge;
    }

    *curr_frame = pipe->settings.default_frame[pipe->settings.default_index];
    *done_frame = pipe->settings.default_frame[pipe->settings.default_index];
    *delay_frame = pipe->settings.default_frame[pipe->settings.default_index];

    pipe->settings.default_index = ( pipe->settings.default_index + 1 ) % DMA_WRITER_DEFAULT_BUFFER_NO;

    return 0;
}

//
static void dma_writer_free_default_frame( dma_pipe *pipe )
{
    acamera_settings *settings = &pipe->settings.p_ctx->settings;
    uint32_t ctx_id = pipe->settings.p_ctx->context_id;
    tframe_t *default_frame;
    void *virt_addr;
    uint64_t dma_addr;
    uint64_t size;
    int i;

    for ( i = 0; i < DMA_WRITER_DEFAULT_BUFFER_NO; i++ ) {
        default_frame = &pipe->settings.default_frame[i];
        dma_addr = default_frame->primary.address;
        virt_addr = default_frame->primary.virt_addr;
        size = default_frame->primary.size;

        settings->callback_dma_free_coherent( ctx_id, size, virt_addr, dma_addr );

        system_memset( default_frame, 0, sizeof( *default_frame ) );
    }
}
#endif

//
static int dma_writer_stream_get_frame( dma_pipe *pipe, tframe_t *tframe )
{
    uint32_t ctx_id = pipe->settings.p_ctx->context_id;
    acamera_stream_type_t type = pipe->type == dma_fr ? ACAMERA_STREAM_FR : ACAMERA_STREAM_DS1;
    acamera_settings *settings = &pipe->settings.p_ctx->settings;
    aframe_t tmp_aframes[2];
    int rc;

    tmp_aframes[0] = tframe->primary;
    tmp_aframes[1] = tframe->secondary;

    rc = settings->callback_stream_get_frame( ctx_id, type, tmp_aframes, 2 );

    tframe->primary = tmp_aframes[0];
    tframe->secondary = tmp_aframes[1];

    return rc;
}

//
static int dma_writer_stream_put_frame( dma_pipe *pipe, tframe_t *tframe )
{
    uint32_t ctx_id = pipe->settings.p_ctx->context_id;
    acamera_stream_type_t type = pipe->type == dma_fr ? ACAMERA_STREAM_FR : ACAMERA_STREAM_DS1;
    acamera_settings *settings = &pipe->settings.p_ctx->settings;
    aframe_t tmp_aframes[2];
    int rc;

    tmp_aframes[0] = tframe->primary;
    tmp_aframes[1] = tframe->secondary;

    rc = settings->callback_stream_put_frame( ctx_id, type, tmp_aframes, 2 );

    tframe->primary = tmp_aframes[0];
    tframe->secondary = tmp_aframes[1];

    return rc;
}

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
//
static int dma_writer_configure_frame_reader( dma_pipe *pipe, tframe_t *frame )
{
    aframe_t *aframe;

    if ( !( pipe->settings.active && pipe->settings.ctx_id == acamera_get_api_context() ) ) {
        return 0;
    }

    aframe = &frame->primary;

    // Perform address buffering to avoid visual artefacts on HDMI output
    // which is likely on multi-context setups
    static uint32_t address_buffer = 0;

    const uint32_t address = aframe->address + pipe->settings.read_offset_y * aframe->line_offset + pipe->settings.read_offset_x;
    pipe->api.p_acamera_fpga_frame_reader_rbase_write( pipe->settings.isp_base, address_buffer );
    pipe->api.p_acamera_fpga_frame_reader_line_offset_write( pipe->settings.isp_base, aframe->line_offset );
    pipe->api.p_acamera_fpga_frame_reader_format_write( pipe->settings.isp_base, aframe->type );
    pipe->api.p_acamera_fpga_frame_reader_rbase_load_write( pipe->settings.isp_base, 1 );
    pipe->api.p_acamera_fpga_frame_reader_rbase_load_write( pipe->settings.isp_base, 0 );

    address_buffer = address;

    return 0;
}
#endif

//
static int dma_writer_configure_frame_writer( dma_pipe *pipe,
                                              aframe_t *aframe,
                                              dma_writer_reg_ops_t *reg_ops )
{
    uint32_t addr;
    uint32_t line_offset;

    if ( aframe->status != dma_buf_purge ) {
        /*
         * For now we don't change the settings, so we take them from the hardware.
         * The reason is that they are configured through a different API.
         */
        aframe->type = reg_ops->format_read( pipe->settings.isp_base );
        aframe->width = reg_ops->active_width_read( pipe->settings.isp_base );
        aframe->height = reg_ops->active_height_read( pipe->settings.isp_base );

        aframe->line_offset = acamera_line_offset( aframe->width, _get_pixel_width( aframe->type ) );
        aframe->size = aframe->line_offset * aframe->height;
        if ( aframe->type == DMA_FORMAT_NV12_UV || aframe->type == DMA_FORMAT_NV12_VU ) {
            aframe->size /= 2;
        }

        addr = aframe->address;
        line_offset = aframe->line_offset;

        if ( pipe->settings.vflip ) {
            addr += aframe->size - aframe->line_offset;
            line_offset = -aframe->line_offset;
        }

        reg_ops->format_write( pipe->settings.isp_base, aframe->type );
        reg_ops->active_width_write( pipe->settings.isp_base, aframe->width );
        reg_ops->active_height_write( pipe->settings.isp_base, aframe->height );
        reg_ops->line_offset_write( pipe->settings.isp_base, line_offset );
        reg_ops->bank0_base_write( pipe->settings.isp_base, addr );
        reg_ops->write_on_write( pipe->settings.isp_base, 1 );
    } else {
        reg_ops->write_on_write( pipe->settings.isp_base, 0 );
    }

    return 0;
}

uint8_t skip_frame( dma_pipe *pipe, dma_writer_reg_ops_t *reg_ops )
{

    pipe->settings.frames_in_cnt++;
    uint8_t skip = ( pipe->settings.frames_in_cnt % pipe->settings.fps_throttle_factor != 0 );

#if DEBUG_FPS
    if ( !skip ) {
        pipe->settings.frames_out_cnt++;
    }
    static uint32_t static_time = 0;
    static uint32_t static_frames_in_cnt = 0;
    static uint32_t static_frames_out_cnt = 0;
    uint32_t cur_time = system_timer_timestamp();
    uint32_t time_elapsed = ( cur_time - static_time ) * 1000 / system_timer_frequency();

    if ( time_elapsed > FPS_CALC_FREQ_MS ) {
        static_time = cur_time;
        LOG( LOG_ERR, "Input fps %d output fps %d",
             ( pipe->settings.frames_in_cnt - static_frames_in_cnt ) * 1000 / time_elapsed,
             ( pipe->settings.frames_out_cnt - static_frames_out_cnt ) * 1000 / time_elapsed );
        static_frames_in_cnt = pipe->settings.frames_in_cnt;
        static_frames_out_cnt = pipe->settings.frames_out_cnt;
    }
#endif
    return skip;
}

//
static int dma_writer_m2m_frame_ready( dma_pipe *pipe )
{
    struct _acamera_context_t *p_ctx = pipe->settings.p_ctx;
    metadata_t *meta = &pipe->settings.curr_metadata;
    tframe_t *done_frame = &pipe->settings.curr_frame;
    tframe_t *curr_frame = &pipe->settings.curr_frame;
    int rc = 0;

    if ( !p_ctx ) {
        return -1;
    }

    pipe->source = dma_source_default;

    meta->frame_id = p_ctx->isp_frame_counter;
    curr_frame->primary.frame_id = meta->frame_id;
    curr_frame->secondary.frame_id = meta->frame_id;

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
    dma_writer_configure_frame_reader( pipe, done_frame );
#endif

    LOG(LOG_DEBUG, "done_frame->primary.status %d, done_frame->secondary.status %d", done_frame->primary.status, done_frame->secondary.status);
    /* Put back the done frame to the application (V4L2 for example). */
    if ( done_frame->primary.status == dma_buf_busy || done_frame->secondary.status == dma_buf_busy ) {
        rc = dma_writer_stream_put_frame( pipe, done_frame );
    }
    return rc;
}

static int dma_writer_configure_pipe_m2m( dma_pipe *pipe )
{
    struct _acamera_context_t *p_ctx = pipe->settings.p_ctx;
    tframe_t *curr_frame = &pipe->settings.curr_frame;
    dma_writer_reg_ops_t *primary_ops = &pipe->primary;
    dma_writer_reg_ops_t *secondary_ops = &pipe->secondary;
    int rc;

    if ( !p_ctx ) {
        return -1;
    }

    /* Try to get a new buffer from application (V4l2 for example). */
    rc = dma_writer_stream_get_frame( pipe, curr_frame );
    if ( rc ) {
        curr_frame->primary.status = dma_buf_purge;
        curr_frame->secondary.status = dma_buf_purge;
    } else {
        if ( curr_frame->primary.status == dma_buf_empty ) {
            curr_frame->primary.status = dma_buf_busy;
        }
        if ( curr_frame->secondary.status == dma_buf_empty ) {
            curr_frame->secondary.status = dma_buf_busy;
        }
    }
    LOG(LOG_DEBUG, "start -> curr_frame->primary.status %d, curr_frame->secondary.status %d", curr_frame->primary.status, curr_frame->secondary.status);

    /* Write the current frame in the software config. */
    dma_writer_configure_frame_writer( pipe, &curr_frame->primary, primary_ops );
    dma_writer_configure_frame_writer( pipe, &curr_frame->secondary, secondary_ops );

    return 0;
}


//
static int dma_writer_configure_pipe( dma_pipe *pipe )
{
    struct _acamera_context_t *p_ctx = pipe->settings.p_ctx;
    metadata_t *meta = &pipe->settings.curr_metadata;
    tframe_t *curr_frame = &pipe->settings.curr_frame;
    tframe_t *done_frame = &pipe->settings.done_frame;
    tframe_t *delay_frame = &pipe->settings.delay_frame;
    dma_writer_reg_ops_t *primary_ops = &pipe->primary;
    dma_writer_reg_ops_t *secondary_ops = &pipe->secondary;
    int rc;

    if ( !p_ctx ) {
        return -1;
    }

    // Check if throttling is enabled and this frame needs to be skipped
    if ( skip_frame( pipe, primary_ops ) == 1 ) {
        return 0;
    }

    curr_frame->primary.frame_id = meta->frame_id;
    curr_frame->secondary.frame_id = meta->frame_id;

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
    dma_writer_configure_frame_reader( pipe, done_frame );
#endif

    /* Put back the done frame to the application (V4L2 for example). */
    if ( done_frame->primary.status == dma_buf_busy || done_frame->secondary.status == dma_buf_busy ) {
        dma_writer_stream_put_frame( pipe, done_frame );
    }

    /* Done_frame is the last delayed frame. */
    *done_frame = *delay_frame;

    /* delay_frame is the last current frame written in the software config. */
    *delay_frame = *curr_frame;

    /* Try to get a new buffer from application (V4l2 for example). */
    rc = dma_writer_stream_get_frame( pipe, curr_frame );
    if ( rc ) {
#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
        /* If there is no available buffer, use one of the default buffers. */
        *curr_frame = pipe->settings.default_frame[pipe->settings.default_index];
        pipe->settings.default_index = ( pipe->settings.default_index + 1 ) % DMA_WRITER_DEFAULT_BUFFER_NO;
#else
        curr_frame->primary.status = dma_buf_purge;
        curr_frame->secondary.status = dma_buf_purge;
#endif
    } else {
        if ( curr_frame->primary.status == dma_buf_empty ) {
            curr_frame->primary.status = dma_buf_busy;
        }
        if ( curr_frame->secondary.status == dma_buf_empty ) {
            curr_frame->secondary.status = dma_buf_busy;
        }
    }

    /* Write the current frame in the software config. */
    dma_writer_configure_frame_writer( pipe, &curr_frame->primary, primary_ops );
    dma_writer_configure_frame_writer( pipe, &curr_frame->secondary, secondary_ops );

    return 0;
}

static dma_handle s_handle[FIRMWARE_CONTEXT_NUMBER];
static int32_t ctx_pos = 0;

//
dma_error dma_writer_create( void **handle )
{
    dma_error result = edma_ok;
    if ( handle != NULL ) {

        if ( ctx_pos < acamera_get_context_number() ) {
            *handle = &s_handle[ctx_pos];
            system_memset( (void *)*handle, 0, sizeof( dma_handle ) );
            ctx_pos++;
        } else {
            *handle = NULL;
            result = edma_fail;
            LOG( LOG_ERR, "DMA context overshoot." );
        }
    } else {
        result = edma_fail;
    }
    return result;
}

//
void dma_writer_exit( void *handle )
{
#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
    dma_handle *p_dma = (dma_handle *)handle;

    dma_writer_free_default_frame( &p_dma->pipe[dma_fr] );
#if ISP_HAS_DS1
    dma_writer_free_default_frame( &p_dma->pipe[dma_ds1] );
#endif
#endif // #if CONFIG_DMA_WRITER_DEFAULT_BUFFER

    ctx_pos = 0;
}

//
dma_error dma_writer_update_state( dma_pipe *pipe )
{
    dma_error result = edma_ok;
    if ( pipe != NULL ) {
        LOG( LOG_INFO, "State update %dx%d", (int)pipe->settings.width, (int)pipe->settings.height );
        if ( pipe->settings.width == 0 || pipe->settings.height == 0 ) {
            result = edma_invalid_settings;
            pipe->settings.enabled = 0;
            pipe->api.p_acamera_isp_dma_writer_frame_write_on_write( pipe->settings.isp_base, pipe->settings.enabled ); // Disable pipe on invalid settings.
            pipe->api.p_acamera_isp_dma_writer_frame_write_on_write_uv( pipe->settings.isp_base, pipe->settings.enabled );
            return result;
        }

        // Set default settings here.
        pipe->api.p_acamera_isp_dma_writer_max_bank_write( pipe->settings.isp_base, 0 );
        pipe->api.p_acamera_isp_dma_writer_active_width_write( pipe->settings.isp_base, pipe->settings.width );
        pipe->api.p_acamera_isp_dma_writer_active_height_write( pipe->settings.isp_base, pipe->settings.height );

        pipe->api.p_acamera_isp_dma_writer_max_bank_write_uv( pipe->settings.isp_base, 0 );
        pipe->api.p_acamera_isp_dma_writer_active_width_write_uv( pipe->settings.isp_base, pipe->settings.width );
        pipe->api.p_acamera_isp_dma_writer_active_height_write_uv( pipe->settings.isp_base, pipe->settings.height );
    } else {
        result = edma_fail;
    }
    return result;
}

//
dma_error dma_writer_get_settings( void *handle, dma_type type, dma_pipe_settings *settings )
{
    dma_error result = edma_ok;
    if ( handle != NULL ) {
        dma_handle *p_dma = (dma_handle *)handle;
        system_memcpy( (void *)settings, &p_dma->pipe[type].settings, sizeof( dma_pipe_settings ) );
    } else {
        result = edma_fail;
    }
    return result;
}

//
dma_error dma_writer_set_settings( void *handle, dma_type type, dma_pipe_settings *settings )
{
    dma_error result = edma_ok;
    if ( handle != NULL ) {
        dma_handle *p_dma = (dma_handle *)handle;
        system_memcpy( (void *)&p_dma->pipe[type].settings, settings, sizeof( dma_pipe_settings ) );
        result = dma_writer_update_state( &p_dma->pipe[type] );

    } else {
        LOG( LOG_ERR, "Set settings handle NULL." );
        result = edma_fail;
    }
    return result;
}

//
dma_error dma_writer_get_ptr_settings( void *handle, dma_type type, dma_pipe_settings **settings )
{
    dma_error result = edma_ok;
    if ( handle != NULL ) {
        dma_handle *p_dma = (dma_handle *)handle;
        *settings = &p_dma->pipe[type].settings;
    } else {
        result = edma_fail;
    }
    return result;
}

//
void dma_writer_set_initialized( void *handle, dma_type type, uint8_t initialized )
{
    if ( handle != NULL ) {
        dma_handle *p_dma = (dma_handle *)handle;
        p_dma->pipe[type].state.initialized = initialized;
    }
}

//
dma_error dma_writer_init( void *handle, dma_type type, dma_pipe_settings *settings, dma_api *api )
{
    dma_error result = edma_ok;
#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
    int rc;
#endif

    if ( handle != NULL ) {
        dma_handle *p_dma = (dma_handle *)handle;
        p_dma->pipe[type].type = type;
        p_dma->pipe[type].source = dma_source_default;

        system_memcpy( (void *)&p_dma->pipe[type].api, api, sizeof( dma_api ) );
        result = dma_writer_set_settings( handle, type, settings );

        dma_writer_initialize_reg_ops( &p_dma->pipe[type] );

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
        rc = dma_writer_alloc_default_frame( &p_dma->pipe[type] );
        if ( rc ) {
            LOG( LOG_ERR, "%s: Failed to alloc default frame type: %d", TAG, (int)type );
        }
#endif

        if ( result == edma_ok ) {
            LOG( LOG_INFO, "%s: Initialized a DMA writer output. %dx%d ", TAG, (int)settings->width, (int)settings->height );
        } else {
            LOG( LOG_ERR, "%s: Failed to initialize a DMA writer type: %d output. %dx%d.",
                 TAG, (int)type, (int)settings->width, (int)settings->height );
        }
    } else {
        result = edma_fail;
    }
    return result;
}

dma_error dma_writer_configure_m2m_pipes( void *handle )
{
    int idx;
    dma_error result;
    dma_handle *p_dma = (dma_handle *)handle;

    if ( !p_dma ) {
        LOG( LOG_ERR, "p_dma is NULL!" );
        return edma_fail;
    }

    for ( idx = 0; idx < dma_max; idx++ ) {
        LOG( LOG_DEBUG, "idx %d", idx );
        p_dma->pipe[idx].source = dma_source_m2m;
        result = dma_writer_configure_pipe_m2m( &p_dma->pipe[idx] );
    }
    return result;
}

//
dma_error dma_writer_pipe_process_interrupt( dma_pipe *pipe, uint32_t irq_event )
{
    switch ( irq_event ) {
    case ACAMERA_IRQ_FRAME_WRITER_FR:
        if ( pipe->type == dma_fr ) {
            if ( pipe->source == dma_source_m2m ) {
                dma_writer_m2m_frame_ready( pipe );
            } else {
                dma_writer_configure_pipe( pipe );
            }
        }
        break;
    case ACAMERA_IRQ_FRAME_WRITER_DS:
        if ( pipe->type == dma_ds1 ) {
            if ( pipe->source == dma_source_m2m ) {
                dma_writer_m2m_frame_ready( pipe );
            } else {
                dma_writer_configure_pipe( pipe );
            }
        }
        break;
    }

    return 0;
}

//
dma_error dma_writer_process_interrupt( void *handle, uint32_t irq_event )
{
    dma_error result = edma_ok;
    uint32_t idx = 0;

    dma_handle *p_dma = (dma_handle *)handle;
    if ( !p_dma ) {
        LOG( LOG_ERR, "p_dma is NULL for event: %u.", (unsigned int)irq_event );
        return edma_fail;
    }

    for ( idx = 0; idx < dma_max; idx++ ) {
        dma_writer_pipe_process_interrupt( &p_dma->pipe[idx], irq_event );
    }
    return result;
}

//
metadata_t *dma_writer_return_metadata( void *handle, dma_type type )
{
    if ( handle != NULL ) {

        dma_handle *p_dma = (dma_handle *)handle;

        metadata_t *ret = &( p_dma->pipe[type].settings.curr_metadata );
        return ret;
    }
    return 0;
}

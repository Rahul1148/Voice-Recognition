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

#include "acamera_fw.h"
#include "dma_writer_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_DMA_WRITER
#endif

void dma_writer_fsm_clear( dma_writer_fsm_t *p_fsm )
{
    p_fsm->dma_reader_out = dma_fr;
    p_fsm->dma_reader_offset_x = 0;
    p_fsm->dma_reader_offset_y = 0;
    p_fsm->context_created = 0;
    p_fsm->dis_ds_base_offset = 0;
    p_fsm->handle = NULL;
    uint8_t pipe;
    for ( pipe = dma_fr; pipe < dma_max; pipe++ ) {
        p_fsm->fps_throttle_settings[pipe] = 1;
    }
}

void dma_writer_request_interrupt( dma_writer_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}

void dma_writer_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    dma_writer_fsm_t *p_fsm = (dma_writer_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    dma_writer_fsm_clear( p_fsm );

    p_fsm->state = dma_writer_state_wait_for_sensor;
    frame_buffer_initialize( p_fsm );
}

int dma_writer_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    dma_writer_fsm_t *p_fsm = (dma_writer_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_DMA_PIPE_SETTING: {
        fsm_param_dma_pipe_setting_t *p_pipe_setting = NULL;
        if ( !input || input_size != sizeof( fsm_param_dma_pipe_setting_t ) ) {
            LOG( LOG_ERR, "Size mismatch, param_id: %d.", param_id );
            rc = -1;
            break;
        }
        /*
         * For now p_pipe_setting is unused. We may want to use it in future
         */
        (void)p_pipe_setting;

        fsm_raise_event( p_fsm, event_id_frame_buf_reinit );

        break;
    }

    case FSM_PARAM_SET_DMA_READER_OUTPUT:
        if ( !input || input_size != sizeof( dma_type ) ) {
            LOG( LOG_ERR, "Size mismatch, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->dma_reader_out = *(dma_type *)input;
        acamera_frame_buffer_update( p_fsm );

        break;

    case FSM_PARAM_SET_DMA_WRITER_M2M_BUF:
        rc = dma_writer_configure_m2m_pipes( p_fsm->handle );
        break;

    case FSM_PARAM_SET_DMA_READER_OFFSET_X:
        p_fsm->dma_reader_offset_x = *(uint32_t *)input;
        acamera_frame_buffer_update( p_fsm );
        break;
    case FSM_PARAM_SET_DMA_READER_OFFSET_Y:
        p_fsm->dma_reader_offset_y = *(uint32_t *)input;
        acamera_frame_buffer_update( p_fsm );
        break;

    case FSM_PARAM_SET_DMA_VFLIP:
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Size mismatch, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->vflip = *(uint32_t *)input;
        acamera_frame_buffer_update( p_fsm );

        break;
    case FSM_PARAM_SET_DMA_FPS_THROTTLING_FACTOR: {
        fsm_param_dma_fps_throttle_setting_t *fps_throttle = (fsm_param_dma_fps_throttle_setting_t *)input;
        p_fsm->fps_throttle_settings[fps_throttle->pipe_id] = fps_throttle->factor;
        acamera_frame_buffer_update( p_fsm );
        break;
    }
    default:
        rc = -1;
        break;
    }

    return rc;
}

int dma_writer_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    dma_writer_fsm_t *p_fsm = (dma_writer_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_DMA_READER_OUTPUT:
        if ( !output || output_size != sizeof( dma_type ) ) {
            LOG( LOG_ERR, "Size mismatch, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(dma_type *)output = p_fsm->dma_reader_out;

        break;

    case FSM_PARAM_GET_DMA_VFLIP:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Size mismatch, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->vflip;

        break;
    case FSM_PARAM_GET_DMA_READER_OFFSET_X:
        *(uint32_t *)output = p_fsm->dma_reader_offset_x;
        break;
    case FSM_PARAM_GET_DMA_READER_OFFSET_Y:
        *(uint32_t *)output = p_fsm->dma_reader_offset_y;
        break;
    case FSM_PARAM_GET_DMA_FPS_THROTTLING_FACTOR: {
        uint8_t pipe_id = *(uint8_t *)input;
        *(uint32_t *)output = p_fsm->fps_throttle_settings[pipe_id];
        break;
    }
    default:
        rc = -1;
        break;
    }

    return rc;
}


uint8_t dma_writer_fsm_process_event( dma_writer_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_frame_buffer_fr_ready:
        if ( p_fsm->state == dma_writer_state_frame_processing_wait_events ) {
            p_fsm->state = dma_writer_state_frame_processing_FR_finished;
            frame_buffer_fr_finished( p_fsm );
            p_fsm->state = dma_writer_state_frame_processing_wait_events;
            b_event_processed = 1;
        }
        break;
    case event_id_frame_buffer_ds_ready:
        if ( p_fsm->state == dma_writer_state_frame_processing_wait_events ) {
            p_fsm->state = dma_writer_state_frame_processing_DS_finished;
            frame_buffer_ds_finished( p_fsm );
            p_fsm->state = dma_writer_state_frame_processing_wait_events;
            b_event_processed = 1;
        }
        break;
#ifdef ISP_HAS_CROP_FSM
    case event_id_crop_updated:
#else
    case event_id_sensor_ready:
#endif
        if ( ( p_fsm->state == dma_writer_state_wait_for_sensor ) ||
             ( p_fsm->state == dma_writer_state_frame_processing_wait_events ) ) {
            p_fsm->state = dma_writer_state_frame_processing_init;
            acamera_frame_buffer_update( p_fsm );
            p_fsm->state = dma_writer_state_frame_processing_wait_events;
            b_event_processed = 1;
        }
        break;
    case event_id_frame_buf_reinit:
        if ( p_fsm->state == dma_writer_state_frame_processing_wait_events ) {
            p_fsm->state = dma_writer_state_frame_processing_buf_reinit;
            acamera_frame_buffer_update( p_fsm );
            p_fsm->state = dma_writer_state_frame_processing_wait_events;
            b_event_processed = 1;
        }
        break;
    case event_id_sensor_not_ready:
        if ( ( p_fsm->state >= dma_writer_state_frame_processing ) && ( p_fsm->state < next_to_dma_writer_state_frame_processing ) ) {
            p_fsm->state = dma_writer_state_wait_for_sensor;
            b_event_processed = 1;
        }
        break;
    case event_id_frame_buffer_metadata:
        if ( p_fsm->state == dma_writer_state_frame_processing_wait_events ) {
            p_fsm->state = dma_writer_state_frame_processing_prepare_metadata;
            frame_buffer_prepare_metadata( p_fsm );
            p_fsm->state = dma_writer_state_frame_processing_wait_events;
            b_event_processed = 1;
        }
        break;
    }

    return b_event_processed;
}

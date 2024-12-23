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

#include "acamera_types.h"
#include "acamera_fw.h"
#include "acamera.h"
#include "system_log.h"
#include "acamera_isp_config.h"
#include "sw_mcfe.h"
#include "sw_mcfe_queue.h"
#include "sw_mcfe_external_driver.h"

#if ( ISP_HAS_FPGA_WRAPPER )
#include "fpga_dma_input.h"
#endif
#if defined( ISP_HAS_FPGA_DMA_FE_FSM )
#define MAX_Q_ENTRIES ( ( FIRMWARE_CONTEXT_NUMBER * ISP_FE_BUFFER_SIZE ) + 1 )
#else
#define MAX_Q_ENTRIES ( ( FIRMWARE_CONTEXT_NUMBER * 3 ) + 1 )
#endif

typedef enum {
    STATE_FREE,
    STATE_OCCUPIED,
    STATE_MAX
} frame_state_t;

typedef enum {
    SOURCE_V4L2,
    SOURCE_INTERNAL
} frame_source_e;

// Reference data structure to store frame private data.
typedef struct {
    frame_state_t  frame_state;
    aframe_t       frame;
    frame_source_e frame_source;
} ext_driver_private_t;

// Data structure to store all the necessary info for this external driver module
typedef struct _driver_info {
    acamera_firmware_t *fw;                      // Handle to the Acamera firmware instance.
    ext_driver_private_t entries[MAX_Q_ENTRIES]; // Array to store frame private data
    sys_spinlock queue_lock;                     // lock to protect queue concurrency
    uint8_t initialised;
} driver_info_t;

// Global handle to the driver info
static driver_info_t g_driver_hdl;

/* Store frame address in an empty entry and return */
static ext_driver_private_t *get_entry( uint32_t address )
{
    ext_driver_private_t *entry = NULL;
    uint8_t idx;

    unsigned long flags = system_spinlock_lock( g_driver_hdl.queue_lock );
    // Find a free entry
    for ( idx = 0; idx < MAX_Q_ENTRIES; idx++ ) {
        if ( g_driver_hdl.entries[idx].frame_state == STATE_FREE ) {
            break;
        }
    }

    // No empty entries, error
    if ( idx == MAX_Q_ENTRIES ) {
        LOG( LOG_ERR, "Failed to get empty entry, all %d entries are in use.", MAX_Q_ENTRIES );
        system_spinlock_unlock( g_driver_hdl.queue_lock, flags );
        return NULL;
    }

    // Entry found, store frame address in it and return
    entry = &g_driver_hdl.entries[idx];
    entry->frame_state = STATE_OCCUPIED;
    entry->frame.address = address;
    system_spinlock_unlock( g_driver_hdl.queue_lock, flags );
    return entry;
}

/* Release the entry pointed by private data */
static void release_entry( ext_driver_private_t *entry )
{
    unsigned long flags = system_spinlock_lock( g_driver_hdl.queue_lock );
    entry->frame_state = STATE_FREE;
    entry->frame.address = 0;
    system_spinlock_unlock( g_driver_hdl.queue_lock, flags );
}

static void external_v4l2_frame_done(uint32_t ctx_id, ext_driver_private_t *entry)
{
    acamera_settings *p_settings = &g_driver_hdl.fw->fw_ctx[ctx_id].settings;
    int rc = p_settings->callback_stream_put_frame( ctx_id, ACAMERA_STREAM_RAW, &entry->frame, 1 );
    if ( rc ) {
        LOG( LOG_ERR, "Put frame on context %d error %d", ctx_id, rc );
    }
}

/* Callback from MCFE that a frame has been processed by ISP */
static void external_frame_done_cb( uint32_t ctx_id, void *private )
{
    // Consider releasing private data, marking frame and its associated memory status as free, etc.
    if ( g_driver_hdl.initialised ) {
        ext_driver_private_t *entry = (ext_driver_private_t *)private;
        if ( entry->frame_source == SOURCE_V4L2 ) {
            external_v4l2_frame_done( ctx_id, entry );
        }
        release_entry( (ext_driver_private_t *)private );
    }
}

/* Callback from MCFE to start sending a frame to ISP */
static void external_start_frame_cb( uint32_t ctx_id, void *private )
{
#if ( ISP_HAS_FPGA_WRAPPER )
    // This internally invokes triggers DMA read operation in the external component to send a frame to the ISP
    if ( g_driver_hdl.initialised ) {
        ext_driver_private_t *entry = (ext_driver_private_t *)private;
        dma_input_process_context( g_driver_hdl.fw, ctx_id, entry->frame.address );
    }
#endif
}

#if defined( ISP_HAS_FPGA_DMA_FE_FSM )
/* Process a frame received from a DMA reader/writer and notify MCFE */
static int32_t external_process_context_frame( uint32_t ctx_id )
{
    int32_t result = NO_ERROR;

    if ( ctx_id >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_ERR, "Context ID (%d) provided is out of range [0;%d].", ctx_id, FIRMWARE_CONTEXT_NUMBER - 1 );
        return -1;
    }

    aframe_t *frame = dma_input_get_latest_frame( g_driver_hdl.fw, ctx_id );
    if ( ( frame != NULL ) && ( frame->address != 0 ) ) {
        // Notify MCFE that a new frame is available
        LOG( LOG_DEBUG, "DMA capture new frame from context %d at address 0x%x", ctx_id, frame->address );
        ext_driver_private_t *entry = get_entry( frame->address );
        if ( entry != NULL ) {
            entry->frame_source = SOURCE_INTERNAL;
            result = sw_mcfe_notify_frame( ctx_id, CONTEXT_TYPE_M2M, entry );
        }
    }
    return result;
}
#endif

/* Initialize the driver here */
int32_t sw_mcfe_external_driver_init( acamera_firmware_t *g_fw )
{
    g_driver_hdl.fw = g_fw;
    system_spinlock_init( &g_driver_hdl.queue_lock );
    system_memset( &g_driver_hdl.entries[0], 0, sizeof( g_driver_hdl.entries ) );

    // Register frame done and start frame callbacks with MCFE.
    sw_mcfe_register( external_frame_done_cb, external_start_frame_cb );

#if ( ISP_HAS_FPGA_WRAPPER )
    // Initialize the FPGA DMA writers and readers
    fpga_dma_input_init( g_fw );
#endif

    g_driver_hdl.initialised = 1;

    return NO_ERROR;
}

/* Deinitialize the driver here */
int32_t sw_mcfe_external_driver_deinit( void )
{
    g_driver_hdl.initialised = 0;
#if ( ISP_HAS_FPGA_WRAPPER )
    // Stop the data inflow from DMA readers/writers
    fpga_dma_input_stop( g_driver_hdl.fw );
    // Wait for all DMA readers/writers to stop
    system_timer_usleep( 60 * 1000 );
#endif
    if ( g_driver_hdl.queue_lock ) {
        system_spinlock_destroy( g_driver_hdl.queue_lock );
    }
    return NO_ERROR;
}

/* Interrupt handler to process interrupts from FPGA DMA Writers */
int32_t sw_mcfe_external_driver_interrupt_handler( uint32_t event_mask )
{
#if defined( ISP_HAS_FPGA_DMA_FE_FSM )
    // Check if external driver is initialised
    if ( g_driver_hdl.initialised ) {
        uint32_t ctx_id;

        for ( ctx_id = 0; ctx_id < FIRMWARE_CONTEXT_NUMBER; ctx_id++, event_mask >>= 1 ) {
            if ( event_mask & 0x1 ) {
                external_process_context_frame( ctx_id );
            }
        }
    }
#endif
    return NO_ERROR;
}

/* Process a frame received from a V4L2 and notify MCFE */
int32_t sw_mcfe_external_process_request_v4l2( uint32_t ctx_id )
{
    int32_t result = NO_ERROR;
    ext_driver_private_t *entry;

    if ( ctx_id >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_ERR, "Context ID (%d) provided is out of range [0;%d].", ctx_id, FIRMWARE_CONTEXT_NUMBER - 1 );
        return -1;
    }
    if ( !g_driver_hdl.initialised ) {
        LOG( LOG_ERR, "Driver is not inialized!" );
        return -1;
    }

    entry = get_entry(-1);
    if ( entry != NULL ) {
        acamera_settings *p_settings = &g_driver_hdl.fw->fw_ctx->settings;
        int rc = p_settings->callback_stream_get_frame( ctx_id, ACAMERA_STREAM_RAW, &entry->frame, 1 );
        if ( rc == 0 ) {
            entry->frame_source = SOURCE_V4L2;
            // Notify MCFE that a new frame is available
            result = sw_mcfe_notify_frame( ctx_id, CONTEXT_TYPE_M2M, entry );
        }
    } else {
        LOG(LOG_ERR, "no frame!");
    }
    return result;
}

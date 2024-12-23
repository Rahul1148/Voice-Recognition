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
#include "system_cdma.h"
#include "sw_mcfe.h"
#include "sw_mcfe_external_driver.h"

static mcfe_info_t g_mcfe_hdl;

#define ENABLE_MCFE_LOGGING 0

#if ENABLE_MCFE_LOGGING
#define MCFE_LOG( ... ) LOG( LOG_ERR, __VA_ARGS__ )

static const char *config_state_name[CONFIG_STATE_MAX] = {
    "CONFIG_STATE_IDLE",
    "CONFIG_STATE_CONFIG_DMA_IN_PROGRESS",
    "CONFIG_STATE_CONFIG_DMA_DONE",
    "CONFIG_STATE_SCHEDULED",
    "CONFIG_STATE_ACTIVE"};

static const char *config_event_name[CONFIG_EVENT_MAX] = {
    "CONFIG_EVENT_EXTRACT_STATS",
    "CONFIG_EVENT_PREPARE",
    "CONFIG_EVENT_DMA_DONE",
    "CONFIG_EVENT_SCHEDULE",
    "CONFIG_EVENT_START",
    "CONFIG_EVENT_RESET"};

static const char *mcfe_event_name[MCFE_EVENT_MAX] = {
    "MCFE_EVENT_NEW_FRAME",
    "MCFE_EVENT_DMA_CONFIG_DONE",
    "MCFE_EVENT_DMA_METERING_DONE",
    "MCFE_EVENT_FRAME_START",
    "MCFE_EVENT_FRAME_END"};

#else
#define MCFE_LOG( ... )
#endif

#define GET_CONFIG_STR( cfg ) ( ( cfg == ISP_CONFIG_PING ) ? "PING" : "PONG" )
#define COMPL( cfg ) ( 1 - cfg )

static int32_t handle_mcfe_event( uint32_t event, uint32_t ctx_id, uint8_t cfg_id );

/* Initialize the MCFE module here */
int32_t sw_mcfe_init( acamera_firmware_t *g_fw )
{
    system_memset( &g_mcfe_hdl, 0, sizeof( g_mcfe_hdl ) );
    g_mcfe_hdl.fw = g_fw;

    int cfg_id;
    for ( cfg_id = 0; cfg_id < ISP_CONFIG_SPACE_MAX_NUM; cfg_id++ ) {
        g_mcfe_hdl.cfg[cfg_id].ctx_id = -1;
        g_mcfe_hdl.cfg[cfg_id].last_ctx_id = -1;
    }

    system_spinlock_init( &g_mcfe_hdl.context_lock );
    sw_mcfe_queue_init();

    sw_mcfe_external_driver_init( g_fw );

    return NO_ERROR;
}

/* Deinitialize the MCFE module here */
int32_t sw_mcfe_deinit()
{
    sw_mcfe_external_driver_deinit();

    sw_mcfe_queue_deinit();
    system_spinlock_destroy( g_mcfe_hdl.context_lock );

    return NO_ERROR;
}

/* Registration API for external driver to register its callback functions */
void sw_mcfe_register( notify_frame_done_func frame_done_cb, start_frame_func start_frame_cb )
{
    g_mcfe_hdl.frame_done_cb = frame_done_cb;
    g_mcfe_hdl.start_frame_cb = start_frame_cb;
}

/* Check if any context is already scheduled to be processed  */
static uint8_t is_sw_mcfe_idle( void )
{
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
    uint32_t count = g_mcfe_hdl.frames_scheduled;
    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

    MCFE_LOG( "Frames scheduled so far: %d", count );
    return ( count == 0 );
}

/* Check if any context is already prepared/preparing to be loaded into ping/pong space */
static uint8_t is_isp_config_empty( void )
{
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
    uint32_t count = g_mcfe_hdl.frames_prepared;
    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

    MCFE_LOG( "ISP configuration check, frames prepared so far: %d", count );
    return ( count == 0 );
}

// Utility function to get configuration space id which with matching current context id.
// Used for general context to configuration space mapping
static uint8_t get_config_id_curr_ctx( uint32_t ctx_id )
{
    uint8_t cfg_id;
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
    // Identify the config id corresponding to this ctx_id
    for ( cfg_id = 0; cfg_id < ISP_CONFIG_SPACE_MAX_NUM; cfg_id++ ) {
        if ( g_mcfe_hdl.cfg[cfg_id].ctx_id == ctx_id ) {
            break;
        }
    }
    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

    if ( cfg_id == ISP_CONFIG_SPACE_MAX_NUM ) {
        LOG( LOG_ERR, "Error! Context id %d is not associated with any of configuration spaces", ctx_id );
    } else {
        MCFE_LOG( "Context id: %d is assigned to: %s space", ctx_id, GET_CONFIG_STR( cfg_id ) );
    }

    return cfg_id;
}

// Utility function to get configuration space id which with matching last context id.
// Used for stats copy when configuration space is reset
static uint8_t get_config_id_last_ctx( uint32_t ctx_id )
{
    uint8_t cfg_id;
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
    // Identify the config id with last context id matching ctx_id
    for ( cfg_id = 0; cfg_id < ISP_CONFIG_SPACE_MAX_NUM; cfg_id++ ) {
        if ( g_mcfe_hdl.cfg[cfg_id].last_ctx_id == ctx_id ) {
            break;
        }
    }
    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

    if ( cfg_id == ISP_CONFIG_SPACE_MAX_NUM ) {
        LOG( LOG_ERR, "Error! Context id %d is not associated with last context id with any of configuration spaces", ctx_id );
    } else {
        MCFE_LOG( "Context id: %d is last context id of: %s space", ctx_id, GET_CONFIG_STR( cfg_id ) );
    }

    return cfg_id;
}

/* Utility function to get the frame details from ping/pong configuration space id */
static mcfe_frame_t get_context_frame( uint8_t cfg_id )
{
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
    mcfe_frame_t frame = g_mcfe_hdl.cfg[cfg_id].frame;
    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

    return frame;
}

/* Start 3A processing on the frame after copying stats */
static int32_t start_3a( uint32_t ctx_id )
{
    acamera_context_ptr_t p_ctx = (acamera_context_ptr_t)&g_mcfe_hdl.fw->fw_ctx[ctx_id];

    MCFE_LOG( "Starting 3A for the context id: %d", ctx_id );

    // new_stats event to start reading metering memory and run 3A
    acamera_fw_raise_event( p_ctx, event_id_new_stats );

    return NO_ERROR;
}

/* Callback function after context configuration is copied to ISP ping/pong space */
static void dma_complete_context_cb( void *arg, uint32_t ctx_id )
{
    MCFE_LOG( "Configuration DMA completed for context id: %d", ctx_id );

    handle_mcfe_event( MCFE_EVENT_DMA_CONFIG_DONE, ctx_id, 0 );

    if ( arg ) {
        system_cdma_unmap_sg( arg );
    }
}

/* Callback function after metering stats data is transferred from ping/pong space to software context */
static void dma_complete_metering_cb( void *arg, uint32_t ctx_id )
{
    MCFE_LOG( "Metering stats DMA completed for context id: %d", ctx_id );

    handle_mcfe_event( MCFE_EVENT_DMA_METERING_DONE, ctx_id, 0 );

    if ( arg ) {
        system_cdma_unmap_sg( arg );
    }
}

/* Initialise stats DMA copy from configuration space specified */
static int32_t trigger_stats_dma_transfer( uint8_t cfg_id, uint32_t ctx_id )
{
    MCFE_LOG( "Triggering metering stats DMA transfer for context id: %d", ctx_id );

    g_mcfe_hdl.cfg[cfg_id].metering_dma_completed = 0;

    // DMA all the metering stats memory from selected configuration space to the software context
    system_cdma_copy_sg( g_mcfe_hdl.fw->dma_chan_isp_metering, cfg_id, SYS_DMA_FROM_DEVICE, dma_complete_metering_cb, ctx_id );

    return NO_ERROR;
}

/* Initialise configuration DMA copy to configuration space specified */
static int32_t trigger_config_dma_transfer( uint8_t cfg_id )
{
    mcfe_frame_t frame;

    // Dequeue a frame from the SW MCFE queue and update the configuration space with the context configuration
    if ( sw_mcfe_dequeue( &frame ) ) {
        // In case the next context configuration is not available at the moment
        // set config_dma_completed flag to notify the 3A triggering logic not to wait for it
        g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 1;
        return NO_ERROR;
    }

    g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 0;

    MCFE_LOG( "New frame dequeued from the MCFE queue, context id: %d", frame.ctx_id );

    g_mcfe_hdl.cfg[cfg_id].ctx_id = frame.ctx_id;
    g_mcfe_hdl.cfg[cfg_id].frame = frame;
    g_mcfe_hdl.cfg[cfg_id].state = CONFIG_STATE_CONFIG_DMA_IN_PROGRESS;
    g_mcfe_hdl.frames_prepared++;

    // DMA copy context configuration to the selected configuration space
    system_cdma_copy_sg( g_mcfe_hdl.fw->dma_chan_isp_config, cfg_id, SYS_DMA_TO_DEVICE, dma_complete_context_cb, frame.ctx_id );

    MCFE_LOG( "Triggering configuration DMA transfer for context: %d, space: %s, state: %s, frames prepared: %d",
              frame.ctx_id, GET_CONFIG_STR( cfg_id ), config_state_name[g_mcfe_hdl.cfg[cfg_id].state], g_mcfe_hdl.frames_prepared );

    return NO_ERROR;
}

/* Schedule a frame to be processed by ISP */
static int32_t schedule_frame( uint8_t cfg_id )
{
    // Extract the frame from the configuration space descriptor
    mcfe_frame_t frame = g_mcfe_hdl.cfg[cfg_id].frame;

    MCFE_LOG( "Requesting frame pixel data DMA reader for context id: %d, target configuration space: %s",
              frame.ctx_id, GET_CONFIG_STR( cfg_id ) );

    // Signal external driver to send this frame to the ISP pipeline
    g_mcfe_hdl.start_frame_cb( frame.ctx_id, frame.private );
    return NO_ERROR;
}

/* Update config states moving from one state to another */
static int32_t handle_config_event( uint32_t event, uint8_t cfg_id )
{
    int ret = NO_ERROR;
    unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );

    MCFE_LOG( "Handling configuration space event %s for %s, current state: %s",
              config_event_name[event], GET_CONFIG_STR( cfg_id ), config_state_name[g_mcfe_hdl.cfg[cfg_id].state] );

    switch ( g_mcfe_hdl.cfg[cfg_id].state ) {

    case CONFIG_STATE_IDLE:
        // If stats were collected on the previously processed context then trigger a transfer
        // If we are in the CONFIG_STATE_IDLE when CONFIG_EVENT_EXTRACT_STATS is received it means
        // there is no further context configuration available
        if ( event == CONFIG_EVENT_EXTRACT_STATS ) {
            MCFE_LOG( "Checking metering stats collected status (%d) for %s space, last context id on it: %d",
                      g_mcfe_hdl.cfg[cfg_id].metering_collected, GET_CONFIG_STR( cfg_id ), g_mcfe_hdl.cfg[cfg_id].last_ctx_id );

            if ( g_mcfe_hdl.cfg[cfg_id].metering_collected && ( g_mcfe_hdl.cfg[cfg_id].last_ctx_id >= 0 ) ) {
                ret = trigger_stats_dma_transfer( cfg_id, g_mcfe_hdl.cfg[cfg_id].last_ctx_id );
                g_mcfe_hdl.cfg[cfg_id].metering_collected = 0;
            }
            // Configure the specified configuration space with the context config from SW MCFE queue
        } else if ( ( event == CONFIG_EVENT_PREPARE ) || ( event == CONFIG_EVENT_SCHEDULE ) ) {
            ret = trigger_config_dma_transfer( cfg_id );
        }
        break;
    case CONFIG_STATE_CONFIG_DMA_IN_PROGRESS:
        // If stats were collected on the previously processed context then trigger a transfer
        // If we are in the CONFIG_STATE_CONFIG_DMA_IN_PROGRESS when CONFIG_EVENT_EXTRACT_STATS is received
        // it means the configuration space is being updated with the next context configuration
        if ( event == CONFIG_EVENT_EXTRACT_STATS ) {
            MCFE_LOG( "Checking metering stats collected status (%d) for %s space, last context id on it: %d",
                      g_mcfe_hdl.cfg[cfg_id].metering_collected, GET_CONFIG_STR( cfg_id ), g_mcfe_hdl.cfg[cfg_id].last_ctx_id );

            if ( g_mcfe_hdl.cfg[cfg_id].metering_collected && ( g_mcfe_hdl.cfg[cfg_id].last_ctx_id >= 0 ) ) {
                ret = trigger_stats_dma_transfer( cfg_id, g_mcfe_hdl.cfg[cfg_id].last_ctx_id );
                g_mcfe_hdl.cfg[cfg_id].metering_collected = 0;
            }
            // Update configuration space status and configure ISP to use this configuration space for the next frame
        } else if ( event == CONFIG_EVENT_DMA_DONE ) {
            g_mcfe_hdl.cfg[cfg_id].state = CONFIG_STATE_CONFIG_DMA_DONE;
            acamera_isp_isp_global_mcu_ping_pong_config_select_write( 0, cfg_id );
        }
        break;
    case CONFIG_STATE_CONFIG_DMA_DONE:
        if ( event == CONFIG_EVENT_SCHEDULE ) {
            g_mcfe_hdl.cfg[cfg_id].state = CONFIG_STATE_SCHEDULED;
            ret = schedule_frame( cfg_id );
            g_mcfe_hdl.frames_scheduled++;
        }
        break;
    case CONFIG_STATE_SCHEDULED:
        if ( event == CONFIG_EVENT_START ) {
            g_mcfe_hdl.cfg[cfg_id].state = CONFIG_STATE_ACTIVE;
            g_mcfe_hdl.last_config_space_id = cfg_id;
        }
        break;
    case CONFIG_STATE_ACTIVE:
        // Reset the config data
        if ( event == CONFIG_EVENT_RESET ) {
            g_mcfe_hdl.cfg[cfg_id].state = CONFIG_STATE_IDLE;
            g_mcfe_hdl.cfg[cfg_id].last_ctx_id = g_mcfe_hdl.cfg[cfg_id].ctx_id;
            g_mcfe_hdl.cfg[cfg_id].ctx_id = -1;

            system_memset( &( g_mcfe_hdl.cfg[cfg_id].frame ), 0, sizeof( mcfe_frame_t ) );

            // Set metering collected flag. Stats will be processed in the next frame start interrupt
            g_mcfe_hdl.cfg[cfg_id].metering_collected = 1;
            g_mcfe_hdl.cfg[cfg_id].metering_dma_completed = 0;
            g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 0;

            g_mcfe_hdl.frames_prepared--;
            g_mcfe_hdl.frames_scheduled--;
        }
        break;
    default:
        break;
    }

    MCFE_LOG( "Configuration space event %s for %s, handled. New state is: %s",
              config_event_name[event], GET_CONFIG_STR( cfg_id ), config_state_name[g_mcfe_hdl.cfg[cfg_id].state] );

    system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );
    return ret;
}

/* Frame end event */
static int32_t handle_frame_end_event( uint8_t cfg_id )
{
    int32_t ret = NO_ERROR;

    // Extract the frame from the config
    mcfe_frame_t frame = get_context_frame( cfg_id );

    MCFE_LOG( "Frame end event for configuration space: %s, context id: %d, calling frame done callback",
              GET_CONFIG_STR( cfg_id ), frame.ctx_id );

    acamera_context_ptr_t p_ctx = (acamera_context_ptr_t)&g_mcfe_hdl.fw->fw_ctx[frame.ctx_id];
    acamera_fw_raise_event( p_ctx, event_id_end_frame );

    // Notify external driver that ISP has done processing current frame
    g_mcfe_hdl.frame_done_cb( frame.ctx_id, frame.private );

    // Active context - reset config state and data.
    // Passive context - schedule next frame
    MCFE_LOG( "Sending events to reset %s configuration space and schedule %s",
              GET_CONFIG_STR( cfg_id ), GET_CONFIG_STR( COMPL( cfg_id ) ) );
    handle_config_event( CONFIG_EVENT_RESET, cfg_id );
    handle_config_event( CONFIG_EVENT_SCHEDULE, COMPL( cfg_id ) );

    return ret;
}

/* Frame start event */
static int32_t handle_frame_start_event( uint8_t cfg_id )
{
    int32_t ret = NO_ERROR;
    mcfe_frame_t frame = get_context_frame( cfg_id );

    acamera_context_ptr_t p_ctx = (acamera_context_ptr_t)&g_mcfe_hdl.fw->fw_ctx[frame.ctx_id];
    acamera_fw_raise_event( p_ctx, event_id_new_frame );

    // Active context - state transition to active.
    // Passive context - extract any previous stats and prepare next frame
    MCFE_LOG( "Sending events to mark %s configuration space as started and get metering stats/prepare for %s",
              GET_CONFIG_STR( cfg_id ), GET_CONFIG_STR( COMPL( cfg_id ) ) );
    handle_config_event( CONFIG_EVENT_START, cfg_id );
    handle_config_event( CONFIG_EVENT_EXTRACT_STATS, COMPL( cfg_id ) );
    handle_config_event( CONFIG_EVENT_PREPARE, COMPL( cfg_id ) );

    return ret;
}

/* Handle configuration DMA done event */
static int32_t handle_config_dma_done_event( uint32_t ctx_id )
{
    int32_t ret = NO_ERROR;
    uint8_t cfg_id = get_config_id_curr_ctx( ctx_id );

    MCFE_LOG( "Configuration DMA done event handling for context id: %d, space: %s, triggering CONFIG_EVENT_DMA_DONE event",
              ctx_id, GET_CONFIG_STR( cfg_id ) );

    if ( cfg_id < ISP_CONFIG_SPACE_MAX_NUM ) {

        // Check if configuration DMA is complete and we are safe to start 3A
        unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
        uint8_t trigger_3a = 0;
        if ( g_mcfe_hdl.cfg[cfg_id].metering_dma_completed ) {
            trigger_3a = 1;
            g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 0;
            g_mcfe_hdl.cfg[cfg_id].metering_dma_completed = 0;
        } else {
            g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 1;
        }
        system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

        if ( trigger_3a ) {
            ret = start_3a( ctx_id );
        }

        if ( ret == NO_ERROR ) {
            ret = handle_config_event( CONFIG_EVENT_DMA_DONE, cfg_id );
        }

        MCFE_LOG( "Check if MCFE is idle and we can schedule this configuration space: %s",
                  ( is_sw_mcfe_idle() ? "yes" : "no" ) );

        // If ISP is idle, schedule this frame now
        if ( ( ret == NO_ERROR ) && is_sw_mcfe_idle() ) {
            MCFE_LOG( "Triggering event CONFIG_EVENT_SCHEDULE for context id: %d, space: %s",
                      ctx_id, GET_CONFIG_STR( cfg_id ) );
            ret = handle_config_event( CONFIG_EVENT_SCHEDULE, cfg_id );
        }
    } else {
        ret = -1;
    }

    return ret;
}

/* Handle metering stats DMA done event */
static int32_t handle_metering_dma_done_event( uint32_t ctx_id )
{
    int32_t ret = NO_ERROR;
    uint8_t cfg_id = get_config_id_last_ctx( ctx_id );

    MCFE_LOG( "Metering stats DMA done event handling for context id: %d, space: %s",
              ctx_id, GET_CONFIG_STR( cfg_id ) );

    if ( cfg_id < ISP_CONFIG_SPACE_MAX_NUM ) {

        // Check if configuration DMA is complete and we are safe to start 3A
        unsigned long flags = system_spinlock_lock( g_mcfe_hdl.context_lock );
        uint8_t trigger_3a = 0;
        if ( g_mcfe_hdl.cfg[cfg_id].config_dma_completed ) {
            trigger_3a = 1;
            g_mcfe_hdl.cfg[cfg_id].config_dma_completed = 0;
            g_mcfe_hdl.cfg[cfg_id].metering_dma_completed = 0;
        } else {
            g_mcfe_hdl.cfg[cfg_id].metering_dma_completed = 1;
        }

        // Reset last context ID to handle cases when SW MCFE runs only one context
        g_mcfe_hdl.cfg[cfg_id].last_ctx_id = -1;
        system_spinlock_unlock( g_mcfe_hdl.context_lock, flags );

        if ( trigger_3a ) {
            ret = start_3a( ctx_id );
        }

    } else {
        ret = -1;
    }

    return ret;
}

/* MCFE main event handler */
static int32_t handle_mcfe_event( uint32_t event, uint32_t ctx_id, uint8_t cfg_id )
{
    int32_t ret = NO_ERROR;

    // Check event type for proper log message, depending on type ctx_id/cfg_id might not be relevant
    if ( ( event == MCFE_EVENT_FRAME_START ) || ( event == MCFE_EVENT_FRAME_END ) ) {
        MCFE_LOG( "Handling MCFE event %s, configuration space: %s", mcfe_event_name[event], GET_CONFIG_STR( cfg_id ) );
    } else {
        MCFE_LOG( "Handling MCFE event %s, context id: %d", mcfe_event_name[event], ctx_id );
    }

    switch ( event ) {
    case MCFE_EVENT_NEW_FRAME:
        // Select complement to the last active configuration space to create alternating pattern
        // Helps to follow the same ping/pong swap strategy under low load so new context doesn't get into the same
        // configuration space all the time
        cfg_id = COMPL( g_mcfe_hdl.last_config_space_id );
        MCFE_LOG( "New frame configuration for context id: %d will be allocated on %s space", ctx_id, GET_CONFIG_STR( cfg_id ) );
        ret = handle_config_event( CONFIG_EVENT_PREPARE, cfg_id );
        break;
    case MCFE_EVENT_DMA_CONFIG_DONE:
        ret = handle_config_dma_done_event( ctx_id );
        break;
    case MCFE_EVENT_DMA_METERING_DONE:
        ret = handle_metering_dma_done_event( ctx_id );
        break;
    case MCFE_EVENT_FRAME_START:
        ret = handle_frame_start_event( cfg_id );
        break;
    case MCFE_EVENT_FRAME_END:
        ret = handle_frame_end_event( cfg_id );
        break;
    }
    return ret;
}

/* Interrupt handler to handle ISP FS/FE interrupts */
int32_t sw_mcfe_handle_interrupt( uint32_t irq_event )
{
    int32_t result = NO_ERROR;
    uint32_t event_id = MCFE_EVENT_MAX;
    uint8_t cfg_id = acamera_isp_isp_global_ping_pong_config_select_read( 0 );

    if ( irq_event == ISP_INTERRUPT_EVENT_ISP_START_FRAME_START ) {
        event_id = MCFE_EVENT_FRAME_START;
    } else if ( irq_event == ISP_INTERRUPT_EVENT_ISP_END_FRAME_END ) {
        event_id = MCFE_EVENT_FRAME_END;
    }

    // Send the FS/FE event to MCFE
    if ( event_id != MCFE_EVENT_MAX ) {
        result = handle_mcfe_event( event_id, 0, cfg_id );
    }

    return result;
}

/* Notification callback to MCFE that a new frame is available to schedule */
int32_t sw_mcfe_notify_frame( uint32_t ctx_id, uint32_t ctx_type, void *pvt_data )
{
    int32_t ret = NO_ERROR;

    // Enqueue the new frame to MCFE queue
    mcfe_frame_t new_frame = {ctx_id, ctx_type, pvt_data};
    ret = sw_mcfe_enqueue( &new_frame );

    MCFE_LOG( "New frame enqueued for context id: %d, is_isp_config_empty: %d, triggering EVENT_NEW_FRAME",
              ctx_id, is_isp_config_empty() );

    // Check if this new frame can be prepared immediately ( if ISP is idle )
    if ( ( ret == NO_ERROR ) && is_isp_config_empty() ) {
        ret = handle_mcfe_event( MCFE_EVENT_NEW_FRAME, ctx_id, 0 );
    }

    return ret;
}
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
#if ACAMERA_ISP_PROFILING
#include "system_profiler.h"
#include "acamera_profiler.h"
#endif
#include "acamera_logger.h"
#include "system_semaphore.h"

extern fsm_common_t *sensor_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *cmos_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *general_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *AE_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *AWB_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *AF_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *color_matrix_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *purple_fringe_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *iridix_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *noise_reduction_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *crop_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *sharpening_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *matrix_yuv_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *gamma_acamera_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *dma_writer_get_fsm_common( uint8_t ctx_id );
extern fsm_common_t *monitor_get_fsm_common( uint8_t ctx_id );

void acamera_fsm_mgr_init( acamera_fsm_mgr_t *p_fsm_mgr )
{
    uint8_t idx;
    fsm_init_param_t init_param;

    FUN_PTR_GET_FSM_COMMON fun_ptr_arr[] = {
        sensor_get_fsm_common,
        cmos_get_fsm_common,
        general_get_fsm_common,
        AE_get_fsm_common,
        AWB_get_fsm_common,
        AF_get_fsm_common,
        color_matrix_get_fsm_common,
        purple_fringe_get_fsm_common,
        iridix_get_fsm_common,
        noise_reduction_get_fsm_common,
        crop_get_fsm_common,
        sharpening_get_fsm_common,
        matrix_yuv_get_fsm_common,
        gamma_acamera_get_fsm_common,
        dma_writer_get_fsm_common,
        monitor_get_fsm_common,
    };

    for ( idx = 0; idx < FSM_ID_MAX; idx++ ) {
        p_fsm_mgr->fsm_arr[idx] = fun_ptr_arr[idx]( p_fsm_mgr->ctx_id );
    }

    if ( number_of_event_ids > 256 ) {
        LOG( LOG_CRIT, "Too much events in the system. Will not work correctly!" );
    }

    acamera_event_queue_init( &( p_fsm_mgr->event_queue ), p_fsm_mgr->event_queue_data, ACAMERA_EVENT_QUEUE_SIZE );

    init_param.p_fsm_mgr = p_fsm_mgr;
    init_param.isp_base = p_fsm_mgr->isp_base;
    for ( idx = 0; idx < FSM_ID_MAX; idx++ ) {
        p_fsm_mgr->fsm_arr[idx]->ops.init( p_fsm_mgr->fsm_arr[idx]->p_fsm, &init_param );
    }

    /* We can reload_isp_calibratons after all FSMs initialized. */
    acamera_fsm_mgr_set_param( p_fsm_mgr, FSM_PARAM_SET_RELOAD_CALIBRATION, NULL, 0 );
}

void acamera_fsm_mgr_deinit( acamera_fsm_mgr_t *p_fsm_mgr )
{
    uint8_t idx;

    for ( idx = 0; idx < FSM_ID_MAX; idx++ ) {
        if ( p_fsm_mgr->fsm_arr[idx]->ops.deinit ) {
            p_fsm_mgr->fsm_arr[idx]->ops.deinit( p_fsm_mgr->fsm_arr[idx]->p_fsm );
        }
    }

    acamera_event_queue_deinit( &( p_fsm_mgr->event_queue ) );
}

void acamera_fsm_mgr_process_interrupt( acamera_fsm_mgr_t *p_fsm_mgr, uint8_t irq_event )
{
    uint8_t idx;

    for ( idx = 0; idx < FSM_ID_MAX; idx++ ) {
        if ( p_fsm_mgr->fsm_arr[idx]->ops.proc_interrupt ) {
#if ACAMERA_ISP_PROFILING
            acamera_profiler_start( idx + 1 );
#endif
            p_fsm_mgr->fsm_arr[idx]->ops.proc_interrupt( p_fsm_mgr->fsm_arr[idx]->p_fsm, irq_event );
#if ACAMERA_ISP_PROFILING
            acamera_profiler_stop( idx + 1, 0 );
#endif
        }
    }
}

static const char *const event_name[] = {
    "event_id_acamera_reset_sensor_hw",
    "event_id_ae_stats_ready",
    "event_id_af_converged",
    "event_id_af_fast_search_finished",
    "event_id_af_refocus",
    "event_id_af_stats_ready",
    "event_id_antiflicker_changed",
    "event_id_awb_stats_ready",
    "event_id_cmos_refresh",
    "event_id_crop_changed",
    "event_id_crop_updated",
    "event_id_end_frame",
    "event_id_exposure_changed",
    "event_id_frame_buf_reinit",
    "event_id_frame_buffer_ds_ready",
    "event_id_frame_buffer_fr_ready",
    "event_id_frame_buffer_metadata",
    "event_id_frame_end",
    "event_id_gamma_stats_ready",
    "event_id_monitor_frame_end",
    "event_id_monitor_notify_other_fsm",
    "event_id_new_frame",
    "event_id_new_stats",
    "event_id_sensor_not_ready",
    "event_id_sensor_ready",
    "event_id_sensor_sw_reset",
    "event_id_sharp_lut_update",
    "event_id_update_iridix",
    "event_id_update_sharp_lut",
    "unknown"
};

void acamera_fsm_mgr_process_events( acamera_fsm_mgr_t *p_fsm_mgr, int n_max_events )
{
    int n_event = 0;

    for ( ;; ) {
        acamera_isp_interrupts_disable( p_fsm_mgr );
        int event = acamera_event_queue_pop( &( p_fsm_mgr->event_queue ) );
        acamera_isp_interrupts_enable( p_fsm_mgr );
        if ( event < 0 ) {
            break;
        } else {
            event_id_t event_id = (event_id_t)( event );
            uint8_t b_event_processed = 0, b_processed;
            uint8_t idx;
            LOG( LOG_DEBUG, "Processing event: %d %s.", event_id, event_name[event_id] );

            for ( idx = 0; idx < FSM_ID_MAX; idx++ ) {
                if ( p_fsm_mgr->fsm_arr[idx]->ops.proc_event ) {
#if ACAMERA_ISP_PROFILING
                    acamera_profiler_start( idx + 1 );
#endif
                    b_processed = p_fsm_mgr->fsm_arr[idx]->ops.proc_event( p_fsm_mgr->fsm_arr[idx]->p_fsm, event_id );
                    b_event_processed |= b_processed;
#if ACAMERA_ISP_PROFILING
                    acamera_profiler_stop( idx + 1, b_processed );
#endif
                }
            }

            if ( b_event_processed ) {
                ++n_event;
                if ( ( n_max_events > 0 ) && ( n_event >= n_max_events ) ) {
                    break;
                }
            }
        }
    }
}



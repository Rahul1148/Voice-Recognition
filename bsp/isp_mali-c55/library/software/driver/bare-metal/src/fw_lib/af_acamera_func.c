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
#include "acamera_metering_stats_mem_config.h"
#include "acamera_math.h"
#include "acamera_lens_api.h"
#include "system_stdlib.h"
#include "af_acamera_fsm.h"

//================================================================================
//#define TRACE
//#define TRACE_IQ
//#define TRACE_SCENE_CHANGE
//================================================================================

#if defined( ISP_METERING_OFFSET_AF )
#define ISP_METERING_OFFSET_AUTO_FOCUS ISP_METERING_OFFSET_AF
#else
#error "The AF metering offset is not defined in acamera_metering_mem_config.h"
#endif

#if FW_ALG_SUPPORT_SHARED_LIB
#include <dlfcn.h>
#endif

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_AF_ACAMERA
#endif

static __inline void af_acamera_stats_mem_array_data_read( af_acamera_fsm_const_ptr_t p_fsm, uint32_t index_inp, uint32_t *stats )
{
#if ISP_HW_IS_MALI_C32_C52
    stats[0] = acamera_metering_stats_mem_array_data_read( p_fsm->cmn.isp_base, ISP_METERING_OFFSET_AUTO_FOCUS + ( ( index_inp ) << 1 ) + 0 );
    stats[1] = acamera_metering_stats_mem_array_data_read( p_fsm->cmn.isp_base, ISP_METERING_OFFSET_AUTO_FOCUS + ( ( index_inp ) << 1 ) + 1 );
#else
    stats[0] = acamera_metering_stats_mem_array_data_read( p_fsm->cmn.isp_base, ISP_METERING_OFFSET_AUTO_FOCUS + index_inp );
#endif
}

void af_acamera_config_input_roi( af_acamera_fsm_ptr_t p_fsm )
{
#if !ISP_HW_IS_MALI_C32_C52
    af_acamera_input_roi_param_t *param = (af_acamera_input_roi_param_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_INPUT_ROI );

    if ( param ) {
        fsm_param_sensor_info_t sensor_info;
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );

        if ( ( ( param->af_input_roi_right_border + param->af_input_roi_left_border ) >= sensor_info.active_width ) ||
             ( ( param->af_input_roi_top_border + param->af_input_roi_bottom_border ) >= sensor_info.active_height ) ) {

            LOG( LOG_ERR, "Incorrect AF input ROI border configuration (left: %d, right: %d, top: %d, bottom: %d) for %dx%d input resolution.",
                 param->af_input_roi_left_border,
                 param->af_input_roi_right_border,
                 param->af_input_roi_top_border,
                 param->af_input_roi_bottom_border,
                 sensor_info.active_width,
                 sensor_info.active_height );
        } else {
            const uint16_t af_roi_horiz_end = sensor_info.active_width - ( param->af_input_roi_right_border + 1 );
            const uint16_t af_roi_vert_end = sensor_info.active_height - ( param->af_input_roi_bottom_border + 1 );

            acamera_isp_metering_af_roi_horiz_start_write( p_fsm->cmn.isp_base, param->af_input_roi_left_border );
            acamera_isp_metering_af_roi_horiz_end_write( p_fsm->cmn.isp_base, af_roi_horiz_end );
            acamera_isp_metering_af_roi_vert_start_write( p_fsm->cmn.isp_base, param->af_input_roi_top_border );
            acamera_isp_metering_af_roi_vert_end_write( p_fsm->cmn.isp_base, af_roi_vert_end );
        }
    }
#endif
}

static void af_acamera_read_stats_data( af_acamera_fsm_ptr_t p_fsm )
{
    uint8_t x, y;
    uint32_t( *stats )[AF_STATS_NUM_ROWS];

    p_fsm->zones_horiz = acamera_isp_metering_af_nodes_used_horiz_read( p_fsm->cmn.isp_base );
    p_fsm->zones_vert = acamera_isp_metering_af_nodes_used_vert_read( p_fsm->cmn.isp_base );
    stats = p_fsm->zone_raw_statistic;

    if ( !p_fsm->zones_horiz || !p_fsm->zones_vert ) {
        p_fsm->zones_horiz = ISP_DEFAULT_AF_ZONES_HOR;
        p_fsm->zones_vert = ISP_DEFAULT_AF_ZONES_VERT;
    }

    for ( y = 0; y < p_fsm->zones_vert; y++ ) {
        uint32_t inx = (uint32_t)y * p_fsm->zones_horiz;
        for ( x = 0; x < p_fsm->zones_horiz; x++ ) {
            uint32_t full_inx = inx + x;
            af_acamera_stats_mem_array_data_read( p_fsm, full_inx, stats[full_inx] );
        }
    }
}

//================================================================================
void af_acamera_fsm_process_interrupt( af_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event )
{
    if ( acamera_fsm_util_is_irq_event_ignored( (fsm_irq_mask_t *)( &p_fsm->mask ), irq_event ) )
        return;

    //check if lens was initialised properly
    if ( p_fsm->lens_driver_ok == 0 )
        return;

    switch ( irq_event ) {
    case ACAMERA_IRQ_AF2_STATS:
        af_acamera_read_stats_data( (af_acamera_fsm_ptr_t)p_fsm );
        fsm_raise_event( p_fsm, event_id_af_stats_ready );
        break;
    }
}
//================================================================================
void af_acamera_init( af_acamera_fsm_ptr_t p_fsm )
{
    af_lms_param_t *param = NULL;
    //check if lens was initialised properly
    if ( !p_fsm->lens_driver_ok ) {
#if USER_MODULE
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_KLENS_STATUS, NULL, 0, &p_fsm->lens_driver_ok, sizeof( p_fsm->lens_driver_ok ) );
        if ( p_fsm->lens_driver_ok ) {
            param = (af_lms_param_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS );
            acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_KLENS_PARAM, NULL, 0, &p_fsm->lens_param, sizeof( p_fsm->lens_param ) );
        }
#else
        p_fsm->lens_ctx = NULL;

        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->settings.lens_init != NULL ) {
            int32_t result = 0;
            result = ACAMERA_FSM2CTX_PTR( p_fsm )->settings.lens_init( &p_fsm->lens_ctx, &p_fsm->lens_ctrl );
            if ( result != -1 && p_fsm->lens_ctx != NULL ) {
                const lens_param_t *p_lens_param = p_fsm->lens_ctrl.get_parameters( p_fsm->lens_ctx );
                p_fsm->lens_param = *p_lens_param;
                //only on lens init success populate param
                param = (af_lms_param_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS );
                p_fsm->lens_driver_ok = 1;
            } else {
                p_fsm->lens_driver_ok = 0;
            }
        } else {
            p_fsm->lens_driver_ok = 0;
        }
#endif
    }

    if ( param ) {
        p_fsm->pos_min = param->pos_min;
        p_fsm->pos_max = param->pos_max;

        p_fsm->mask.repeat_irq_mask = ACAMERA_IRQ_MASK( ACAMERA_IRQ_AF2_STATS );
        af_acamera_request_interrupt( p_fsm, p_fsm->mask.repeat_irq_mask );

#if FW_ALG_SUPPORT_SHARED_LIB

        p_fsm->lib_handle = dlopen( "custom_alg.so", RTLD_LAZY );
        LOG( LOG_INFO, "AF: try to open custom_alg library, return: %p.", p_fsm->lib_handle );
        if ( !p_fsm->lib_handle ) {
            p_fsm->lib_handle = dlopen( "./libacamera_alg_core.so", RTLD_LAZY );
            LOG( LOG_INFO, "AF: try to open acamera_alg_core library, return: %p.", p_fsm->lib_handle );
        }

        if ( p_fsm->lib_handle ) {
            p_fsm->af_alg_obj.init = dlsym( p_fsm->lib_handle, "af_acamera_core_init" );
            p_fsm->af_alg_obj.deinit = dlsym( p_fsm->lib_handle, "af_acamera_core_deinit" );
            p_fsm->af_alg_obj.proc = dlsym( p_fsm->lib_handle, "af_acamera_core_proc" );
            LOG( LOG_INFO, "AF: init: %p, deinit: %p, proc: %p .", p_fsm->af_alg_obj.init, p_fsm->af_alg_obj.deinit, p_fsm->af_alg_obj.proc );
        } else {
            LOG( LOG_ERR, "Load failed, error: %s.", dlerror() );
        }

#else
        p_fsm->af_alg_obj.init = af_acamera_core_init;
        p_fsm->af_alg_obj.deinit = af_acamera_core_deinit;
        p_fsm->af_alg_obj.proc = af_acamera_core_proc;
#endif

        if ( p_fsm->af_alg_obj.init ) {
            p_fsm->af_alg_obj.af_ctx = p_fsm->af_alg_obj.init( p_fsm->cmn.ctx_id );
            LOG( LOG_INFO, "Init AF core, ret: %p.", p_fsm->af_alg_obj.af_ctx );
        }
    }
}


void af_acamera_update( af_acamera_fsm_ptr_t p_fsm )
{
#if USER_MODULE
    p_fsm->last_position = p_fsm->new_lens_pos;
    p_fsm->last_sharp_done = p_fsm->new_sharp_val;

#else
    const lens_param_t *lens_param = p_fsm->lens_ctrl.get_parameters( p_fsm->lens_ctx );
    af_lms_param_t *param = (af_lms_param_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS );

    LOG( LOG_INFO, "last position: %d, new_lens_pos: %d.", p_fsm->last_position, p_fsm->new_lens_pos );

    /* the new AF position is updated in sbuf FSM */
    if ( p_fsm->last_position != p_fsm->new_lens_pos ) {
        int fw_id = p_fsm->cmn.ctx_id;

        p_fsm->lens_ctrl.move( p_fsm->lens_ctx, p_fsm->new_lens_pos );
        LOG( LOG_INFO, "ctx: %d, new af applied, position: %u, last_position: %u.", fw_id, p_fsm->new_lens_pos, p_fsm->last_position );

        if ( param->print_debug )
            LOG( LOG_NOTICE, "ctx: %d, new af applied, position: %u, last_position: %u.", fw_id, p_fsm->new_lens_pos, p_fsm->last_position );

        /* update the done position and sharpness when sharpness value changed */
        if ( ( p_fsm->last_sharp_done != p_fsm->new_sharp_val ) && ( p_fsm->new_sharp_val != 0 ) ) {
            // p_fsm->last_pos_done = p_fsm->last_position;
            p_fsm->last_sharp_done = p_fsm->new_sharp_val;

            if ( AF_MODE_CALIBRATION == p_fsm->mode && param->print_debug )
                LOG( LOG_NOTICE, "new af calibration, pos: %u, sharp: %d.", p_fsm->last_position / lens_param->min_step, p_fsm->last_sharp_done );
        }

        p_fsm->last_position = p_fsm->new_lens_pos;

        status_info_param_t *p_status_info = (status_info_param_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STATUS_INFO );
        p_status_info->af_info.lens_pos = p_fsm->last_position;
        p_status_info->af_info.focus_value = p_fsm->last_sharp_done;
    } else {
        LOG( LOG_INFO, "last position(%u) not changed.", p_fsm->last_position );
    }
#endif
}


static void af_acamera_prepare_input( af_acamera_fsm_ptr_t p_fsm, af_custom_input_t *custom_input, af_acamera_input_t *acamera_input )
{
    system_memset( custom_input, 0, sizeof( *custom_input ) );
    system_memset( acamera_input, 0, sizeof( *acamera_input ) );

    // acamera_input
    int16_t accel_angle = 0;

#if defined( FSM_PARAM_GET_ACCEL_DATA )
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_ACCEL_DATA, NULL, 0, &accel_angle, sizeof( accel_angle ) );
#endif
    acamera_input->misc_info.accel_angle = accel_angle;
    acamera_input->misc_info.lens_min_step = p_fsm->lens_param.min_step;

#if !ISP_HW_IS_MALI_C32_C52
    int32_t total_gain = 0;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );
    acamera_input->misc_info.total_gain = total_gain;
#endif

    acamera_input->af_info.refocus_required = p_fsm->refocus_required;

#if USER_MODULE
    // Decrease of skip_frames is controlled by skip_cur_frame set on kernel side (delivered via SBUF)
    // Lens moving status is irrelevant here
    acamera_input->af_info.skip_cur_frame = p_fsm->skip_cur_frame;
    acamera_input->af_info.is_lens_moving = 0;
#else
    // Decrease of skip_frames is always allowed
    acamera_input->af_info.skip_cur_frame = 1;
    acamera_input->af_info.is_lens_moving = ( ( p_fsm->lens_driver_ok ) &&
                                              ( p_fsm->lens_ctrl.is_moving != NULL ) &&
                                              ( p_fsm->lens_ctrl.is_moving( p_fsm->lens_ctx ) ) );
#endif

    // reset to 0 after passed to core algorithm
    p_fsm->refocus_required = 0;
    acamera_input->af_info.roi = p_fsm->roi;
    acamera_input->af_info.af_mode = p_fsm->mode;
    acamera_input->af_info.zones_horiz = p_fsm->zones_horiz;
    acamera_input->af_info.zones_vert = p_fsm->zones_vert;
    acamera_input->af_info.af_pos_manual = p_fsm->pos_manual;

    acamera_input->cali_data.af_param = (af_lms_param_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS );
    acamera_input->cali_data.af_zone_whgh_h = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_ZONE_WGHT_HOR );
    acamera_input->cali_data.af_zone_whgh_h_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_ZONE_WGHT_HOR );
    acamera_input->cali_data.af_zone_whgh_v = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_ZONE_WGHT_VER );
    acamera_input->cali_data.af_zone_whgh_v_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_ZONE_WGHT_VER );
#if !ISP_HW_IS_MALI_C32_C52
    acamera_input->cali_data.af_calib_exit_thresh = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS_EXIT_THRESHOLD );
    acamera_input->cali_data.af_calib_exit_thresh_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AF_LMS_EXIT_THRESHOLD );
#endif
}

void af_acamera_process_stats( af_acamera_fsm_ptr_t p_fsm )
{
    if ( !p_fsm->af_alg_obj.proc ) {
        LOG( LOG_ERR, "AF: can't process stats since function is NULL." );
        return;
    }

    af_stats_data_t stats;
    stats.zones_stats = (uint32_t *)p_fsm->zone_raw_statistic;
    stats.zones_size = array_size( p_fsm->zone_raw_statistic );

    af_acamera_input_t acamera_af_input;
    af_custom_input_t custom_af_input;
    af_input_data_t af_input;

    af_acamera_prepare_input( p_fsm, &custom_af_input, &acamera_af_input );
    af_input.custom_input = &custom_af_input;
    af_input.acamera_input = &acamera_af_input;

    af_output_data_t af_output;
    af_acamera_output_t acamera_af_output;
    system_memset( &acamera_af_output, 0, sizeof( acamera_af_output ) );
    af_output.acamera_output = &acamera_af_output;
    af_output.custom_output = NULL;

    // call the core algorithm to calculate new lens position and state
    if ( p_fsm->af_alg_obj.proc( p_fsm->af_alg_obj.af_ctx, &stats, &af_input, &af_output ) != 0 ) {
        LOG( LOG_ERR, "AE algorithm process failed." );
        return;
    }

    p_fsm->new_lens_pos = acamera_af_output.af_lens_pos;
    p_fsm->new_sharp_val = acamera_af_output.af_sharp_val;
    p_fsm->skip_frames = acamera_af_output.af_skip_frames;
    p_fsm->state = acamera_af_output.state;
    p_fsm->caf_state = acamera_af_output.caf_state;

    LOG( LOG_DEBUG, "mode: %d, new_lens_pos: %d, new_sharp_val: %d.", p_fsm->mode, p_fsm->new_lens_pos, p_fsm->new_sharp_val );
}

void af_acamera_deinit( af_acamera_fsm_ptr_t p_fsm )
{
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->settings.lens_deinit )
        ACAMERA_FSM2CTX_PTR( p_fsm )
            ->settings.lens_deinit( p_fsm->lens_ctx );
}

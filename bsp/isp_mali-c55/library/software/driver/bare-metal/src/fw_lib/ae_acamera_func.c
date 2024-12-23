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

#include "acamera_firmware_api.h"
#include "acamera_fw.h"

#include "acamera_aexp_hist_stats_mem_config.h"
#include "acamera_metering_stats_mem_config.h"

#include "ae_acamera_fsm.h"
#include "cmos_fsm.h"
#include "ae_acamera_core.h"

#if FW_ALG_SUPPORT_SHARED_LIB
#include <dlfcn.h>
#endif

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_AE_ACAMERA
#endif

void ae_roi_update( ae_acamera_fsm_ptr_t p_fsm )
{
    uint16_t horz_zones = acamera_isp_metering_hist_aexp_nodes_used_horiz_read( p_fsm->cmn.isp_base );
    uint16_t vert_zones = acamera_isp_metering_hist_aexp_nodes_used_vert_read( p_fsm->cmn.isp_base );
    uint16_t x, y;

    uint8_t x_start = ( uint8_t )( ( ( ( p_fsm->roi >> 24 ) & 0xFF ) * horz_zones + 128 ) >> 8 );
    uint8_t x_end = ( uint8_t )( ( ( ( p_fsm->roi >> 8 ) & 0xFF ) * horz_zones + 128 ) >> 8 );
    uint8_t y_start = ( uint8_t )( ( ( ( p_fsm->roi >> 16 ) & 0xFF ) * vert_zones + 128 ) >> 8 );
    uint8_t y_end = ( uint8_t )( ( ( ( p_fsm->roi >> 0 ) & 0xFF ) * vert_zones + 128 ) >> 8 );
    uint8_t ae_weight;

    for ( y = 0; y < vert_zones; y++ ) {
        for ( x = 0; x < horz_zones; x++ ) {

            if ( y >= y_start && y <= y_end &&
                 x >= x_start && x <= x_end ) {

                if ( ( x == x_end && x_start != x_end ) ||
                     ( y == y_end && y_start != y_end ) ) {
                    ae_weight = 0;
                } else {
                    ae_weight = 15;
                }

            } else {
                ae_weight = 0;
            }

            acamera_isp_metering_hist_aexp_zones_weight_write( p_fsm->cmn.isp_base, ISP_METERING_ZONES_MAX_H * y + x, ae_weight );
        }
    }
}


void ae_acamera_read_full_histogram_data( ae_acamera_fsm_ptr_t p_fsm )
{
    int i;
    uint32_t sum = 0;
    fsm_param_mon_alg_flow_t ae_flow;

    ae_flow.frame_id_tracking = acamera_fsm_util_get_cur_frame_id( &p_fsm->cmn );
    p_fsm->cur_using_stats_frame_id = ae_flow.frame_id_tracking;

#if ISP_HW_IS_MALI_C32_C52
    // Each 32-bit register contains one 16-bit histogram bin in 4.12 format
    for ( i = 0; i < ISP_FULL_HISTOGRAM_SIZE; ++i ) {
        uint32_t v = acamera_aexp_hist_stats_mem_array_data_read( p_fsm->cmn.isp_base, i );

        const uint32_t shift = ( v >> 12 ) & 0xF;
        v = v & 0xFFF;
        if ( shift ) {
            v = ( v | 0x1000 ) << ( shift - 1 );
        }
        p_fsm->fullhist[i] = v;
        sum += v;
    }
#else
    // Each 32-bit register contains two 16-bit histogram bins in 4.12 format
    for ( i = 0; i < ISP_FULL_HISTOGRAM_SIZE / 2; ++i ) {
        const uint32_t v = acamera_aexp_hist_stats_mem_array_data_read( p_fsm->cmn.isp_base, i );

        uint32_t v0 = v & 0xFFFF; // Histogram bin N
        uint32_t v1 = v >> 16;    // Histogram bin N+1

        uint32_t shift = ( v0 >> 12 ) & 0xF;
        v0 = v0 & 0xFFF;
        if ( shift ) {
            v0 = ( v0 | 0x1000 ) << ( shift - 1 );
        }
        p_fsm->fullhist[i * 2] = v0;
        sum += v0;

        shift = ( v1 >> 12 ) & 0xF;
        v1 = v1 & 0xFFF;
        if ( shift ) {
            v1 = ( v1 | 0x1000 ) << ( shift - 1 );
        }
        p_fsm->fullhist[( i * 2 ) + 1] = v1;
        sum += v1;
    }
#endif
    p_fsm->fullhist_sum = sum;

    ae_flow.frame_id_current = acamera_fsm_util_get_cur_frame_id( &p_fsm->cmn );
    ae_flow.flow_state = MON_ALG_FLOW_STATE_INPUT_READY;
    acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_MON_AE_FLOW, &ae_flow, sizeof( ae_flow ) );
    LOG( LOG_INFO, "AE flow: INPUT_READY: frame_id_tracking: %d, cur frame_id: %u.", ae_flow.frame_id_tracking, ae_flow.frame_id_current );

    int j;
    for ( i = 0; i < ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_DEFAULT; i++ ) {
        for ( j = 0; j < ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DEFAULT; j++ ) {
            p_fsm->hist4[i * ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DEFAULT + j] = ( uint16_t )( acamera_metering_stats_mem_array_data_read( p_fsm->cmn.isp_base, ( i * ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DEFAULT + j ) * 2 + 1 ) >> 16 );
        }
    }
}

void ae_acamera_fsm_process_interrupt( ae_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event )
{
    if ( acamera_fsm_util_is_irq_event_ignored( (fsm_irq_mask_t *)( &p_fsm->mask ), irq_event ) )
        return;

    switch ( irq_event ) {
    case ACAMERA_IRQ_AE_STATS:
        ae_acamera_read_full_histogram_data( (ae_acamera_fsm_ptr_t)p_fsm );
        fsm_raise_event( p_fsm, event_id_ae_stats_ready );
        break;
    }
}

static inline uint32_t full_ratio_to_adjaced( int32_t sensor_exp_number, uint32_t ratio )
{
    switch ( sensor_exp_number ) {
    case 4:
        return acamera_math_exp2( acamera_log2_fixed_to_fixed( ratio, 6, 8 ) / 3, 8, 6 ) >> 6;
        break;
    case 3:
        return acamera_sqrt32( ratio >> 6 );
        break;
    default:
    case 2:
        return ratio >> 6;
        break;
    }
}

static void ae_prepare_input( ae_acamera_fsm_ptr_t p_fsm, ae_custom_input_t *custom_input, ae_acamera_input_t *acamera_input )
{
    system_memset( custom_input, 0, sizeof( *custom_input ) );
    system_memset( acamera_input, 0, sizeof( *acamera_input ) );

    // acamera_input
    acamera_input->ae_ctrl = (ae_balanced_param_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_CONTROL );

    fsm_param_sensor_info_t sensor_info;
    sensor_info.sensor_exp_number = 1;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );
    acamera_input->misc_info.sensor_exp_number = sensor_info.sensor_exp_number;

    int32_t total_gain = 0;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );
    acamera_input->misc_info.total_gain = total_gain;

    int32_t max_exposure_log2 = 0;
    int32_t type = CMOS_MAX_EXPOSURE_LOG2;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXPOSURE_LOG2, &type, sizeof( type ), &max_exposure_log2, sizeof( max_exposure_log2 ) );
    acamera_input->misc_info.max_exposure_log2 = max_exposure_log2;

    cmos_control_param_t *param_cmos = (cmos_control_param_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CMOS_CONTROL );
    acamera_input->misc_info.global_max_exposure_ratio = param_cmos->global_max_exposure_ratio;

    uint32_t iridix_contrast = 256;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_IRIDIX_CONTRAST, NULL, 0, &iridix_contrast, sizeof( iridix_contrast ) );
    acamera_input->misc_info.iridix_contrast = iridix_contrast;

    acamera_input->misc_info.global_exposure = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_exposure;
    acamera_input->misc_info.global_ae_compensation = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_ae_compensation;
    acamera_input->misc_info.global_manual_exposure = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_exposure;
    acamera_input->misc_info.global_manual_exposure_ratio = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_exposure_ratio;
    acamera_input->misc_info.global_exposure_ratio = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_exposure_ratio;

    acamera_input->cali_data.ae_corr_lut = _GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_CORRECTION );
    acamera_input->cali_data.ae_corr_lut_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_CORRECTION );
    acamera_input->cali_data.ae_exp_corr_lut = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_EXPOSURE_CORRECTION );
    acamera_input->cali_data.ae_exp_corr_lut_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_EXPOSURE_CORRECTION );
    acamera_input->cali_data.ae_hdr_target = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_CONTROL_HDR_TARGET );
    acamera_input->cali_data.ae_hdr_target_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_AE_CONTROL_HDR_TARGET );
    acamera_input->cali_data.ae_exp_ratio_adjustment = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT );
    acamera_input->cali_data.ae_exp_ratio_adjustment_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT );
}

void ae_process_stats( ae_acamera_fsm_ptr_t p_fsm )
{
    if ( !p_fsm->ae_alg_obj.proc ) {
        LOG( LOG_ERR, "AE: can't process stats since function is NULL." );
        return;
    }

    ae_stats_data_t stats;
    stats.fullhist = p_fsm->fullhist;
    stats.fullhist_size = array_size( p_fsm->fullhist );
    stats.fullhist_sum = p_fsm->fullhist_sum;
    stats.zone_hist = p_fsm->hist4;
    stats.zone_hist_size = array_size( p_fsm->hist4 );


    ae_acamera_input_t acamera_ae_input;
    ae_custom_input_t custom_ae_input;
    ae_input_data_t ae_input;

    ae_prepare_input( p_fsm, &custom_ae_input, &acamera_ae_input );
    ae_input.custom_input = &custom_ae_input;
    ae_input.acamera_input = &acamera_ae_input;

    ae_output_data_t ae_output;
    ae_acamera_output_t acamera_ae_output;
    system_memset( &acamera_ae_output, 0, sizeof( acamera_ae_output ) );
    ae_output.acamera_output = &acamera_ae_output;
    ae_output.custom_output = NULL;

    // call the core algorithm to calculate target exposure and exposure_ratio
    if ( p_fsm->ae_alg_obj.proc( p_fsm->ae_alg_obj.ae_ctx, &stats, &ae_input, &ae_output ) != 0 ) {
        LOG( LOG_ERR, "AE algorithm process failed." );
        return;
    }

    p_fsm->exposure_log2 = acamera_ae_output.exposure_log2;
    p_fsm->exposure_ratio = acamera_ae_output.exposure_ratio;
    p_fsm->ae_converged = acamera_ae_output.ae_converged;

    if ( !ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_exposure ) {
        ACAMERA_FSM2CTX_PTR( p_fsm )
            ->stab.global_exposure = ( acamera_math_exp2( p_fsm->exposure_log2, LOG2_GAIN_SHIFT, 6 ) );
    }

    if ( !ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_exposure_ratio ) {
        ACAMERA_FSM2CTX_PTR( p_fsm )
            ->stab.global_exposure_ratio = full_ratio_to_adjaced( acamera_ae_input.misc_info.sensor_exp_number, p_fsm->exposure_ratio );
    }

    fsm_param_exposure_target_t exp_target;
    exp_target.exposure_log2 = p_fsm->exposure_log2;
    exp_target.exposure_ratio = p_fsm->exposure_ratio;
    exp_target.frame_id_tracking = p_fsm->cur_using_stats_frame_id;

    acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_EXPOSURE_TARGET, &exp_target, sizeof( exp_target ) );

    // skip when frame_id is 0.
    if ( p_fsm->cur_using_stats_frame_id ) {
        fsm_param_mon_alg_flow_t ae_flow;
        ae_flow.frame_id_tracking = p_fsm->cur_using_stats_frame_id;
        ae_flow.frame_id_current = acamera_fsm_util_get_cur_frame_id( &p_fsm->cmn );
        ae_flow.flow_state = MON_ALG_FLOW_STATE_OUTPUT_READY;
        acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_MON_AE_FLOW, &ae_flow, sizeof( ae_flow ) );
        LOG( LOG_INFO, "AE flow: OUTPUT_READY: frame_id_tracking: %d, cur frame_id: %u.", ae_flow.frame_id_tracking, ae_flow.frame_id_current );
    }
}

void ae_acamera_initialize( ae_acamera_fsm_ptr_t p_fsm )
{
#if FW_ALG_SUPPORT_SHARED_LIB

    p_fsm->lib_handle = dlopen( "custom_alg.so", RTLD_LAZY );
    LOG( LOG_INFO, "AE: try to open custom_alg library, return: %p.", p_fsm->lib_handle );
    if ( !p_fsm->lib_handle ) {
        p_fsm->lib_handle = dlopen( "./libacamera_alg_core.so", RTLD_LAZY );
        LOG( LOG_INFO, "AE: try to open acamera_alg_core library, return: %p.", p_fsm->lib_handle );
    }

    if ( p_fsm->lib_handle ) {
        p_fsm->ae_alg_obj.init = dlsym( p_fsm->lib_handle, "ae_acamera_core_init" );
        p_fsm->ae_alg_obj.deinit = dlsym( p_fsm->lib_handle, "ae_acamera_core_deinit" );
        p_fsm->ae_alg_obj.proc = dlsym( p_fsm->lib_handle, "ae_acamera_core_proc" );
        LOG( LOG_INFO, "AE: init: %p, deinit: %p, proc: %p .", p_fsm->ae_alg_obj.init, p_fsm->ae_alg_obj.deinit, p_fsm->ae_alg_obj.proc );
    }

#else
    p_fsm->ae_alg_obj.init = ae_acamera_core_init;
    p_fsm->ae_alg_obj.deinit = ae_acamera_core_deinit;
    p_fsm->ae_alg_obj.proc = ae_acamera_core_proc;
#endif

    if ( p_fsm->ae_alg_obj.init ) {
        p_fsm->ae_alg_obj.ae_ctx = p_fsm->ae_alg_obj.init( p_fsm->cmn.ctx_id );
        LOG( LOG_INFO, "Init AE core, ret: %p.", p_fsm->ae_alg_obj.ae_ctx );
    }

    acamera_isp_metering_aexp_hist_thresh_0_1_write( p_fsm->cmn.isp_base, 0 );
    acamera_isp_metering_aexp_hist_thresh_1_2_write( p_fsm->cmn.isp_base, 0 );
    acamera_isp_metering_aexp_hist_thresh_3_4_write( p_fsm->cmn.isp_base, 0 );
    acamera_isp_metering_aexp_hist_thresh_4_5_write( p_fsm->cmn.isp_base, 224 );

    int i, j;
    for ( i = 0; i < ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_DEFAULT; i++ ) {
        for ( j = 0; j < ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DEFAULT; j++ ) {
            acamera_isp_metering_hist_aexp_zones_weight_write( p_fsm->cmn.isp_base, ISP_METERING_ZONES_MAX_H * i + j, 15 );
        }
    }

    ae_roi_update( p_fsm );
}

void ae_acamera_deinitialize( ae_acamera_fsm_ptr_t p_fsm )
{
    if ( p_fsm->ae_alg_obj.deinit ) {
        p_fsm->ae_alg_obj.deinit( p_fsm->ae_alg_obj.ae_ctx );
    }

#if FW_ALG_SUPPORT_SHARED_LIB
    if ( p_fsm->lib_handle ) {
        dlclose( p_fsm->lib_handle );
    }
#endif
}

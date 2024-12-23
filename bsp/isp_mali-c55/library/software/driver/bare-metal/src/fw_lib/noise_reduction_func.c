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
#include "acamera_math.h"
#include "acamera_firmware_config.h"
#include "noise_reduction_fsm.h"
#include "cmos_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_NOISE_REDUCTION
#endif


static void sinter_load_radial_lut( noise_reduction_fsm_t *p_fsm )
{
    const uint8_t *p_sinter_radial_lut = (uint8_t *)_GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_RADIAL_LUT );
    // Params must be in the following format: rm_enable, rm_centre_x, rm_centre_y, rm_off_centre_mult.
    const uint16_t *p_sinter_radial_params = (uint16_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_RADIAL_PARAMS );
    int i;
    uint8_t number_of_nodes = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_RADIAL_LUT );

    for ( i = 0; i < number_of_nodes; ++i ) {
        acamera_isp_sinter_shading_rm_shading_lut_write( p_fsm->cmn.isp_base, i, p_sinter_radial_lut[i] );
    }

    acamera_isp_sinter_rm_enable_write( p_fsm->cmn.isp_base, p_sinter_radial_params[0] );
    acamera_isp_sinter_rm_center_x_write( p_fsm->cmn.isp_base, p_sinter_radial_params[1] );
    acamera_isp_sinter_rm_center_y_write( p_fsm->cmn.isp_base, p_sinter_radial_params[2] );
    acamera_isp_sinter_rm_off_center_mult_write( p_fsm->cmn.isp_base, p_sinter_radial_params[3] );
}

#if ( ISP_HW_IS_MALI_C32_C52 == 0 ) // Smith only
static void sinter_load_noise_profile_config( noise_reduction_fsm_t *p_fsm )
{
    /*
    CALIBRATION_SINTER_NOISE_PROFILE_CONFIG
    // 0 sinter noise profile/add_lut (0)
    // 1 sinter noise profile/motion_offset
    */
    uint8_t *sinter_config = (uint8_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_NOISE_PROFILE_CONFIG );
    acamera_isp_sinter_noise_profile_add_lut_write( p_fsm->cmn.isp_base, sinter_config[0] );
    acamera_isp_sinter_noise_profile_add_motion_offset_write( p_fsm->cmn.isp_base, sinter_config[1] );
}

static void temper_load_noise_profile_config( noise_reduction_fsm_t *p_fsm )
{
    /*
    CALIBRATION_TEMPER_NOISE_PROFILE_CONFIG
    // 0 temper noise profile/motion_thresh_0
    // 1 temper noise profile/motion_thresh_1
    // 2 temper noise profile/motion_thresh_2
    */
    uint8_t *temper_config = (uint8_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_NOISE_PROFILE_CONFIG );
    acamera_isp_temper_noise_profile_motion_thresh_0_write( p_fsm->cmn.isp_base, temper_config[0] );
    acamera_isp_temper_noise_profile_motion_thresh_1_write( p_fsm->cmn.isp_base, temper_config[1] );
    acamera_isp_temper_noise_profile_motion_thresh_2_write( p_fsm->cmn.isp_base, temper_config[2] );
}
#endif

static void cnr_load_noise_profile_config( noise_reduction_fsm_t *p_fsm )
{
    // CNR
    // Common registers
    //  0 square_root_enable (1)
    //  1 enable (1)
    //  2 debug_reg (16)
    //  3 delta_factor (12)
    //  4 uv_seg1_offset (12)
    //  5 uv_seg1_slope (16)
    //  6 Enable gamma RGB fr (1)
    //  7 Enable gamma RGB ds (1)
    // Smith registers
    //  8 uv_seg1_min (12)
    //  9 uv_mean_offset (12)
    // 10 uv_mean_slope (16)
    // 11 uv_var_offset (12)
    // 12 uv_var_slope (16)
    // 13 uv_delta_offset (12)
    // 14 uv_delta_slope (16)
    // C32/52 registers
    // 15 mode (8)
    // 16 effective_kernel (6)
    // 17 u_center (12)
    // 18 v_center (12)
    // 19 global_offset (12)
    // 20 global_slope (16)
    // 21 uv_seg1_threshold (12)
    // 22 umean1_threshold (12)
    // 23 umean1_offset (12)
    // 24 umean1_slope (16)
    // 25 umean2_threshold (12)
    // 26 umean2_offset (12)
    // 27 umean2_slope (16)
    // 28 vmean1_threshold (12)
    // 29 vmean1_offset (12)
    // 30 vmean1_slope (16)
    // 31 vmean2_threshold (12)
    // 32 vmean2_offset (12)
    // 33 vmean2_slope (16)
    // 34 uv_var1_threshold (12)
    // 35 uv_var1_offset (12)
    // 36 uv_var1_slope (16)
    // 37 uv_var2_threshold (12)
    // 38 uv_var2_offset (12)
    // 39 uv_var2_slope (16)
    // 40 uv_var1_scale (6)
    // 41 uv_var2_scale (6)
    // 42 uv_delta1_threshold (12)
    // 43 uv_delta1_offset (12)
    // 44 uv_delta1_slope (16)
    // 45 uv_delta2_threshold (12)
    // 46 uv_delta2_offset (12)
    // 47 uv_delta2_slope (16)
    uint16_t *cnr_config = (uint16_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CNR_CONFIG );
    acamera_isp_cnr_square_root_enable_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[0] & 0x01 );
    acamera_isp_cnr_enable_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[1] & 0x01 );
    acamera_isp_cnr_debug_reg_write( p_fsm->cmn.isp_base, cnr_config[2] );
    acamera_isp_cnr_delta_factor_write( p_fsm->cmn.isp_base, cnr_config[3] & 0x0fff );
    acamera_isp_cnr_uv_seg1_offset_write( p_fsm->cmn.isp_base, cnr_config[4] & 0x0fff );
    acamera_isp_cnr_uv_seg1_slope_write( p_fsm->cmn.isp_base, cnr_config[5] );
    acamera_isp_fr_gamma_rgb_enable_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[6] & 0x01 );
    acamera_isp_ds1_gamma_rgb_enable_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[7] & 0x01 );
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    acamera_isp_cnr_uv_seg1_min_write( p_fsm->cmn.isp_base, cnr_config[8] & 0x0fff );
    acamera_isp_cnr_uv_mean_offset_write( p_fsm->cmn.isp_base, cnr_config[9] & 0x0fff );
    acamera_isp_cnr_uv_mean_slope_write( p_fsm->cmn.isp_base, cnr_config[10] );
    acamera_isp_cnr_uv_var_offset_write( p_fsm->cmn.isp_base, cnr_config[11] & 0x0fff );
    acamera_isp_cnr_uv_var_slope_write( p_fsm->cmn.isp_base, cnr_config[12] );
    acamera_isp_cnr_uv_delta_offset_write( p_fsm->cmn.isp_base, cnr_config[13] & 0x0fff );
    acamera_isp_cnr_uv_delta_slope_write( p_fsm->cmn.isp_base, cnr_config[14] );
#else
    acamera_isp_cnr_mode_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[15] );
    acamera_isp_cnr_effective_kernel_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[16] & 0x7f );
    acamera_isp_cnr_u_center_write( p_fsm->cmn.isp_base, cnr_config[17] & 0x0fff );
    acamera_isp_cnr_v_center_write( p_fsm->cmn.isp_base, cnr_config[18] & 0x0fff );
    acamera_isp_cnr_global_offset_write( p_fsm->cmn.isp_base, cnr_config[19] & 0x0fff );
    acamera_isp_cnr_global_slope_write( p_fsm->cmn.isp_base, cnr_config[20] );
    acamera_isp_cnr_uv_seg1_threshold_write( p_fsm->cmn.isp_base, cnr_config[21] & 0x0fff );
    acamera_isp_cnr_umean1_threshold_write( p_fsm->cmn.isp_base, cnr_config[22] & 0x0fff );
    acamera_isp_cnr_umean1_offset_write( p_fsm->cmn.isp_base, cnr_config[23] & 0x0fff );
    acamera_isp_cnr_umean1_slope_write( p_fsm->cmn.isp_base, cnr_config[24] );
    acamera_isp_cnr_umean2_threshold_write( p_fsm->cmn.isp_base, cnr_config[25] & 0x0fff );
    acamera_isp_cnr_umean2_offset_write( p_fsm->cmn.isp_base, cnr_config[26] & 0x0fff );
    acamera_isp_cnr_umean2_slope_write( p_fsm->cmn.isp_base, cnr_config[27] );
    acamera_isp_cnr_vmean1_threshold_write( p_fsm->cmn.isp_base, cnr_config[28] & 0x0fff );
    acamera_isp_cnr_vmean1_offset_write( p_fsm->cmn.isp_base, cnr_config[29] & 0x0fff );
    acamera_isp_cnr_vmean1_slope_write( p_fsm->cmn.isp_base, cnr_config[30] );
    acamera_isp_cnr_vmean2_threshold_write( p_fsm->cmn.isp_base, cnr_config[31] & 0x0fff );
    acamera_isp_cnr_vmean2_offset_write( p_fsm->cmn.isp_base, cnr_config[32] & 0x0fff );
    acamera_isp_cnr_vmean2_slope_write( p_fsm->cmn.isp_base, cnr_config[33] );
    acamera_isp_cnr_uv_var1_threshold_write( p_fsm->cmn.isp_base, cnr_config[34] & 0x0fff );
    acamera_isp_cnr_uv_var1_offset_write( p_fsm->cmn.isp_base, cnr_config[35] & 0x0fff );
    acamera_isp_cnr_uv_var1_slope_write( p_fsm->cmn.isp_base, cnr_config[36] );
    acamera_isp_cnr_uv_var2_threshold_write( p_fsm->cmn.isp_base, cnr_config[37] & 0x0fff );
    acamera_isp_cnr_uv_var2_offset_write( p_fsm->cmn.isp_base, cnr_config[38] & 0x0fff );
    acamera_isp_cnr_uv_var2_slope_write( p_fsm->cmn.isp_base, cnr_config[39] );
    acamera_isp_cnr_uv_var1_scale_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[40] & 0x3f );
    acamera_isp_cnr_uv_var2_scale_write( p_fsm->cmn.isp_base, (uint8_t)cnr_config[41] & 0x3f );
    acamera_isp_cnr_uv_delta1_threshold_write( p_fsm->cmn.isp_base, cnr_config[42] & 0x0fff );
    acamera_isp_cnr_uv_delta1_offset_write( p_fsm->cmn.isp_base, cnr_config[43] & 0x0fff );
    acamera_isp_cnr_uv_delta1_slope_write( p_fsm->cmn.isp_base, cnr_config[44] );
    acamera_isp_cnr_uv_delta2_threshold_write( p_fsm->cmn.isp_base, cnr_config[45] & 0x0fff );
    acamera_isp_cnr_uv_delta2_offset_write( p_fsm->cmn.isp_base, cnr_config[46] & 0x0fff );
    acamera_isp_cnr_uv_delta2_slope_write( p_fsm->cmn.isp_base, cnr_config[47] );
#endif
}

void dynamic_dpc_strength_calculate( noise_reduction_fsm_t *p_fsm )
{
    int32_t total_gain;

    // Do not update registers if in manual mode.
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_raw_frontend ) {
        return;
    }

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );

    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    uint16_t dp_slope = acamera_isp_raw_frontend_dp_slope_read( p_fsm->cmn.isp_base );
    uint16_t dp_threshold = acamera_isp_raw_frontend_dp_threshold_read( p_fsm->cmn.isp_base );
    {
        uint32_t dp_slope_table_idx = CALIBRATION_DP_SLOPE;
        uint32_t dp_threshold_table_idx = CALIBRATION_DP_THRESHOLD;

        modulation_entry_t *dp_slope_table = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), dp_slope_table_idx );
        uint32_t dp_slope_table_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), dp_slope_table_idx );
        modulation_entry_t *dp_threshold_table = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), dp_threshold_table_idx );
        uint32_t dp_threshold_table_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), dp_threshold_table_idx );

        dp_slope = acamera_calc_modulation_u16( log2_gain, dp_slope_table, dp_slope_table_len );
        dp_threshold = acamera_calc_modulation_u16( log2_gain, dp_threshold_table, dp_threshold_table_len );
    }
    acamera_isp_raw_frontend_dp_slope_write( p_fsm->cmn.isp_base, dp_slope );
    acamera_isp_raw_frontend_dp_threshold_write( p_fsm->cmn.isp_base, dp_threshold );
}


void stitching_error_calculate( noise_reduction_fsm_t *p_fsm )
{
    // Do not update frame stitch registers if in manual mode.
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_frame_stitch ) {
        return;
    }
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr == 0 ) {
        return;
    }

    /*
    -------------------------------------------------------
        Modulation for frame stitching
    -------------------------------------------------------
    */
    int32_t total_gain = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );

    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );
    // Long medium motion
    uint16_t lm_np = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_NP ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_NP ) );
    uint16_t lm_mov_mult = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_MOV_MULT ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_MOV_MULT ) );

#if ISP_HW_IS_MALI_C32_C52 // Smith does not have this.
    // Medium short motion
    uint16_t ms_np = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_MS_NP ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_MS_NP ) );
    uint16_t ms_mov_mult = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_MS_MOV_MULT ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_MS_MOV_MULT ) );

    // Short very short motion
    uint16_t svs_np = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_SVS_NP ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_SVS_NP ) );
    uint16_t svs_mov_mult = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_SVS_MOV_MULT ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_SVS_MOV_MULT ) );
#endif

    // Change to MC off mode when gain is higher than gain_log2 value found in calibration.
    uint16_t MC_off_enable_gain = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_FS_MC_OFF )[0];

    if ( log2_gain > MC_off_enable_gain ) {
        acamera_isp_frame_stitch_mcoff_mode_enable_write( p_fsm->cmn.isp_base, 1 );
        //printf( "%d %d %d\n", (int)log2_gain, 1, (int)MC_off_enable_gain );
    } else if ( log2_gain <= MC_off_enable_gain ) {
        acamera_isp_frame_stitch_mcoff_mode_enable_write( p_fsm->cmn.isp_base, 0 );
        //printf( "%d %d %d\n", (int)log2_gain, 0, (int)MC_off_enable_gain );
    }

    uint16_t stitching_lm_med_noise_intensity_thresh = acamera_calc_modulation_u16( log2_gain, (modulation_entry_t *)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_MED_NOISE_INTENSITY ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_STITCHING_LM_MED_NOISE_INTENSITY ) );

#if ISP_WDR_SWITCH
    uint32_t wdr_mode = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_WDR_MODE, NULL, 0, &wdr_mode, sizeof( wdr_mode ) );
    if ( WDR_MODE_FS_LIN == wdr_mode ) {
        fsm_param_sensor_info_t sensor_info;
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );

        switch ( sensor_info.sensor_exp_number ) {
        case 4:
#if ISP_HW_IS_MALI_C32_C52
            acamera_isp_frame_stitch_lm_np_mult_write( p_fsm->cmn.isp_base, lm_np );
            acamera_isp_frame_stitch_lm_alpha_mov_slope_write( p_fsm->cmn.isp_base, lm_mov_mult );
            acamera_isp_frame_stitch_ms_np_mult_write( p_fsm->cmn.isp_base, ms_np );
            acamera_isp_frame_stitch_ms_alpha_mov_slope_write( p_fsm->cmn.isp_base, ms_mov_mult );
            acamera_isp_frame_stitch_svs_np_mult_write( p_fsm->cmn.isp_base, svs_np );
            acamera_isp_frame_stitch_svs_alpha_mov_slope_write( p_fsm->cmn.isp_base, svs_mov_mult );
            acamera_isp_frame_stitch_lm_med_noise_intensity_thresh_write( p_fsm->cmn.isp_base, stitching_lm_med_noise_intensity_thresh );
#else
            LOG( LOG_ERR, "Current HW config does not support %d exposures", sensor_info.sensor_exp_number );
#endif
            break;

        case 3:
#if ISP_HW_IS_MALI_C32_C52
            acamera_isp_frame_stitch_lm_np_mult_write( p_fsm->cmn.isp_base, lm_np );
            acamera_isp_frame_stitch_lm_alpha_mov_slope_write( p_fsm->cmn.isp_base, lm_mov_mult );
            acamera_isp_frame_stitch_ms_np_mult_write( p_fsm->cmn.isp_base, ms_np );
            acamera_isp_frame_stitch_ms_alpha_mov_slope_write( p_fsm->cmn.isp_base, ms_mov_mult );
            acamera_isp_frame_stitch_lm_med_noise_intensity_thresh_write( p_fsm->cmn.isp_base, stitching_lm_med_noise_intensity_thresh );
#else
            LOG( LOG_ERR, "Current HW config does not support %d exposures", sensor_info.sensor_exp_number );
#endif
            break;

        case 2:
            acamera_isp_frame_stitch_lm_np_mult_write( p_fsm->cmn.isp_base, lm_np );
            acamera_isp_frame_stitch_lm_alpha_mov_slope_write( p_fsm->cmn.isp_base, lm_mov_mult );
            acamera_isp_frame_stitch_lm_med_noise_intensity_thresh_write( p_fsm->cmn.isp_base, stitching_lm_med_noise_intensity_thresh );
            break;

        default:
            LOG( LOG_ERR, "Unsupported exposures number: %d", sensor_info.sensor_exp_number );
            break;
        }
    }
#endif
}

void sinter_strength_calculate( noise_reduction_fsm_t *p_fsm )
{
    uint32_t cmos_exp_ratio = 0;
    uint32_t wdr_mode = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXPOSURE_RATIO, NULL, 0, &cmos_exp_ratio, sizeof( cmos_exp_ratio ) );
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_WDR_MODE, NULL, 0, &wdr_mode, sizeof( wdr_mode ) );
    uint32_t snr_thresh_master;

    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_sinter == 0 ) { // Do not update values if in manual mode.
        // Get LUT indexes for the current HDR mode.
        uint32_t sinter_strength_idx = CALIBRATION_SINTER_STRENGTH;
        uint32_t sinter_strength1_idx = CALIBRATION_SINTER_STRENGTH1;
        uint32_t sinter_thresh1_idx = CALIBRATION_SINTER_THRESH1;
        uint32_t sinter_thresh4_idx = CALIBRATION_SINTER_THRESH4;
        uint32_t sinter_int_config_idx = CALIBRATION_SINTER_INTCONFIG;
        int32_t total_gain = 0;

        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );

        uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

        //LOG( LOG_NOTICE, "log2_gain %d total_gain %d", log2_gain, total_gain );

        snr_thresh_master = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength_idx ) );
#if ( defined( ISP_HAS_IRIDIX8_FSM ) || defined( ISP_HAS_IRIDIX8_MANUAL_FSM ) || defined( ISP_HAS_IRIDIX_ACAMERA_FSM ) ) && defined( CALIBRATION_SINTER_STRENGTH_MC_CONTRAST ) // CHECK IF LOGIC IS CORRECT.
        uint32_t sinter_strength_mc_contrast_idx = CALIBRATION_SINTER_STRENGTH_MC_CONTRAST;

        // Adjust strength according to contrast.
        uint32_t iridix_contrast = 256; // Remove the 8 bit precision?
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_IRIDIX_CONTRAST, NULL, 0, &iridix_contrast, sizeof( iridix_contrast ) );

        iridix_contrast = iridix_contrast >> 8;
        uint32_t snr_thresh_master_contrast = acamera_calc_modulation_u16( iridix_contrast, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength_mc_contrast_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength_mc_contrast_idx ) );
        if ( snr_thresh_master_contrast > 0xFF ) {
            snr_thresh_master_contrast = 0xFF;
        }

        // It will only affect short exposure.
        p_fsm->snr_thresh_contrast = snr_thresh_master_contrast;

#endif

        if ( snr_thresh_master > 0xFF ) {
            snr_thresh_master = 0xFF;
        }

        ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_sinter_threshold_target = ( snr_thresh_master );

        uint16_t sinter_strenght1 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength1_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_strength1_idx ) );
        //LOG( LOG_INFO, "sinter_strenght1 %d log2_gain %d ", (int)sinter_strenght1, (int)log2_gain );
        acamera_isp_sinter_strength_1_write( p_fsm->cmn.isp_base, sinter_strenght1 );
        uint16_t sinter_thresh1 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_thresh1_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_thresh1_idx ) );
        acamera_isp_sinter_thresh_1h_write( p_fsm->cmn.isp_base, sinter_thresh1 );
        acamera_isp_sinter_thresh_1v_write( p_fsm->cmn.isp_base, sinter_thresh1 );
        uint16_t sinter_thresh4 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_thresh4_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_thresh4_idx ) );
        acamera_isp_sinter_thresh_4h_write( p_fsm->cmn.isp_base, sinter_thresh4 );
        acamera_isp_sinter_thresh_4v_write( p_fsm->cmn.isp_base, sinter_thresh4 );

        uint16_t sinter_int_config = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_int_config_idx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_int_config_idx ) );
        acamera_isp_sinter_int_config_write( p_fsm->cmn.isp_base, sinter_int_config );

        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter_lite == 0 ) { // Sinter 3 is used.
#if ISP_HW_IS_MALI_C32_C52
            int sinter_sad_inx = CALIBRATION_SINTER_SAD;
            acamera_isp_sinter_sad_filt_thresh_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_sad_inx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sinter_sad_inx ) ) );
#else
            uint16_t sinter_motion_offset0 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_0 ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_0 ) );
            acamera_isp_sinter_noise_profile_motion_offset_0_write( p_fsm->cmn.isp_base, sinter_motion_offset0 );

            uint16_t sinter_motion_offset1 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_1 ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_1 ) );
            acamera_isp_sinter_noise_profile_motion_offset_1_write( p_fsm->cmn.isp_base, sinter_motion_offset1 );

            uint16_t sinter_motion_offset2 = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_2 ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SINTER_MOTION_OFFSET_2 ) );
            acamera_isp_sinter_noise_profile_motion_offset_2_write( p_fsm->cmn.isp_base, sinter_motion_offset2 );
#endif
        }
    } else {
        snr_thresh_master = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_sinter_threshold_target;
    }

    p_fsm->snr_thresh_master = snr_thresh_master;
}

void temper_strength_calculate( noise_reduction_fsm_t *p_fsm )
{
    uint32_t cmos_exp_ratio = 0;
    uint32_t wdr_mode = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXPOSURE_RATIO, NULL, 0, &cmos_exp_ratio, sizeof( cmos_exp_ratio ) );
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_WDR_MODE, NULL, 0, &wdr_mode, sizeof( wdr_mode ) );

    uint32_t tnr_thresh_master;
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    uint16_t tnr_mot_thresh = p_fsm->tnr_mot_thresh;
    uint16_t tnr_mot_slope = p_fsm->tnr_mot_slope;
#endif
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper && ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_temper == 0 ) //  Do not update values if manual mode
    {
        int32_t total_gain = 0;
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );
        uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );
        // This drives global offset.
        tnr_thresh_master = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_STRENGTH ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_STRENGTH ) );
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
        tnr_mot_thresh = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_MOT_THRESH ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_MOT_THRESH ) );
        tnr_mot_slope = acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_MOT_SLOPE ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_TEMPER_MOT_SLOPE ) );
#endif
        ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_temper_threshold_target = ( tnr_thresh_master );

        switch ( wdr_mode ) {
        case WDR_MODE_FS_LIN: {
            if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr == 0 ) {
                break;
            }

            fsm_param_sensor_info_t sensor_info;
            acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );

            exposure_data_set_t exp_write_set;
            acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXP_WRITE_SET, NULL, 0, &exp_write_set, sizeof( exp_write_set ) );

            switch ( sensor_info.sensor_exp_number ) {
            case 4:
#if ISP_HW_IS_MALI_C32_C52
            {
                const uint32_t SVS_exp_ratio = exp_write_set.exposure_ratio_short;  // Usomething.6
                const uint32_t MS_exp_ratio = exp_write_set.exposure_ratio_medium;  // Usomething.6
                const uint32_t LM_exp_ratio = exp_write_set.exposure_ratio_medium2; // Usomething.6

                // Noise level: 4:1
                // noise level 0 => ( very short ) = 64:
                // noise level 1 => ( short )      = 64 - 8 * log2( svs_expoosure ratio )
                // noise level 2 => ( medium )     = 64 - 8 * log2( svs_expoosure ratio * sm_expoosure ratio )
                // noise level 3 => ( long )       = 64 - 8 * log2( svs_expoosure ratio * sm_expoosure ratio * lm_expoosure ratio )

                int8_t short_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( SVS_exp_ratio >> 6, 8, 0 ) >> 8 );
                int8_t medium_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( SVS_exp_ratio * MS_exp_ratio ) >> 12, 8, 0 ) >> 8 );
                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( (uint64_t)SVS_exp_ratio * (uint64_t)MS_exp_ratio * (uint64_t)LM_exp_ratio ) >> 18, 8, 0 ) >> 8 );

                if ( short_thresh < 0 ) {
                    short_thresh = 0;
                }
                if ( medium_thresh < 0 ) {
                    medium_thresh = 0;
                }
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }

                acamera_isp_temper_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 );
                acamera_isp_temper_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, short_thresh );
                acamera_isp_temper_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, medium_thresh );
                acamera_isp_temper_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, long_thresh );

                uint32_t mult = ( 2 << 17 ) / SVS_exp_ratio; // u1.11
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                uint32_t FS_thresh = acamera_isp_frame_stitch_svs_thresh_low_read( p_fsm->cmn.isp_base );
                FS_thresh = ( FS_thresh * mult ) << 3;
                uint32_t FS_thresh_sqrt_svs = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );

                mult = ( 2 << 17 ) / ( ( SVS_exp_ratio * MS_exp_ratio ) >> 6 ); // u1.11
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                FS_thresh = acamera_isp_frame_stitch_ms_thresh_low_read( p_fsm->cmn.isp_base );
                FS_thresh = ( FS_thresh * mult ) << 3;
                uint32_t FS_thresh_sqrt_ms = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );

                mult = ( 2 << 17 ) / ( ( LM_exp_ratio * MS_exp_ratio * SVS_exp_ratio ) >> 12 ); // u1.11
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                FS_thresh = acamera_isp_frame_stitch_lm_thresh_low_read( p_fsm->cmn.isp_base );
                FS_thresh = ( FS_thresh * mult ) << 3;
                uint32_t FS_thresh_sqrt_lm = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );

                acamera_isp_temper_noise_profile_thresh3_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_svs );
                acamera_isp_temper_noise_profile_thresh2_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_ms );
                acamera_isp_temper_noise_profile_thresh1_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_lm );

            }
#else
                LOG( LOG_ERR, "Current HW config does not support %d exposures", sensor_info.sensor_exp_number );
#endif
            break;

            case 3:
#if ISP_HW_IS_MALI_C32_C52
            {
                // If WDR mode: intensity thresholds and noise profile for different exposures need to be updated according to exposure ratio.
                const uint32_t MS_exp_ratio = exp_write_set.exposure_ratio_short;  // Usomething.6
                const uint32_t LM_exp_ratio = exp_write_set.exposure_ratio_medium; // Usomething.6

                // Noise level: 3:1
                // noise level 0 => (short)  = 64:
                // noise level 1 => (medium) = 64 - 8 * log2( sm_expoosure ratio )
                // noise level 2 => (long)   = 64 - 8 * log2( sm_expoosure ratio * lm_expoosure ratio )

                int8_t medium_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( MS_exp_ratio >> 6, 8, 0 ) >> 8 );
                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( LM_exp_ratio * MS_exp_ratio ) >> 12, 8, 0 ) >> 8 );
                if ( medium_thresh < 0 ) {
                    medium_thresh = 0;
                }
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }

                //LOG( LOG_INFO, "%d ", (int) p_fsm->snr_thresh_contrast );
                acamera_isp_temper_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 );
                acamera_isp_temper_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, medium_thresh );
                acamera_isp_temper_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, long_thresh );
                acamera_isp_temper_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, 64 );

                // DW_Out = 20;
                // DW_In = 12;
                // ExpRatio = [1:256] * 64;
                // FS_thresh = 3500;
                // % 2 : Compute scaling values
                // DW_Inc = DW_Out - DW_In;
                // mult = min( 2048, fix( ( 2 ^ 17 )./ ExpRatio ) ); % 1.11
                // % 3 : Scale parameters
                // FS_thresh = bitshift( FS_thresh * mult, DW_Inc - 11 ); % 0.DW_Out
                // FS_thresh_sqrt = round( sqrt( FS_thresh * 4096 ) );
                uint32_t mult;
                uint32_t FS_thresh;
                uint32_t FS_thresh_sqrt_ms, FS_thresh_sqrt_lm;

                mult = ( 2 << 17 ) / MS_exp_ratio; // u1.11
                //if ( mult < 2048 ) { mult = 2048;  }
                FS_thresh = acamera_isp_frame_stitch_ms_thresh_low_read( p_fsm->cmn.isp_base );
                //LOG( LOG_INFO, " 1 FS_thresh %d MS_exp_ratio %d mult %d", (int)FS_thresh, (int)MS_exp_ratio, (int)mult );
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                FS_thresh = ( FS_thresh * mult ) << 3;
                FS_thresh_sqrt_ms = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );
                //LOG( LOG_INFO, " 1 FS_thresh %d FS_thresh_sqrt_ms %d mult %d", (int)FS_thresh, (int)FS_thresh_sqrt_ms, (int)mult );

                mult = ( 2 << 17 ) / ( ( LM_exp_ratio * MS_exp_ratio ) >> 6 ); //u1.11
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                FS_thresh = acamera_isp_frame_stitch_lm_thresh_low_read( p_fsm->cmn.isp_base );
                FS_thresh = ( FS_thresh * mult ) << 3;
                FS_thresh_sqrt_lm = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );

                //LOG( LOG_INFO, " 2 FS_thresh %d FS_thresh_sqrt_lm %d mult %d", (int)FS_thresh, (int)FS_thresh_sqrt_lm, (int)mult );

                acamera_isp_temper_noise_profile_thresh3_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_ms );
                acamera_isp_temper_noise_profile_thresh2_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_lm );
                acamera_isp_temper_noise_profile_thresh1_write( p_fsm->cmn.isp_base, 0 );
            }
#else
                LOG( LOG_ERR, "Current HW config does not support %d exposures", sensor_info.sensor_exp_number );
#endif
            break;

            case 2: {
                // Noise level : 2:1
                // noise level 0 => ( short ) = 64:
                // noise level 1 => ( long )  = 64 - 8 * log2( lm_expoosure ratio )

                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( exp_write_set.exposure_ratio >> 6, 8, 0 ) >> 8 );
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }

                //LOG( LOG_INFO, "%d ", (int) p_fsm->snr_thresh_contrast );
                acamera_isp_temper_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 );
                acamera_isp_temper_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, long_thresh );
                acamera_isp_temper_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, 64 );
                acamera_isp_temper_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, 64 );

                // DW_Out = 20;
                // DW_In = 12;
                // ExpRatio = [1:256] * 64;
                // FS_thresh = 3500;
                // % 2 : Compute scaling values
                // DW_Inc = DW_Out - DW_In;
                // mult = min( 2048, fix( ( 2 ^ 17 )./ ExpRatio ) ); % 1.11
                // % 3 : Scale parameters
                // FS_thresh = bitshift( FS_thresh * mult, DW_Inc - 11 ); % 0.DW_Out
                // FS_thresh_sqrt = round( sqrt( FS_thresh * 4096 ) );
                uint32_t mult;
                uint32_t FS_thresh;
                uint32_t FS_thresh_sqrt_lm;

                mult = ( 2 << 17 ) / exp_write_set.exposure_ratio; // u1.11
                if ( mult > 2048 ) {
                    mult = 2048;
                }
                if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr ) {
                    FS_thresh = acamera_isp_frame_stitch_lm_thresh_low_read( p_fsm->cmn.isp_base );
                } else {
                    FS_thresh = 0;
                }
                FS_thresh = ( FS_thresh * mult ) << 3;
                FS_thresh_sqrt_lm = acamera_sqrt32( FS_thresh ) + acamera_isp_sqrt_black_level_out_read( p_fsm->cmn.isp_base );

                acamera_isp_temper_noise_profile_thresh3_write( p_fsm->cmn.isp_base, FS_thresh_sqrt_lm );
                acamera_isp_temper_noise_profile_thresh2_write( p_fsm->cmn.isp_base, 0 );
                acamera_isp_temper_noise_profile_thresh1_write( p_fsm->cmn.isp_base, 0 );

            } break;

            default: {
                LOG( LOG_ERR, "Unsupported exposures number: %d", sensor_info.sensor_exp_number );
            } break;
            }
            break;
        }
        case WDR_MODE_LINEAR:
            acamera_isp_temper_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 );
            acamera_isp_temper_noise_profile_thresh3_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_thresh2_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_thresh1_write( p_fsm->cmn.isp_base, 0 );
            break;

        default:
            break;
        }
    } else {
        tnr_thresh_master = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_temper_threshold_target;
    }


    if ( tnr_thresh_master > 0xFF ) {
        tnr_thresh_master = 0xFF;
    }
    p_fsm->tnr_thresh_master = tnr_thresh_master;

#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    if ( tnr_mot_thresh > 0x3FF ) {
        tnr_mot_thresh = 0x3FF;
    }
    p_fsm->tnr_mot_thresh = tnr_mot_thresh;

    if ( tnr_mot_slope > 0xFFF ) {
        tnr_mot_slope = 0xFFF;
    }
    p_fsm->tnr_mot_slope = tnr_mot_slope;
#endif
}

void noise_reduction_hw_init( noise_reduction_fsm_t *p_fsm )
{
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter ) {
        sinter_load_radial_lut( p_fsm );
    }
#if ( ISP_HW_IS_MALI_C32_C52 == 0 ) // Smith only
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter ) {
        sinter_load_noise_profile_config( p_fsm );
    }
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper ) {
        temper_load_noise_profile_config( p_fsm );
    }
#endif
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.cnr ) {
        cnr_load_noise_profile_config( p_fsm );
    }
}

void noise_reduction_initialize( noise_reduction_fsm_t *p_fsm )
{
    p_fsm->tnr_strength_target = 15;
    p_fsm->snr_strength_target = 15;
    p_fsm->tnr_thresh_master = p_fsm->tnr_strength_target; // Same as target
    p_fsm->snr_thresh_master = p_fsm->snr_strength_target; // Same as target
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    p_fsm->tnr_mot_thresh = 300;
    p_fsm->tnr_mot_slope = 150;
#endif
}

void noise_reduction_update( noise_reduction_fsm_t *p_fsm )
{
    int32_t total_gain = 0;
    uint32_t wdr_mode = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_WDR_MODE, NULL, 0, &wdr_mode, sizeof( wdr_mode ) );
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );

    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    if ( p_fsm->nr_mode == NOISE_REDUCTION_MODE_OFF ) {

        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper ) {
            /*
            * Turn off Temper
            */
            acamera_isp_temper_noise_profile_global_offset_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_temper_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, 0 );
        }
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter ) {
            /*
            * Turn off Sinter
            */
            acamera_isp_sinter_noise_profile_global_offset_write( p_fsm->cmn.isp_base, 0 );
#if ISP_HW_IS_MALI_C32_C52
            acamera_isp_sinter_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_sinter_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_sinter_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, 0 );
            acamera_isp_sinter_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, 0 );
#endif
        }
        return;
    }

    // Do not update values if in manual mode.
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_cnr == 0 && ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.cnr ) {
        const modulation_entry_t *cnr_uv_delta12_slope = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CNR_UV_DELTA12_SLOPE );
        uint32_t cnr_uv_delta12_slope_len = _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CNR_UV_DELTA12_SLOPE );
        uint16_t uv_delta_slope = acamera_calc_modulation_u16( log2_gain, cnr_uv_delta12_slope, cnr_uv_delta12_slope_len );

#if ISP_HW_IS_MALI_C32_C52
        acamera_isp_cnr_uv_delta1_slope_write( p_fsm->cmn.isp_base, uv_delta_slope );
        acamera_isp_cnr_uv_delta2_slope_write( p_fsm->cmn.isp_base, uv_delta_slope );
#else
        acamera_isp_cnr_uv_delta_slope_write( p_fsm->cmn.isp_base, uv_delta_slope );
#endif
    }

    if ( wdr_mode == WDR_MODE_FS_LIN ) {
        stitching_error_calculate( p_fsm );
    }
    //////////////////////////////////////////////////

    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter && ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_sinter == 0 ) {
        sinter_strength_calculate( p_fsm );

        uint32_t exp_ratio = 0;

        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXPOSURE_RATIO, NULL, 0, &exp_ratio, sizeof( exp_ratio ) );

        if ( exp_ratio != 0 && wdr_mode == WDR_MODE_FS_LIN ) {
            exposure_data_set_t exp_write_set;
            acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_EXP_WRITE_SET, NULL, 0, &exp_write_set, sizeof( exp_write_set ) );

            fsm_param_sensor_info_t sensor_info;
            acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );
            switch ( sensor_info.sensor_exp_number ) {
            case 4: {
                // Noise level: 4:1
                // noise level 0 => (very short) = 64:
                // noise level 1 => (short)  = 64 - 8 * log2(svs_expoosure ratio)
                // noise level 2 => (medium) = 64 - 8 * log2(svs_expoosure ratio*sm_expoosure ratio)
                // noise level 3 => (long)   = 64 - 8 * log2(svs_expoosure ratio*sm_expoosure ratio*lm_expoosure ratio)

                int8_t short_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( exp_write_set.exposure_ratio_short >> 6, 8, 0 ) >> 8 );
                int8_t medium_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( exp_write_set.exposure_ratio_short * exp_write_set.exposure_ratio_medium ) >> 12, 8, 0 ) >> 8 );
                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( (uint64_t)exp_write_set.exposure_ratio_short * (uint64_t)exp_write_set.exposure_ratio_medium * (uint64_t)exp_write_set.exposure_ratio_medium2 ) >> 18, 8, 0 ) >> 8 );

                if ( short_thresh < 0 ) {
                    short_thresh = 0;
                }
                if ( medium_thresh < 0 ) {
                    medium_thresh = 0;
                }
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }

#if ISP_HW_IS_MALI_C32_C52
                acamera_isp_sinter_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 + ( p_fsm->snr_thresh_contrast ) );
                acamera_isp_sinter_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, short_thresh );
                acamera_isp_sinter_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, medium_thresh );
                acamera_isp_sinter_noise_profile_noise_level_3_write( p_fsm->cmn.isp_base, long_thresh );
#endif
            } break;

            case 3: {
                // Noise level: 3:1
                // noise level 0 => ( short )  = 64:
                // noise level 1 => ( medium ) = 64 - 8 * log2( sm_expoosure ratio )
                // noise level 2 => ( long )   = 64 - 8 * log2( sm_expoosure ratio * lm_expoosure ratio )

                uint32_t MS_exp_ratio = exp_write_set.exposure_ratio_short;  // Usomething.6
                uint32_t LM_exp_ratio = exp_write_set.exposure_ratio_medium; // Usomething.6

                int8_t medium_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( MS_exp_ratio >> 6, 8, 0 ) >> 8 );
                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( ( LM_exp_ratio * MS_exp_ratio ) >> 12, 8, 0 ) >> 8 );
                if ( medium_thresh < 0 ) {
                    medium_thresh = 0;
                }
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }
#if ISP_HW_IS_MALI_C32_C52
                acamera_isp_sinter_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 + ( p_fsm->snr_thresh_contrast ) );
                acamera_isp_sinter_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, medium_thresh );
                acamera_isp_sinter_noise_profile_noise_level_2_write( p_fsm->cmn.isp_base, long_thresh );
#endif
            } break;

            case 2: {
                // Noise level : 2:1
                // noise level 0 => ( short ) = 64:
                // noise level 1 => ( long )  = 64 - 8 * log2( lm_expoosure ratio )

                int8_t long_thresh = 64 - ( 8 * acamera_log2_int_to_fixed( exp_write_set.exposure_ratio >> 6, 8, 0 ) >> 8 );
                if ( long_thresh < 0 ) {
                    long_thresh = 0;
                }
#if ISP_HW_IS_MALI_C32_C52
                acamera_isp_sinter_noise_profile_noise_level_0_write( p_fsm->cmn.isp_base, 64 + ( p_fsm->snr_thresh_contrast ) );
                acamera_isp_sinter_noise_profile_noise_level_1_write( p_fsm->cmn.isp_base, long_thresh );
#endif
            } break;

            default: {
                LOG( LOG_ERR, "Unsupported exposures number: %d", sensor_info.sensor_exp_number );
            } break;
            }
        }
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_sinter == 0 ) { // Do not update values if in manual mode.
            acamera_isp_sinter_noise_profile_global_offset_write( p_fsm->cmn.isp_base, ( uint8_t )( p_fsm->snr_thresh_master > 255 ? 255 : p_fsm->snr_thresh_master ) );
        }
    }
    dynamic_dpc_strength_calculate( p_fsm );

    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper && ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_temper == 0 ) {
        temper_strength_calculate( p_fsm );
        acamera_isp_temper_noise_profile_global_offset_write( p_fsm->cmn.isp_base, ( uint8_t )( p_fsm->tnr_thresh_master > 255 ? 255 : p_fsm->tnr_thresh_master ) );
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
        acamera_isp_temper_mot_thresh_write( p_fsm->cmn.isp_base, ( uint16_t )( p_fsm->tnr_mot_thresh > 0x3FF ? 0x3FF : p_fsm->tnr_mot_thresh ) );
        acamera_isp_temper_mot_slope_write( p_fsm->cmn.isp_base, ( uint16_t )( p_fsm->tnr_mot_slope > 0xFFF ? 0xFFF : p_fsm->tnr_mot_slope ) );
#endif
    }
}

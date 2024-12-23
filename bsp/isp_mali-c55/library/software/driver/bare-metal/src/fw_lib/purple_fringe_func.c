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
#include "general_fsm.h"
#include "acamera_firmware_api.h"
#include "purple_fringe_fsm.h"

#include "acamera_logger.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_PURPLE_FRINGE
#endif


void purple_fringe_initialize( purple_fringe_fsm_ptr_t p_fsm )
{
    // Load purple fringe radial shading LUT
    uint32_t i;
    const uint8_t *lut_pf = _GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_RADIAL_LUT );
    for ( i = 0; i < _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_RADIAL_LUT ); i++ ) {
        acamera_isp_pf_correction_shading_shading_lut_write( p_fsm->cmn.isp_base, i, lut_pf[i] );
    }

    // Initialise purple fringe radial shading centers
    const uint16_t *p_pf_radial_params = (uint16_t *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_RADIAL_PARAMS );
    acamera_isp_pf_correction_center_x_write( p_fsm->cmn.isp_base, p_pf_radial_params[0] );
    acamera_isp_pf_correction_center_y_write( p_fsm->cmn.isp_base, p_pf_radial_params[1] );
    acamera_isp_pf_correction_off_center_mult_write( p_fsm->cmn.isp_base, p_pf_radial_params[2] );

    /*
    // CALBRATION_PF_CONFIG:
    //  0 use_color_corrected_rgb (1)
    //  1 hue_strength (12)
    //  2 sat_strength (12)
    //  3 luma_strength (12)
    //  4 purple_strength (12)
    //  5 saturation_strength (8)
    //  6 sad_offset (12)
    //  7 hue_low_slope (12)
    //  8 hue_low_offset (12)
    //  9 hue_low_thresh (12)
    // 10 hue_high_slope (12)
    // 11 hue_high_offset (12)
    // 12 hue_high_thresh (12)
    // 13 sat_low_slope (12)
    // 14 sat_low_offset (12)
    // 15 sat_low_thresh (12)
    // 16 sat_high_slope (12)
    // 17 sat_high_offset (12)
    // 18 sat_high_thresh (12)
    // 19 luma1_low_slope (12)
    // 20 luma1_low_offset (12)
    // 21 luma1_low_thresh (12)
    // 22 luma1_high_slope (12)
    // 23 luma1_high_offset (12)
    // 24 luma1_high_thresh (12)
    // 25 luma2_low_slope (12)
    // 26 luma2_low_offset (12)
    // 27 luma2_low_thresh (12)
    // 28 luma2_high_slope (12)
    // 29 luma2_high_offset (12)
    // 30 luma2_high_thresh (12)
    // 31 hsl_slope (12)
    // 32 hsl_offset (12)
    // 33 hsl_thresh (12)
    // 34 debug_sel (8)
    */

    // Initialise purple fringe static parameters
    uint16_t *pf_config = (uint16_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_CONFIG );
    acamera_isp_pf_correction_use_color_corrected_rgb_write( p_fsm->cmn.isp_base, (uint8_t)pf_config[0] & 0x01 );
    acamera_isp_pf_correction_hue_strength_write( p_fsm->cmn.isp_base, pf_config[1] & 0x0fff );
    acamera_isp_pf_correction_sat_strength_write( p_fsm->cmn.isp_base, pf_config[2] & 0x0fff );
    acamera_isp_pf_correction_luma_strength_write( p_fsm->cmn.isp_base, pf_config[3] & 0x0fff );
    acamera_isp_pf_correction_purple_strength_write( p_fsm->cmn.isp_base, pf_config[4] & 0x0fff );
    acamera_isp_pf_correction_saturation_strength_write( p_fsm->cmn.isp_base, (uint8_t)pf_config[5] );
    acamera_isp_pf_correction_sad_offset_write( p_fsm->cmn.isp_base, pf_config[6] & 0x0fff );
    acamera_isp_pf_correction_hue_low_slope_write( p_fsm->cmn.isp_base, pf_config[7] & 0x0fff );
    acamera_isp_pf_correction_hue_low_offset_write( p_fsm->cmn.isp_base, pf_config[8] & 0x0fff );
    acamera_isp_pf_correction_hue_low_thresh_write( p_fsm->cmn.isp_base, pf_config[9] & 0x0fff );
    acamera_isp_pf_correction_hue_high_slope_write( p_fsm->cmn.isp_base, pf_config[10] & 0x0fff );
    acamera_isp_pf_correction_hue_high_offset_write( p_fsm->cmn.isp_base, pf_config[11] & 0x0fff );
    acamera_isp_pf_correction_hue_high_thresh_write( p_fsm->cmn.isp_base, pf_config[12] & 0x0fff );
    acamera_isp_pf_correction_sat_low_slope_write( p_fsm->cmn.isp_base, pf_config[13] & 0x0fff );
    acamera_isp_pf_correction_sat_low_offset_write( p_fsm->cmn.isp_base, pf_config[14] & 0x0fff );
    acamera_isp_pf_correction_sat_low_thresh_write( p_fsm->cmn.isp_base, pf_config[15] & 0x0fff );
    acamera_isp_pf_correction_sat_high_slope_write( p_fsm->cmn.isp_base, pf_config[16] & 0x0fff );
    acamera_isp_pf_correction_sat_high_offset_write( p_fsm->cmn.isp_base, pf_config[17] & 0x0fff );
    acamera_isp_pf_correction_sat_high_thresh_write( p_fsm->cmn.isp_base, pf_config[18] & 0x0fff );
    acamera_isp_pf_correction_luma1_low_slope_write( p_fsm->cmn.isp_base, pf_config[19] & 0x0fff );
    acamera_isp_pf_correction_luma1_low_offset_write( p_fsm->cmn.isp_base, pf_config[20] & 0x0fff );
    acamera_isp_pf_correction_luma1_low_thresh_write( p_fsm->cmn.isp_base, pf_config[21] & 0x0fff );
    acamera_isp_pf_correction_luma1_high_slope_write( p_fsm->cmn.isp_base, pf_config[22] & 0x0fff );
    acamera_isp_pf_correction_luma1_high_offset_write( p_fsm->cmn.isp_base, pf_config[23] & 0x0fff );
    acamera_isp_pf_correction_luma1_high_thresh_write( p_fsm->cmn.isp_base, pf_config[24] & 0x0fff );
    acamera_isp_pf_correction_luma2_low_slope_write( p_fsm->cmn.isp_base, pf_config[25] & 0x0fff );
    acamera_isp_pf_correction_luma2_low_offset_write( p_fsm->cmn.isp_base, pf_config[26] & 0x0fff );
    acamera_isp_pf_correction_luma2_low_thresh_write( p_fsm->cmn.isp_base, pf_config[27] & 0x0fff );
    acamera_isp_pf_correction_luma2_high_slope_write( p_fsm->cmn.isp_base, pf_config[28] & 0x0fff );
    acamera_isp_pf_correction_luma2_high_offset_write( p_fsm->cmn.isp_base, pf_config[29] & 0x0fff );
    acamera_isp_pf_correction_luma2_high_thresh_write( p_fsm->cmn.isp_base, pf_config[30] & 0x0fff );
    acamera_isp_pf_correction_hsl_slope_write( p_fsm->cmn.isp_base, pf_config[31] & 0x0fff );
    acamera_isp_pf_correction_hsl_offset_write( p_fsm->cmn.isp_base, pf_config[32] & 0x0fff );
    acamera_isp_pf_correction_hsl_thresh_write( p_fsm->cmn.isp_base, pf_config[33] & 0x0fff );
    acamera_isp_pf_correction_debug_sel_write( p_fsm->cmn.isp_base, (uint8_t)pf_config[34] );
}

void purple_fringe_update( purple_fringe_fsm_ptr_t p_fsm )
{
    int32_t total_gain = 0;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );
    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    // Modulation of sad_thresh and sad_slope
    acamera_isp_pf_correction_sad_thresh_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_SAD_THRESH ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_SAD_THRESH ) ) );
    acamera_isp_pf_correction_sad_slope_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_SAD_SLOPE ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_PF_SAD_SLOPE ) ) );
}

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
#include "acamera_math.h"
#include "acamera_command_api.h"
#include "sharpening_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SHARPENING
#endif

#define VIDEO_OUT_WIDTH 10


void sharpening_initialize( sharpening_fsm_t *p_fsm )
{
    // CALIBRATION_SHARP_FR/DS1_CONFIG:
    //  0 sharpen/alpha undershoot
    //  1 sharpen/clip_str_min
    //  2 sharpen/clip_str_max
    //  3 sharpen/luma_thresh_low
    //  4 sharpen/luma_thresh_high
    //  5 sharpen/luma_slope_low
    //  6 sharpen/luma_slope_high
    uint16_t *sharp_config = (uint16_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_FR_CONFIG );
    acamera_isp_fr_sharpen_alpha_undershoot_write( p_fsm->cmn.isp_base, (uint8_t)sharp_config[0] );
    acamera_isp_fr_sharpen_clip_str_min_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[1] );
    acamera_isp_fr_sharpen_clip_str_max_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[2] );
    acamera_isp_fr_sharpen_luma_thresh_low_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[3] );
    acamera_isp_fr_sharpen_luma_thresh_high_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[4] );
    acamera_isp_fr_sharpen_luma_slope_low_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[5] );
    acamera_isp_fr_sharpen_luma_slope_high_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[6] );
#if ISP_HAS_DS1
    sharp_config = (uint16_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_DS1_CONFIG );
    acamera_isp_ds1_sharpen_alpha_undershoot_write( p_fsm->cmn.isp_base, (uint8_t)sharp_config[0] );
    acamera_isp_ds1_sharpen_clip_str_min_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[1] );
    acamera_isp_ds1_sharpen_clip_str_max_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[2] );
    acamera_isp_ds1_sharpen_luma_thresh_low_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[3] );
    acamera_isp_ds1_sharpen_luma_thresh_high_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[4] );
    acamera_isp_ds1_sharpen_luma_slope_low_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[5] );
    acamera_isp_ds1_sharpen_luma_slope_high_write( p_fsm->cmn.isp_base, (uint16_t)sharp_config[6] );
#endif
}


void sharpening_update( sharpening_fsm_t *p_fsm )
{
    int32_t total_gain = 0;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_CMOS_TOTAL_GAIN, NULL, 0, &total_gain, sizeof( total_gain ) );

    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );
    uint16_t alt_d, alt_ud;
    uint16_t alt_du = 0;

    const modulation_entry_t *sharp_alt_d_table_ptr;
    const modulation_entry_t *sharp_alt_ud_table_ptr;
    modulation_entry_t *sharp_alt_du_table_ptr;

#if ISP_WDR_SWITCH
    uint32_t sharp_alt_d_idx = CALIBRATION_SHARP_ALT_D;
    uint32_t sharp_alt_ud_idx = CALIBRATION_SHARP_ALT_UD;
    sharp_alt_d_table_ptr = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_d_idx );
    sharp_alt_ud_table_ptr = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_ud_idx );
    uint32_t sharp_alt_du_idx = CALIBRATION_SHARP_ALT_DU;
    sharp_alt_du_table_ptr = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_du_idx );

#else

    uint32_t sharp_alt_du_idx = CALIBRATION_SHARP_ALT_DU;
    sharp_alt_du_table_ptr = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_du_idx );
    sharp_alt_d_table_ptr = ( _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_ALT_D ) );
    sharp_alt_ud_table_ptr = ( _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_ALT_UD ) );

#endif // ISP_WDR_SWITCH

    // Do not update values if manual mode.
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_demosaic == 0 ) {
#if ISP_WDR_SWITCH
        // Use LUTs for modulation instead!
        alt_d = acamera_calc_modulation_u16( log2_gain, sharp_alt_d_table_ptr, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_d_idx ) );
#else
        alt_d = acamera_calc_modulation_u16( log2_gain, sharp_alt_d_table_ptr, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_ALT_D ) );
#endif

        alt_du = acamera_calc_modulation_u16( log2_gain, sharp_alt_du_table_ptr, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_du_idx ) );
        alt_d = ( alt_d * p_fsm->sharpening_mult ) / 128;

#if ISP_WDR_SWITCH
        // Use LUTs for modulation instead!
        alt_ud = acamera_calc_modulation_u16( log2_gain, sharp_alt_ud_table_ptr, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), sharp_alt_ud_idx ) );
#else
        alt_ud = acamera_calc_modulation_u16( log2_gain, sharp_alt_ud_table_ptr, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARP_ALT_UD ) );
#endif
        alt_ud = ( alt_ud * p_fsm->sharpening_mult ) / 128;

#if ISP_HW_IS_MALI_C32_C52
        if ( alt_d >= ( 1 << ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_D_DATASIZE ) ) {
            alt_d = ( 1 << ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_D_DATASIZE ) - 1;
        }
        if ( alt_ud >= ( 1 << ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_UD_DATASIZE ) ) {
            alt_ud = ( 1 << ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_UD_DATASIZE ) - 1;
        }

        acamera_isp_demosaic_rgb_sharp_alt_d_write( p_fsm->cmn.isp_base, alt_d );
        acamera_isp_demosaic_rgb_sharp_alt_ud_write( p_fsm->cmn.isp_base, alt_ud );
#endif

        acamera_isp_demosaic_rgb_sharp_alt_ld_write( p_fsm->cmn.isp_base, alt_d );
        acamera_isp_demosaic_rgb_sharp_alt_ldu_write( p_fsm->cmn.isp_base, alt_du );

        acamera_isp_demosaic_rgb_sharp_alt_lu_write( p_fsm->cmn.isp_base, alt_ud );

        int tbl_inx = CALIBRATION_DEMOSAIC_UU_SLOPE;
        acamera_isp_demosaic_rgb_uu_slope_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ) ) );

        tbl_inx = CALIBRATION_DEMOSAIC_UU_SH_SLOPE;
        acamera_isp_demosaic_rgb_uu_sh_slope_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ) ) );
    
        tbl_inx = CALIBRATION_DEMOSAIC_FC_SLOPE;
        acamera_isp_demosaic_rgb_fc_slope_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), tbl_inx ) ) );
    }

    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_sharpen == 0 ) {
        const modulation_entry_t *sharpen_fr_table = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARPEN_FR );
        acamera_isp_fr_sharpen_strength_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, sharpen_fr_table, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARPEN_FR ) ) );

#if ISP_HAS_DS1
        const modulation_entry_t *sharpen_ds1_table = _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARPEN_DS1 );
        acamera_isp_ds1_sharpen_strength_write( p_fsm->cmn.isp_base, acamera_calc_modulation_u16( log2_gain, sharpen_ds1_table, _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHARPEN_DS1 ) ) );
#endif // ISP_HAS_DS1
    }
}

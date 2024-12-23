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
#include "acamera_isp_config.h"
#include "system_timer.h"

#include "acamera_logger.h"
#include "sensor_fsm.h"

#include "acamera.h"

#if USER_MODULE
#include "sbuf.h"
#endif

typedef struct {
    uint16_t active_width;
    uint16_t active_height;
    uint16_t total_width;
    uint16_t total_height;
    uint16_t offset_x;
    uint16_t offset_y;
    uint16_t h_front_porch;
    uint16_t v_front_porch;
    uint16_t h_sync_width;
    uint16_t v_sync_width;
} dvi_sync_param_t;


#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SENSOR
#endif

void sensor_init_output( sensor_fsm_ptr_t p_fsm, int mode )
{
    const sensor_param_t *param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
    if ( ( mode != 720 ) && ( mode != 1080 ) ) {
        if ( param->active.height >= 1080 ) {
            mode = 1080;
        } else {
            mode = 720;
        }
    }

    // decrease output mode to 720p if active_height < mode
    if ( mode > param->active.height )
        mode = 720;

    p_fsm->isp_output_mode = mode;
}

///////////////////////////////////////////////////////////////////////////////

uint32_t sensor_boot_init( sensor_fsm_ptr_t p_fsm )
{
    ACAMERA_FSM2CTX_PTR( p_fsm )->settings.sensor_init( &p_fsm->sensor_ctx, &p_fsm->ctrl );

#if USER_MODULE
    uint32_t idx = 0;
    sensor_param_t *param = (sensor_param_t *)p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
    struct sensor_info ksensor_info;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_KSENSOR_INFO, NULL, 0, &ksensor_info, sizeof( ksensor_info ) );

    param->modes_num = ksensor_info.modes_num;
    if ( param->modes_num > ISP_MAX_SENSOR_MODES ) {
        param->modes_num = ISP_MAX_SENSOR_MODES;
    }

    for ( idx = 0; idx < param->modes_num; idx++ ) {
        param->modes_table[idx] = ksensor_info.modes[idx];

        LOG( LOG_INFO, "Sensor_mode[%d]: wdr_mode: %d, exp: %d.", idx,
             param->modes_table[idx].wdr_mode,
             param->modes_table[idx].exposures );
    }
#endif

    return 0;
}

void sensor_hw_init( sensor_fsm_ptr_t p_fsm )
{
#if FW_DO_INITIALIZATION
    acamera_isp_input_port_mode_request_write( p_fsm->cmn.isp_base, ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_SAFE_STOP ); // urgent stop
#endif                                                                                                               //FW_DO_INITIALIZATION

    // 1): set sensor to preset_mode as required.
    p_fsm->ctrl.stop_streaming( p_fsm->sensor_ctx );
    p_fsm->ctrl.set_mode( p_fsm->sensor_ctx, p_fsm->preset_mode );
    p_fsm->ctrl.disable_sensor_isp( p_fsm->sensor_ctx );

    if ( p_fsm->is_streaming ) {
        p_fsm->ctrl.start_streaming( p_fsm->sensor_ctx );
    }

    // 2): set to wdr_mode through general router (wdr_mode changed in sensor param in 1st step).
    const sensor_param_t *param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );

    fsm_param_set_wdr_param_t set_wdr_param;
    set_wdr_param.wdr_mode = param->modes_table[param->mode].wdr_mode;
    set_wdr_param.exp_number = param->modes_table[param->mode].exposures;
    acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_WDR_MODE, &set_wdr_param, sizeof( set_wdr_param ) );

    // 3): Init or update the calibration data.
    acamera_init_calibrations( ACAMERA_FSM2CTX_PTR( p_fsm ) );

    // 4). update new settings to ISP if necessary
    acamera_update_cur_settings_to_isp( p_fsm->cmn.ctx_id );
}

void sensor_sw_init( sensor_fsm_ptr_t p_fsm )
{
    const sensor_param_t *param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );

#if FW_DO_INITIALIZATION
    /* sensor resolution */
    acamera_isp_top_active_width_write( p_fsm->cmn.isp_base, param->active.width );
    acamera_isp_top_active_height_write( p_fsm->cmn.isp_base, param->active.height );

#if ISP_HW_IS_MALI_C32_C52
    acamera_isp_metering_af_active_width_write( p_fsm->cmn.isp_base, param->active.width );
    acamera_isp_metering_af_active_height_write( p_fsm->cmn.isp_base, param->active.height );

    acamera_isp_lumvar_active_width_write( p_fsm->cmn.isp_base, param->active.width );
    acamera_isp_lumvar_active_height_write( p_fsm->cmn.isp_base, param->active.height );

    acamera_isp_input_port_hc_size1_write( p_fsm->cmn.isp_base, param->active.width );
#else
    // Configure RGGB start
    acamera_isp_top_rggb_start_write( p_fsm->cmn.isp_base, param->rggb_start );
#endif
    acamera_isp_input_port_hc_size0_write( p_fsm->cmn.isp_base, param->active.width );
    acamera_isp_input_port_vc_size_write( p_fsm->cmn.isp_base, param->active.height );

    sensor_init_output( p_fsm, p_fsm->isp_output_mode );
#endif //FW_DO_INITIALIZATION

    sensor_tpg_start_stop_streaming( p_fsm );

    acamera_isp_input_port_mode_request_write( p_fsm->cmn.isp_base, ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_SAFE_START );

    sensor_update_black( p_fsm );

    LOG( LOG_NOTICE, "Sensor initialization is complete, ID 0x%04X resolution %dx%d", p_fsm->ctrl.get_id( p_fsm->sensor_ctx ), param->active.width, param->active.height );
}

void sensor_update_black( sensor_fsm_ptr_t p_fsm )
{
    int32_t stub = 0;
    exposure_set_t exp;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_FRAME_EXPOSURE_SET, &stub, sizeof( stub ), &exp, sizeof( exp ) );

    uint16_t again_log2 = ( uint16_t )( exp.info.again_log2 >> ( LOG2_GAIN_SHIFT - 5 ) ); // makes again in format log2(gain)*32

    uint32_t idx_r = CALIBRATION_BLACK_LEVEL_R;
    uint32_t idx_b = CALIBRATION_BLACK_LEVEL_B;
    uint32_t idx_gr = CALIBRATION_BLACK_LEVEL_GR;
    uint32_t idx_gb = CALIBRATION_BLACK_LEVEL_GB;
    uint32_t r = acamera_calc_modulation_u16( again_log2, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_r ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_r ) );
    uint32_t b = acamera_calc_modulation_u16( again_log2, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_b ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_b ) );
    uint32_t gr = acamera_calc_modulation_u16( again_log2, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gr ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gr ) );
    uint32_t gb = acamera_calc_modulation_u16( again_log2, _GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gb ), _GET_ROWS( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gb ) );

    uint32_t wdr_mode = 0;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_WDR_MODE, NULL, 0, &wdr_mode, sizeof( wdr_mode ) );

    // Update black-level FSM variable with average black level.
    p_fsm->black_level = ( r + b + gr + gb ) >> 2;

    // Default black level shift and value
    uint32_t black_level_shift = BLACK_LEVEL_SHIFT_DG;
    uint32_t black_level = p_fsm->black_level << black_level_shift;

    if ( wdr_mode == WDR_MODE_FS_LIN ) {
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_frame_stitch == 0 && ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr ) ) {
            acamera_isp_frame_stitch_black_level_long_write( p_fsm->cmn.isp_base, p_fsm->black_level );
            acamera_isp_frame_stitch_black_level_medium_write( p_fsm->cmn.isp_base, p_fsm->black_level );
#if ISP_HW_IS_MALI_C32_C52
            acamera_isp_frame_stitch_black_level_short_write( p_fsm->cmn.isp_base, p_fsm->black_level );
            acamera_isp_frame_stitch_black_level_very_short_write( p_fsm->cmn.isp_base, p_fsm->black_level );
#endif
        }

        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_black_level == 0 ) {
            acamera_isp_sensor_offset_pre_shading_offset_00_write( p_fsm->cmn.isp_base, (uint32_t)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_r )->y << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_01_write( p_fsm->cmn.isp_base, (uint32_t)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gr )->y << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_10_write( p_fsm->cmn.isp_base, (uint32_t)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_gb )->y << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_11_write( p_fsm->cmn.isp_base, (uint32_t)_GET_MOD_ENTRY16_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), idx_b )->y << BLACK_LEVEL_SHIFT_WB );
        }

    } else {
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_black_level == 0 ) {
            acamera_isp_sensor_offset_pre_shading_offset_00_write( p_fsm->cmn.isp_base, r << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_01_write( p_fsm->cmn.isp_base, gr << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_10_write( p_fsm->cmn.isp_base, gb << BLACK_LEVEL_SHIFT_WB );
            acamera_isp_sensor_offset_pre_shading_offset_11_write( p_fsm->cmn.isp_base, b << BLACK_LEVEL_SHIFT_WB );
        }
    }
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_manual_black_level == 0 ) {
        acamera_isp_digital_gain_offset_write( p_fsm->cmn.isp_base, black_level );

#if ISP_HW_IS_MALI_C32_C52
        // FE/BE and FS blackLevel set to the average of offset blackLevel.
        acamera_isp_sqrt_black_level_in_write( p_fsm->cmn.isp_base, black_level );
        acamera_isp_square_be_black_level_out_write( p_fsm->cmn.isp_base, black_level );
#else
        /** Calculation of black level normalization in sqrt and square domains as per below formula :
            sqrt_norm_numerator = (2^sqrt_dw_out-1)^2 * 2^(sqrt_dw_in - 2*sqrt_dw_out);
            sqrt_norm_denominator = 2^sqrt_dw_in-1 + 2*sqrt((2^sqrt_dw_in - 1 - sqrt_bl_in)*sqrt_bl_in);
            sqrt_norm = (sqrt_norm_numerator/sqrt_norm_denominator)
            sqrt_bl_out = round(sqrt(sqrt_norm * sqrt_bl_in * 2^(2*sqrt_dw_out-sqrt_dw_in)));
            sq_norm = 1/sqrt_norm;
            // Alignment of normalisation parameters to allocated bits
            sqrt_norm = round(sqrt_norm*(2^16-1));
            sq_norm = round(sq_norm*(2^16-1));
        **/

        const uint32_t sqrt_bl_in = black_level;
        const uint32_t temp2P12 = ( 1 << 12 ) - 1;
        const uint32_t temp2P20 = ( 1 << 20 ) - 1;
        const uint32_t numerator = temp2P12 * temp2P12;
        const uint32_t denominator = temp2P20 + acamera_sqrt64( ( uint64_t )( temp2P20 - sqrt_bl_in ) * sqrt_bl_in * 4 );

        const uint32_t sqrt_norm_reg = ( (uint64_t)numerator << 12 ) / denominator;
        const uint16_t sqrt_bl_out = acamera_sqrt32( ( uint32_t )( ( (uint64_t)sqrt_norm_reg * sqrt_bl_in ) >> 12 ) );
        // Square block in/out are fed from out/in of sqrt block
        const uint16_t square_bl_in = sqrt_bl_out;
        const uint32_t square_bl_out = sqrt_bl_in;
        const uint32_t square_norm_reg = ( (uint64_t)denominator << 20 ) / numerator;

        acamera_isp_sqrt_black_level_in_write( p_fsm->cmn.isp_base, sqrt_bl_in );
        acamera_isp_sqrt_black_level_out_write( p_fsm->cmn.isp_base, sqrt_bl_out );
        acamera_isp_sqrt_normalization_write( p_fsm->cmn.isp_base, sqrt_norm_reg );

        acamera_isp_square_be_black_level_in_write( p_fsm->cmn.isp_base, square_bl_in );
        acamera_isp_square_be_black_level_out_write( p_fsm->cmn.isp_base, square_bl_out );
        acamera_isp_square_be_normalization_write( p_fsm->cmn.isp_base, square_norm_reg );
#endif
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr ) {
            acamera_isp_frame_stitch_black_level_out_write( p_fsm->cmn.isp_base, black_level );
        }
    }
}

uint32_t sensor_get_lines_second( sensor_fsm_ptr_t p_fsm )
{
    const sensor_param_t *param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
    return param->lines_per_second;
}

void sensor_tpg_start_stop_streaming( sensor_fsm_ptr_t p_fsm )
{
    const sensor_param_t *param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
    if ( !param->is_tpg ) {
        return;
    }

#if !ISP_HW_IS_MALI_C32_C52
    // Calculate hblank and vblank for TPG generator to match TPG sensor FPS
    const uint64_t pixel_clock = ISP_VCLK_FREQ_MHZ * 1000 * 1000;
    const uint32_t hblank = ACAMERA_ISP_INPUT_PORT_GEN_HBLANK_DEFAULT * 4;
    uint32_t vblank = ( ( pixel_clock * 256 ) / ( ( param->modes_table[param->mode].resolution.width + hblank ) * param->modes_table[param->mode].fps ) );
    vblank = ( vblank < param->modes_table[param->mode].resolution.height ) ? ACAMERA_ISP_INPUT_PORT_GEN_VBLANK_DEFAULT : vblank - param->modes_table[param->mode].resolution.height;

    acamera_isp_input_port_gen_hblank_write( p_fsm->cmn.isp_base, hblank );
    acamera_isp_input_port_gen_vblank_write( p_fsm->cmn.isp_base, vblank );

    acamera_isp_input_port_gen_video_multi_write( p_fsm->cmn.isp_base, p_fsm->is_streaming );
    acamera_isp_input_port_gen_video_on_write( p_fsm->cmn.isp_base, p_fsm->is_streaming );
#endif

#if defined( TSYSTEM ) && defined( TEST_PATTERN_ENABLE_ID ) && defined( TEST_PATTERN_MODE_ID )
    uint32_t ret_val;
    acamera_command( p_fsm->cmn.ctx_id, TSYSTEM, TEST_PATTERN_ENABLE_ID, p_fsm->is_streaming ? ON : OFF, COMMAND_SET, &ret_val );
    acamera_command( p_fsm->cmn.ctx_id, TSYSTEM, TEST_PATTERN_MODE_ID, param->modes_table[param->mode].tpg_mode, COMMAND_SET, &ret_val );
#endif
}

void sensor_deinit( sensor_fsm_ptr_t p_fsm )
{
    if ( p_fsm->ctrl.stop_streaming ) {
        p_fsm->ctrl.stop_streaming( p_fsm->sensor_ctx );
    } else {
        LOG( LOG_ERR, "Error. Sensor API 'stop_streaming' is not initialized (NULL).\n" );
    }

    p_fsm->is_streaming = 0;

    sensor_tpg_start_stop_streaming( p_fsm );

    ACAMERA_FSM2CTX_PTR( p_fsm )->settings.sensor_deinit( p_fsm->sensor_ctx );
}

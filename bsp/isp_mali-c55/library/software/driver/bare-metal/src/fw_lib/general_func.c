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
#include "acamera.h"
#include "acamera_command_api.h"
#include "acamera_math.h"

#include "isp_config_seq.h"
#include "acamera_sbus_api.h"

#include "acamera_fr_gamma_rgb_mem_config.h"

#if ISP_HAS_DS1
#include "acamera_ds1_gamma_rgb_mem_config.h"
#endif

#include "acamera_isp_config.h"

#include "general_fsm.h"

#if ISP_HW_IS_MALI_C32_C52
#include "acamera_ca_correction_filter_mem_config.h"
#include "acamera_ca_correction_mesh_mem_config.h"

#include "acamera_lut3d_mem_config.h"

#if defined( CALIBRATION_SHADING_RADIAL_R )
#include "acamera_radial_shading_mem_config.h"
#endif

#endif

#if defined( CALIBRATION_DECOMPANDER0_MEM )
#include "acamera_decompander0_mem_config.h"
#endif

#if defined( CALIBRATION_DECOMPANDER1_MEM )
#include "acamera_decompander1_mem_config.h"
#endif

#if ISP_HAS_FPGA_WRAPPER
#include "acamera_fpga_config.h"
#endif

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_GENERAL
#endif

#define CAC_MEM_LUT_LEN 4096

#define BIT_SHIFT( v, s ) ( ( s > 0 ) ? ( v << s ) : ( v >> ( -s ) ) )

typedef uint16_t( CAC_MEM_LUT_T )[][10];

#define FRAME_ALIGN( val, align ) ( ( val ) + (align)-1 ) & ~( (align)-1 )

#define TEMPER4_MAX_DMA_BPP 20

#if GENERAL_TEMPER_ENABLED
static int general_temper_init( general_fsm_ptr_t p_fsm );
static int general_temper_exit( general_fsm_ptr_t p_fsm );
static int general_temper_configure( general_fsm_ptr_t p_fsm );
#endif

static int32_t signed_bitshift( int32_t val, int32_t shift )
{
    int32_t out_val = 0;
    uint8_t val_sign = val < 0;

    val = ( val > 0 ) ? val : -val;

    if ( val_sign ) {
        out_val = -BIT_SHIFT( val, shift );
    } else {
        out_val = BIT_SHIFT( val, shift );
    }

    return out_val;
}

#if ISP_HW_IS_MALI_C32_C52
static void general_cac_memory_lut_reload( general_fsm_ptr_t p_fsm )
{
    uint32_t cac_mem_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CA_CORRECTION_MEM );
    const CAC_MEM_LUT_T *p_calibration_ca_model = (const CAC_MEM_LUT_T *)_GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CA_CORRECTION_MEM );
    const uint16_t *p_calibration_cac_cfg = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CA_CORRECTION );

    uint16_t calibration_ca_min_correction = p_calibration_cac_cfg[0];
    uint16_t calibration_ca_mesh_width = p_calibration_cac_cfg[1];
    uint16_t calibration_ca_mesh_height = p_calibration_cac_cfg[2];

    uint8_t cfa_pattern = acamera_isp_top_cfa_pattern_read( p_fsm->cmn.isp_base );

    uint8_t line_offset = calibration_ca_mesh_width;
    uint16_t plane_offset = calibration_ca_mesh_width * calibration_ca_mesh_height;

    int32_t ca_model[10] = {0};
    int32_t mesh_vars[9] = {0};
    uint16_t component;
    uint8_t term;
    uint8_t plane_count;
    uint32_t plane_offset_val;
    uint8_t x;
    uint8_t y;
    uint16_t vh_shift;
    uint16_t lut_index = 0;

    if ( CAC_MEM_LUT_LEN != ( ACAMERA_CA_CORRECTION_MESH_MEM_SIZE >> 2 ) ) {
        LOG( LOG_ERR, "cac_mem_lut size mismatch, hw_size: %d, expected: %d.", ( ACAMERA_CA_CORRECTION_MESH_MEM_SIZE >> 2 ), CAC_MEM_LUT_LEN );
        return;
    }

    // Configure mesh size and reset the table.
    acamera_isp_ca_correction_mesh_scale_write( p_fsm->cmn.isp_base, 1 );
    acamera_isp_ca_correction_mesh_width_write( p_fsm->cmn.isp_base, calibration_ca_mesh_width );
    acamera_isp_ca_correction_mesh_height_write( p_fsm->cmn.isp_base, calibration_ca_mesh_height );
    acamera_isp_ca_correction_line_offset_write( p_fsm->cmn.isp_base, calibration_ca_mesh_width );
    acamera_isp_ca_correction_plane_offset_write( p_fsm->cmn.isp_base, calibration_ca_mesh_width * calibration_ca_mesh_height );

    // Reset to 0
    for ( lut_index = 0; lut_index < CAC_MEM_LUT_LEN; lut_index++ ) {
        acamera_ca_correction_mesh_mem_array_data_write( p_fsm->cmn.isp_base, lut_index, 0 );
    }

    switch ( cfa_pattern ) {
    case 0: // RGGB
        plane_count = 2;
        break;
    case 1: // RCCC
        plane_count = 1;
        break;
    default: // RGBIr
        plane_count = 3;
        break;
    }

    LOG( LOG_INFO, "cfa_pattern: %d, plane_count: %d, cac_mem_len: %d", cfa_pattern, plane_count, cac_mem_len );

    for ( component = 0; component < plane_count * 2; component++ ) {
        // Generate s15.0 ca_model (int32) from u16.0 ca_model_u (uint16)
        for ( term = 0; term < 10; term++ ) {
            if ( ( *p_calibration_ca_model )[component][term] < 32768 )
                ca_model[term] = ( *p_calibration_ca_model )[component][term];
            else
                ca_model[term] = ( *p_calibration_ca_model )[component][term] - 65536;
        }

        plane_offset_val = plane_offset * ( component >> 1 );
        vh_shift = ( component % 2 ) * 8;

        for ( x = 0; x < calibration_ca_mesh_width; x++ ) {
            for ( y = 0; y < calibration_ca_mesh_height; y++ ) {
                int32_t z32 = 0;
                int16_t z16 = 0;
                int16_t z_norm = 0;
                int32_t product = 0;
                uint8_t z_sign = 0;
                uint32_t zu32 = 0;
                uint8_t lut_shift = 0;
                uint32_t old_value = 0;
                uint32_t new_value = 0;

                // Apply model - this polynomial:
                // z = b0*x^3 + b1*x^2*y + b2*x*y^2 + b3*y^3 + b4*x^2 + b5*x*y + b6*y^2 + b7*x + b8*y +b9

                // mesh_vars(:,1:4) are u18.0, coeffs(1:4) are s-10.23 so product is s8.23
                // mesh_vars(:,5:7) are u12.0, coeffs(5:7) are s-3.17 so product is s9.17
                // mesh_vars(:,8:9) are u6.0, coeffs(8:9) are s2.11 so product is s8.11
                // mesh_vars(:,10) are u1.0, coeffs(10) is s6.5 so product is s6.5

                mesh_vars[8] = y;
                mesh_vars[7] = x;
                mesh_vars[6] = y * y;
                mesh_vars[5] = x * y;
                mesh_vars[4] = x * x;
                mesh_vars[3] = mesh_vars[6] * y;
                mesh_vars[2] = mesh_vars[5] * y;
                mesh_vars[1] = mesh_vars[4] * y;
                mesh_vars[0] = mesh_vars[4] * x;

                for ( term = 0; term < 4; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    product = signed_bitshift( product, -4 );
                    z32 = z32 + product;
                }

                // Drop precision to match next set of coefficients
                z32 = signed_bitshift( z32, -2 );

                for ( term = 4; term < 7; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    z32 = z32 + product;
                }

                // Drop precision to match next set of coefficients
                z32 = signed_bitshift( z32, -6 );

                for ( term = 7; term < 9; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    z32 = z32 + product;
                }

                // Drop precision to match error model (precision of coeff 10 is also set to match this)
                z32 = signed_bitshift( z32, -4 );

                z32 = z32 + ca_model[9];

                // Clip to s4.7 range
                z32 = MAX( z32, -2048 );
                z32 = MIN( z32, 2047 );

                // Cast z from int32 to int16 here. Its size is only 12 bits.
                z16 = (int16_t)z32;

                // Apply periodic linear approximation of error model
                // z = z - 0.1*sin(pi*z)
                // Approximation between is z = z+0.25z_norm

                // z_norm is equivalent position of z within linear range of +/-0.5
                if ( ( z16 + 128 ) < 0 ) {
                    z_norm = ( ( z16 + 128 ) % 256 ) - 128;
                    z_norm = 256 + z_norm;
                } else {
                    z_norm = ( ( z16 + 128 ) % 256 ) - 128;
                }

                if ( z_norm < -64 ) {
                    z_norm = -128 - z_norm;
                } else if ( z_norm > 64 ) {
                    z_norm = 128 - z_norm;
                }

                // Shift by -2 is like multiplying by 0.25z_norm
                z_norm = signed_bitshift( z_norm, -2 );
                z16 = z16 - z_norm;

                z16 = signed_bitshift( z16, -2 );

                // Now manipulate z to the format of the mesh (u4.4, 2s complement)

                z_sign = z16 < 0;

                // Round z to 4 bits precision
                z16 = ( z16 > 0 ) ? z16 : -z16;
                z16 = ( z16 % 2 ) + ( z16 >> 1 );

                // Apply ca_min_correction (clip small corrections to 0)
                if ( z16 <= calibration_ca_min_correction ) {
                    z_sign = 0;
                    z16 = 0;
                }

                if ( z16 > 127 ) {
                    z16 = 127;
                }

                // Convert to 2s complement
                if ( z_sign ) {
                    z16 = 256 - z16;
                }

                // Cast z from int16 to uint32 here
                zu32 = (uint32_t)z16;

                // Work out which LUT entry this z value should be placed in
                lut_index = plane_offset_val + y * line_offset + x;

                // Shift increases by 16 bits for odd entries
                lut_shift = vh_shift + ( lut_index % 2 ) * 16;

                // Find location within half sized array (2 blocks per register)
                lut_index = ( lut_index >> 1 );

                // Clip to size of LUT (in case of error)
                lut_index = lut_index & 4095;

                old_value = acamera_ca_correction_mesh_mem_array_data_read( p_fsm->cmn.isp_base, lut_index );
                new_value = old_value + BIT_SHIFT( zu32, lut_shift );
                acamera_ca_correction_mesh_mem_array_data_write( p_fsm->cmn.isp_base, lut_index, new_value );
            }
        }
    }

    acamera_isp_ca_correction_mesh_reload_write( p_fsm->cmn.isp_base, 0 );
    acamera_isp_ca_correction_mesh_reload_write( p_fsm->cmn.isp_base, 1 );
    acamera_isp_ca_correction_mesh_reload_write( p_fsm->cmn.isp_base, 0 );

    return;
}
#endif

void general_default_gamma_update( general_fsm_ptr_t p_fsm )
{
    const uint16_t *gamma_lut = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA );
    const uint32_t gamma_lut_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA );

    uint32_t exp_gamma_size = ACAMERA_FR_GAMMA_RGB_MEM_SIZE / ( ACAMERA_FR_GAMMA_RGB_MEM_ARRAY_DATA_DATASIZE >> 3 );

    if ( gamma_lut_len != exp_gamma_size )
        LOG( LOG_ERR, "Wrong elements number in gamma_rgb -> current size %d but expected %d.", (int)gamma_lut_len, (int)exp_gamma_size );
    int i = 0;
    for ( i = 0; i < gamma_lut_len; i++ ) {
        acamera_fr_gamma_rgb_mem_array_data_write( p_fsm->cmn.isp_base, i, gamma_lut[i] );
#if ISP_HAS_DS1
        acamera_ds1_gamma_rgb_mem_array_data_write( p_fsm->cmn.isp_base, i, gamma_lut[i] );
#endif
    }
}

void acamera_reload_isp_calibratons( general_fsm_ptr_t p_fsm )
{
    int32_t i = 0;
    (void)i; // No unused warning

// Temp lut to test new FS module
#if ISP_WDR_SWITCH == 0
    uint32_t mode = p_fsm->wdr_mode;
    if ( mode != WDR_MODE_LINEAR ) {
        LOG( LOG_ERR, "Failed to apply wdr switch. Firmware doesn't support WDR mode." );
    }
#endif

    general_default_gamma_update( p_fsm );

#if ISP_HW_IS_MALI_C32_C52
    const uint8_t *demosaic_lut = _GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DEMOSAIC );

    for ( i = 0; i < _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DEMOSAIC ); i++ ) {
        acamera_isp_demosaic_rgb_noise_profile_lut_weight_lut_write( p_fsm->cmn.isp_base, i, demosaic_lut[i] );
    }
#endif

    const uint8_t *np_lut_wdr = _GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_WDR_NP_LUT );
    const uint8_t *np_lut = _GET_UCHAR_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_NOISE_PROFILE );

    for ( i = 0; i < _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_NOISE_PROFILE ); i++ ) {
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.sinter ) {
            acamera_isp_sinter_noise_profile_lut_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut[i] );
        }
        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper ) {
            acamera_isp_temper_noise_profile_lut_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut[i] );
        }

        if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.wdr ) {
#if ISP_HW_IS_MALI_C32_C52
            acamera_isp_frame_stitch_np_lut_vs_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut_wdr[i] );
            acamera_isp_frame_stitch_np_lut_s_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut_wdr[i] );
            acamera_isp_frame_stitch_np_lut_m_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut_wdr[i] );
#endif
            acamera_isp_frame_stitch_np_lut_l_weight_lut_write( p_fsm->cmn.isp_base, i, np_lut_wdr[i] );
        }
    }

#if ISP_HAS_COLOR_MATRIX_FSM
    acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_SHADING_MESH_RELOAD, NULL, 0 );

    {
        // This wdr_switch is called when resolution change happens.
        // We need to reload ccm matrix in the case when several set of
        // settings are supported for each resolution.
        acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_CCM_CHANGE, NULL, 0 );
    }
#endif

#if defined( ISP_HAS_IRIDIX_FSM ) || defined( ISP_HAS_IRIDIX8_FSM ) || defined( ISP_HAS_IRIDIX_ACAMERA_FSM )
    acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_IRIDIX_INIT, NULL, 0 );
#endif

#if ISP_HW_IS_MALI_C32_C52
    uint32_t ca_filter_mem_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CA_FILTER_MEM );
    const uint32_t *p_ca_filter_mem = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CA_FILTER_MEM );
    LOG( LOG_INFO, "ca_filter_mem_len: %d", ca_filter_mem_len );
    for ( i = 0; i < ca_filter_mem_len; i++ ) {
        acamera_ca_correction_filter_mem_array_data_write( p_fsm->cmn.isp_base, i, p_ca_filter_mem[i] );
    }

    if ( acamera_isp_isp_global_parameter_status_cac_read( p_fsm->cmn.isp_base ) == 0 ) // Present on 0
        general_cac_memory_lut_reload( p_fsm );

    if ( acamera_isp_isp_global_parameter_status_lut_3d_read( p_fsm->cmn.isp_base ) == 0 ) { // Present on 0
        uint32_t lut3d_mem_len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_LUT3D_MEM );
        const uint32_t *p_lut3d_mem = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_LUT3D_MEM );
        LOG( LOG_INFO, "lut3d_mem_len: %d", lut3d_mem_len );
        for ( i = 0; i < lut3d_mem_len; i++ ) {
            acamera_lut3d_mem_array_data_write( p_fsm->cmn.isp_base, i, p_lut3d_mem[i] );
        }
    }
#endif

#if defined( CALIBRATION_DECOMPANDER0_MEM )
    for ( i = 0; i < _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DECOMPANDER0_MEM ); i++ ) {
        acamera_decompander0_mem_array_data_write( p_fsm->cmn.isp_base, i, _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DECOMPANDER0_MEM )[i] );
    }
#endif

#if defined( CALIBRATION_DECOMPANDER1_MEM )
    for ( i = 0; i < _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DECOMPANDER1_MEM ); i++ ) {
        acamera_decompander1_mem_array_data_write( p_fsm->cmn.isp_base, i, _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DECOMPANDER1_MEM )[i] );
    }
#endif

#if defined( CALIBRATION_SHADING_RADIAL_R ) && defined( CALIBRATION_SHADING_RADIAL_G ) && defined( CALIBRATION_SHADING_RADIAL_B ) && defined( CALIBRATION_SHADING_RADIAL_IR ) && ISP_HW_IS_MALI_C32_C52
    uint32_t len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_R );
    uint16_t *p_lut = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_R );
    uint32_t bank_offset = 0;
    for ( i = 0; i < len; i++ ) {
        acamera_radial_shading_mem_array_data_write( p_fsm->cmn.isp_base, bank_offset + i, p_lut[i] );
    }

    len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_G );
    p_lut = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_G );
    bank_offset += 256;
    for ( i = 0; i < len; i++ ) {
        acamera_radial_shading_mem_array_data_write( p_fsm->cmn.isp_base, bank_offset + i, p_lut[i] );
    }

    len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_B );
    p_lut = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_B );
    bank_offset += 256;
    for ( i = 0; i < len; i++ ) {
        acamera_radial_shading_mem_array_data_write( p_fsm->cmn.isp_base, bank_offset + i, p_lut[i] );
    }

    len = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_IR );
    p_lut = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_IR );
    bank_offset += 256;
    for ( i = 0; i < len; i++ ) {
        acamera_radial_shading_mem_array_data_write( p_fsm->cmn.isp_base, bank_offset + i, p_lut[i] );
    }
#endif

#if defined( CALIBRATION_SHADING_RADIAL_CENTRE_AND_MULT ) && ISP_HW_IS_MALI_C32_C52
    uint32_t len_cm = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_CENTRE_AND_MULT );
    uint32_t *radial_shading_lut_cm = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_SHADING_RADIAL_CENTRE_AND_MULT );

    if ( len_cm == 16 ) {
        // R
        acamera_isp_radial_shading_centerr_x_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[0] );
        acamera_isp_radial_shading_centerr_y_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[1] );
        acamera_isp_radial_shading_off_center_multrx_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[2] );
        acamera_isp_radial_shading_off_center_multry_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[3] );
        // G
        acamera_isp_radial_shading_centerg_x_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[4] );
        acamera_isp_radial_shading_centerg_y_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[5] );
        acamera_isp_radial_shading_off_center_multgx_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[6] );
        acamera_isp_radial_shading_off_center_multgy_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[7] );
        // B
        acamera_isp_radial_shading_centerb_x_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[8] );
        acamera_isp_radial_shading_centerb_y_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[9] );
        acamera_isp_radial_shading_off_center_multbx_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[10] );
        acamera_isp_radial_shading_off_center_multby_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[11] );
        // IR
        acamera_isp_radial_shading_centerir_x_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[12] );
        acamera_isp_radial_shading_centerir_y_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[13] );
        acamera_isp_radial_shading_off_center_multirx_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[14] );
        acamera_isp_radial_shading_off_center_multiry_write( p_fsm->cmn.isp_base, radial_shading_lut_cm[15] );
    } else {
        LOG( LOG_ERR, "CALIBRATION_SHADING_RADIAL_CENTRE_AND_MULT has wrong size %d but expected 16.", len_cm );
    }
#endif

    {
        /*
        CALIBRATION_DEMOSAIC_CONTROL
        //  0 demosaic/min_d_strength
        //  1 demosaic/min_ud_strength
        //  2 demosaic/max_d_strength
        //  3 demosaic/max_ud_strength
        //  4 demosaic/fc alias slope
        //  5 demosaic/uu thresh
        //  6 demosaic/uu sh thresh
        //  7 demosaic/sad_amp
        */
        uint16_t *demosaic_config = (uint16_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_DEMOSAIC_CONFIG );
        acamera_isp_demosaic_rgb_min_d_strength_write( p_fsm->cmn.isp_base, demosaic_config[0] );
        acamera_isp_demosaic_rgb_min_ud_strength_write( p_fsm->cmn.isp_base, demosaic_config[1] );
        acamera_isp_demosaic_rgb_max_d_strength_write( p_fsm->cmn.isp_base, demosaic_config[2] );
        acamera_isp_demosaic_rgb_max_ud_strength_write( p_fsm->cmn.isp_base, demosaic_config[3] );
        acamera_isp_demosaic_rgb_fc_alias_slope_write( p_fsm->cmn.isp_base, (uint8_t)demosaic_config[4] );
        acamera_isp_demosaic_rgb_uu_thresh_write( p_fsm->cmn.isp_base, demosaic_config[5] );
        acamera_isp_demosaic_rgb_uu_sh_thresh_write( p_fsm->cmn.isp_base, demosaic_config[6] );
        acamera_isp_demosaic_rgb_sad_amp_write( p_fsm->cmn.isp_base, (uint8_t)demosaic_config[7] );
    }

#if FW_HAS_CUSTOM_SETTINGS
    // The custom initialization may be required for a context.
    const acam_reg_t *p_custom_settings_context[] = {NULL};
    p_custom_settings_context[0] = (const acam_reg_t *)_GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_CUSTOM_SETTINGS_CONTEXT );
    acamera_load_sw_sequence( ACAMERA_FSM2CTX_PTR( p_fsm )->settings.isp_base, p_custom_settings_context, 0 );
#endif
}


void general_fsm_process_interrupt( general_fsm_const_ptr_t p_fsm, uint8_t irq_event )
{
    if ( acamera_fsm_util_is_irq_event_ignored( (fsm_irq_mask_t *)( &p_fsm->mask ), irq_event ) )
        return;
    switch ( irq_event ) {
    case ACAMERA_IRQ_FRAME_START:
        general_frame_start( (general_fsm_ptr_t)p_fsm );
        break;
    case ACAMERA_IRQ_FRAME_END:
        general_frame_end( (general_fsm_ptr_t)p_fsm );
        break;
    }
}

void general_set_hdmi_resolution( general_fsm_ptr_t p_fsm )
{
#if ( ISP_HAS_FPGA_WRAPPER ) && ( KERNEL_MODULE )
    uint32_t base = 0;
    fsm_param_sensor_info_t sensor_info;

    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );

    if ( ( sensor_info.active_width == 3840 && sensor_info.active_height == 2160 ) || ( sensor_info.active_width == 4032 && sensor_info.active_height == 3024 ) ) {
        // Needed only to display 4K ISP output on HD displays.
        if ( 0 == p_fsm->hdmi_4k ) { // Max HD
            LOG( LOG_ERR, "HDMI set HD" );
#ifdef ACAMERA_FPGA_HDMI_TOP_CLOCK_148_DEFAULT
            // Only on bitfiles with 4K support.
            acamera_fpga_hdmi_top_clock_148_write( base, 0 );
#endif
#ifdef ACAMERA_FPGA_HDMI_TOP_CLOCK_SEL_DEFAULT
            acamera_fpga_hdmi_top_clock_sel_write( base, 2 );
#endif
            acamera_fpga_hdmi_sync_total_width_write( base, 2200 );
            acamera_fpga_hdmi_sync_total_height_write( base, 1125 );
            acamera_fpga_hdmi_sync_active_width_write( base, 1920 );
            acamera_fpga_hdmi_sync_active_height_write( base, 1080 );
            acamera_fpga_frame_reader_active_width_write( base, 1920 );
            acamera_fpga_frame_reader_active_height_write( base, 1080 );
        } else { // Max 4K
            LOG( LOG_ERR, "HDMI set 4K" );
#ifdef ACAMERA_FPGA_HDMI_TOP_CLOCK_148_DEFAULT
            // Only on bitfiles with 4K support.
            acamera_fpga_hdmi_top_clock_148_write( base, 1 );
#endif
#ifdef ACAMERA_FPGA_HDMI_TOP_CLOCK_SEL_DEFAULT
            acamera_fpga_hdmi_top_clock_sel_write( base, 1 );
#endif
            acamera_fpga_hdmi_sync_total_width_write( base, 4400 );
            acamera_fpga_hdmi_sync_total_height_write( base, 2250 );
            acamera_fpga_hdmi_sync_active_width_write( base, 3840 );
            acamera_fpga_hdmi_sync_active_height_write( base, 2160 );
            acamera_fpga_frame_reader_active_width_write( base, 3840 );
            acamera_fpga_frame_reader_active_height_write( base, 2160 );
        }
    } else {
#ifdef ACAMERA_FPGA_HDMI_TOP_CLOCK_SEL_DEFAULT
        acamera_fpga_hdmi_top_clock_sel_write( base, 2 );
#endif
    }
#endif // (ISP_HAS_FPGA_WRAPPER) && (KERNEL_MODULE)
}

void general_set_wdr_mux_resolution( general_fsm_ptr_t p_fsm )
{
#if ( ISP_HAS_FPGA_WRAPPER ) && ( !USER_MODULE )
    // Sensor actual resolution on MIPI could be slightly bigger than configured on sensor preset
    // and then cropped to the required size at the ISP input port. But WDR frame buffer must keep the whole frame so
    // we add 16 pixels to each line to cover worst case scenario as actual MIPI value would be available only after 2-3 frames
    const uint16_t extra_width = 16;

    fsm_param_sensor_info_t sensor_info;
    acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_INFO, NULL, 0, &sensor_info, sizeof( sensor_info ) );
    LOG( LOG_CRIT, "INFO active width %d height %d", sensor_info.active_width, sensor_info.active_height );

    acamera_fpga_fpga_wdr_frame_buffer1_active_width_write( p_fsm->cmn.isp_base, sensor_info.active_width + extra_width );
    acamera_fpga_fpga_wdr_frame_buffer1_active_height_write( p_fsm->cmn.isp_base, sensor_info.active_height );
    acamera_fpga_fpga_wdr_frame_buffer1_line_offset_write( p_fsm->cmn.isp_base, ( sensor_info.active_width + extra_width ) * 2 );

    acamera_fpga_fpga_wdr_frame_buffer2_active_width_write( p_fsm->cmn.isp_base, sensor_info.active_width + extra_width );
    acamera_fpga_fpga_wdr_frame_buffer2_active_height_write( p_fsm->cmn.isp_base, sensor_info.active_height );
    acamera_fpga_fpga_wdr_frame_buffer2_line_offset_write( p_fsm->cmn.isp_base, ( sensor_info.active_width + extra_width ) * 2 );

    acamera_fpga_fpga_wdr_frame_buffer3_active_width_write( p_fsm->cmn.isp_base, sensor_info.active_width + extra_width );
    acamera_fpga_fpga_wdr_frame_buffer3_active_height_write( p_fsm->cmn.isp_base, sensor_info.active_height );
    acamera_fpga_fpga_wdr_frame_buffer3_line_offset_write( p_fsm->cmn.isp_base, ( sensor_info.active_width + extra_width ) * 2 );
#endif
}

void general_set_wdr_mode( general_fsm_ptr_t p_fsm )
{
#if ISP_BINARY_SEQUENCE == 0 // Remove compile error.
    UNUSED( seq_table );
#endif
    if ( !p_fsm || !ACAMERA_FSM2MGR_PTR( p_fsm ) || !ACAMERA_FSM2CTX_PTR( p_fsm ) ) {
        LOG( LOG_INFO, "Bad input params" );
        return;
    }

    switch ( p_fsm->wdr_mode ) {
    case WDR_MODE_LINEAR:
#ifdef SENSOR_ISP_SEQUENCE_DEFAULT_LINEAR
        LOG( LOG_INFO, "Setting Linear Binary ISP Sequence\n" );
        acamera_load_sw_sequence( p_fsm->cmn.isp_base, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_LINEAR );
#else
        LOG( LOG_WARNING, "No Linear Binary ISP Sequence is available\n" );
#endif

#if ISP_HAS_FPGA_WRAPPER
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_LINEAR )
        LOG( LOG_INFO, "Setting Linear Binary FPGA Sequence\n" );
        acamera_load_isp_sequence( 0, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_LINEAR );
#else
        LOG( LOG_WARNING, "No Linear Binary FPGA Sequence is available\n" );
#endif
#endif // ISP_HAS_FPGA_WRAPPER
        break;

    case WDR_MODE_FS_LIN: {

        if ( 2 == p_fsm->cur_exp_number ) {
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_2EXP )
            acamera_load_sw_sequence( p_fsm->cmn.isp_base, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_2EXP );
            LOG( LOG_INFO, "Setting FS_Lin_2Exp ISP Binary Sequence." );
#else
            LOG( LOG_WARNING, "No FS_Lin_2Exp ISP Binary Sequence is available." );
#endif
        } else if ( 3 == p_fsm->cur_exp_number ) {
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_3EXP )
            acamera_load_sw_sequence( p_fsm->cmn.isp_base, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_3EXP );
            LOG( LOG_INFO, "Setting FS_Lin_3Exp ISP Binary Sequence." );
#else
            LOG( LOG_WARNING, "No FS_Lin_3Exp ISP Binary Sequence is available." );
#endif
        } else if ( 4 == p_fsm->cur_exp_number ) {
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_4EXP )
            acamera_load_sw_sequence( p_fsm->cmn.isp_base, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FS_LIN_4EXP );
            LOG( LOG_INFO, "Setting FS_Lin_4Exp ISP Binary Sequence." );
#else
            LOG( LOG_WARNING, "No FS_Lin_4Exp ISP Binary Sequence is available." );
#endif
        }

#if ISP_HAS_FPGA_WRAPPER
        if ( 2 == p_fsm->cur_exp_number ) {
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_FS_LIN_2EXP )
            acamera_load_isp_sequence( 0, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_FS_LIN_2EXP );
            LOG( LOG_CRIT, "Setting FS_Lin_2Exp Binary Sequence. FPGA" );
#else
            LOG( LOG_WARNING, "No FS_Lin_2Exp FPGA Binary Sequence is available." );
#endif
        } else if ( 3 == p_fsm->cur_exp_number ) {
#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_FS_LIN_3EXP )
            acamera_load_isp_sequence( 0, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_FPGA_FS_LIN_3EXP );
            LOG( LOG_CRIT, "Setting FS_Lin_3Exp Binary Sequence. FPGA" );
#else
            LOG( LOG_WARNING, "No FS_Lin_3Exp FPGA Binary Sequence is available." );
#endif
        }
#endif // ISP_HAS_FPGA_WRAPPER

        break;
    }

    case WDR_MODE_NATIVE:
#ifdef SENSOR_ISP_SEQUENCE_DEFAULT_NATIVE
        acamera_load_sw_sequence( p_fsm->cmn.isp_base, ACAMERA_FSM2CTX_PTR( p_fsm )->isp_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_NATIVE );
#endif
        break;
    }
    general_set_hdmi_resolution( p_fsm );
    general_set_wdr_mux_resolution( p_fsm );
}

void general_initialize( general_fsm_ptr_t p_fsm )
{

    // Initialize ISP SBUS to get access to ISP memory
    // in api function REGISTERS_SOURCE_ID.
    acamera_sbus_init( &p_fsm->isp_sbus, sbus_isp );
    p_fsm->isp_sbus.mask = SBUS_MASK_SAMPLE_8BITS | SBUS_MASK_ADDR_16BITS | SBUS_MASK_SAMPLE_32BITS;

// API related
#ifdef COLOR_MODE_ID
    p_fsm->api_color_mode = NORMAL;
#endif
#ifdef SCENE_MODE_ID
    p_fsm->api_scene_mode = AUTO;
#endif

#if defined REGISTERS_SOURCE_ID && defined SENSOR
    p_fsm->api_reg_source = SENSOR;
#endif
    p_fsm->hdmi_4k = 0;

    p_fsm->return_default_gamma = 0;

    general_set_wdr_mode( p_fsm );

    p_fsm->mask.repeat_irq_mask = ACAMERA_IRQ_MASK( ACAMERA_IRQ_FRAME_START ) | ACAMERA_IRQ_MASK( ACAMERA_IRQ_FRAME_END );
    // Finally request interrupts
    general_request_interrupt( p_fsm, p_fsm->mask.repeat_irq_mask );

#if GENERAL_TEMPER_ENABLED
    p_fsm->temper_fitted = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.temper;
    if ( p_fsm->temper_fitted ) {
        general_temper_init( p_fsm );
        general_temper_configure( p_fsm );
    }
#endif
}

void general_deinitialize( general_fsm_ptr_t p_fsm )
{
#if GENERAL_TEMPER_ENABLED
    general_temper_exit( p_fsm );
#endif
}


static void general_dynamic_gamma_update( general_fsm_ptr_t p_fsm )
{
    // Update gamma here.
    const uint16_t *gamma_ev1 = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_EV1 );
    const uint16_t *gamma_ev2 = _GET_USHORT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_EV2 );
    const uint32_t gamma_len_ev1 = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_EV1 );
    const uint32_t gamma_len_ev2 = _GET_LEN( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_EV2 );

    uint32_t expected_gamma_size = ACAMERA_FR_GAMMA_RGB_MEM_SIZE / ( ACAMERA_FR_GAMMA_RGB_MEM_ARRAY_DATA_DATASIZE >> 3 );

    if ( ( gamma_len_ev1 == expected_gamma_size ) && ( gamma_len_ev2 == expected_gamma_size ) ) {
        fsm_param_ae_info_t ae_info;
        uint32_t i = 0;
        // Get current exposure value.
        acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_AE_INFO, NULL, 0, &ae_info, sizeof( ae_info ) );
        uint32_t exposure_log2 = ae_info.exposure_log2;
        uint32_t ev1_thresh = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_THRESHOLD )[0];
        uint32_t ev2_thresh = _GET_UINT_PTR( ACAMERA_FSM2CTX_PTR( p_fsm ), CALIBRATION_GAMMA_THRESHOLD )[1];

        modulation_entry_32_t p_table[2];
        p_table[0].x = ev1_thresh;
        p_table[1].x = ev2_thresh;
        // Use EV1 gamma curve if EV < EV1_THRESHOLD
        // Use EV2 gamma curve if EV > EV2_THRESHOLD
        // Do alpha blending between EV1 and EV2 when EV1_THRESHOLD < EV < EV2_THRESHOLD
        for ( i = 0; i < expected_gamma_size; i++ ) {
            p_table[0].y = gamma_ev1[i];
            p_table[1].y = gamma_ev2[i];
            // do alpha blending between two gammas for bin [i]
            uint16_t gamma_bin = acamera_calc_modulation_u32( exposure_log2, p_table, 2 );
            LOG( LOG_DEBUG, "Gamma update: ev %d, ev1 %d, ev2 %d, ref_gamma_ev1 %d, ref_gamma_ev2 %d, result %d.", exposure_log2, ev1_thresh, ev2_thresh, gamma_ev1[i], gamma_ev2[i], gamma_bin );
            // update the hardware gamma curve for fr and ds
            acamera_fr_gamma_rgb_mem_array_data_write( p_fsm->cmn.isp_base, i, gamma_bin );
#if ISP_HAS_DS1
            acamera_ds1_gamma_rgb_mem_array_data_write( p_fsm->cmn.isp_base, i, gamma_bin );
#endif
        }
    } else {
        // wrong gamma lut size
        LOG( LOG_ERR, "Wrong elements number in gamma_rgb_ev1 or ev2 -> ev1 size %d, ev2 size %d, expected %d.", (int)gamma_len_ev1, (int)gamma_len_ev2, (int)expected_gamma_size );
    }
}

void general_frame_start( general_fsm_ptr_t p_fsm )
{
#if GENERAL_TEMPER_ENABLED
    /* Enable temper after second frame to avoid broken frame */
    if ( p_fsm->cnt_for_temper++ == 2 ) {
        acamera_isp_temper_enable_write( p_fsm->cmn.isp_base, 1 );
    }
#endif
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.global_dynamic_gamma_enable ) {
        general_dynamic_gamma_update( p_fsm );
        p_fsm->return_default_gamma = 1;
    } else if ( p_fsm->return_default_gamma ) {
        // apply default gamma curve only once if dynamic_gamma is disabled
        general_default_gamma_update( p_fsm );
        p_fsm->return_default_gamma = 0;
    }
}

void general_frame_end( general_fsm_ptr_t p_fsm )
{
#if ISP_WDR_SWITCH

    // Called on frame end
    if ( p_fsm->wdr_mode_req != p_fsm->wdr_mode ) {
        p_fsm->wdr_mode = p_fsm->wdr_mode_req;

        general_set_wdr_mode( p_fsm );

        p_fsm->wdr_mode_frames = 0;
    }
#endif
}

uint32_t general_calc_fe_lut_output( general_fsm_ptr_t p_fsm, uint16_t val )
{
    // Calculate the output of the FE LUT(s) for input {val}.
    uint32_t result = val;
#if ISP_WDR_SWITCH
    // New switching system
    result = val;
#else

    // Standard old system - just use sqrt.
    result = acamera_sqrt32( val );
#endif
    return result;
}

uint32_t general_calc_fe_lut_input( general_fsm_ptr_t p_fsm, uint16_t val )
{
    // Calculate the input of the FE LUT(s) for output {val}.
#if ISP_WDR_SWITCH
    return val;
#else
    // Standard old system - just use sqrt.
    return val * val;
#endif
}

#if GENERAL_TEMPER_ENABLED

#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
static uint32_t general_temper4_get_dma_size( general_fsm_ptr_t p_fsm )
{
    uint8_t finite_mode = ( p_fsm->temper_mode == TEMPER4_MODE_FINITE );
    uint32_t mode = p_fsm->temper4_compress_pixel_mode << 2 | p_fsm->temper4_compress_meta_mode << 1 | finite_mode;
    uint32_t dma_bits;

    /*
    case {compress_pixel_data, compress_meta_data, finite_mode}
        000: configure to 10+10
        001: configure to 12
        110: configure to 10
        100: configure to 16
        101: configure to 8
        010: configure to 16
        011: configure to 12
        111: configure to 8
    */

    switch ( mode ) {
    case 1:
    case 3:
        dma_bits = 12;
        break;
    case 2:
    case 4:
        dma_bits = 16;
        break;
    case 5:
    case 7:
        dma_bits = 8;
        break;
    case 6:
        dma_bits = 10;
        break;
    case 0:
    default:
        dma_bits = 20;
        break;
    }

    LOG( LOG_DEBUG, "temper DMA bpp: %d", dma_bits );

    return dma_bits;
}

static image_resolution_t general_get_sensor_dim( general_fsm_ptr_t p_fsm )
{
    image_resolution_t sensor_dim = {0};
    const sensor_param_t *param = NULL;

    int rc = acamera_fsm_mgr_get_param( p_fsm->p_fsm_mgr, FSM_PARAM_GET_SENSOR_PARAM, NULL, 0, &param, sizeof( param ) );
    if ( rc == 0 ) {
        uint32_t cur_mode = param->mode;
        if ( cur_mode < param->modes_num ) {
            sensor_dim = param->modes_table[cur_mode].resolution;
        }
    }

    return sensor_dim;
}
#endif

static int general_temper_alloc_frame_buf( general_fsm_ptr_t p_fsm )
{
    aframe_t *temper_frame;
    image_resolution_t max_res;
    void *virt_addr;
    uint64_t dma_addr;
    int i, rc;

    acamera_settings *p_settings = &( ACAMERA_FSM2CTX_PTR( p_fsm )->settings );

    rc = acamera_fsm_mgr_get_param( p_fsm->p_fsm_mgr, FSM_PARAM_GET_SENSOR_MAX_RESOLUTION,
                                    NULL, 0, &max_res, sizeof( max_res ) );
    if ( rc ) {
        LOG( LOG_ERR, "unable to get max resolution" );
        return -1;
    }

    for ( i = 0; i < TEMPER_FRAMES_NO; i++ ) {
        temper_frame = &p_fsm->temper_frames[i];
        temper_frame->width = max_res.width;
        temper_frame->height = max_res.height;
        temper_frame->type = acamera_isp_temper_dma_format_read( p_fsm->cmn.isp_base );
#if ISP_HW_IS_MALI_C32_C52
        temper_frame->line_offset = acamera_line_offset( temper_frame->width, TEMPER_PIXEL_WIDTH );
#else
        // Always allocate buffer with max sensor resolution and max bpp to avoid realloc
        temper_frame->line_offset = ( FRAME_ALIGN( ( temper_frame->width * TEMPER4_MAX_DMA_BPP ), 128 ) ) / 8;
#endif
        temper_frame->size = temper_frame->height * temper_frame->line_offset;

        virt_addr = p_settings->callback_dma_alloc_coherent( p_fsm->cmn.ctx_id,
                                                             temper_frame->size, &dma_addr );
        if ( !virt_addr ) {
            temper_frame->virt_addr = 0;
            LOG( LOG_ERR, "unable to alloc temper_frame[%d] ctx_id: %d size: %d",
                 i, p_fsm->cmn.ctx_id, temper_frame->size );
            return -1;
        }

        temper_frame->address = (uint32_t)dma_addr;
        temper_frame->virt_addr = virt_addr;

        LOG( LOG_INFO, "alloc temper_frame[%d] w: %d h: %d size: %d dma_addr: 0x%x",
             i, temper_frame->width, temper_frame->height,
             temper_frame->size, temper_frame->address );
    }

    return 0;
}

static int general_temper_free_frame_buf( general_fsm_ptr_t p_fsm )
{
    acamera_settings *p_settings = &( ACAMERA_FSM2CTX_PTR( p_fsm )->settings );
    aframe_t *temper_frame;
    void *virt_addr;
    uint64_t dma_addr;
    uint32_t size;
    int i;

    for ( i = 0; i < TEMPER_FRAMES_NO; i++ ) {
        temper_frame = &p_fsm->temper_frames[i];

        virt_addr = temper_frame->virt_addr;
        dma_addr = temper_frame->address;
        size = temper_frame->size;

        p_settings->callback_dma_free_coherent( p_fsm->cmn.ctx_id, size, virt_addr, dma_addr );

        LOG( LOG_INFO, "free temper_frame[%d] w: %d h: %d size: %d dma_addr: 0x%x",
             i, temper_frame->width, temper_frame->height,
             temper_frame->size, temper_frame->address );
    }

    return 0;
}

static int general_temper_init( general_fsm_ptr_t p_fsm )
{
    int rc;

#if ISP_HW_IS_MALI_C32_C52
    p_fsm->temper_mode = TEMPER_MODE_DEFAULT;
#endif

    /* Disable temper at the beginning */
    p_fsm->cnt_for_temper = 0;
    acamera_isp_temper_enable_write( p_fsm->cmn.isp_base, 0 );


#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    p_fsm->temper_mode = ACAMERA_ISP_TEMPER_MODE_DEFAULT;
    p_fsm->temper4_compress_pixel_mode = ACAMERA_ISP_TEMPER_COMPRESS_PIXEL_DATA_DEFAULT;
    p_fsm->temper4_compress_meta_mode = ACAMERA_ISP_TEMPER_COMPRESS_META_DATA_DEFAULT;
#endif

    rc = general_temper_alloc_frame_buf( p_fsm );

    if ( rc ) {
        LOG( LOG_ERR, "unable to allocate frame buf" );
        return -1;
    }

    return 0;
}

static int general_temper_exit( general_fsm_ptr_t p_fsm )
{
    int rc = 0;

    rc = general_temper_free_frame_buf( p_fsm );

    return rc;
}

#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
static int general_temper4_set_format( general_fsm_ptr_t p_fsm )
{
    uintptr_t isp_base = p_fsm->cmn.isp_base;
    uint32_t mode = p_fsm->temper_mode << 2 | p_fsm->temper4_compress_pixel_mode << 1 | p_fsm->temper4_compress_meta_mode;
    uint32_t temper_format;

    /*
    case {temper_mode, compress_pixel_data, compress_meta_data}
            0000: configure to 0x14 (hex)
            0001: configure to 0x06 (hex)
            0010: configure to 0x06 (hex)
            0011: configure to 0x11 (hex)
            0100: configure to 0x14 (hex)
            0101: configure to 0x06 (hex)
            0110: configure to 0x06 (hex)
            0111: configure to 0x11 (hex)
            1000: configure to 0x07 (hex)
            1001: configure to 0x07 (hex)
            1010: configure to 0x0D (hex)
            1011: configure to 0x0D (hex)
            1100: configure to 0x07 (hex)
            1101: configure to 0x07 (hex)
            1110: configure to 0x0D (hex)
            1111: configure to 0x0D (hex)
    */

    switch ( mode ) {
    case 1:
    case 2:
    case 5:
    case 6:
        temper_format = 0x06;
        break;
    case 3:
    case 7:
        temper_format = 0x11;
        break;
    case 8:
    case 9:
    case 12:
    case 13:
        temper_format = 0x07;
        break;
    case 10:
    case 11:
    case 14:
    case 15:
        temper_format = 0x0D;
        break;
    case 0:
    case 4:
    default:
        temper_format = 0x14;
        break;
    }

    acamera_isp_temper_dma_format_write( isp_base, temper_format );

    LOG( LOG_INFO, "set temper format: %d", temper_format );

    return 0;
}

int general_temper4_configure( general_fsm_ptr_t p_fsm )
{
    if ( !p_fsm->temper_fitted ) {
        // Temper not fitted, skip further configuration.
        return 0;
    }

    uintptr_t isp_base = p_fsm->cmn.isp_base;
    aframe_t *frame_buf = NULL;

    /* Turn off */
    acamera_isp_top_bypass_temper_write( isp_base, 1 );

    /* Disable LSB */
    acamera_isp_temper_dma_frame_write_on_dma_write( isp_base, 0 );
    acamera_isp_temper_dma_frame_read_on_dma_write( isp_base, 0 );

    frame_buf = &p_fsm->temper_frames[0];

    if ( !frame_buf->virt_addr ) {
        LOG( LOG_ERR, "unable to configure TEMPER" );
        return -1;
    }

    /* Configure DMA address */
    acamera_isp_temper_dma_bank_base_reader_write( isp_base, frame_buf->address );
    acamera_isp_temper_dma_bank_base_writer_write( isp_base, frame_buf->address );

    // Calculate and set DMA line offset
    image_resolution_t sensor_dim = general_get_sensor_dim( p_fsm );
    uint32_t bpp = general_temper4_get_dma_size( p_fsm );
    uint16_t line_offset = ( FRAME_ALIGN( ( sensor_dim.width * bpp ), 128 ) ) / 8;
    acamera_isp_temper_dma_line_offset_write( isp_base, line_offset );

    // Set temper4 mode
    acamera_isp_temper_mode_write( isp_base, (uint8_t)p_fsm->temper_mode );
    if ( ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.compression ) {
        // Configure pixel compression
        acamera_isp_temper_compress_pixel_data_write( isp_base, p_fsm->temper4_compress_pixel_mode );
        // Configure meta compression
        acamera_isp_temper_compress_meta_data_write( isp_base, p_fsm->temper4_compress_meta_mode );
    }
    general_temper4_set_format( p_fsm );

    acamera_isp_temper_dma_frame_write_on_dma_write( isp_base, 1 );
    acamera_isp_temper_dma_frame_read_on_dma_write( isp_base, 1 );

    /* Turn on */
    acamera_isp_top_bypass_temper_write( isp_base, 0 );

    return 0;
}
#endif

static int general_temper_configure( general_fsm_ptr_t p_fsm )
{
    uintptr_t isp_base = p_fsm->cmn.isp_base;
    aframe_t *lsb_frame = NULL;
    aframe_t *msb_frame = NULL;

    /* Turn off */
    acamera_isp_top_bypass_temper_write( isp_base, 1 );
#if ISP_HW_IS_MALI_C32_C52

    /* Disable LSB */
    acamera_isp_temper_dma_frame_write_on_lsb_dma_write( isp_base, 0 );
    acamera_isp_temper_dma_frame_read_on_lsb_dma_write( isp_base, 0 );

    /* Disable MSB */
    acamera_isp_temper_dma_frame_write_on_msb_dma_write( isp_base, 0 );
    acamera_isp_temper_dma_frame_read_on_msb_dma_write( isp_base, 0 );

    if ( TEMPER_FRAMES_NO >= 1 )
        lsb_frame = &p_fsm->temper_frames[0];
    if ( TEMPER_FRAMES_NO >= 2 )
        msb_frame = &p_fsm->temper_frames[1];

    if ( !lsb_frame ) {
        LOG( LOG_ERR, "unable to configure TEMPER" );
        return -1;
    }

    if ( p_fsm->temper_mode == TEMPER3_MODE && !msb_frame ) {
        LOG( LOG_ERR, "unable to configure TEMPER3_MODE" );
        return -1;
    }

    /* Configure LSB */
    acamera_isp_temper_dma_lsb_bank_base_reader_write( isp_base, lsb_frame->address );
    acamera_isp_temper_dma_lsb_bank_base_writer_write( isp_base, lsb_frame->address );
    acamera_isp_temper_dma_frame_write_on_lsb_dma_write( isp_base, 1 );
    acamera_isp_temper_dma_frame_read_on_lsb_dma_write( isp_base, 1 );

    /* Configure MSB if TEMPER3_MODE */
    if ( p_fsm->temper_mode == TEMPER3_MODE ) {
        acamera_isp_temper_dma_msb_bank_base_reader_write( isp_base, msb_frame->address );
        acamera_isp_temper_dma_msb_bank_base_writer_write( isp_base, msb_frame->address );
        acamera_isp_temper_dma_frame_write_on_msb_dma_write( isp_base, 1 );
        acamera_isp_temper_dma_frame_read_on_msb_dma_write( isp_base, 1 );
    }

    acamera_isp_temper_temper2_mode_write( isp_base, p_fsm->temper_mode == TEMPER2_MODE );
    acamera_isp_temper_dma_line_offset_write( isp_base, lsb_frame->line_offset );

    /* Turn on */
    acamera_isp_top_bypass_temper_write( isp_base, 0 );
#else
    (void)msb_frame; //mute 'variable unused' warning
    (void)lsb_frame;
    (void)signed_bitshift; // mute 'unused' warning
    general_temper4_configure( p_fsm );
#endif // ISP_HW_IS_MALI_C32_C52

    return 0;
}

#if ISP_HW_IS_MALI_C32_C52
int general_temper_set_mode( general_fsm_ptr_t p_fsm, uint32_t mode )
{
    if ( mode != TEMPER3_MODE && mode != TEMPER2_MODE ) {
        LOG( LOG_ERR, "invalid temper_mode: %d", mode );
        return -1;
    }

    p_fsm->temper_mode = mode;

    LOG( LOG_INFO, "set temper_mode: %d", p_fsm->temper_mode );

    return general_temper_configure( p_fsm );
}
#else
int general_temper4_set_mode( general_fsm_ptr_t p_fsm, uint32_t mode )
{
    if ( mode > TEMPER4_MODE_FINITE ) {
        LOG( LOG_ERR, "invalid temper_mode: %d", mode );
        return -1;
    }
    if ( !p_fsm->temper_fitted ) {
        LOG( LOG_ERR, "temper4 is not fitted!" );
        return -1;
    }

    p_fsm->temper_mode = mode;

    LOG( LOG_INFO, "set temper_mode: %d", p_fsm->temper_mode );

    // Disable meta compression if finite mode.
    if ( mode >= TEMPER4_MODE_FINITE ) {
        p_fsm->temper4_compress_meta_mode = 0;
    }

    return general_temper4_configure( p_fsm );
}

int general_temper4_set_compress_pixel_mode( general_fsm_ptr_t p_fsm, uint8_t mode )
{
    uint8_t compression_fitted = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.compression;
    // If compression HW is not fitted then return not supported
    if ( 0 == p_fsm->temper_fitted || 0 == compression_fitted ) {
        return -1;
    }
    p_fsm->temper4_compress_pixel_mode = mode & compression_fitted;

    // Reconfigure temper
    return general_temper4_configure( p_fsm );
}

int general_temper4_set_compress_meta_mode( general_fsm_ptr_t p_fsm, uint8_t mode )
{
    uint8_t compression_fitted = ACAMERA_FSM2CTX_PTR( p_fsm )->stab.hw_fitted.compression;
    // If compression HW is not fitted then return not supported
    if ( 0 == p_fsm->temper_fitted || 0 == compression_fitted ) {
        return -1;
    }
    p_fsm->temper4_compress_meta_mode = mode & compression_fitted;

    // Disable meta compression if finite.
    if ( p_fsm->temper_mode >= TEMPER4_MODE_FINITE ) {
        p_fsm->temper4_compress_meta_mode = 0;
    }

    // Reconfigure temper
    return general_temper4_configure( p_fsm );
}
#endif
#endif // GENERAL_TEMPER_ENABLED

int general_set_fr_raw_bypass( general_fsm_ptr_t p_fsm, uint32_t enabled )
{
    uintptr_t isp_base = p_fsm->cmn.isp_base;

// FR RAW bypass configuration is slightly different on C32/C52 and C55
#if ISP_HW_IS_MALI_C32_C52
    acamera_isp_top_isp_processing_fr_bypass_mode_write( isp_base, ( enabled ) ? 1U : 0U );
#else
    acamera_isp_top_isp_processing_fr_bypass_mode_write( isp_base, ( enabled ) ? 2U : 0U );
#endif

    p_fsm->fr_raw_bypass = ( enabled ) ? 1U : 0U;

    return 0;
}
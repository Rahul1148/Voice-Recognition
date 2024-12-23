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

#ifndef _AWB_ACAMERA_CORE_H_
#define _AWB_ACAMERA_CORE_H_

#include "acamera_math.h"
#include "awb_standard_api.h"


#define D50_DEFAULT 256
#define AWB_LIGHT_SOURCE_UNKNOWN 0
#define AWB_LIGHT_SOURCE_A 0x01
#define AWB_LIGHT_SOURCE_D40 0x02
#define AWB_LIGHT_SOURCE_D50 0x03
#define AWB_LIGHT_SOURCE_A_TEMPERATURE 2850
#define AWB_LIGHT_SOURCE_D40_TEMPERATURE 4000
#define AWB_LIGHT_SOURCE_D50_TEMPERATURE 5000
#define AWB_DLS_LIGHT_SOURCE_A_D40_BORDER ( AWB_LIGHT_SOURCE_A_TEMPERATURE + AWB_LIGHT_SOURCE_D40_TEMPERATURE ) / 2
#define AWB_DLS_LIGHT_SOURCE_D40_D50_BORDER ( AWB_LIGHT_SOURCE_D40_TEMPERATURE + AWB_LIGHT_SOURCE_D50_TEMPERATURE ) / 2


typedef struct _awb_misc_info_ {

    uint16_t log2_gain;
    int32_t cur_exposure_log2;
    uint32_t iridix_contrast;

    uint8_t global_manual_awb;
    uint16_t global_awb_red_gain;
    uint16_t global_awb_blue_gain;
} awb_misc_info_t;


typedef unsigned short ( *calibration_light_src_t )[2];

typedef struct _awb_calibration_data_ {
    calibration_light_src_t cali_light_src;
    uint32_t cali_light_src_len;

    uint32_t *cali_evtolux_ev_lut;
    uint32_t cali_evtolux_ev_lut_len;

    uint32_t *cali_evtolux_lux_lut;
    uint32_t cali_evtolux_lux_lut_len;

    uint8_t *cali_awb_avg_coef;
    uint32_t cali_awb_avg_coef_len;

    uint16_t *cali_rg_pos;
    uint32_t cali_rg_pos_len;

    uint16_t *cali_bg_pos;
    uint32_t cali_bg_pos_len;

    uint16_t *cali_color_temp;
    uint32_t cali_color_temp_len;

    uint16_t *cali_ct_rg_pos_calc;
    uint32_t cali_ct_rg_pos_calc_len;

    uint16_t *cali_ct_bg_pos_calc;
    uint32_t cali_ct_bg_pos_calc_len;

    modulation_entry_t *cali_awb_bg_max_gain;
    uint32_t cali_awb_bg_max_gain_len;

    uint16_t *cali_mesh_ls_weight;
    uint16_t *cali_mesh_rgbg_weight;
    uint8_t *cali_evtolux_probability_enable;
    uint32_t *cali_awb_mix_light_param;
    uint16_t *cali_ct65pos;
    uint16_t *cali_ct40pos;
    uint16_t *cali_ct30pos;
    uint16_t *cali_sky_lux_th;
    uint16_t *cali_wb_strength;
    uint16_t *cali_mesh_color_temperature;
    uint16_t *cali_awb_warming_ls_a;
    uint16_t *cali_awb_warming_ls_d75;
    uint16_t *cali_awb_warming_ls_d50;
    uint16_t *cali_awb_colour_preference;
} awb_calibration_data_t;


typedef struct _awb_acamera_input_ {
    awb_misc_info_t misc_info;
    awb_calibration_data_t cali_data;
} awb_acamera_input_t;


typedef struct _awb_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} awb_custom_input_t;


typedef struct _awb_acamera_output_ {
    uint16_t rg_coef;
    uint16_t bg_coef;
    int32_t temperature_detected;
    uint8_t p_high;
    uint8_t light_source_candidate;
    int32_t awb_warming[3];
    uint8_t awb_converged;
} awb_acamera_output_t;


void *awb_acamera_core_init( uint32_t ctx_id );
int32_t awb_acamera_core_deinit( void *awb_ctx );
int32_t awb_acamera_core_proc( void *awb_ctx, awb_stats_data_t *stats, awb_input_data_t *input, awb_output_data_t *output );


#endif

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

#ifndef _AE_ACAMERA_CORE_H_
#define _AE_ACAMERA_CORE_H_

#include "acamera_math.h"
#include "ae_standard_api.h"

typedef struct _ae_balanced_param_t {
    uint32_t pi_coeff;
    uint32_t target_point;
    uint32_t tail_weight;
    uint32_t long_clip;
    uint32_t er_avg_coeff;
    uint32_t hi_target_prc;
    uint32_t hi_target_p;
    uint32_t enable_iridix_gdg;
    uint32_t AE_tol;
} ae_balanced_param_t;


typedef struct _ae_misc_info_ {
    int32_t sensor_exp_number;

    int32_t total_gain;
    int32_t max_exposure_log2;
    uint32_t global_max_exposure_ratio;

    uint32_t iridix_contrast;
    uint32_t global_exposure;
    uint8_t global_ae_compensation;
    uint8_t global_manual_exposure;
    uint8_t global_manual_exposure_ratio;
    uint8_t global_exposure_ratio;
} ae_misc_info_t;


typedef struct _ae_calibration_data_ {
    uint8_t *ae_corr_lut;
    uint32_t ae_corr_lut_len;

    uint32_t *ae_exp_corr_lut;
    uint32_t ae_exp_corr_lut_len;

    modulation_entry_t *ae_hdr_target;
    uint32_t ae_hdr_target_len;

    modulation_entry_t *ae_exp_ratio_adjustment;
    uint32_t ae_exp_ratio_adjustment_len;
} ae_calibration_data_t;


typedef struct _ae_acamera_input_ {
    ae_balanced_param_t *ae_ctrl;
    ae_misc_info_t misc_info;
    ae_calibration_data_t cali_data;
} ae_acamera_input_t;


typedef struct _ae_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} ae_custom_input_t;


typedef struct _ae_acamera_output_ {
    int32_t exposure_log2;
    uint32_t exposure_ratio;

    uint8_t ae_converged;
} ae_acamera_output_t;


void *ae_acamera_core_init( uint32_t ctx_id );
int32_t ae_acamera_core_deinit( void *ae_ctx );
int32_t ae_acamera_core_proc( void *ae_ctx, ae_stats_data_t *stats, ae_input_data_t *input, ae_output_data_t *output );


#endif

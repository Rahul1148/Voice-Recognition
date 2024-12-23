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

#ifndef _IRIDIX_ACAMERA_CORE_H_
#define _IRIDIX_ACAMERA_CORE_H_

#include "acamera_math.h"
#include "iridix_standard_api.h"

typedef struct _iridix_misc_info_ {

    uint8_t global_manual_iridix;
    uint8_t global_iridix_strength_target;
    uint8_t global_minimum_iridix_strength;
    uint8_t global_maximum_iridix_strength;

    int32_t cur_exposure_log2;
} iridix_misc_info_t;


typedef struct _iridix_calibration_data_ {

    uint8_t *cali_iridix_avg_coef;

    uint16_t *cali_iridix_min_max_str;

    uint32_t *cali_ae_ctrl;
    uint32_t *cali_iridix_ev_lim_no_str;
    uint32_t *cali_iridix_ev_lim_full_str;
    uint32_t *cali_iridix_strength_dk_enh_ctrl;
} iridix_calibration_data_t;


typedef struct _iridix_acamera_input_ {
    iridix_misc_info_t misc_info;
    iridix_calibration_data_t cali_data;
} iridix_acamera_input_t;


typedef struct _iridix_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} iridix_custom_input_t;


typedef struct _iridix_acamera_output_ {
    uint16_t strength_target;
    uint16_t dark_enh;
    uint16_t iridix_global_DG;
    uint32_t iridix_contrast;
} iridix_acamera_output_t;


void *iridix_acamera_core_init( uint32_t ctx_id );
int32_t iridix_acamera_core_deinit( void *iridix_ctx );
int32_t iridix_acamera_core_proc( void *iridix_ctx, iridix_stats_data_t *stats, iridix_input_data_t *input, iridix_output_data_t *output );


#endif
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

#ifndef _GAMMA_ACAMERA_CORE_H_
#define _GAMMA_ACAMERA_CORE_H_

#include "acamera_math.h"
#include "gamma_standard_api.h"


typedef struct _gamma_calibration_data_ {
    uint32_t *auto_level_ctrl;
} gamma_calibration_data_t;


typedef struct _gamma_acamera_input_ {
    gamma_calibration_data_t cali_data;
} gamma_acamera_input_t;


typedef struct _gamma_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} gamma_custom_input_t;


typedef struct _gamma_acamera_output_ {
    uint32_t gamma_gain;
    uint32_t gamma_offset;
} gamma_acamera_output_t;


void *gamma_acamera_core_init( uint32_t ctx_id );
int32_t gamma_acamera_core_deinit( void *gamma_ctx );
int32_t gamma_acamera_core_proc( void *gamma_ctx, gamma_stats_data_t *stats, gamma_input_data_t *input, gamma_output_data_t *output );


#endif
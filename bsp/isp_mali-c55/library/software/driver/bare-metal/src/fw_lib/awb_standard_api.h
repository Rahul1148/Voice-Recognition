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

#ifndef _AWB_STANDARD_API_H_
#define _AWB_STANDARD_API_H_


typedef struct _awb_zone_t {
    uint16_t rg;
    uint16_t bg;
    uint32_t sum;
} awb_zone_t;

typedef struct _awb_stats_data_ {
    awb_zone_t *awb_zones;
    uint32_t zones_size;
} awb_stats_data_t;


typedef struct _awb_input_data_ {
    void *custom_input;
    void *acamera_input;
} awb_input_data_t;


typedef struct _awb_output_data_ {
    void *custom_output;
    void *acamera_output;
} awb_output_data_t;


typedef void *( *awb_std_init_func )( uint32_t ctx_id );
typedef int32_t ( *awb_std_proc_func )( void *awb_ctx, awb_stats_data_t *stats, awb_input_data_t *input, awb_output_data_t *output );
typedef int32_t ( *awb_std_deinit_func )( void *awb_ctx );


typedef struct _awb_std_obj_ {
    void *awb_ctx;
    awb_std_init_func init;
    awb_std_proc_func proc;
    awb_std_deinit_func deinit;
} awb_std_obj_t;


#endif
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

#ifndef _AF_STANDARD_API_H_
#define _AF_STANDARD_API_H_


typedef struct _af_stats_data_ {
    uint32_t *zones_stats;
    uint32_t zones_size;
} af_stats_data_t;


typedef struct _af_input_data_ {
    void *custom_input;
    void *acamera_input;
} af_input_data_t;


typedef struct _af_output_data_ {
    void *custom_output;
    void *acamera_output;
} af_output_data_t;


typedef void *( *af_std_init_func )( uint32_t ctx_id );
typedef int32_t ( *af_std_proc_func )( void *af_ctx, af_stats_data_t *stats, af_input_data_t *input, af_output_data_t *output );
typedef int32_t ( *af_std_deinit_func )( void *af_ctx );


typedef struct _af_std_obj_ {
    void *af_ctx;
    af_std_init_func init;
    af_std_proc_func proc;
    af_std_deinit_func deinit;
} af_std_obj_t;


#endif
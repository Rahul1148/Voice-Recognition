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

#ifndef _IRIDIX_STANDARD_API_H_
#define _IRIDIX_STANDARD_API_H_


typedef struct _iridix_stats_data_ {
    const uint32_t *fullhist;
    uint32_t fullhist_size;
    uint32_t fullhist_sum;
} iridix_stats_data_t;


typedef struct _iridix_input_data_ {
    void *custom_input;
    void *acamera_input;
} iridix_input_data_t;


typedef struct _iridix_output_data_ {
    void *custom_output;
    void *acamera_output;
} iridix_output_data_t;


typedef void *( *iridix_std_init_func )( uint32_t ctx_id );
typedef int32_t ( *iridix_std_proc_func )( void *iridix_ctx, iridix_stats_data_t *stats, iridix_input_data_t *input, iridix_output_data_t *output );
typedef int32_t ( *iridix_std_deinit_func )( void *iridix_ctx );


typedef struct _iridix_std_obj_ {
    void *iridix_ctx;
    iridix_std_init_func init;
    iridix_std_proc_func proc;
    iridix_std_deinit_func deinit;
} iridix_std_obj_t;


#endif
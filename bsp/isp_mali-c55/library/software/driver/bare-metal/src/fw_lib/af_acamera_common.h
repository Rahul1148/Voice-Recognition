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

#ifndef _AF_ACAMERA_COMMON_H_
#define _AF_ACAMERA_COMMON_H_


typedef struct _af_lms_param_t {
    uint32_t pos_min_down;
    uint32_t pos_min;
    uint32_t pos_min_up;
    uint32_t pos_inf_down;
    uint32_t pos_inf;
    uint32_t pos_inf_up;
    uint32_t pos_macro_down;
    uint32_t pos_macro;
    uint32_t pos_macro_up;
    uint32_t pos_max_down;
    uint32_t pos_max;
    uint32_t pos_max_up;
    uint32_t fast_search_positions;
    uint32_t skip_frames_init;
    uint32_t skip_frames_move;
    uint32_t dynamic_range_th;
    uint32_t spot_tolerance;
    uint32_t exit_th;
    uint32_t caf_trigger_th;
    uint32_t caf_stable_th;
    uint32_t print_debug;
} af_lms_param_t;


#endif
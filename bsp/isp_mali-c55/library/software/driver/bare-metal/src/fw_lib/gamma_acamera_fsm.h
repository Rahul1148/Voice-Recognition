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

#if !defined( __GAMMA_CONTRAST_FSM_H__ )
#define __GAMMA_CONTRAST_FSM_H__

#include "gamma_standard_api.h"


typedef struct _gamma_acamera_fsm_t gamma_acamera_fsm_t;
typedef struct _gamma_acamera_fsm_t *gamma_acamera_fsm_ptr_t;
typedef const struct _gamma_acamera_fsm_t *gamma_acamera_fsm_const_ptr_t;

void gamma_acamera_init( gamma_acamera_fsm_ptr_t p_fsm );
void gamma_acamera_deinit( gamma_acamera_fsm_ptr_t p_fsm );
void gamma_acamera_process_stats( gamma_acamera_fsm_ptr_t p_fsm );

struct _gamma_acamera_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;

    uint32_t fullhist_sum;
    uint32_t fullhist[ISP_FULL_HISTOGRAM_SIZE];

    uint32_t cur_using_stats_frame_id;
    uint32_t gamma_gain;
    uint32_t gamma_offset;


#if FW_ALG_SUPPORT_SHARED_LIB
    void *lib_handle;
#endif
    gamma_std_obj_t gamma_alg_obj;
};


void gamma_acamera_fsm_clear( gamma_acamera_fsm_ptr_t p_fsm );

void gamma_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param );
void gamma_acamera_fsm_deinit( void *fsm );
int gamma_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int gamma_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t gamma_acamera_fsm_process_event( gamma_acamera_fsm_ptr_t p_fsm, event_id_t event_id );

void gamma_acamera_fsm_process_interrupt( gamma_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void gamma_contrast_request_interrupt( gamma_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif

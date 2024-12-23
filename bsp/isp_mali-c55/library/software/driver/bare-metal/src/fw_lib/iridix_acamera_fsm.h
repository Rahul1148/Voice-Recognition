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

#if !defined( __IRIDIX_FSM_H__ )
#define __IRIDIX_FSM_H__

#include "iridix_standard_api.h"

typedef struct _iridix_acamera_fsm_t iridix_acamera_fsm_t;
typedef struct _iridix_acamera_fsm_t *iridix_acamera_fsm_ptr_t;
typedef const struct _iridix_acamera_fsm_t *iridix_acamera_fsm_const_ptr_t;

void iridix_initialize( iridix_acamera_fsm_ptr_t p_fsm );
void iridix_deinitialize( iridix_acamera_fsm_ptr_t p_fsm );
void iridix_init_cali_lut( iridix_acamera_fsm_ptr_t p_fsm );
void iridix_calculate( iridix_acamera_fsm_ptr_t p_fsm );


struct _iridix_acamera_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint16_t strength_target;
    uint32_t strength_avg;
    uint16_t dark_enh;

    uint32_t iridix_contrast;
    uint16_t iridix_global_DG;
    uint16_t iridix_global_DG_prev;

    uint32_t frame_id_tracking;

#if FW_ALG_SUPPORT_SHARED_LIB
    void *lib_handle;
#endif
    iridix_std_obj_t iridix_alg_obj;
};


void iridix_acamera_fsm_clear( iridix_acamera_fsm_ptr_t p_fsm );
void iridix_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param );
void iridix_acamera_fsm_deinit( void *fsm );
int iridix_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int iridix_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );
uint8_t iridix_acamera_fsm_process_event( iridix_acamera_fsm_ptr_t p_fsm, event_id_t event_id );
void iridix_acamera_fsm_process_interrupt( iridix_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event );
void iridix_acamera_request_interrupt( iridix_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __IRIDIX_FSM_H__ */

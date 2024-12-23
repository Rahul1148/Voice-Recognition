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

#if !defined( __AE_FSM_H__ )
#define __AE_FSM_H__


#include "acamera_firmware_config.h"
#include "ae_standard_api.h"

typedef struct _ae_acamera_fsm_t ae_acamera_fsm_t;
typedef struct _ae_acamera_fsm_t *ae_acamera_fsm_ptr_t;
typedef const struct _ae_acamera_fsm_t *ae_acamera_fsm_const_ptr_t;

#define ISP_HAS_AE_FSM 1

enum { AE_CLIPPING_ANTIFLICKER_N = 5 };

void ae_acamera_initialize( ae_acamera_fsm_ptr_t p_fsm );
void ae_acamera_deinitialize( ae_acamera_fsm_ptr_t p_fsm );
void ae_calculate_target( ae_acamera_fsm_ptr_t p_fsm );
void ae_calculate_exposure( ae_acamera_fsm_ptr_t p_fsm );
void ae_roi_update( ae_acamera_fsm_ptr_t p_fsm );
void ae_process_stats( ae_acamera_fsm_ptr_t p_fsm );

struct _ae_acamera_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint32_t cur_using_stats_frame_id;

    int32_t exposure_log2;
    uint32_t exposure_ratio;
    uint32_t fullhist[ISP_FULL_HISTOGRAM_SIZE];
    uint32_t fullhist_sum;
    uint32_t ae_roi_api;
    uint32_t roi;
    uint16_t hist4[ACAMERA_ISP_METERING_AEXP_NODES_USED_HORIZ_DEFAULT * ACAMERA_ISP_METERING_AEXP_NODES_USED_VERT_DEFAULT];

    uint8_t ae_converged;

#if FW_ALG_SUPPORT_SHARED_LIB
    void *lib_handle;
#endif
    ae_std_obj_t ae_alg_obj;
};


void ae_acamera_fsm_clear( ae_acamera_fsm_ptr_t p_fsm );

void ae_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param );
void ae_acamera_fsm_deinit( void *fsm );
int ae_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int ae_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t ae_acamera_fsm_process_event( ae_acamera_fsm_ptr_t p_fsm, event_id_t event_id );

void ae_acamera_fsm_process_interrupt( ae_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void ae_acamera_request_interrupt( ae_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __AE_FSM_H__ */

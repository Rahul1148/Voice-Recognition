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

#if !defined( __NOISE_REDUCTION_FSM_H__ )
#define __NOISE_REDUCTION_FSM_H__



typedef struct _noise_reduction_fsm_t noise_reduction_fsm_t;
typedef struct _noise_reduction_fsm_t *noise_reduction_fsm_ptr_t;
typedef const struct _noise_reduction_fsm_t *noise_reduction_fsm_const_ptr_t;

#define MAGIC_GAIN_DIGITAL_FINE 0x03FF
#define MAGIC_TNR_EXP_TRESH 192 * 64
#define NR_LUT_SIZE 128
#define NR_SINTER_BITS 16

void noise_reduction_initialize( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_update( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_hw_init( noise_reduction_fsm_ptr_t p_fsm );

#include "acamera_metering_stats_mem_config.h"


struct _noise_reduction_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    int16_t tnr_thresh_exp1;
    int16_t tnr_thresh_exp2;
    int16_t snr_thresh_exp1;
    int16_t snr_thresh_exp2;
    uint8_t tnr_exp_thresh;
    uint8_t tnr_exp1_ratio;
    uint8_t tnr_exp2_ratio;
    uint8_t tnr_strength_target;
    uint8_t snr_strength_target;
    int16_t tnr_thresh_master;
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    int16_t tnr_mot_thresh;
    int16_t tnr_mot_slope;
#endif
    int16_t snr_thresh_master;
    int16_t snr_thresh_contrast;
    uint32_t temper_ev_previous_frame;
    uint32_t temper_diff_avg;
    uint32_t temper_diff_coeff;

    noise_reduction_mode_t nr_mode;
};


void noise_reduction_fsm_clear( noise_reduction_fsm_ptr_t p_fsm );

void noise_reduction_fsm_init( void *fsm, fsm_init_param_t *init_param );

uint8_t noise_reduction_fsm_process_event( noise_reduction_fsm_ptr_t p_fsm, event_id_t event_id );

int noise_reduction_fsm_set_param( void *fsm, uint32_t param_id,
                                   void *input, uint32_t input_size );

int noise_reduction_fsm_get_param( void *fsm, uint32_t param_id,
                                    void *input, uint32_t input_size,
                                    void *output, uint32_t output_size );

void noise_reduction_fsm_process_interrupt( noise_reduction_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void noise_reduction_request_interrupt( noise_reduction_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __NOISE_REDUCTION_FSM_H__ */

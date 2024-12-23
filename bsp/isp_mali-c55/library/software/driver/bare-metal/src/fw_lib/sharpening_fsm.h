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

#if !defined( __SHARPENING_FSM_H__ )
#define __SHARPENING_FSM_H__



typedef struct _sharpening_fsm_t sharpening_fsm_t;
typedef struct _sharpening_fsm_t *sharpening_fsm_ptr_t;
typedef const struct _sharpening_fsm_t *sharpening_fsm_const_ptr_t;

#define AU_BLACK_HISTORY_SIZE 10
#define SHARP_LUT_SIZE 256

void sharpening_initialize( sharpening_fsm_ptr_t p_fsm );
void sharpening_update( sharpening_fsm_ptr_t p_fsm );
#define AU_NORMALIZE_VALUE 10000000

struct _sharpening_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint32_t sharpening_target;
    uint32_t med_strength;
    uint32_t sys_gain;
    uint8_t min_strength;
    uint8_t max_strength;
    uint32_t sharpening_mult;
    uint8_t api_value;
    uint32_t black_val_hist[10];

    uint32_t fullhist_cum_sum[ISP_FULL_HISTOGRAM_SIZE];
};


void sharpening_fsm_clear( sharpening_fsm_ptr_t p_fsm );

void sharpening_fsm_init( void *fsm, fsm_init_param_t *init_param );
int sharpening_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int sharpening_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t sharpening_fsm_process_event( sharpening_fsm_ptr_t p_fsm, event_id_t event_id );

void sharpening_fsm_process_interrupt( sharpening_fsm_const_ptr_t p_fsm, uint8_t irq_event );


#endif /* __SHARPENING_FSM_H__ */

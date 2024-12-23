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

#if !defined( __CROP_FSM_H__ )
#define __CROP_FSM_H__



typedef struct _crop_fsm_t crop_fsm_t;
typedef struct _crop_fsm_t *crop_fsm_ptr_t;
typedef const struct _crop_fsm_t *crop_fsm_const_ptr_t;

typedef struct _crop_t {
    uint8_t enable;
    uint8_t done;
    uint16_t xsize;
    uint16_t ysize;
    uint16_t xoffset;
    uint16_t yoffset;
} crop_t;
typedef struct _scaler_t {
    uint8_t enable;
    uint8_t done;
    uint16_t xsize;
    uint16_t ysize;
    uint16_t bank;
} scaler_t;
void crop_initialize( crop_fsm_ptr_t p_fsm );
void crop_resolution_changed( crop_fsm_ptr_t p_fsm );

struct _crop_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint16_t resize_type;
    crop_t crop_fr;
#if !ISP_HW_IS_MALI_C32_C52
    scaler_t scaler_fr;
#endif
    uint16_t width_fr;
    uint16_t height_fr;


#if ISP_HAS_DS1
    crop_t crop_ds;
    scaler_t scaler_ds;
    uint16_t width_ds;
    uint16_t height_ds;
#endif
    uint8_t need_updating;
};

void crop_fsm_clear( crop_fsm_ptr_t p_fsm );
void crop_fsm_init( void *fsm, fsm_init_param_t *init_param );

int crop_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int crop_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t crop_fsm_process_event( crop_fsm_ptr_t p_fsm, event_id_t event_id );

void crop_fsm_process_interrupt( crop_fsm_const_ptr_t p_fsm, uint8_t irq_event );

int crop_validate_size( crop_fsm_t *p_fsm, uint16_t type, uint16_t sizeto, int isWidth );

void crop_request_interrupt( crop_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __CROP_FSM_H__ */

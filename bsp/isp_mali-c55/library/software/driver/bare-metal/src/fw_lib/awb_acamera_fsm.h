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

#if !defined( __AWB_ACAMERA_FSM_H__ )
#define __AWB_ACAMERA_FSM_H__

#include "awb_standard_api.h"


typedef struct _awb_acamera_fsm_t awb_acamera_fsm_t;
typedef struct _awb_acamera_fsm_t *awb_acamera_fsm_ptr_t;
typedef const struct _awb_acamera_fsm_t *awb_acamera_fsm_const_ptr_t;


#define ISP_HAS_AWB_FSM 1

#define MAX_AWB_ZONES ( ISP_METERING_ZONES_MAX_V * ISP_METERING_ZONES_MAX_H )
#define AWB_DLS_SWITCH_LIGHT_SOURCE_DETECT_FRAMES_QUANTITY 15
#define AWB_DLS_SWITCH_LIGHT_SOURCE_CHANGE_FRAMES_QUANTITY 35


void awb_init( awb_acamera_fsm_ptr_t p_fsm );
void awb_deinit( awb_acamera_fsm_ptr_t p_fsm );
void awb_process_light_source( awb_acamera_fsm_ptr_t p_fsm );
void awb_normalise( awb_acamera_fsm_ptr_t p_fsm );
void awb_process_stats( awb_acamera_fsm_ptr_t p_fsm );


struct _awb_acamera_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint16_t curr_AWB_ZONES;
    uint16_t rg_coef;
    uint16_t bg_coef;
    uint8_t p_high;
    uint32_t avg_GR;
    uint32_t avg_GB;
    awb_zone_t awb_zones[MAX_AWB_ZONES];
    int32_t wb_log2[4];
    int32_t temperature_detected;
    uint8_t light_source_detected;
    uint8_t light_source_candidate;
    uint8_t detect_light_source_frames_count;
    uint32_t mode;
    uint32_t roi;

    int32_t awb_warming[3];
    uint32_t switch_light_source_detect_frames_quantity;
    uint32_t switch_light_source_change_frames_quantity;
    uint8_t is_ready;

    uint32_t cur_using_stats_frame_id;
    uint32_t cur_result_gain_frame_id;

    uint8_t awb_converged;

#if FW_ALG_SUPPORT_SHARED_LIB
    void *lib_handle;
#endif
    awb_std_obj_t awb_alg_obj;
};


void awb_acamera_fsm_clear( awb_acamera_fsm_ptr_t p_fsm );
void awb_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param );
void awb_acamera_fsm_deinit( void *fsm );
int awb_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int awb_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );
uint8_t awb_acamera_fsm_process_event( awb_acamera_fsm_ptr_t p_fsm, event_id_t event_id );
void awb_acamera_fsm_process_interrupt( awb_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event );
void awb_acamera_fsm_request_interrupt( awb_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __AWB_ACAMERA_FSM_H__ */

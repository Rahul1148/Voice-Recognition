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

#if !defined( __AF_ACAMERA_FSM_H__ )
#define __AF_ACAMERA_FSM_H__


#include "af_standard_api.h"
#include "af_acamera_core.h"
#include "af_acamera_common.h"


typedef struct _af_acamera_fsm_t af_acamera_fsm_t;
typedef struct _af_acamera_fsm_t *af_acamera_fsm_ptr_t;
typedef const struct _af_acamera_fsm_t *af_acamera_fsm_const_ptr_t;


#define ISP_HAS_AF_FSM 1

#include "acamera_isp_config.h"
#include "acamera_lens_api.h"

#define ISP_HAS_AF_ACAMERA_FSM 1
#define AF_ZONES_COUNT_MAX ( ISP_METERING_ZONES_MAX_V * ISP_METERING_ZONES_MAX_H )

// for AF5 stats we need to read only one row of 32bit for each zone
#if !ISP_HW_IS_MALI_C32_C52
#define AF_STATS_NUM_ROWS 1
#else
#define AF_STATS_NUM_ROWS 2
#endif


void af_acamera_init( af_acamera_fsm_ptr_t p_fsm );
void af_acamera_deinit( af_acamera_fsm_ptr_t p_fsm );
void af_acamera_process_stats( af_acamera_fsm_ptr_t p_fsm );
void af_acamera_update( af_acamera_fsm_ptr_t p_fsm );
void af_acamera_config_input_roi( af_acamera_fsm_ptr_t p_fsm );

#include "acamera_metering_stats_mem_config.h"

struct _af_acamera_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint32_t zone_raw_statistic[AF_ZONES_COUNT_MAX][AF_STATS_NUM_ROWS];
    uint8_t zones_horiz;
    uint8_t zones_vert;
    uint8_t skip_frames;

    uint32_t pos_min;
    uint32_t pos_max;
    uint8_t mode;
    uint32_t pos_manual;
    uint32_t roi;
    int32_t lens_driver_ok;
    uint32_t roi_api;
    uint32_t last_position;
    int32_t last_sharp_done;

    uint32_t new_lens_pos;
    int32_t new_sharp_val;

    void *lens_ctx;
    lens_control_t lens_ctrl;
    af_status_t af_status;
    af_state_t state;
    caf_state_t caf_state;
    lens_param_t lens_param;

    uint8_t refocus_required;

#if FW_ALG_SUPPORT_SHARED_LIB
    void *lib_handle;
#endif
    af_std_obj_t af_alg_obj;
#if USER_MODULE
    uint8_t skip_cur_frame;
#endif
};


void af_acamera_fsm_clear( af_acamera_fsm_ptr_t p_fsm );

void af_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param );
void af_acamera_fsm_deinit( void *fsm );
int af_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int af_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t af_acamera_fsm_process_event( af_acamera_fsm_ptr_t p_fsm, event_id_t event_id );
void af_acamera_fsm_process_interrupt( af_acamera_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void af_acamera_request_interrupt( af_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __AF_ACAMERA_FSM_H__ */

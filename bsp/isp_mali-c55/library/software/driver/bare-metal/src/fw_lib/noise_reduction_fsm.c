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

#include "acamera_fw.h"
#include "noise_reduction_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_NOISE_REDUCTION
#endif

void noise_reduction_fsm_clear( noise_reduction_fsm_t *p_fsm )
{
    p_fsm->temper_ev_previous_frame = 0;
    p_fsm->temper_diff_avg = 0;
    p_fsm->temper_diff_coeff = 10;
    p_fsm->snr_thresh_contrast = 0;

    p_fsm->nr_mode = NOISE_REDUCTION_MODE_ON;
}

void noise_reduction_request_interrupt( noise_reduction_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}

void noise_reduction_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    noise_reduction_fsm_t *p_fsm = (noise_reduction_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    noise_reduction_fsm_clear( p_fsm );

    noise_reduction_initialize( p_fsm );
    noise_reduction_hw_init( p_fsm );
}

uint8_t noise_reduction_fsm_process_event( noise_reduction_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_frame_end:
        noise_reduction_update( p_fsm );
        noise_reduction_initialize( p_fsm );
        b_event_processed = 1;
        break;
    }

    return b_event_processed;
}

int noise_reduction_fsm_set_param( void *fsm, uint32_t param_id,
                                   void *input, uint32_t input_size )
{
    int rc = 0;
    noise_reduction_fsm_t *p_fsm = (noise_reduction_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_NOISE_REDUCTION_MODE: {
        if ( !input || input_size != sizeof( noise_reduction_mode_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->nr_mode = *(noise_reduction_mode_t *)input;

        break;
    }

    default:
        rc = -1;
        break;
    };

    return rc;
}

int noise_reduction_fsm_get_param( void *fsm, uint32_t param_id,
                                    void *input, uint32_t input_size,
                                    void *output, uint32_t output_size )
{
    int rc = 0;
    noise_reduction_fsm_t *p_fsm = (noise_reduction_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_NOISE_REDUCTION_MODE: {

        if ( !output || output_size != sizeof( noise_reduction_mode_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(noise_reduction_mode_t *)output = p_fsm->nr_mode;

        break;
    }

    default:
        rc = -1;
        break;
    };

    return rc;
}


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
#include "gamma_acamera_fsm.h"

#if defined( ISP_HAS_USER2KERNEL_FSM )
#include "sbuf.h"
#endif

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_GAMMA_ACAMERA
#endif

void gamma_acamera_fsm_clear( gamma_acamera_fsm_t *p_fsm )
{
    p_fsm->cur_using_stats_frame_id = 0;
    p_fsm->gamma_gain = 256;
    p_fsm->gamma_offset = 0;

#if FW_ALG_SUPPORT_SHARED_LIB
    p_fsm->lib_handle = NULL;
#endif
    memset( &p_fsm->gamma_alg_obj, 0, sizeof( p_fsm->gamma_alg_obj ) );
}

void gamma_contrast_request_interrupt( gamma_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}

void gamma_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    gamma_acamera_fsm_t *p_fsm = (gamma_acamera_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    gamma_acamera_fsm_clear( p_fsm );

    gamma_acamera_init( p_fsm );
}

void gamma_acamera_fsm_deinit( void *fsm )
{
    gamma_acamera_fsm_ptr_t p_fsm = (gamma_acamera_fsm_ptr_t)fsm;
    gamma_acamera_deinit( p_fsm );
}

int gamma_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;

#if defined( ISP_HAS_USER2KERNEL_FSM )
    gamma_acamera_fsm_t *p_fsm = (gamma_acamera_fsm_t *)fsm;
#endif

    switch ( param_id ) {
#if defined( ISP_HAS_USER2KERNEL_FSM )
    case FSM_PARAM_SET_GAMMA_STATS: {
        if ( !input || input_size != sizeof( sbuf_gamma_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        sbuf_gamma_t *p_sbuf_gamma = (sbuf_gamma_t *)input;

        p_fsm->fullhist_sum = p_sbuf_gamma->fullhist_sum;
        system_memcpy( p_fsm->fullhist, p_sbuf_gamma->stats_data, sizeof( p_fsm->fullhist ) );
        fsm_raise_event( p_fsm, event_id_gamma_stats_ready );

        break;
    }
#endif
    default:
        rc = -1;
        break;
    }

    return rc;
}


int gamma_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    gamma_acamera_fsm_t *p_fsm = (gamma_acamera_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_GAMMA_CONTRAST_RESULT: {
        if ( !output || output_size != sizeof( fsm_param_gamma_result_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_gamma_result_t *p_result = (fsm_param_gamma_result_t *)output;

        p_result->gamma_gain = p_fsm->gamma_gain;
        p_result->gamma_offset = p_fsm->gamma_offset;

        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}


uint8_t gamma_acamera_fsm_process_event( gamma_acamera_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_gamma_stats_ready:
        gamma_acamera_process_stats( p_fsm );
        gamma_contrast_request_interrupt( p_fsm, ACAMERA_IRQ_MASK( ACAMERA_IRQ_ANTIFOG_HIST ) );
        b_event_processed = 1;
        break;
    }

    return b_event_processed;
}

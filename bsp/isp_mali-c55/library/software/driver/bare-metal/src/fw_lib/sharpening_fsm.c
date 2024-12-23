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
#include "sharpening_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SHARPENING
#endif

void sharpening_fsm_clear( sharpening_fsm_t *p_fsm )
{
    p_fsm->sharpening_mult = 128;
    p_fsm->api_value = 128;
}

void sharpening_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    sharpening_fsm_t *p_fsm = (sharpening_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    sharpening_fsm_clear( p_fsm );

    sharpening_initialize( p_fsm );
    fsm_raise_event( p_fsm, event_id_sharp_lut_update );
}


int sharpening_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    sharpening_fsm_t *p_fsm = (sharpening_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_SHARPENING_INIT:
        sharpening_initialize( p_fsm );
        break;
    case FSM_PARAM_SET_SHARPENING_MULT: {
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->sharpening_mult = *(uint32_t *)input;
        break;
    }

    case FSM_PARAM_SET_SHARPENING_STRENGTH: {
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->api_value = *(uint32_t *)input;

        if ( p_fsm->api_value <= 128 ) {
            p_fsm->sharpening_mult = p_fsm->api_value;
        } else {
            uint32_t store;
            // 4th power seems to be a good fit for this
            // as alt_d/ud are O(10) and max is 255.
            store = ( p_fsm->api_value * p_fsm->api_value * p_fsm->api_value * p_fsm->api_value );
            store /= 0x200000;
            p_fsm->sharpening_mult = store;
        }

        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}


int sharpening_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    sharpening_fsm_t *p_fsm = (sharpening_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_SHARPENING_STRENGTH: {
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->api_value;

        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}


uint8_t sharpening_fsm_process_event( sharpening_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;

    case event_id_frame_end:
        sharpening_update( p_fsm );
        b_event_processed = 1;
        break;

    case event_id_update_sharp_lut:

        break;
    }

    return b_event_processed;
}

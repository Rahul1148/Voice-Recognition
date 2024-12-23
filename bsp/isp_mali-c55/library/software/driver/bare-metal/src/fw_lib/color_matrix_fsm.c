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
#include "color_matrix_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_COLOR_MATRIX
#endif


void color_matrix_fsm_clear( color_matrix_fsm_t *p_fsm )
{
    p_fsm->light_source = AWB_LIGHT_SOURCE_D50;
    p_fsm->light_source_previous = AWB_LIGHT_SOURCE_D50;
    p_fsm->light_source_ccm = AWB_LIGHT_SOURCE_D50;
    p_fsm->light_source_ccm_previous = AWB_LIGHT_SOURCE_D50;
    p_fsm->light_source_change_frames = 20;
    p_fsm->light_source_change_frames_left = 0;
    p_fsm->manual_CCM = 0;
}


void color_matrix_request_interrupt( color_matrix_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}


void color_matrix_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    color_matrix_fsm_t *p_fsm = (color_matrix_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    color_matrix_fsm_clear( p_fsm );

    color_matrix_initialize( p_fsm );
    color_matrix_request_interrupt( p_fsm, ACAMERA_IRQ_MASK( ACAMERA_IRQ_FRAME_END ) );
}


int color_matrix_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    color_matrix_fsm_t *p_fsm = (color_matrix_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_CCM_INFO: {
        if ( !input || input_size != sizeof( fsm_param_ccm_info_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_ccm_info_t *p_info = (fsm_param_ccm_info_t *)input;

        p_fsm->light_source = p_info->light_source;
        p_fsm->light_source_previous = p_info->light_source_previous;
        p_fsm->light_source_ccm = p_info->light_source_ccm;
        p_fsm->light_source_ccm_previous = p_info->light_source_ccm_previous;
        p_fsm->light_source_change_frames = p_info->light_source_change_frames;
        p_fsm->light_source_change_frames_left = p_info->light_source_change_frames_left;

        break;
    }

    case FSM_PARAM_SET_CCM_CHANGE:
        color_matrix_change_CCMs( p_fsm );
        break;

    case FSM_PARAM_SET_SHADING_MESH_RELOAD:
        color_matrix_shading_mesh_reload( p_fsm );
        break;

    case FSM_PARAM_SET_MANUAL_CCM: {
        if ( !input || input_size != sizeof( fsm_param_ccm_manual_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_ccm_manual_t *p_manual = (fsm_param_ccm_manual_t *)input;

        p_fsm->manual_CCM = p_manual->manual_CCM;
        if ( p_fsm->manual_CCM ) {
            system_memcpy( p_fsm->manual_color_matrix, p_manual->manual_color_matrix, sizeof( p_manual->manual_color_matrix ) );
        }
        break;
    }

    case FSM_PARAM_SET_SHADING_STRENGTH:
        if ( !input || input_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->manual_shading_mesh_strength = *(int32_t *)input;

        break;

    default:
        rc = -1;
        break;
    }

    return rc;
}


int color_matrix_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    color_matrix_fsm_t *p_fsm = (color_matrix_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_CCM_INFO: {
        if ( !output || output_size != sizeof( fsm_param_ccm_info_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_ccm_info_t *p_info = (fsm_param_ccm_info_t *)output;

        p_info->light_source = p_fsm->light_source;
        p_info->light_source_previous = p_fsm->light_source_previous;
        p_info->light_source_ccm = p_fsm->light_source_ccm;
        p_info->light_source_ccm_previous = p_fsm->light_source_ccm_previous;
        p_info->light_source_change_frames = p_fsm->light_source_change_frames;
        p_info->light_source_change_frames_left = p_fsm->light_source_change_frames_left;

        break;
    }

    case FSM_PARAM_GET_SHADING_ALPHA:
        if ( !output || output_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(int32_t *)output = p_fsm->shading_alpha;

        break;

    case FSM_PARAM_GET_SHADING_MESH_MAP: {
        if ( !output || output_size != sizeof( fsm_param_lsc_mesh_map_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_lsc_mesh_map_t *p_lsc_map = (fsm_param_lsc_mesh_map_t *)output;
        rc = color_matrix_mesh_get_lsc_map( p_fsm, p_lsc_map );
        if (rc) {
            LOG( LOG_ERR, "Unable to get lsc map rc: %d.", rc );
            return rc;
        }

        break;
    }

    case FSM_PARAM_GET_SHADING_STRENGTH:
        if ( !output || output_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(int32_t *)output = p_fsm->shading_mesh_strength;

        break;

    default:
        rc = -1;
        break;
    }

    return rc;
}


uint8_t color_matrix_fsm_process_event( color_matrix_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_frame_end:
        color_matrix_update( p_fsm );
        color_matrix_request_interrupt( p_fsm, ACAMERA_IRQ_MASK( ACAMERA_IRQ_FRAME_END ) );
        b_event_processed = 1;
        break;
    }

    return b_event_processed;
}

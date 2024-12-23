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
#include "af_acamera_fsm.h"

#if defined( ISP_HAS_USER2KERNEL_FSM )
#include "sbuf.h"
#endif

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_AF_ACAMERA
#endif

void af_acamera_fsm_clear( af_acamera_fsm_t *p_fsm )
{
    p_fsm->mode = AF_MODE_CAF;
    p_fsm->pos_manual = 0;
    p_fsm->roi = 0x4040C0C0;
    p_fsm->lens_driver_ok = 0;
    p_fsm->roi_api = 0x4040C0C0;
    p_fsm->af_status = AF_STATUS_INVALID;
    p_fsm->last_sharp_done = 0;
    p_fsm->zones_horiz = 0;
    p_fsm->zones_vert = 0;
    p_fsm->refocus_required = 1;
    p_fsm->last_position = 0;
    p_fsm->new_lens_pos = 0;
    p_fsm->new_sharp_val = 0;
    p_fsm->state = AF_STATE_INACTIVE;
    memset( &p_fsm->lens_ctrl, 0, sizeof( p_fsm->lens_ctrl ) );
    memset( &p_fsm->lens_param, 0, sizeof( p_fsm->lens_param ) );
}

void af_acamera_request_interrupt( af_acamera_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}

void af_acamera_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    af_acamera_fsm_t *p_fsm = (af_acamera_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    af_acamera_fsm_clear( p_fsm );

    af_acamera_init( p_fsm );
}

void af_acamera_fsm_deinit( void *fsm )
{
    af_acamera_fsm_t *p_fsm = (af_acamera_fsm_t *)fsm;
    af_acamera_deinit( p_fsm );
}

int af_acamera_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    af_acamera_fsm_t *p_fsm = (af_acamera_fsm_t *)fsm;

    if ( !p_fsm->lens_driver_ok ) {
        LOG( LOG_INFO, "Not supported: no lens driver." );
        return -1;
    }

    switch ( param_id ) {
#if defined( ISP_HAS_USER2KERNEL_FSM )
    case FSM_PARAM_SET_AF_STATS: {
        if ( !input || input_size != sizeof( sbuf_af_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        sbuf_af_t *p_sbuf_af = (sbuf_af_t *)input;

        p_fsm->zones_horiz = p_sbuf_af->zones_horiz;
        p_fsm->zones_vert = p_sbuf_af->zones_vert;
        p_fsm->skip_cur_frame = p_sbuf_af->skip_cur_frame;
        system_memcpy( p_fsm->zone_raw_statistic, p_sbuf_af->stats_data, sizeof( p_fsm->zone_raw_statistic ) );
        fsm_raise_event( p_fsm, event_id_af_stats_ready );

        break;
    }
#endif

    case FSM_PARAM_SET_AF_MODE:
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->mode = *(uint32_t *)input;
        fsm_raise_event( p_fsm, event_id_af_refocus );

        break;

    case FSM_PARAM_SET_AF_MANUAL_POS: {
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        uint32_t pos_manual = *(uint32_t *)input;

        if ( pos_manual <= 256 ) {
            p_fsm->pos_manual = pos_manual;
            fsm_raise_event( p_fsm, event_id_af_refocus );
        }

        break;
    }

    case FSM_PARAM_SET_AF_ROI: {
        if ( !input || input_size != sizeof( fsm_param_roi_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_roi_t *p_new = (fsm_param_roi_t *)input;
        p_fsm->roi_api = p_new->roi_api;
        p_fsm->roi = p_new->roi;

        fsm_raise_event( p_fsm, event_id_af_refocus );

        break;
    }

    case FSM_PARAM_SET_AF_INPUT_ROI_RELOAD: {
        af_acamera_config_input_roi( p_fsm );
        break;
    }

    case FSM_PARAM_SET_AF_LENS_REG: {
        if ( !input || input_size != sizeof( fsm_param_reg_cfg_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_reg_cfg_t *p_cfg = (fsm_param_reg_cfg_t *)input;
        p_fsm->lens_ctrl.write_lens_register( p_fsm->lens_ctx, p_cfg->reg_addr, p_cfg->reg_value );
        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}


int af_acamera_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    af_acamera_fsm_t *p_fsm = (af_acamera_fsm_t *)fsm;

    if ( !p_fsm->lens_driver_ok ) {
        LOG( LOG_INFO, "Not supported: no lens driver." );
        return -1;
    }

    switch ( param_id ) {
    case FSM_PARAM_GET_AF_INFO: {
        if ( !output || output_size != sizeof( fsm_param_af_info_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_af_info_t *p_af_info = (fsm_param_af_info_t *)output;

        p_af_info->last_position = p_fsm->last_position;
        p_af_info->last_sharp = p_fsm->last_sharp_done;
        p_af_info->skip_frames = p_fsm->skip_frames;
        break;
    }

    case FSM_PARAM_GET_AF_MODE:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->mode;

        break;

    case FSM_PARAM_GET_CAF_STATE: {
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }
        *(caf_state_t *)output = p_fsm->caf_state;
        break;
    }

    case FSM_PARAM_GET_AF_STATE: {
        if ( !output || output_size != sizeof( af_state_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(af_state_t *)output = p_fsm->state;

        break;
    }

    case FSM_PARAM_GET_LENS_PARAM: {
        if ( !output || output_size != sizeof( lens_param_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        const lens_param_t *p_lens_param = p_fsm->lens_ctrl.get_parameters( p_fsm->lens_ctx );

        *(lens_param_t *)output = *p_lens_param;

        break;
    }

    case FSM_PARAM_GET_AF_MANUAL_POS: {
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        uint16_t af_range = p_fsm->pos_max - p_fsm->pos_min;
        uint32_t last_position = p_fsm->last_position;
        uint32_t pos = 0;

        if ( last_position < p_fsm->pos_min ) {
            last_position = p_fsm->pos_min;
        } else if ( last_position > p_fsm->pos_max ) {
            last_position = p_fsm->pos_max;
        }

        pos = ( ( ( last_position - p_fsm->pos_min ) << 8 ) + af_range / 2 ) / ( af_range );

        if ( pos > 255 ) {
            pos = 255;
        }

        *(uint32_t *)output = pos;

        break;
    }

    case FSM_PARAM_GET_AF_ROI: {
        if ( !output || output_size != sizeof( fsm_param_roi_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_roi_t *p_current = (fsm_param_roi_t *)output;
        p_current->roi_api = p_fsm->roi_api;
        p_current->roi = p_fsm->roi;
        break;
    }

    case FSM_PARAM_GET_AF_LENS_REG:
        if ( !input || input_size != sizeof( uint32_t ) ||
             !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->lens_ctrl.read_lens_register( p_fsm->lens_ctx, *(uint32_t *)input );
        break;

    case FSM_PARAM_GET_AF_LENS_STATUS:
        if ( !output || output_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(int32_t *)output = p_fsm->lens_driver_ok;
        break;

    default:
        rc = -1;
        break;
    }

    return rc;
}

uint8_t af_acamera_fsm_process_event( af_acamera_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;

    if ( !p_fsm->lens_driver_ok ) {
        LOG( LOG_INFO, "Not supported: no lens driver." );
        return 0;
    }

    switch ( event_id ) {
    default:
        break;

    case event_id_af_stats_ready:
        af_acamera_process_stats( p_fsm );
        af_acamera_update( p_fsm );
        b_event_processed = 1;
        break;

    case event_id_af_refocus:
        p_fsm->refocus_required = 1;
        b_event_processed = 1;
        break;

    case event_id_sensor_ready:
        af_acamera_config_input_roi( p_fsm );
        b_event_processed = 1;
        break;
    }

    return b_event_processed;
}

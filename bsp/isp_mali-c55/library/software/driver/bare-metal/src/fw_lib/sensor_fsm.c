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
#include "sensor_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SENSOR
#endif

void sensor_fsm_clear( sensor_fsm_t *p_fsm )
{
    p_fsm->mode = ( 0 );
    p_fsm->preset_mode = SENSOR_DEFAULT_PRESET_MODE;
    p_fsm->isp_output_mode = ( ISP_DISPLAY_MODE );
    p_fsm->is_streaming = ( 0 );
    p_fsm->info_preset_num = SENSOR_DEFAULT_PRESET_MODE;
    p_fsm->boot_status = sensor_boot_init( p_fsm );
}

void sensor_request_interrupt( sensor_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}


void sensor_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    sensor_fsm_t *p_fsm = (sensor_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    sensor_fsm_clear( p_fsm );

    sensor_hw_init( p_fsm );
    sensor_sw_init( p_fsm );
    fsm_raise_event( p_fsm, event_id_sensor_ready );
}

int sensor_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    sensor_fsm_t *p_fsm = (sensor_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_SENSOR_STREAMING:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->is_streaming;

        break;

    case FSM_PARAM_GET_SENSOR_LINES_SECOND:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = sensor_get_lines_second( p_fsm );

        break;

    case FSM_PARAM_GET_SENSOR_INFO: {
        const sensor_param_t *param;
        if ( !output || output_size != sizeof( fsm_param_sensor_info_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
        fsm_param_sensor_info_t *p_sensor_info = (fsm_param_sensor_info_t *)output;

        p_sensor_info->total_width = param->total.width;
        p_sensor_info->total_height = param->total.height;
        p_sensor_info->active_width = param->active.width;
        p_sensor_info->active_height = param->active.height;
        p_sensor_info->pixels_per_line = param->pixels_per_line;
        p_sensor_info->lines_per_second = param->lines_per_second;

        p_sensor_info->again_log2_max = param->again_log2_max;
        p_sensor_info->dgain_log2_max = param->dgain_log2_max;
        p_sensor_info->integration_time_min = param->integration_time_min;
        p_sensor_info->integration_time_max = param->integration_time_max;
        p_sensor_info->integration_time_long_max = param->integration_time_long_max;
        p_sensor_info->integration_time_limit = param->integration_time_limit;

        p_sensor_info->integration_time_apply_delay = param->integration_time_apply_delay;
        p_sensor_info->sensor_exp_number = param->sensor_exp_number;
        p_sensor_info->isp_exposure_channel_delay = param->isp_exposure_channel_delay;

        p_sensor_info->isp_output_mode = p_fsm->isp_output_mode;
        p_sensor_info->resolution_mode = p_fsm->mode;
        p_sensor_info->black_level = p_fsm->black_level;
        p_sensor_info->sensor_bits = param->modes_table[param->mode].bits;
        break;
    }

    case FSM_PARAM_GET_SENSOR_PARAM:
        if ( !output || output_size != sizeof( sensor_param_t ** ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *( (const sensor_param_t **)output ) = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );

        break;

    case FSM_PARAM_GET_SENSOR_INFO_PRESET_NUM:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->info_preset_num;

        break;

    case FSM_PARAM_GET_SENSOR_REG:
        if ( !input || input_size != sizeof( uint32_t ) ||
             !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->ctrl.read_sensor_register( p_fsm->sensor_ctx, *(uint32_t *)input );
        break;

    case FSM_PARAM_GET_SENSOR_ID:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->ctrl.get_id( p_fsm->sensor_ctx );
        break;

    case FSM_PARAM_GET_SENSOR_MAX_RESOLUTION: {
        image_resolution_t *max_res = (image_resolution_t *)output;
        image_resolution_t *cur_res;
        const sensor_param_t *sensor_param = p_fsm->ctrl.get_parameters( p_fsm->sensor_ctx );
        sensor_mode_t *modes_table = sensor_param->modes_table;
        uint32_t max_size = 0, size_res;
        int i;

        if ( !max_res || output_size != sizeof( *max_res ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        if ( !modes_table ) {
            rc = -1;
            break;
        }

        for ( i = 0; i < sensor_param->modes_num; i++ ) {
            cur_res = &modes_table[i].resolution;
            size_res = (uint32_t)cur_res->width * cur_res->height;
            if ( size_res > max_size ) {
                max_size = size_res;
                max_res->width = cur_res->width;
                max_res->height = cur_res->height;
            }
        }

        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}

int sensor_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    sensor_fsm_t *p_fsm = (sensor_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_SENSOR_STREAMING: {
        uint32_t streaming;
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        streaming = *(uint32_t *)input;

        if ( streaming ) {
            p_fsm->ctrl.start_streaming( p_fsm->sensor_ctx );
        } else {
            p_fsm->ctrl.stop_streaming( p_fsm->sensor_ctx );
        }

        p_fsm->is_streaming = streaming;

        sensor_tpg_start_stop_streaming( p_fsm );
        break;
    }

    case FSM_PARAM_SET_SENSOR_PRESET_MODE:
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->preset_mode = *(uint32_t *)input;
        break;

    case FSM_PARAM_SET_SENSOR_INFO_PRESET_NUM:
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->info_preset_num = *(uint32_t *)input;

        break;

    case FSM_PARAM_SET_SENSOR_ALLOC_ANALOG_GAIN: {
        if ( !input || input_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        int32_t expect_again = *( (int32_t *)input );

        *( (int32_t *)input ) = p_fsm->ctrl.alloc_analog_gain( p_fsm->sensor_ctx, expect_again );

        break;
    }

    case FSM_PARAM_SET_SENSOR_ALLOC_DIGITAL_GAIN: {
        if ( !input || input_size != sizeof( int32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        int32_t expect_dgain = *( (int32_t *)input );

        *( (int32_t *)input ) = p_fsm->ctrl.alloc_digital_gain( p_fsm->sensor_ctx, expect_dgain );

        break;
    }

    case FSM_PARAM_SET_SENSOR_ALLOC_INTEGRATION_TIME: {
        if ( !input || input_size != sizeof( fsm_param_sensor_int_time_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_sensor_int_time_t *p_time = (fsm_param_sensor_int_time_t *)input;

        p_fsm->ctrl.alloc_integration_time( p_fsm->sensor_ctx, &p_time->int_time, &p_time->int_time_M, &p_time->int_time_L );

        break;
    }

    case FSM_PARAM_SET_SENSOR_UPDATE:

        p_fsm->ctrl.sensor_update( p_fsm->sensor_ctx );

        break;

    case FSM_PARAM_SET_SENSOR_REG: {
        if ( !input || input_size != sizeof( fsm_param_reg_cfg_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_reg_cfg_t *p_cfg = (fsm_param_reg_cfg_t *)input;
        p_fsm->ctrl.write_sensor_register( p_fsm->sensor_ctx, p_cfg->reg_addr, p_cfg->reg_value );
        break;
    }

    default:
        rc = -1;
        break;
    }

    return rc;
}

uint8_t sensor_fsm_process_event( sensor_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_frame_end:
        sensor_update_black( p_fsm );
        b_event_processed = 1;
        break;

    case event_id_sensor_sw_reset:
        fsm_raise_event( p_fsm, event_id_sensor_not_ready );
        sensor_sw_init( p_fsm );
        fsm_raise_event( p_fsm, event_id_sensor_ready );
        b_event_processed = 1;
        break;

    case event_id_acamera_reset_sensor_hw:
        fsm_raise_event( p_fsm, event_id_sensor_not_ready );
        sensor_hw_init( p_fsm );
        sensor_sw_init( p_fsm );
        fsm_raise_event( p_fsm, event_id_sensor_ready );
        b_event_processed = 1;
        break;
    }

    return b_event_processed;
}

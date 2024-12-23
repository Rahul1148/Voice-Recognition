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
#include "general_fsm.h"

#ifdef LOG_MODULE
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_GENERAL
#endif

void general_fsm_clear( general_fsm_t *p_fsm )
{
    p_fsm->api_reg_addr = 0;
    p_fsm->api_reg_size = 8;
    p_fsm->api_reg_source = 0;
    p_fsm->calibration_read_status = 0;
    p_fsm->wdr_mode = ISP_WDR_DEFAULT_MODE;

#if ISP_WDR_SWITCH
    p_fsm->wdr_mode_req = ISP_WDR_DEFAULT_MODE;
    p_fsm->wdr_mode_frames = 0;
    p_fsm->cur_exp_number = SENSOR_DEFAULT_EXP_NUM;
#endif
}

void general_request_interrupt( general_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    acamera_isp_interrupts_disable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
    p_fsm->mask.irq_mask |= mask;
    acamera_isp_interrupts_enable( ACAMERA_FSM2MGR_PTR( p_fsm ) );
}

void general_fsm_init( void *fsm, fsm_init_param_t *init_param )
{
    general_fsm_t *p_fsm = (general_fsm_t *)fsm;
    p_fsm->cmn.p_fsm_mgr = init_param->p_fsm_mgr;
    p_fsm->cmn.isp_base = init_param->isp_base;
    p_fsm->p_fsm_mgr = init_param->p_fsm_mgr;

    general_initialize( p_fsm );
}

void general_fsm_deinit( void *fsm )
{
    general_fsm_t *p_fsm = (general_fsm_t *)fsm;
    general_deinitialize( p_fsm );
}

static int general_set_reg_value( general_fsm_t *p_fsm, uint32_t value )
{
    int rc = 0;

#if REGISTERS_SOURCE_ID
    switch ( p_fsm->api_reg_source ) {
    case ISP:
        switch ( p_fsm->api_reg_size ) {
        case 8:
            acamera_sbus_write_u8( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr, value );
            break;
        case 16:
            acamera_sbus_write_u16( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr, value );
            break;
        case 32:
            acamera_sbus_write_u32( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr, value );
            break;
        default:
            rc = -1;
            break;
        }

        break;

    case SENSOR: {
        fsm_param_reg_cfg_t reg_cfg;
        reg_cfg.reg_addr = p_fsm->api_reg_addr;
        reg_cfg.reg_value = value;
        rc = acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_SENSOR_REG, &reg_cfg, sizeof( reg_cfg ) );
        break;
    }

#if defined( ISP_HAS_AF_LMS_FSM ) || defined( ISP_HAS_AF_MANUAL_FSM ) || defined( ISP_HAS_AF_ACAMERA_FSM )
    case LENS: {
        fsm_param_reg_cfg_t reg_cfg;
        reg_cfg.reg_addr = p_fsm->api_reg_addr;
        reg_cfg.reg_value = value;
        rc = acamera_fsm_mgr_set_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_SET_AF_LENS_REG, &reg_cfg, sizeof( reg_cfg ) );
        break;
    }
#endif

    default:
        rc = -1;
        break;
    }
#endif

    return rc;
}

int general_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;
    general_fsm_t *p_fsm = (general_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_SET_RELOAD_CALIBRATION:
        acamera_reload_isp_calibratons( p_fsm );
        break;

    case FSM_PARAM_SET_WDR_MODE: {

        if ( !input || input_size != sizeof( fsm_param_set_wdr_param_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_set_wdr_param_t *wdr_param = (fsm_param_set_wdr_param_t *)input;

#if ISP_WDR_SWITCH
        p_fsm->wdr_mode_req = wdr_param->wdr_mode;

        if ( ( p_fsm->wdr_mode_req != p_fsm->wdr_mode ) || ( p_fsm->cur_exp_number != wdr_param->exp_number ) ) {
            p_fsm->wdr_mode = p_fsm->wdr_mode_req;
            p_fsm->cur_exp_number = wdr_param->exp_number;

            general_set_wdr_mode( p_fsm );

            p_fsm->wdr_mode_frames = 0;
        }
#else
        p_fsm->wdr_mode = wdr_param->wdr_mode;
#endif
        break;
    }

    case FSM_PARAM_SET_REG_SETTING: {
        if ( !input || input_size != sizeof( fsm_param_reg_setting_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_reg_setting_t *p_input = (fsm_param_reg_setting_t *)input;

        if ( p_input->flag & REG_SETTING_BIT_REG_ADDR ) {
            p_fsm->api_reg_addr = p_input->api_reg_addr;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_SIZE ) {
            p_fsm->api_reg_size = p_input->api_reg_size;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_SOURCE ) {
            p_fsm->api_reg_source = p_input->api_reg_source;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_VALUE ) {
            rc = general_set_reg_value( p_fsm, p_input->api_reg_value );
        }
        break;
    }

    case FSM_PARAM_SET_SCENE_MODE:
        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        p_fsm->api_scene_mode = *(uint32_t *)input;

        break;
#if ISP_HW_IS_MALI_C32_C52
    case FSM_PARAM_SET_TEMPER_MODE: {
#if GENERAL_TEMPER_ENABLED
        uint32_t mode;

        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        mode = *(uint32_t *)input;
        rc = general_temper_set_mode( p_fsm, mode );
#endif

        break;
    }
#else
    case FSM_PARAM_SET_TEMPER4_MODE: {
#if GENERAL_TEMPER_ENABLED
        uint32_t mode;

        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        mode = *(uint32_t *)input;
        rc = general_temper4_set_mode( p_fsm, mode );
#endif

        break;
    }
    case FSM_PARAM_SET_TEMPER4_COMPRESS_PIXEL_MODE: {
#if GENERAL_TEMPER_ENABLED
        uint32_t mode;

        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        mode = *(uint32_t *)input;
        rc = general_temper4_set_compress_pixel_mode( p_fsm, mode );
#endif

        break;
    }
    case FSM_PARAM_SET_TEMPER4_COMPRESS_META_MODE: {
#if GENERAL_TEMPER_ENABLED
        uint32_t mode;

        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        mode = *(uint32_t *)input;
        rc = general_temper4_set_compress_meta_mode( p_fsm, mode );
#endif

        break;
    }
#endif
    case FSM_PARAM_SET_FR_RAW_BYPASS: {
        uint32_t enabled;

        if ( !input || input_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        enabled = *(uint32_t *)input;
        rc = general_set_fr_raw_bypass( p_fsm, enabled );

        break;
    }
    case FSM_PARAM_SET_HDMI_4K:
        p_fsm->hdmi_4k = *(uint8_t *)input;
        general_set_hdmi_resolution( p_fsm );
        break;


    default:
        rc = -1;
        break;
    }

    return rc;
}

static int general_get_reg_value( general_fsm_t *p_fsm, uint32_t *value )
{
    int rc = 0;

#if REGISTERS_SOURCE_ID
    switch ( p_fsm->api_reg_source ) {
    case ISP:
        switch ( p_fsm->api_reg_size ) {
        case 8:
            *value = acamera_sbus_read_u8( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr );
            break;
        case 16:
            *value = acamera_sbus_read_u16( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr );
            break;
        case 32:
            *value = acamera_sbus_read_u32( &( p_fsm->isp_sbus ), p_fsm->api_reg_addr );
            break;
        default:
            *value = ERR_BAD_ARGUMENT;
            rc = -1;
            break;
        }

        break;

    case SENSOR:
        rc = acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_SENSOR_REG, &p_fsm->api_reg_addr, sizeof( p_fsm->api_reg_addr ), value, sizeof( uint32_t ) );
        break;

#if defined( ISP_HAS_AF_LMS_FSM ) || defined( ISP_HAS_AF_MANUAL_FSM ) || defined( ISP_HAS_AF_ACAMERA_FSM )
    case LENS:
        rc = acamera_fsm_mgr_get_param( p_fsm->cmn.p_fsm_mgr, FSM_PARAM_GET_AF_LENS_REG, &p_fsm->api_reg_addr, sizeof( p_fsm->api_reg_addr ), value, sizeof( uint32_t ) );
        break;
#endif

    default:
        *value = ERR_BAD_ARGUMENT;
        rc = -1;
        break;
    }
#endif

    return rc;
}

int general_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;
    general_fsm_t *p_fsm = (general_fsm_t *)fsm;

    switch ( param_id ) {
    case FSM_PARAM_GET_WDR_MODE:

        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->wdr_mode;

        break;

    case FSM_PARAM_GET_CALC_FE_LUT_OUTPUT:

        if ( !input || input_size != sizeof( uint32_t ) ||
             !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        // Based on old code, the input param is an uint32_t, but in function we just used uint16_t.
        *(uint32_t *)output = general_calc_fe_lut_output( p_fsm, *(uint16_t *)input );

        break;

    case FSM_PARAM_GET_REG_SETTING: {
        if ( !input || input_size != sizeof( fsm_param_reg_setting_t ) ||
             !output || output_size != sizeof( fsm_param_reg_setting_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        fsm_param_reg_setting_t *p_input = (fsm_param_reg_setting_t *)input;
        fsm_param_reg_setting_t *p_output = (fsm_param_reg_setting_t *)output;

        if ( p_input->flag & REG_SETTING_BIT_REG_ADDR ) {
            p_output->api_reg_addr = p_fsm->api_reg_addr;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_SIZE ) {
            p_output->api_reg_size = p_fsm->api_reg_size;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_SOURCE ) {
            p_output->api_reg_source = p_fsm->api_reg_source;
        }

        if ( p_input->flag & REG_SETTING_BIT_REG_VALUE ) {
            rc = general_get_reg_value( p_fsm, &p_output->api_reg_value );
        }

        break;
    }

    case FSM_PARAM_GET_SCENE_MODE:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Invalid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->api_scene_mode;

        break;
#if ISP_HW_IS_MALI_C32_C52
    case FSM_PARAM_GET_TEMPER_MODE:
#if GENERAL_TEMPER_ENABLED
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->temper_mode;
#endif
        break;
#else
    case FSM_PARAM_GET_TEMPER4_MODE:
#if GENERAL_TEMPER_ENABLED
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->temper_mode;
#endif
        break;
    case FSM_PARAM_GET_TEMPER4_COMPRESS_PIXEL_MODE:
#if GENERAL_TEMPER_ENABLED
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->temper4_compress_pixel_mode;
#endif
        break;
    case FSM_PARAM_GET_TEMPER4_COMPRESS_META_MODE:
#if GENERAL_TEMPER_ENABLED
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->temper4_compress_meta_mode;
#endif
        break;
#endif
    case FSM_PARAM_GET_FR_RAW_BYPASS:
        if ( !output || output_size != sizeof( uint32_t ) ) {
            LOG( LOG_ERR, "Inavlid param, param_id: %d.", param_id );
            rc = -1;
            break;
        }

        *(uint32_t *)output = p_fsm->fr_raw_bypass;
        break;
    case FSM_PARAM_GET_HDMI_4K:
        *(uint8_t *)output = p_fsm->hdmi_4k;
        break;

    default:
        rc = -1;
        break;
    }

    return rc;
}

uint8_t general_fsm_process_event( general_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;


    switch ( event_id ) {
    default:
        break;
    case event_id_new_frame:
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_FRAME_START );
        b_event_processed = 1;
        break;
    case event_id_new_stats:
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_ANTIFOG_HIST );
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_AF2_STATS );
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_AWB_STATS );
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_AE_STATS );
        b_event_processed = 1;
        break;
    case event_id_end_frame:
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_FRAME_END );

        //need to be almost sync as the new address available from FR or DS
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_FRAME_WRITER_FR ); //enabled for DMA_WRITER_FSM
        acamera_general_interrupt_hanlder( ACAMERA_FSM2CTX_PTR( p_fsm ), ACAMERA_IRQ_FRAME_WRITER_DS );

        b_event_processed = 1;
        break;
    case event_id_sensor_ready:
#if GENERAL_TEMPER_ENABLED
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
        general_temper4_configure( p_fsm );
#endif
#endif
        general_set_wdr_mux_resolution( p_fsm );
        b_event_processed = 1;
        break;
    }
    return b_event_processed;
}

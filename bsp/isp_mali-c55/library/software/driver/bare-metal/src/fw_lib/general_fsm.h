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

#if !defined( __GENERAL_FSM_H__ )
#define __GENERAL_FSM_H__


#define GENERAL_TEMPER_ENABLED ( USER_MODULE == 0 )

#if GENERAL_TEMPER_ENABLED

#if ISP_HW_IS_MALI_C32_C52
#define TEMPER_FRAMES_NO 2
#define TEMPER_MODE_DEFAULT TEMPER3_MODE
#define TEMPER_PIXEL_WIDTH 32
#else
#define TEMPER_FRAMES_NO 1
#endif

#endif

typedef struct _general_fsm_t general_fsm_t;
typedef struct _general_fsm_t *general_fsm_ptr_t;
typedef const struct _general_fsm_t *general_fsm_const_ptr_t;

#include "acamera_sbus_api.h"
#include "acamera_firmware_config.h"
void acamera_reload_isp_calibratons( general_fsm_ptr_t p_fsm );
void general_initialize( general_fsm_ptr_t p_fsm );
void general_deinitialize( general_fsm_ptr_t p_fsm );
void general_frame_start( general_fsm_ptr_t p_fsm );
void general_frame_end( general_fsm_ptr_t p_fsm );
void general_set_hdmi_resolution( general_fsm_ptr_t p_fsm );
void general_set_wdr_mux_resolution( general_fsm_ptr_t p_fsm );
void general_set_wdr_mode( general_fsm_ptr_t p_fsm );
uint32_t general_calc_fe_lut_output( general_fsm_ptr_t p_fsm, uint16_t val );
uint32_t general_calc_fe_lut_input( general_fsm_ptr_t p_fsm, uint16_t val );
#if GENERAL_TEMPER_ENABLED
#if ISP_HW_IS_MALI_C32_C52
int general_temper_set_mode( general_fsm_ptr_t p_fsm, uint32_t mode );
#else
int general_temper4_set_mode( general_fsm_ptr_t p_fsm, uint32_t mode );
int general_temper4_configure( general_fsm_ptr_t p_fsm );
int general_temper4_set_finite_mode( general_fsm_ptr_t p_fsm, uint8_t mode );
int general_temper4_set_compress_pixel_mode( general_fsm_ptr_t p_fsm, uint8_t mode );
int general_temper4_set_compress_meta_mode( general_fsm_ptr_t p_fsm, uint8_t mode );
#endif
#endif
int general_set_fr_raw_bypass( general_fsm_ptr_t p_fsm, uint32_t enabled );


struct _general_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint32_t api_color_mode;
    uint32_t api_scene_mode;
    uint32_t api_reg_addr;
    uint16_t api_reg_size;
    uint16_t api_reg_source;
    uint16_t calibration_read_status;
    acamera_sbus_t isp_sbus;
    uint32_t wdr_mode;

#if ISP_WDR_SWITCH
    uint32_t wdr_mode_req;
    uint32_t wdr_mode_frames;
    uint32_t cur_exp_number;
#endif
#if GENERAL_TEMPER_ENABLED
    uint8_t temper_fitted;
    aframe_t temper_frames[TEMPER_FRAMES_NO];
    uint32_t temper_mode;
#if ( ISP_HW_IS_MALI_C32_C52 == 0 )
    uint8_t temper4_compress_pixel_mode;
    uint8_t temper4_compress_meta_mode;
#endif
    uint32_t cnt_for_temper;
#endif
    uint8_t fr_raw_bypass;
    uint8_t hdmi_4k;
    //when disabling dynamic gamma, we need to re apply the default only once
    uint8_t return_default_gamma;
};


void general_fsm_clear( general_fsm_ptr_t p_fsm );
void general_fsm_init( void *fsm, fsm_init_param_t *init_param );
void general_fsm_deinit( void *fsm );
int general_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int general_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t general_fsm_process_event( general_fsm_ptr_t p_fsm, event_id_t event_id );

void general_fsm_process_interrupt( general_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void general_request_interrupt( general_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __GENERAL_FSM_H__ */

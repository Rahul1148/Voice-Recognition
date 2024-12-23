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

#if !defined( __COLOR_MATRIX_FSM_H__ )
#define __COLOR_MATRIX_FSM_H__



typedef struct _color_matrix_fsm_t color_matrix_fsm_t;
typedef struct _color_matrix_fsm_t *color_matrix_fsm_ptr_t;
typedef const struct _color_matrix_fsm_t *color_matrix_fsm_const_ptr_t;

#ifndef AWB_LIGHT_SOURCE_D50
#define AWB_LIGHT_SOURCE_D50 0x03
#endif
uint16_t color_matrix_complement_to_direct( int16_t v );
int16_t color_matrix_direct_to_complement( uint16_t v );
void color_matrix_change_CCMs( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_recalculate( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_initialize( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_update( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_write( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_shading_mesh_reload( color_matrix_fsm_ptr_t p_fsm );
int color_matrix_mesh_get_lsc_map( color_matrix_fsm_ptr_t p_fsm,
                                   fsm_param_lsc_mesh_map_t *p_lsc_map );


struct _color_matrix_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    fsm_irq_mask_t mask;
    uint8_t color_matrix_enabled;
    uint8_t manual_saturation_enabled;
    uint8_t saturation_target;
    uint16_t color_wb_matrix[9];
    int16_t color_matrix[9];
    int16_t color_correction_matrix[9];
    int16_t color_saturation_matrix[9];
    uint8_t light_source;
    uint8_t light_source_previous;
    uint8_t light_source_ccm;
    uint8_t light_source_ccm_previous;
    uint8_t light_source_change_frames;
    uint8_t light_source_change_frames_left;
    int16_t color_matrix_A[9];
    int16_t color_matrix_D40[9];
    int16_t color_matrix_D50[9];
    int16_t color_matrix_one[9];
    int16_t shading_alpha;
    uint8_t shading_direction;
    uint8_t shading_source_previous;
    uint8_t manual_CCM;
    int16_t manual_color_matrix[9];
    int32_t temperature_threshold[8];

    int32_t shading_mesh_strength;
    int32_t manual_shading_mesh_strength;
};


void color_matrix_fsm_clear( color_matrix_fsm_ptr_t p_fsm );

void color_matrix_fsm_init( void *fsm, fsm_init_param_t *init_param );
int color_matrix_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int color_matrix_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );

uint8_t color_matrix_fsm_process_event( color_matrix_fsm_ptr_t p_fsm, event_id_t event_id );

void color_matrix_fsm_process_interrupt( color_matrix_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void color_matrix_request_interrupt( color_matrix_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __COLOR_MATRIX_FSM_H__ */

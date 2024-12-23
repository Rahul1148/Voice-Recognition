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

#if !defined( __DMA_WRITER_FSM_H__ )
#define __DMA_WRITER_FSM_H__



typedef struct _dma_writer_fsm_t dma_writer_fsm_t;
typedef struct _dma_writer_fsm_t *dma_writer_fsm_ptr_t;
typedef const struct _dma_writer_fsm_t *dma_writer_fsm_const_ptr_t;

enum _dma_writer_state_t {
    dma_writer_state_wait_for_sensor,
    dma_writer_state_frame_processing,
    dma_writer_state_frame_processing_FR_finished,
    dma_writer_state_frame_processing_wait_events,
    dma_writer_state_frame_processing_DS_finished,
    dma_writer_state_frame_processing_prepare_metadata,
    dma_writer_state_frame_processing_event_processed,
    dma_writer_state_frame_processing_init,
    dma_writer_state_frame_processing_DS2_finished,
    dma_writer_state_frame_processing_buf_reinit,
    dma_writer_state_invalid,
    next_to_dma_writer_state_frame_processing = dma_writer_state_invalid
};

typedef enum _dma_writer_state_t dma_writer_state_t;

#include "acamera.h"
#include "acamera_command_api.h"

void frame_buffer_initialize( dma_writer_fsm_ptr_t p_fsm );
void dma_writer_deinit( dma_writer_fsm_ptr_t p_fsm );
void frame_buffer_prepare_metadata( dma_writer_fsm_ptr_t p_fsm );
void frame_buffer_fr_finished( dma_writer_fsm_ptr_t p_fsm );
void frame_buffer_ds_finished( dma_writer_fsm_ptr_t p_fsm );
void frame_buffer_check_and_run( dma_writer_fsm_ptr_t p_fsm );

int acamera_frame_fr_set_ready_interrupt( acamera_firmware_t *g_fw );
void dma_writer_update_address_interrupt( dma_writer_fsm_const_ptr_t p_fsm, uint8_t irq_event );
void acamera_frame_buffer_update( dma_writer_fsm_const_ptr_t p_fsm );
int dma_writer_configure_m2m_pipes( void *handle );



struct _dma_writer_fsm_t {
    fsm_common_t cmn;

    acamera_fsm_mgr_t *p_fsm_mgr;
    dma_writer_state_t state;
    fsm_irq_mask_t mask;
    uint32_t vflip;

    dma_type dma_reader_out;
    uint32_t dma_reader_offset_x;
    uint32_t dma_reader_offset_y;
    uint8_t context_created;
    int32_t dis_ds_base_offset;
    uint8_t fps_throttle_settings[dma_max];
    void *handle;
};

void dma_writer_fsm_clear( dma_writer_fsm_ptr_t p_fsm );
void dma_writer_fsm_init( void *fsm, fsm_init_param_t *init_param );
int dma_writer_fsm_set_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size );
int dma_writer_fsm_get_param( void *fsm, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size );
uint8_t dma_writer_fsm_process_event( dma_writer_fsm_ptr_t p_fsm, event_id_t event_id );

void dma_writer_fsm_process_interrupt( dma_writer_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void dma_writer_request_interrupt( dma_writer_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __DMA_WRITER_FSM_H__ */

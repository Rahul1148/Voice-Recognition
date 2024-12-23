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

#ifndef __DMA_WRITER_API__
#define __DMA_WRITER_API__

#include "acamera_types.h"
#include "acamera_firmware_config.h"
#include "acamera.h"

#define CONFIG_DMA_WRITER_DEFAULT_BUFFER ( ISP_HAS_FPGA_WRAPPER && ISP_CONTROLS_DMA_READER )

/**
 *   Return codes
 */
typedef enum dma_error {
    edma_ok = 0,
    edma_fail,
    edma_invalid_pipe,
    edma_wrong_parameters,
    edma_invalid_api,
    edma_invalid_settings
} dma_error;


/**
 *   Pipe API
 *   All functions must be initialized properly.
 */
typedef struct dma_api {
    uint8_t ( *p_acamera_isp_dma_writer_format_read )( uintptr_t );
    void ( *p_acamera_isp_dma_writer_format_write )( uintptr_t, uint8_t );
    void ( *p_acamera_isp_dma_writer_bank0_base_write )( uintptr_t, uint32_t );
#if ISP_HAS_FPGA_WRAPPER
    void ( *p_acamera_fpga_frame_reader_rbase_write )( uintptr_t, uint32_t );
    void ( *p_acamera_fpga_frame_reader_line_offset_write )( uintptr_t, uint32_t );
    void ( *p_acamera_fpga_frame_reader_format_write )( uintptr_t base, uint8_t data );
    void ( *p_acamera_fpga_frame_reader_rbase_load_write )( uintptr_t base, uint8_t data );
#endif
    void ( *p_acamera_isp_dma_writer_line_offset_write )( uintptr_t, uint32_t );
    void ( *p_acamera_isp_dma_writer_frame_write_on_write )( uintptr_t, uint8_t );
    void ( *p_acamera_isp_dma_writer_active_width_write )( uintptr_t, uint16_t );
    void ( *p_acamera_isp_dma_writer_active_height_write )( uintptr_t, uint16_t );

    uint16_t ( *p_acamera_isp_dma_writer_active_width_read )( uintptr_t );
    uint16_t ( *p_acamera_isp_dma_writer_active_height_read )( uintptr_t );

    void ( *p_acamera_isp_dma_writer_max_bank_write )( uintptr_t, uint8_t );

    uint8_t ( *p_acamera_isp_dma_writer_format_read_uv )( uintptr_t );
    void ( *p_acamera_isp_dma_writer_format_write_uv )( uintptr_t, uint8_t );
    void ( *p_acamera_isp_dma_writer_bank0_base_write_uv )( uintptr_t, uint32_t );
    void ( *p_acamera_isp_dma_writer_max_bank_write_uv )( uintptr_t, uint8_t );
    void ( *p_acamera_isp_dma_writer_line_offset_write_uv )( uintptr_t, uint32_t );
    void ( *p_acamera_isp_dma_writer_frame_write_on_write_uv )( uintptr_t, uint8_t );
    void ( *p_acamera_isp_dma_writer_active_width_write_uv )( uintptr_t, uint16_t );
    void ( *p_acamera_isp_dma_writer_active_height_write_uv )( uintptr_t, uint16_t );
    uint16_t ( *p_acamera_isp_dma_writer_active_width_read_uv )( uintptr_t );
    uint16_t ( *p_acamera_isp_dma_writer_active_height_read_uv )( uintptr_t );
#if ISP_HAS_FPGA_WRAPPER
    void ( *p_acamera_fpga_frame_reader_rbase_write_uv )( uintptr_t, uint32_t );
    void ( *p_acamera_fpga_frame_reader_line_offset_write_uv )( uintptr_t, uint32_t );
    void ( *p_acamera_fpga_frame_reader_format_write_uv )( uintptr_t base, uint8_t data );
    void ( *p_acamera_fpga_frame_reader_rbase_load_write_uv )( uintptr_t base, uint8_t data );
#endif

} dma_api;


/**
 *   Pipe settings
 */
typedef struct dma_pipe_settings {
    uint32_t width;  // DMA output width
    uint32_t height; // DMA output height

#if CONFIG_DMA_WRITER_DEFAULT_BUFFER
    tframe_t default_frame[DMA_WRITER_DEFAULT_BUFFER_NO]; // Default double buffering
    uint8_t default_index;                                // Marks either ping or pong default buffer
#endif
    tframe_t curr_frame;  // Current frame written in the software configuration
    tframe_t delay_frame; // Delayed frame due to pipeline delay
    tframe_t done_frame;  // Frame done means filled by the DMA writer

    metadata_t curr_metadata;

    uint32_t vflip; // Vertical flip

    int32_t read_offset_x; // Offset for frame reader
    int32_t read_offset_y; // Offset for frame reader
    int32_t write_offset;  // Offset for frame writer
    uint32_t active;       // Frame reader gets data from active pipe
    uint32_t enabled;      // Enable or disable any pipe activity

    uint32_t banks_number; // Number of used banks
    uint32_t clear_memory; // Clear memory befor writing
    uint32_t clear_color;  // Clear color
    uint32_t last_address; // Last address which was used to write a frame
    uintptr_t isp_base;
    uint32_t ctx_id;
    uint32_t frames_in_cnt;      // Input frame counter for frame reader, used for fps throttling
    uint32_t frames_out_cnt;     // Output frame counter for frame reader, frames after throttling
    uint8_t fps_throttle_factor; // FPS throttling factor for frame reader
    uint8_t pause;
    struct _acamera_context_t *p_ctx;
} dma_pipe_settings;


/**
 *   Create a DMA writer instance.
 *
 *   This routine creates a DMA writer instance.
 *   The output pointer to DMA writer structure will be saved in *handle.
 *
 *   @param handle - pointer to the instance
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_create( void **handle );
void dma_writer_exit( void *handle );

/**
 *   Check if the pipe correctly initialized.
 *
 *
 *   @param handle - pointer to the instance
 *
 *   @return edma_ok - initialized properly
 *           edma_fail - fail
 */
dma_error dma_writer_pipe_initialized( void **handle, dma_type type );


/**
 *   Initialize a pipe.
 *
 *   This routine will initialize a pipe with specified settings and given API.
 *   Be sure that all API functions have been initialized properly.
 *
 *   @param handle - pointer to the instance.
 *   @param settings - pointer to the settings structure.
 *   @param api - pointer to the API structure.
 *   @param type - a type of a DMA output
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_init( void *handle, dma_type type, dma_pipe_settings *settings, dma_api *api );


/**
 *   Return current settings.
 *
 *   The routine will copy all settings to your memory for specified pipe.
 *   It is better to use this function when you are
 *   planning to call set_settings after it.
 *
 *   @param handle - pointer to the instance
 *   @param settings - pointer to the settings structure.
 *   @param type - a type of a DMA output
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_get_settings( void *handle, dma_type type, dma_pipe_settings *settings );


/**
 *   Return current settings.
 *
 *   The routine will return a pointer on a settings structure
 *   for a given pipe. It can be used if you need just a fast access
 *   to the settings without modifying it.
 *
 *   @param handle - pointer to the instance
 *   @param settings - pointer to the settings structure.
 *   @param type - a type of a DMA output
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_get_ptr_settings( void *handle, dma_type type, dma_pipe_settings **settings );

/**
 *   Apply new settings for specified pipe
 *
 *   This routine should be used to change the settings of a pipe.
 *
 *   @param handle - pointer to the instance
 *   @param settings - pointer to the settings structure.
 *   @param type - a type of a DMA output
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_set_settings( void *handle, dma_type type, dma_pipe_settings *settings );


/**
 *   Reset a pipe to the initial state.
 *
 *   The routine will reset a specified pipe to its initial state.
 *
 *   @param handle - pointer to the instance
 *   @param type - a type of a DMA output
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_reset( void *handle, dma_type type );


/**
 *   Process an interrupt.
 *
 *   The routine will handle an interrupt to update a state of all pipes
 *
 *   @param handle - pointer to the instance
 *   @param irq_event - input interrupt number
 *
 *   @return edma_ok - success
 *           edma_fail - fail
 */
dma_error dma_writer_process_interrupt( void *handle, uint32_t irq_event );

metadata_t *dma_writer_return_metadata( void *handle, dma_type type );
void dma_writer_set_initialized( void *handle, dma_type type, uint8_t initialized );

#endif /* __DMA_WRITER_API__ */

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

#ifndef __DMA_WRITER__
#define __DMA_WRITER__

#include "acamera_types.h"
#include "dma_writer_api.h"


typedef struct _dma_pipe_state {
    uint8_t initialized;
} dma_pipe_state;

typedef struct dma_writer_reg_ops {
    uint8_t ( *format_read )( uintptr_t );
    void ( *format_write )( uintptr_t, uint8_t );
    void ( *bank0_base_write )( uintptr_t, uint32_t );
    void ( *line_offset_write )( uintptr_t, uint32_t );
    void ( *write_on_write )( uintptr_t, uint8_t );
    void ( *active_width_write )( uintptr_t, uint16_t );
    void ( *active_height_write )( uintptr_t, uint16_t );
    uint16_t ( *active_width_read )( uintptr_t );
    uint16_t ( *active_height_read )( uintptr_t );
} dma_writer_reg_ops_t;

typedef struct _dma_pipe {
    dma_pipe_settings settings;
    dma_pipe_state state;
    dma_api api;
    dma_type type;
    dma_source source;
    dma_writer_reg_ops_t primary;
    dma_writer_reg_ops_t secondary;
} dma_pipe;


typedef struct _dma_handle {
    dma_pipe pipe[dma_max];
} dma_handle;


/**
 *   Get default settings for dis processor.
 *
 *   To be sure that all settings are correct you have to call this function before changing any parameters.
 *   It sets all settings in their default value. After that it can be changed by caller.
 *
 *   @param settings - pointer to the settings structure.
 *
 *   @return 0 - success
 *           1 - fail to set settings.
 */
dma_error dma_writer_update_state( dma_pipe *pipe );


#endif

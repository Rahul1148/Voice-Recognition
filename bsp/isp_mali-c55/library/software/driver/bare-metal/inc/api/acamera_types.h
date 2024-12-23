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

#ifndef __ACAMERA__TYPES_H__
#define __ACAMERA__TYPES_H__

#include "acamera_firmware_config.h"

#if KERNEL_MODULE == 1
#include "linux/types.h"
#else
#include <stdint.h>
#endif
typedef enum af_mode {
    AF_MODE_AF = 0,
    AF_MODE_CAF = 1,
    AF_MODE_MANUAL = 2,
    AF_MODE_CALIBRATION = 3,
    AF_MODE_SAVE_STATS = 4,
} af_mode_t;

typedef enum af_state {
    AF_STATE_INACTIVE,
    AF_STATE_SCAN,
    AF_STATE_FOCUSED,
    AF_STATE_UNFOCUSED
} af_state_t;

typedef enum caf_state {
    CAF_STATE_NOT_RUNNING = 0,
    CAF_STATE_RUNNING,
    CAF_STATE_WAITING_FOR_SCENE_CHANGE,
    CAF_STATE_WAITING_FOR_STABLE_SCENE,
    CAF_STATE_FINISHED_FAILED,
    CAF_STATE_FINISHED_SUCCESSFUL,
} caf_state_t;

typedef enum ae_state {
    AE_STATE_INACTIVE,
    AE_STATE_SEARCHING,
    AE_STATE_CONVERGED,
} ae_state_t;

typedef enum awb_state {
    AWB_STATE_INACTIVE,
    AWB_STATE_SEARCHING,
    AWB_STATE_CONVERGED,
} awb_state_t;

typedef enum acamera_stream_type {
    ACAMERA_STREAM_META,
    ACAMERA_STREAM_RAW,
    ACAMERA_STREAM_FR,
    ACAMERA_STREAM_DS1,
    ACAMERA_STREAM_DS2,
    ACAMERA_STREAM_NUM_STREAM_TYPES
} acamera_stream_type_t;

typedef enum dma_buf_state {
    dma_buf_empty = 0,
    dma_buf_busy,
    dma_buf_ready,
    dma_buf_purge
} dma_buf_state;

/**
 *   supported pipe types
 *   please note that dma_max is used
 *   only as a counter for supported pipes
 */
typedef enum dma_type {
    dma_fr = 0,
    dma_ds1,
    dma_max
} dma_type;

/**
 *   supported pipe sources
 *   please note that dma_source_max is used
 *   only as a counter for supported pipe sources
 */
typedef enum dma_source {
    dma_source_default = 0,
    dma_source_m2m,
    dma_source_max
} dma_source;

typedef struct LookupTable {
    void *ptr;
    uint16_t rows;
    uint16_t cols;
    uint16_t width;
} LookupTable;

#define UNUSED( x ) (void)x

#endif /* __ACAMERA__TYPES_H__ */

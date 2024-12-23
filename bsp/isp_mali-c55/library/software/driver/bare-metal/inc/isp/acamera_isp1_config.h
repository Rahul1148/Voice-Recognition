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

#ifndef __ACAMERA_ISP1_CONFIG_H__
#define __ACAMERA_ISP1_CONFIG_H__


#include "system_sw_io.h"

#include "system_hw_io.h"

// ------------------------------------------------------------------------------ //
// Instance 'isp1' of module 'single_context_config'
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP1_BASE_ADDR (0x18e88)
#define ACAMERA_ISP1_SIZE (0x4000)

// ------------------------------------------------------------------------------ //
// Group: top
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Miscellaneous top-level ISP controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Active Width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video width in pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_ACTIVE_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_TOP_ACTIVE_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_TOP_ACTIVE_WIDTH_OFFSET (0x0)
#define ACAMERA_ISP_TOP_ACTIVE_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_top_active_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18e88);
    system_sw_write_32(base + 0x18e88, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_top_active_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18e88) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Active Height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video height in lines
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_ACTIVE_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_TOP_ACTIVE_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_TOP_ACTIVE_HEIGHT_OFFSET (0x0)
#define ACAMERA_ISP_TOP_ACTIVE_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_top_active_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18e88);
    system_sw_write_32(base + 0x18e88, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_top_active_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18e88) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: RGGB start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Starting color of the rggb pattern
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_RGGB_START_DEFAULT (0x0)
#define ACAMERA_ISP_TOP_RGGB_START_DATASIZE (2)
#define ACAMERA_ISP_TOP_RGGB_START_OFFSET (0x4)
#define ACAMERA_ISP_TOP_RGGB_START_MASK (0x3)
#define ACAMERA_ISP_TOP_RGGB_START_R_GR_GB_B (0)
#define ACAMERA_ISP_TOP_RGGB_START_GR_R_B_GB (1)
#define ACAMERA_ISP_TOP_RGGB_START_GB_B_R_GR (2)
#define ACAMERA_ISP_TOP_RGGB_START_B_GB_GR_R (3)

// args: data (2-bit)
static __inline void acamera_isp_top_rggb_start_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18e8c);
    system_sw_write_32(base + 0x18e8c, (((uint32_t) (data & 0x3)) << 0) | (curr & 0xfffffffc));
}
static __inline uint8_t acamera_isp_top_rggb_start_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18e8c) & 0x3) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cfa pattern
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The pixel arrangement of the CFA array on the sensor. Set in the Top register group and used by several blocks in the pipeline:
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_CFA_PATTERN_DEFAULT (0x0)
#define ACAMERA_ISP_TOP_CFA_PATTERN_DATASIZE (2)
#define ACAMERA_ISP_TOP_CFA_PATTERN_OFFSET (0x4)
#define ACAMERA_ISP_TOP_CFA_PATTERN_MASK (0x30000)
#define ACAMERA_ISP_TOP_CFA_PATTERN_RGGB (0)
#define ACAMERA_ISP_TOP_CFA_PATTERN_RESERVED_2 (1)
#define ACAMERA_ISP_TOP_CFA_PATTERN_RESERVED_3 (2)
#define ACAMERA_ISP_TOP_CFA_PATTERN_RESERVED_4 (3)

// args: data (2-bit)
static __inline void acamera_isp_top_cfa_pattern_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18e8c);
    system_sw_write_32(base + 0x18e8c, (((uint32_t) (data & 0x3)) << 16) | (curr & 0xfffcffff));
}
static __inline uint8_t acamera_isp_top_cfa_pattern_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18e8c) & 0x30000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Linear data src
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear data src
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_DEFAULT (0x0)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_DATASIZE (2)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_OFFSET (0x4)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_MASK (0x3000000)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_SENSOR_STITCHED_AND_LINEAR_DATA_DIRECTLY_COMING_FROM_SENSOR (0)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_LINEAR_DATA_FROM_FRAME_STITCH (1)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_SENSOR_COMPANDED_DATA_LINEARISED_THROUGH_DECOMPANDER (2)
#define ACAMERA_ISP_TOP_LINEAR_DATA_SRC_RESERVED (3)

// args: data (2-bit)
static __inline void acamera_isp_top_linear_data_src_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18e8c);
    system_sw_write_32(base + 0x18e8c, (((uint32_t) (data & 0x3)) << 24) | (curr & 0xfcffffff));
}
static __inline uint8_t acamera_isp_top_linear_data_src_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18e8c) & 0x3000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass video test gen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass video test generator
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_VIDEO_TEST_GEN_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_VIDEO_TEST_GEN_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_VIDEO_TEST_GEN_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_VIDEO_TEST_GEN_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_video_test_gen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_video_test_gen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass input formatter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass input formatter module.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_INPUT_FORMATTER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_INPUT_FORMATTER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_INPUT_FORMATTER_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_INPUT_FORMATTER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_input_formatter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_input_formatter_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass decompander
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass front end decompander
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DECOMPANDER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DECOMPANDER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DECOMPANDER_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_DECOMPANDER_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_decompander_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_top_bypass_decompander_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass sensor offset wdr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass sensor offset wdr
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_WDR_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_WDR_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_WDR_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_WDR_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_sensor_offset_wdr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_sensor_offset_wdr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass gain wdr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass gain wdr
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_GAIN_WDR_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_GAIN_WDR_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_GAIN_WDR_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_GAIN_WDR_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_gain_wdr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_bypass_gain_wdr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass frame stitch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass frame stitching logic
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FRAME_STITCH_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FRAME_STITCH_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FRAME_STITCH_OFFSET (0x24)
#define ACAMERA_ISP_TOP_BYPASS_FRAME_STITCH_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_frame_stitch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eac);
    system_sw_write_32(base + 0x18eac, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_top_bypass_frame_stitch_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eac) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass digital gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass digital gain module
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DIGITAL_GAIN_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DIGITAL_GAIN_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DIGITAL_GAIN_OFFSET (0x28)
#define ACAMERA_ISP_TOP_BYPASS_DIGITAL_GAIN_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_digital_gain_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb0);
    system_sw_write_32(base + 0x18eb0, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_digital_gain_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb0) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass frontend sensor offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass digital gain module
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FRONTEND_SENSOR_OFFSET_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FRONTEND_SENSOR_OFFSET_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FRONTEND_SENSOR_OFFSET_OFFSET (0x28)
#define ACAMERA_ISP_TOP_BYPASS_FRONTEND_SENSOR_OFFSET_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_frontend_sensor_offset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb0);
    system_sw_write_32(base + 0x18eb0, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_frontend_sensor_offset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb0) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fe sqrt
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass square root function before raw frontend 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FE_SQRT_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FE_SQRT_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FE_SQRT_OFFSET (0x28)
#define ACAMERA_ISP_TOP_BYPASS_FE_SQRT_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fe_sqrt_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb0);
    system_sw_write_32(base + 0x18eb0, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_top_bypass_fe_sqrt_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb0) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass RAW frontend
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass RAW frontend (green equalization and dynamic defect pixel)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_RAW_FRONTEND_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_RAW_FRONTEND_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_RAW_FRONTEND_OFFSET (0x28)
#define ACAMERA_ISP_TOP_BYPASS_RAW_FRONTEND_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_raw_frontend_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb0);
    system_sw_write_32(base + 0x18eb0, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_raw_frontend_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb0) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass sinter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass sinter 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_SINTER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_SINTER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_SINTER_OFFSET (0x30)
#define ACAMERA_ISP_TOP_BYPASS_SINTER_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_sinter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb8);
    system_sw_write_32(base + 0x18eb8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_sinter_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass temper
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass temper 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_TEMPER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_TEMPER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_TEMPER_OFFSET (0x30)
#define ACAMERA_ISP_TOP_BYPASS_TEMPER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_temper_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eb8);
    system_sw_write_32(base + 0x18eb8, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_temper_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18eb8) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass square_be
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass backend square
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_SQUARE_BE_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_SQUARE_BE_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_SQUARE_BE_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_SQUARE_BE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_square_be_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_square_be_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass sensor_offset_pre_shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass sensor offset pre shading
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_PRE_SHADING_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_PRE_SHADING_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_PRE_SHADING_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_SENSOR_OFFSET_PRE_SHADING_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_sensor_offset_pre_shading_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_sensor_offset_pre_shading_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass mesh shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass mesh ashading
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_MESH_SHADING_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_MESH_SHADING_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_MESH_SHADING_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_MESH_SHADING_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_mesh_shading_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_mesh_shading_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass white balance
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass white balance 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_WHITE_BALANCE_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_WHITE_BALANCE_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_WHITE_BALANCE_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_WHITE_BALANCE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_white_balance_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_bypass_white_balance_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass iridix gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_GAIN_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_GAIN_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_GAIN_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_GAIN_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_iridix_gain_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_top_bypass_iridix_gain_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass iridix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_OFFSET (0x34)
#define ACAMERA_ISP_TOP_BYPASS_IRIDIX_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_iridix_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ebc);
    system_sw_write_32(base + 0x18ebc, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_top_bypass_iridix_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ebc) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass demosaic rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass demosaic rgb
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DEMOSAIC_RGB_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DEMOSAIC_RGB_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DEMOSAIC_RGB_OFFSET (0x38)
#define ACAMERA_ISP_TOP_BYPASS_DEMOSAIC_RGB_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_demosaic_rgb_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec0);
    system_sw_write_32(base + 0x18ec0, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_demosaic_rgb_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec0) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass pf correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass pf correction
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_PF_CORRECTION_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_PF_CORRECTION_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_PF_CORRECTION_OFFSET (0x38)
#define ACAMERA_ISP_TOP_BYPASS_PF_CORRECTION_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_pf_correction_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec0);
    system_sw_write_32(base + 0x18ec0, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_pf_correction_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec0) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass CCM
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass CCM
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_CCM_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_CCM_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_CCM_OFFSET (0x38)
#define ACAMERA_ISP_TOP_BYPASS_CCM_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ccm_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec0);
    system_sw_write_32(base + 0x18ec0, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_bypass_ccm_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec0) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass CNR
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass CNR
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_CNR_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_CNR_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_CNR_OFFSET (0x38)
#define ACAMERA_ISP_TOP_BYPASS_CNR_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_cnr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec0);
    system_sw_write_32(base + 0x18ec0, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_top_bypass_cnr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec0) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fr crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass fr crop 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FR_CROP_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FR_CROP_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FR_CROP_OFFSET (0x3c)
#define ACAMERA_ISP_TOP_BYPASS_FR_CROP_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fr_crop_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec4);
    system_sw_write_32(base + 0x18ec4, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_fr_crop_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec4) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fr scaler
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass fr scaler 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FR_SCALER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FR_SCALER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FR_SCALER_OFFSET (0x3c)
#define ACAMERA_ISP_TOP_BYPASS_FR_SCALER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fr_scaler_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec4);
    system_sw_write_32(base + 0x18ec4, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_fr_scaler_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec4) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fr gamma rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass fr gamma rgb 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FR_GAMMA_RGB_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FR_GAMMA_RGB_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FR_GAMMA_RGB_OFFSET (0x3c)
#define ACAMERA_ISP_TOP_BYPASS_FR_GAMMA_RGB_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fr_gamma_rgb_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec4);
    system_sw_write_32(base + 0x18ec4, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_top_bypass_fr_gamma_rgb_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec4) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fr sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass fr sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FR_SHARPEN_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FR_SHARPEN_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FR_SHARPEN_OFFSET (0x3c)
#define ACAMERA_ISP_TOP_BYPASS_FR_SHARPEN_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fr_sharpen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec4);
    system_sw_write_32(base + 0x18ec4, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_fr_sharpen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec4) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass fr cs conv
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass fr cs conv
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_FR_CS_CONV_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_FR_CS_CONV_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_FR_CS_CONV_OFFSET (0x3c)
#define ACAMERA_ISP_TOP_BYPASS_FR_CS_CONV_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_fr_cs_conv_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec4);
    system_sw_write_32(base + 0x18ec4, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_bypass_fr_cs_conv_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec4) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass ds crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass ds crop 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DS1_CROP_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CROP_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CROP_OFFSET (0x40)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CROP_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ds1_crop_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec8);
    system_sw_write_32(base + 0x18ec8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_bypass_ds1_crop_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass ds scaler
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass ds scaler 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DS1_SCALER_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SCALER_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SCALER_OFFSET (0x40)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SCALER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ds1_scaler_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec8);
    system_sw_write_32(base + 0x18ec8, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_bypass_ds1_scaler_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec8) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass ds gamma rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass ds gamma rgb 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DS1_GAMMA_RGB_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DS1_GAMMA_RGB_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DS1_GAMMA_RGB_OFFSET (0x40)
#define ACAMERA_ISP_TOP_BYPASS_DS1_GAMMA_RGB_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ds1_gamma_rgb_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec8);
    system_sw_write_32(base + 0x18ec8, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_top_bypass_ds1_gamma_rgb_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec8) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass ds sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass ds sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DS1_SHARPEN_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SHARPEN_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SHARPEN_OFFSET (0x40)
#define ACAMERA_ISP_TOP_BYPASS_DS1_SHARPEN_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ds1_sharpen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec8);
    system_sw_write_32(base + 0x18ec8, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_top_bypass_ds1_sharpen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec8) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Bypass ds cs conv
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bypass ds cs conv
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_BYPASS_DS1_CS_CONV_DEFAULT (0)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CS_CONV_DATASIZE (1)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CS_CONV_OFFSET (0x40)
#define ACAMERA_ISP_TOP_BYPASS_DS1_CS_CONV_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_bypass_ds1_cs_conv_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ec8);
    system_sw_write_32(base + 0x18ec8, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_bypass_ds1_cs_conv_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ec8) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: ISP RAW bypass
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//   Used to select between normal ISP processing with image sensor data and up to 12 bit RGB input.
//                         In the latter case data is reinserted into pipeline after purple fringing correction block.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_DEFAULT (0)
#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_DATASIZE (1)
#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_OFFSET (0x44)
#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_MASK (0x1)
#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_SELECT_PROCESSED (0)
#define ACAMERA_ISP_TOP_ISP_RAW_BYPASS_BYPASS_ISP_RAW_PROCESSING_NOTE_NO_VIDEO_DATA_IS_SENT_TO_THE_MODULE_AFTER_TPG_THE_IMAGE_DATA_IS_REINSERTED_INTO_PIPELINE_AFTER_PURPLE_FRINGE_CORRECTION_BLOCK (1)

// args: data (1-bit)
static __inline void acamera_isp_top_isp_raw_bypass_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ecc);
    system_sw_write_32(base + 0x18ecc, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_isp_raw_bypass_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ecc) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ISP downscale pipe disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Downscale pipeline is enabled
//            1: Downscale pipeline is disabled. No data is sent out in DMA and streaming channel
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_ISP_DOWNSCALE_PIPE_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_TOP_ISP_DOWNSCALE_PIPE_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_ISP_DOWNSCALE_PIPE_DISABLE_OFFSET (0x44)
#define ACAMERA_ISP_TOP_ISP_DOWNSCALE_PIPE_DISABLE_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_top_isp_downscale_pipe_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ecc);
    system_sw_write_32(base + 0x18ecc, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_top_isp_downscale_pipe_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ecc) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: ISP processing fr bypass mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  
//              ISP FR bypass modes. Should be set to 0 for full pipeline operation. 
//              Used to select fr_pipe output and to bypass RAW & RGB ISP processing after input port.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_DEFAULT (0)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_DATASIZE (2)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_OFFSET (0x44)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_MASK (0x300)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_FULL_PROCESSING (0)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_FR_PIPE_OUTPUT_VIDEO_SOURCED_FROM_194_OF_IMAGE_SENSOR_DATA_AFTER_VIDEO_TEST_GEN_MODULE_NOTE_NO_VIDEO_DATA_IS_SENT_TO_THE_MODULE_AFTER_TPG_DATA_IS_REINSERTED_INTO_PIPELINE_AFTER_PURPLE_FRINGING_CORRECTION_BLOCK_IF_ISP_RAW_BYPASS_REGISTER_IS_SET_TO_1_OTHERWISE_IS_REINSERTED_AFTER_COLOR_SPACE_CONVERSION_BLOCK_IN_THE_FR_PIPE_MODULES_AHEAD_THIS_MUX_IN_THE_FR_PIPE_WONT_RECEIVE_IMAGE_DATA (1)
#define ACAMERA_ISP_TOP_ISP_PROCESSING_FR_BYPASS_MODE_FR_PIPE_OUTPUT_VIDEO_SOURCED_FROM_194_OF_IMAGE_SENSOR_DATA_AFTER_VIDEO_TEST_GEN_MODULE_NOTE_MODULES_AHEAD_THIS_MUX_IN_THE_FR_PIPE_WONT_RECEIVE_IMAGE_DATA (2)

// args: data (2-bit)
static __inline void acamera_isp_top_isp_processing_fr_bypass_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ecc);
    system_sw_write_32(base + 0x18ecc, (((uint32_t) (data & 0x3)) << 8) | (curr & 0xfffffcff));
}
static __inline uint8_t acamera_isp_top_isp_processing_fr_bypass_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ecc) & 0x300) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: AE 5bin hist disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: AEXP 5-bin histogram enabled
//        1: AEXP 5-bin histogram disabled
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AE_5BIN_HIST_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_TOP_AE_5BIN_HIST_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_AE_5BIN_HIST_DISABLE_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AE_5BIN_HIST_DISABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_top_ae_5bin_hist_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_top_ae_5bin_hist_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: AE switch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AE 5bin histogram tap in the pipeline.  Location of AE statistic collection.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AE_SWITCH_DEFAULT (0)
#define ACAMERA_ISP_TOP_AE_SWITCH_DATASIZE (2)
#define ACAMERA_ISP_TOP_AE_SWITCH_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AE_SWITCH_MASK (0x6)
#define ACAMERA_ISP_TOP_AE_SWITCH_AFTER_STATIC_WHITE_BALANCE_WHOSE_POSITION_IS_SELECTED_BY_AEXP_SRC_SIGNAL (0)
#define ACAMERA_ISP_TOP_AE_SWITCH_AFTER_WDR_FRAME_STITCH_IF_ITS_SENSOR_COMPANDED_DATA_THEN_USE_DECOMPANDED_OUTPUT_IF_ITS_SENSOR_LINEARISED_DATA_THEN_USE_IT_DIRECTLY (1)
#define ACAMERA_ISP_TOP_AE_SWITCH_AFTER_VTPG (2)
#define ACAMERA_ISP_TOP_AE_SWITCH_RESERVED (3)

// args: data (2-bit)
static __inline void acamera_isp_top_ae_switch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x3)) << 1) | (curr & 0xfffffff9));
}
static __inline uint8_t acamera_isp_top_ae_switch_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x6) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: AF disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: AF enabled
//        1: AF disabled
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AF_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_TOP_AF_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_AF_DISABLE_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AF_DISABLE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_top_af_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_top_af_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: AF switch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AF tap in the pipeline.  .
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AF_SWITCH_DEFAULT (1)
#define ACAMERA_ISP_TOP_AF_SWITCH_DATASIZE (1)
#define ACAMERA_ISP_TOP_AF_SWITCH_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AF_SWITCH_MASK (0x20)
#define ACAMERA_ISP_TOP_AF_SWITCH_BEFORE_TEMPER (0)
#define ACAMERA_ISP_TOP_AF_SWITCH_AFTER_DIGITAL_GAIN (1)

// args: data (1-bit)
static __inline void acamera_isp_top_af_switch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_top_af_switch_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: AWB disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: AWB enabled
//        1: AWB disabled
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AWB_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_TOP_AWB_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_AWB_DISABLE_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AWB_DISABLE_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_top_awb_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_top_awb_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: AWB switch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AWB tap in the pipeline.  Location of AWB statistics collection.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AWB_SWITCH_DEFAULT (0)
#define ACAMERA_ISP_TOP_AWB_SWITCH_DATASIZE (1)
#define ACAMERA_ISP_TOP_AWB_SWITCH_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AWB_SWITCH_MASK (0x200)
#define ACAMERA_ISP_TOP_AWB_SWITCH_IMMEDIATELY_AFTER_PURPLE_FRINGE (0)
#define ACAMERA_ISP_TOP_AWB_SWITCH_IMMEDIATELY_AFTER_CNR (1)

// args: data (1-bit)
static __inline void acamera_isp_top_awb_switch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_top_awb_switch_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: AEXP hist disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: AEXP 1024-bin histogram enabled
//        1: AEXP 1024-bin histogram disabled
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AEXP_HIST_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_TOP_AEXP_HIST_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_AEXP_HIST_DISABLE_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AEXP_HIST_DISABLE_MASK (0x1000)

// args: data (1-bit)
static __inline void acamera_isp_top_aexp_hist_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 12) | (curr & 0xffffefff));
}
static __inline uint8_t acamera_isp_top_aexp_hist_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x1000) >> 12);
}
// ------------------------------------------------------------------------------ //
// Register: AEXP Histogram switch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AE global histogram tap in the pipeline.  Location of statistics gathering for 1024 bin global histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_DEFAULT (0)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_DATASIZE (2)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_MASK (0x6000)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_AFTER_STATIC_WHITE_BALANCE_WHOSE_POSITION_IS_SELECTED_BY_AEXP_SRC_SIGNAL (0)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_AFTER_WDR_FRAME_STITCH_IF_ITS_SENSOR_COMPANDED_DATA_THEN_USE_DECOMPANDED_OUTPUT_IF_ITS_SENSOR_LINEARISED_DATA_THEN_USE_IT_DIRECTLY (1)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_AFTER_VTPG (2)
#define ACAMERA_ISP_TOP_AEXP_HISTOGRAM_SWITCH_RESERVED (3)

// args: data (2-bit)
static __inline void acamera_isp_top_aexp_histogram_switch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x3)) << 13) | (curr & 0xffff9fff));
}
static __inline uint8_t acamera_isp_top_aexp_histogram_switch_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x6000) >> 13);
}
// ------------------------------------------------------------------------------ //
// Register: iHist disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Post iridix histogram enable.  Enables statistics gathering for global histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_IHIST_DISABLE_DEFAULT (1)
#define ACAMERA_ISP_TOP_IHIST_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_TOP_IHIST_DISABLE_OFFSET (0x48)
#define ACAMERA_ISP_TOP_IHIST_DISABLE_MASK (0x10000)
#define ACAMERA_ISP_TOP_IHIST_DISABLE_ENABLED (0)
#define ACAMERA_ISP_TOP_IHIST_DISABLE_DISABLED (1)

// args: data (1-bit)
static __inline void acamera_isp_top_ihist_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 16) | (curr & 0xfffeffff));
}
static __inline uint8_t acamera_isp_top_ihist_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x10000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: aexp_src
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TOP_AEXP_SRC_DEFAULT (0)
#define ACAMERA_ISP_TOP_AEXP_SRC_DATASIZE (1)
#define ACAMERA_ISP_TOP_AEXP_SRC_OFFSET (0x48)
#define ACAMERA_ISP_TOP_AEXP_SRC_MASK (0x1000000)
#define ACAMERA_ISP_TOP_AEXP_SRC_AFTER_STATIC_WHITE_BALANCE_WHEN_APPLIED_BEFORE_SHADING (0)
#define ACAMERA_ISP_TOP_AEXP_SRC_AFTER_STATIC_WHITE_BALANCE_WHEN_APPLIED_AFTER_SHADING (1)

// args: data (1-bit)
static __inline void acamera_isp_top_aexp_src_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed0);
    system_sw_write_32(base + 0x18ed0, (((uint32_t) (data & 0x1)) << 24) | (curr & 0xfeffffff));
}
static __inline uint8_t acamera_isp_top_aexp_src_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed0) & 0x1000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Group: crossbar
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: channel0_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// channel0 selection from the input 3 channels: 0= Chan0, 1=Chan1, 2=Chan2, 3=Null/unused 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CROSSBAR_CHANNEL0_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_CROSSBAR_CHANNEL0_SELECT_DATASIZE (2)
#define ACAMERA_ISP_CROSSBAR_CHANNEL0_SELECT_OFFSET (0x4c)
#define ACAMERA_ISP_CROSSBAR_CHANNEL0_SELECT_MASK (0x3)

// args: data (2-bit)
static __inline void acamera_isp_crossbar_channel0_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed4);
    system_sw_write_32(base + 0x18ed4, (((uint32_t) (data & 0x3)) << 0) | (curr & 0xfffffffc));
}
static __inline uint8_t acamera_isp_crossbar_channel0_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed4) & 0x3) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: channel1_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// channel1 selection from the input 3 channels: 0= Chan0, 1=Chan1, 2=Chan2, 3=Null/unused 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CROSSBAR_CHANNEL1_SELECT_DEFAULT (0x1)
#define ACAMERA_ISP_CROSSBAR_CHANNEL1_SELECT_DATASIZE (2)
#define ACAMERA_ISP_CROSSBAR_CHANNEL1_SELECT_OFFSET (0x4c)
#define ACAMERA_ISP_CROSSBAR_CHANNEL1_SELECT_MASK (0x300)

// args: data (2-bit)
static __inline void acamera_isp_crossbar_channel1_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed4);
    system_sw_write_32(base + 0x18ed4, (((uint32_t) (data & 0x3)) << 8) | (curr & 0xfffffcff));
}
static __inline uint8_t acamera_isp_crossbar_channel1_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed4) & 0x300) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: channel2_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// channel2 selection from the input 3 channels: 0= Chan0, 1=Chan1, 2=Chan2, 3=Null/unused 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CROSSBAR_CHANNEL2_SELECT_DEFAULT (0x2)
#define ACAMERA_ISP_CROSSBAR_CHANNEL2_SELECT_DATASIZE (2)
#define ACAMERA_ISP_CROSSBAR_CHANNEL2_SELECT_OFFSET (0x4c)
#define ACAMERA_ISP_CROSSBAR_CHANNEL2_SELECT_MASK (0x30000)

// args: data (2-bit)
static __inline void acamera_isp_crossbar_channel2_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed4);
    system_sw_write_32(base + 0x18ed4, (((uint32_t) (data & 0x3)) << 16) | (curr & 0xfffcffff));
}
static __inline uint8_t acamera_isp_crossbar_channel2_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed4) & 0x30000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: video test gen ch0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Video test generator controls.  See Arm ISP Technical Reference Manual for further details
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: test_pattern_off on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Test pattern off-on: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_TEST_PATTERN_OFF_ON_DEFAULT (0)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_TEST_PATTERN_OFF_ON_DATASIZE (1)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_TEST_PATTERN_OFF_ON_OFFSET (0x50)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_TEST_PATTERN_OFF_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_video_test_gen_ch0_test_pattern_off_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed8);
    system_sw_write_32(base + 0x18ed8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_video_test_gen_ch0_test_pattern_off_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bayer_rgb_o sel
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bayer or RGB select for output video: 0=bayer, 1=RGB
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_BAYER_RGB_O_SEL_DEFAULT (0)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_BAYER_RGB_O_SEL_DATASIZE (1)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_BAYER_RGB_O_SEL_OFFSET (0x50)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_BAYER_RGB_O_SEL_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_video_test_gen_ch0_bayer_rgb_o_sel_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ed8);
    system_sw_write_32(base + 0x18ed8, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_video_test_gen_ch0_bayer_rgb_o_sel_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18ed8) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: pattern type
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Pattern type select: 0=Flat field,1=Horizontal gradient,2=Vertical Gradient,3=Vertical Bars,4=Rectangle,5-255=Default white frame on black
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_PATTERN_TYPE_DEFAULT (0x03)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_PATTERN_TYPE_DATASIZE (8)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_PATTERN_TYPE_OFFSET (0x54)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_PATTERN_TYPE_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_video_test_gen_ch0_pattern_type_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18edc);
    system_sw_write_32(base + 0x18edc, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_video_test_gen_ch0_pattern_type_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18edc) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: r backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Red background  value 16bit, MSB aligned to used width 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_BACKGND_OFFSET (0x58)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_r_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ee0);
    system_sw_write_32(base + 0x18ee0, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_r_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18ee0) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: g backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Green background value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_BACKGND_OFFSET (0x5c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_g_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ee4);
    system_sw_write_32(base + 0x18ee4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_g_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18ee4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: b backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Blue background value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_BACKGND_OFFSET (0x60)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_b_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ee8);
    system_sw_write_32(base + 0x18ee8, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_b_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18ee8) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: r foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Red foreground  value 16bit, MSB aligned to used width 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_FOREGND_OFFSET (0x64)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_R_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_r_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18eec);
    system_sw_write_32(base + 0x18eec, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_r_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18eec) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: g foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Green foreground value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_FOREGND_OFFSET (0x68)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_G_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_g_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ef0);
    system_sw_write_32(base + 0x18ef0, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_g_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18ef0) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: b foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Blue foreground value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_FOREGND_OFFSET (0x6c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_B_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_b_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ef4);
    system_sw_write_32(base + 0x18ef4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_b_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18ef4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rgb gradient
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// RGB gradient increment per pixel (0-15) for first channel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_DEFAULT (0x3CAA)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_DATASIZE (16)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_OFFSET (0x70)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_video_test_gen_ch0_rgb_gradient_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ef8);
    system_sw_write_32(base + 0x18ef8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch0_rgb_gradient_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18ef8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rgb_gradient start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// RGB gradient start value for first channel 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_START_DEFAULT (0x0000)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_START_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_START_OFFSET (0x74)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RGB_GRADIENT_START_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch0_rgb_gradient_start_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18efc);
    system_sw_write_32(base + 0x18efc, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch0_rgb_gradient_start_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18efc) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect top
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle top line number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_TOP_DEFAULT (0x0001)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_TOP_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_TOP_OFFSET (0x78)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_TOP_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch0_rect_top_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f00);
    system_sw_write_32(base + 0x18f00, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch0_rect_top_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f00) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect bot
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle bottom line number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_BOT_DEFAULT (0x0100)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_BOT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_BOT_OFFSET (0x78)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_BOT_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch0_rect_bot_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f00);
    system_sw_write_32(base + 0x18f00, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_video_test_gen_ch0_rect_bot_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f00) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: rect left
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle left pixel number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_LEFT_DEFAULT (0x0001)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_LEFT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_LEFT_OFFSET (0x7c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_LEFT_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch0_rect_left_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f04);
    system_sw_write_32(base + 0x18f04, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch0_rect_left_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f04) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect right
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle right pixel number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_RIGHT_DEFAULT (0x0100)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_RIGHT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_RIGHT_OFFSET (0x7c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH0_RECT_RIGHT_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch0_rect_right_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f04);
    system_sw_write_32(base + 0x18f04, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_video_test_gen_ch0_rect_right_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f04) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: video test gen ch1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Video test generator controls.  See Arm ISP Technical Reference Manual for further details
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: test_pattern_off on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Test pattern off-on: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_TEST_PATTERN_OFF_ON_DEFAULT (0)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_TEST_PATTERN_OFF_ON_DATASIZE (1)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_TEST_PATTERN_OFF_ON_OFFSET (0x80)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_TEST_PATTERN_OFF_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_video_test_gen_ch1_test_pattern_off_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f08);
    system_sw_write_32(base + 0x18f08, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_video_test_gen_ch1_test_pattern_off_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18f08) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bayer_rgb_o sel
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bayer or RGB select for output video: 0=bayer, 1=RGB
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_BAYER_RGB_O_SEL_DEFAULT (0)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_BAYER_RGB_O_SEL_DATASIZE (1)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_BAYER_RGB_O_SEL_OFFSET (0x80)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_BAYER_RGB_O_SEL_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_video_test_gen_ch1_bayer_rgb_o_sel_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f08);
    system_sw_write_32(base + 0x18f08, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_video_test_gen_ch1_bayer_rgb_o_sel_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18f08) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: pattern type
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Pattern type select: 0=Flat field,1=Horizontal gradient,2=Vertical Gradient,3=Vertical Bars,4=Rectangle,5-255=Default white frame on black
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_PATTERN_TYPE_DEFAULT (0x03)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_PATTERN_TYPE_DATASIZE (8)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_PATTERN_TYPE_OFFSET (0x84)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_PATTERN_TYPE_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_video_test_gen_ch1_pattern_type_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f0c);
    system_sw_write_32(base + 0x18f0c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_video_test_gen_ch1_pattern_type_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18f0c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: r backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Red background  value 16bit, MSB aligned to used width 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_BACKGND_OFFSET (0x88)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_r_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f10);
    system_sw_write_32(base + 0x18f10, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_r_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f10) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: g backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Green background value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_BACKGND_OFFSET (0x8c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_g_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f14);
    system_sw_write_32(base + 0x18f14, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_g_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f14) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: b backgnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Blue background value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_BACKGND_DEFAULT (0xFFFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_BACKGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_BACKGND_OFFSET (0x90)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_BACKGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_b_backgnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f18);
    system_sw_write_32(base + 0x18f18, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_b_backgnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f18) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: r foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Red foreground  value 16bit, MSB aligned to used width 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_FOREGND_OFFSET (0x94)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_R_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_r_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f1c);
    system_sw_write_32(base + 0x18f1c, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_r_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f1c) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: g foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Green foreground value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_FOREGND_OFFSET (0x98)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_G_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_g_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f20);
    system_sw_write_32(base + 0x18f20, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_g_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f20) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: b foregnd
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Blue foreground value 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_FOREGND_DEFAULT (0x8FFF)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_FOREGND_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_FOREGND_OFFSET (0x9c)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_B_FOREGND_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_b_foregnd_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f24);
    system_sw_write_32(base + 0x18f24, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_b_foregnd_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f24) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rgb gradient
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// RGB gradient increment per pixel (0-15) for first channel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_DEFAULT (0x3CAA)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_DATASIZE (16)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_OFFSET (0xa0)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_video_test_gen_ch1_rgb_gradient_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f28);
    system_sw_write_32(base + 0x18f28, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch1_rgb_gradient_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f28) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rgb_gradient start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// RGB gradient start value for first channel 16bit, MSB aligned to used width
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_START_DEFAULT (0x0000)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_START_DATASIZE (20)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_START_OFFSET (0xa4)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RGB_GRADIENT_START_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_video_test_gen_ch1_rgb_gradient_start_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f2c);
    system_sw_write_32(base + 0x18f2c, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_video_test_gen_ch1_rgb_gradient_start_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f2c) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect top
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle top line number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_TOP_DEFAULT (0x0001)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_TOP_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_TOP_OFFSET (0xa8)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_TOP_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch1_rect_top_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f30);
    system_sw_write_32(base + 0x18f30, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch1_rect_top_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f30) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect bot
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle bottom line number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_BOT_DEFAULT (0x0100)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_BOT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_BOT_OFFSET (0xa8)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_BOT_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch1_rect_bot_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f30);
    system_sw_write_32(base + 0x18f30, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_video_test_gen_ch1_rect_bot_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f30) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: rect left
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle left pixel number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_LEFT_DEFAULT (0x0001)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_LEFT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_LEFT_OFFSET (0xac)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_LEFT_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch1_rect_left_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f34);
    system_sw_write_32(base + 0x18f34, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_video_test_gen_ch1_rect_left_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f34) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rect right
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Rectangle right pixel number 1-n
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_RIGHT_DEFAULT (0x0100)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_RIGHT_DATASIZE (14)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_RIGHT_OFFSET (0xac)
#define ACAMERA_ISP_VIDEO_TEST_GEN_CH1_RECT_RIGHT_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_video_test_gen_ch1_rect_right_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f34);
    system_sw_write_32(base + 0x18f34, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_video_test_gen_ch1_rect_right_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18f34) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: input formatter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Adapts received data format to ISP format see the ISP Technical Reference Manual for a table of setting to be used for various sensors/modes.
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: mode in
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Input mode 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_DEFAULT (0)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_DATASIZE (3)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_OFFSET (0x110)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_MASK (0x7)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_LINEAR_DATA (0)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_LOGARITHMIC_ENCODING (2)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_COMPANDING_CURVE_WITH_KNEE_POINTS (3)
#define ACAMERA_ISP_INPUT_FORMATTER_MODE_IN_PASS_THROUGH_MODE (7)

// args: data (3-bit)
static __inline void acamera_isp_input_formatter_mode_in_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f98);
    system_sw_write_32(base + 0x18f98, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_input_formatter_mode_in_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18f98) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: input bitwidth select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Input bitwidth select 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_DEFAULT (2)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_DATASIZE (3)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_OFFSET (0x110)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_MASK (0x70000)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_8_BITS (0)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_10_BITS (1)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_12_BITS (2)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_14_BITS (3)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_16_BITS (4)
#define ACAMERA_ISP_INPUT_FORMATTER_INPUT_BITWIDTH_SELECT_20_BITS_NO_18_BITS (5)

// args: data (3-bit)
static __inline void acamera_isp_input_formatter_input_bitwidth_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f98);
    system_sw_write_32(base + 0x18f98, (((uint32_t) (data & 0x7)) << 16) | (curr & 0xfff8ffff));
}
static __inline uint8_t acamera_isp_input_formatter_input_bitwidth_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18f98) & 0x70000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: factor ML
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  18 bit, 6.12 fix point - ratio between long and medium exposure for 2:3 multiplexed mode 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_ML_DEFAULT (0x1000)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_ML_DATASIZE (18)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_ML_OFFSET (0x114)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_ML_MASK (0x3ffff)

// args: data (18-bit)
static __inline void acamera_isp_input_formatter_factor_ml_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18f9c);
    system_sw_write_32(base + 0x18f9c, (((uint32_t) (data & 0x3ffff)) << 0) | (curr & 0xfffc0000));
}
static __inline uint32_t acamera_isp_input_formatter_factor_ml_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x18f9c) & 0x3ffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: factor MS
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  13 bit, 1.12 fix point - ratio between short and medium exposure for 2:3 multiplexed mode 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_MS_DEFAULT (0x1000)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_MS_DATASIZE (13)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_MS_OFFSET (0x118)
#define ACAMERA_ISP_INPUT_FORMATTER_FACTOR_MS_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_input_formatter_factor_ms_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fa0);
    system_sw_write_32(base + 0x18fa0, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_input_formatter_factor_ms_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fa0) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: black level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Black level of sensor data for 2:3 multiplexed mode 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_BLACK_LEVEL_DEFAULT (0)
#define ACAMERA_ISP_INPUT_FORMATTER_BLACK_LEVEL_DATASIZE (12)
#define ACAMERA_ISP_INPUT_FORMATTER_BLACK_LEVEL_OFFSET (0x11c)
#define ACAMERA_ISP_INPUT_FORMATTER_BLACK_LEVEL_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_input_formatter_black_level_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fa4);
    system_sw_write_32(base + 0x18fa4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_input_formatter_black_level_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fa4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: knee point0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  First knee point
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT0_DEFAULT (512)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT0_DATASIZE (16)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT0_OFFSET (0x120)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT0_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_input_formatter_knee_point0_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fa8);
    system_sw_write_32(base + 0x18fa8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_input_formatter_knee_point0_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fa8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: knee point1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Second knee point
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT1_DEFAULT (1408)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT1_DATASIZE (16)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT1_OFFSET (0x120)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT1_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_input_formatter_knee_point1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fa8);
    system_sw_write_32(base + 0x18fa8, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_input_formatter_knee_point1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fa8) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: knee point2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Third knee point
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT2_DEFAULT (2177)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT2_DATASIZE (16)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT2_OFFSET (0x124)
#define ACAMERA_ISP_INPUT_FORMATTER_KNEE_POINT2_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_input_formatter_knee_point2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fac);
    system_sw_write_32(base + 0x18fac, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_input_formatter_knee_point2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fac) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: slope0 select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  First slope for companding table segments
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_DEFAULT (2)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_DATASIZE (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_OFFSET (0x128)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_MASK (0xf)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_1X (0)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_2X (1)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_4X (2)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_8X (3)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_16X (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_32X (5)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_64X (6)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_128X (7)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_256X (8)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_512X (9)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_1024X (10)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_2048X (11)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_4096X (12)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_8192X (13)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_16384X (14)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE0_SELECT_32768X (15)

// args: data (4-bit)
static __inline void acamera_isp_input_formatter_slope0_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fb0);
    system_sw_write_32(base + 0x18fb0, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_input_formatter_slope0_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18fb0) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: slope1 select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Second slope for companding table segments (encoding is the same as slope0 select)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE1_SELECT_DEFAULT (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE1_SELECT_DATASIZE (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE1_SELECT_OFFSET (0x128)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE1_SELECT_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_input_formatter_slope1_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fb0);
    system_sw_write_32(base + 0x18fb0, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_input_formatter_slope1_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18fb0) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: slope2 select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Third slope for companding table segments (encoding is the same as slope0 select)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE2_SELECT_DEFAULT (6)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE2_SELECT_DATASIZE (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE2_SELECT_OFFSET (0x128)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE2_SELECT_MASK (0xf0000)

// args: data (4-bit)
static __inline void acamera_isp_input_formatter_slope2_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fb0);
    system_sw_write_32(base + 0x18fb0, (((uint32_t) (data & 0xf)) << 16) | (curr & 0xfff0ffff));
}
static __inline uint8_t acamera_isp_input_formatter_slope2_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18fb0) & 0xf0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: slope3 select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Last slope for companding table segments (encoding is the same as slope0 select)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE3_SELECT_DEFAULT (9)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE3_SELECT_DATASIZE (4)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE3_SELECT_OFFSET (0x128)
#define ACAMERA_ISP_INPUT_FORMATTER_SLOPE3_SELECT_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_input_formatter_slope3_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fb0);
    system_sw_write_32(base + 0x18fb0, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_input_formatter_slope3_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x18fb0) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Group: sensor offset wdr l
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset subtraction for each color channel and exposure
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: offset 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_00_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_00_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_00_OFFSET (0x13c)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_00_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_l_offset_00_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fc4);
    system_sw_write_32(base + 0x18fc4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_l_offset_00_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fc4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_01_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_01_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_01_OFFSET (0x13c)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_01_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_l_offset_01_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fc4);
    system_sw_write_32(base + 0x18fc4, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_l_offset_01_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fc4) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: offset 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_10_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_10_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_10_OFFSET (0x140)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_10_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_l_offset_10_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fc8);
    system_sw_write_32(base + 0x18fc8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_l_offset_10_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fc8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_11_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_11_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_11_OFFSET (0x140)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_L_OFFSET_11_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_l_offset_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fc8);
    system_sw_write_32(base + 0x18fc8, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_l_offset_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fc8) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: sensor offset wdr m
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset subtraction for each color channel and exposure
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: offset 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_00_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_00_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_00_OFFSET (0x144)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_00_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_m_offset_00_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fcc);
    system_sw_write_32(base + 0x18fcc, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_m_offset_00_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fcc) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_01_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_01_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_01_OFFSET (0x144)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_01_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_m_offset_01_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fcc);
    system_sw_write_32(base + 0x18fcc, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_m_offset_01_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fcc) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: offset 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_10_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_10_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_10_OFFSET (0x148)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_10_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_m_offset_10_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fd0);
    system_sw_write_32(base + 0x18fd0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_m_offset_10_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fd0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_11_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_11_DATASIZE (12)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_11_OFFSET (0x148)
#define ACAMERA_ISP_SENSOR_OFFSET_WDR_M_OFFSET_11_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sensor_offset_wdr_m_offset_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fd0);
    system_sw_write_32(base + 0x18fd0, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sensor_offset_wdr_m_offset_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fd0) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: gain wdr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gain adjustment for the WDR stitching 
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Gain_l
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gain applied to ch-short data in 5.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_GAIN_WDR_GAIN_L_DEFAULT (0x100)
#define ACAMERA_ISP_GAIN_WDR_GAIN_L_DATASIZE (13)
#define ACAMERA_ISP_GAIN_WDR_GAIN_L_OFFSET (0x150)
#define ACAMERA_ISP_GAIN_WDR_GAIN_L_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_gain_wdr_gain_l_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fd8);
    system_sw_write_32(base + 0x18fd8, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_gain_wdr_gain_l_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fd8) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain_m
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gain applied to ch-vs data in 5.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_GAIN_WDR_GAIN_M_DEFAULT (0x100)
#define ACAMERA_ISP_GAIN_WDR_GAIN_M_DATASIZE (13)
#define ACAMERA_ISP_GAIN_WDR_GAIN_M_OFFSET (0x150)
#define ACAMERA_ISP_GAIN_WDR_GAIN_M_MASK (0x1fff0000)

// args: data (13-bit)
static __inline void acamera_isp_gain_wdr_gain_m_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fd8);
    system_sw_write_32(base + 0x18fd8, (((uint32_t) (data & 0x1fff)) << 16) | (curr & 0xe000ffff));
}
static __inline uint16_t acamera_isp_gain_wdr_gain_m_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fd8) & 0x1fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: black_level_l
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sensor offset applied to ch-short data
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_L_DEFAULT (0x0000)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_L_DATASIZE (12)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_L_OFFSET (0x158)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_L_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_gain_wdr_black_level_l_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fe0);
    system_sw_write_32(base + 0x18fe0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_gain_wdr_black_level_l_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fe0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: black_level_m
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sensor offset applied to ch-veryshort data
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_M_DEFAULT (0x0000)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_M_DATASIZE (12)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_M_OFFSET (0x158)
#define ACAMERA_ISP_GAIN_WDR_BLACK_LEVEL_M_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_gain_wdr_black_level_m_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fe0);
    system_sw_write_32(base + 0x18fe0, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_gain_wdr_black_level_m_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fe0) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: frame stitch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                2-exposure wide-dynamic-range blending
//
//                NOTE: 
//                    If the WDR is configured to stitch 2 exposures, then the configuration must be done through the LM_ pair
//                    The short exposures black level must be programmed through the med_black_level register so that the LM pair 
//                    can be used.
//
//
//          
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: LM_Exposure_Ratio
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sets ratio between long and medium exposures - this must match the actual exposure ratio on the sensor
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DEFAULT (0x100)
#define ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_OFFSET (0x160)
#define ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_exposure_ratio_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18fe8);
    system_sw_write_32(base + 0x18fe8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_exposure_ratio_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18fe8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: LM_Thresh_high
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            These two thresholds are for LM pairs. Both are with respect to the longer stitches.
//            Data above this threshold will be taken from short exposure only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_HIGH_DEFAULT (0x0F00)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_HIGH_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_HIGH_OFFSET (0x168)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_HIGH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_thresh_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ff0);
    system_sw_write_32(base + 0x18ff0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_thresh_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18ff0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: LM_Thresh_low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Data below this threshold will be taken from long exposure only
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_LOW_DEFAULT (0x0C00)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_LOW_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_LOW_OFFSET (0x168)
#define ACAMERA_ISP_FRAME_STITCH_LM_THRESH_LOW_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_thresh_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ff0);
    system_sw_write_32(base + 0x18ff0, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_thresh_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18ff0) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Black_level_long
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Black level for long exposure input
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_LONG_DEFAULT (0x000)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_LONG_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_LONG_OFFSET (0x174)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_LONG_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_black_level_long_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ffc);
    system_sw_write_32(base + 0x18ffc, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_black_level_long_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18ffc) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Black_level_Medium
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Black level for medium exposure input
//            *** NOTE ***:
//            If the WDR unit is configured to use as 2-exposure, THIS REGISTER POSITION must contain the black level of
//            short exposure as the LM pair is used for all other configurations
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM_DEFAULT (0x00)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM_OFFSET (0x174)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_black_level_medium_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x18ffc);
    system_sw_write_32(base + 0x18ffc, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_black_level_medium_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x18ffc) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Black_level_Out
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Black level for module output
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_OUT_DEFAULT (0x000)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_OUT_DATASIZE (20)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_OUT_OFFSET (0x17c)
#define ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_OUT_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_frame_stitch_black_level_out_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19004);
    system_sw_write_32(base + 0x19004, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_frame_stitch_black_level_out_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19004) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: LM_NP_mult
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            The noise profile weights are multiplied by this value to give expected noise amplitude. 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_NP_MULT_DEFAULT (0x180)
#define ACAMERA_ISP_FRAME_STITCH_LM_NP_MULT_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_NP_MULT_OFFSET (0x180)
#define ACAMERA_ISP_FRAME_STITCH_LM_NP_MULT_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_np_mult_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19008);
    system_sw_write_32(base + 0x19008, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_np_mult_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19008) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: LM_Alpha_MOV_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This defines the gradient of the motion alpha ramp. Higher values mean a steeper ramp and so a more rapid transition between 
//            non-motion-corrected and motion-corrected regions.
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_ALPHA_MOV_SLOPE_DEFAULT (0xC00)
#define ACAMERA_ISP_FRAME_STITCH_LM_ALPHA_MOV_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_ALPHA_MOV_SLOPE_OFFSET (0x184)
#define ACAMERA_ISP_FRAME_STITCH_LM_ALPHA_MOV_SLOPE_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_alpha_mov_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1900c);
    system_sw_write_32(base + 0x1900c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_alpha_mov_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1900c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Gain_R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            White balance gain multiplier for color channel R
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_GAIN_R_DEFAULT (0x100)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_R_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_R_OFFSET (0x18c)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_gain_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19014);
    system_sw_write_32(base + 0x19014, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_gain_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19014) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain_B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            White balance gain multiplier for color channel B
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_GAIN_B_DEFAULT (0x100)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_B_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_B_OFFSET (0x18c)
#define ACAMERA_ISP_FRAME_STITCH_GAIN_B_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_gain_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19014);
    system_sw_write_32(base + 0x19014, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_gain_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19014) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: lm_noise_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Higher values make it more likely to interpret differences between the long and medium exposures as noise (and thus do no motion correction).
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_NOISE_THRESH_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_LM_NOISE_THRESH_DATASIZE (6)
#define ACAMERA_ISP_FRAME_STITCH_LM_NOISE_THRESH_OFFSET (0x198)
#define ACAMERA_ISP_FRAME_STITCH_LM_NOISE_THRESH_MASK (0x3f)

// args: data (6-bit)
static __inline void acamera_isp_frame_stitch_lm_noise_thresh_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19020);
    system_sw_write_32(base + 0x19020, (((uint32_t) (data & 0x3f)) << 0) | (curr & 0xffffffc0));
}
static __inline uint8_t acamera_isp_frame_stitch_lm_noise_thresh_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19020) & 0x3f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: lm_pos_weight
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Lower values make it more likely to interpret  differences between the long and medium exposures as noise (and thus do no motion correction).
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_POS_WEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_LM_POS_WEIGHT_DATASIZE (6)
#define ACAMERA_ISP_FRAME_STITCH_LM_POS_WEIGHT_OFFSET (0x198)
#define ACAMERA_ISP_FRAME_STITCH_LM_POS_WEIGHT_MASK (0x3f00)

// args: data (6-bit)
static __inline void acamera_isp_frame_stitch_lm_pos_weight_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19020);
    system_sw_write_32(base + 0x19020, (((uint32_t) (data & 0x3f)) << 8) | (curr & 0xffffc0ff));
}
static __inline uint8_t acamera_isp_frame_stitch_lm_pos_weight_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19020) & 0x3f00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: lm_neg_weight
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Higher values make it more likely to interpret differences between the long and medium exposures as noise (and thus do no motion correction).
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_NEG_WEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_LM_NEG_WEIGHT_DATASIZE (6)
#define ACAMERA_ISP_FRAME_STITCH_LM_NEG_WEIGHT_OFFSET (0x198)
#define ACAMERA_ISP_FRAME_STITCH_LM_NEG_WEIGHT_MASK (0x3f0000)

// args: data (6-bit)
static __inline void acamera_isp_frame_stitch_lm_neg_weight_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19020);
    system_sw_write_32(base + 0x19020, (((uint32_t) (data & 0x3f)) << 16) | (curr & 0xffc0ffff));
}
static __inline uint8_t acamera_isp_frame_stitch_lm_neg_weight_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19020) & 0x3f0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: lm_med_noise_alpha_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Used in Stitch(LM), for the exposure mask generation.
//            If Alpha value above this alpha_thresh and the selected smax_3x3 below intensity_thresh, the exposure mask will be set to 2.
//            Format: u.12
//            Range: [0, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_ALPHA_THRESH_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_ALPHA_THRESH_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_ALPHA_THRESH_OFFSET (0x19c)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_ALPHA_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_med_noise_alpha_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19024);
    system_sw_write_32(base + 0x19024, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_med_noise_alpha_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19024) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: lm_med_noise_intensity_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Used in Stitch(LM), for the exposure mask generation.
//            If Alpha value above this alpha_thresh and the selected smax_3x3 below intensity_thresh, the exposure mask will be set to 2. 
//            Format: u12.0
//            Range: [0, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_INTENSITY_THRESH_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_INTENSITY_THRESH_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_INTENSITY_THRESH_OFFSET (0x19c)
#define ACAMERA_ISP_FRAME_STITCH_LM_MED_NOISE_INTENSITY_THRESH_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_lm_med_noise_intensity_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19024);
    system_sw_write_32(base + 0x19024, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_lm_med_noise_intensity_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19024) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff WB offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            White balance compensation gain. Only used when bwb_select being 1, for MCOFF Stitich internal clip_up thresholds generation.
//            Format: u4.8
//            Range: [256, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_WB_OFFSET_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_WB_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_WB_OFFSET_OFFSET (0x1c0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_WB_OFFSET_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_wb_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19048);
    system_sw_write_32(base + 0x19048, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_wb_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19048) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Exposure_mask_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Threshold for selection of exposure mask in blending regions.
//              Where the alpha value is above this value the shorter exposure will be indicated.
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_EXPOSURE_MASK_THRESH_DEFAULT (0x20)
#define ACAMERA_ISP_FRAME_STITCH_EXPOSURE_MASK_THRESH_DATASIZE (8)
#define ACAMERA_ISP_FRAME_STITCH_EXPOSURE_MASK_THRESH_OFFSET (0x1c0)
#define ACAMERA_ISP_FRAME_STITCH_EXPOSURE_MASK_THRESH_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_frame_stitch_exposure_mask_thresh_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19048);
    system_sw_write_32(base + 0x19048, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_frame_stitch_exposure_mask_thresh_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19048) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: bwb_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            To decide the method for MCOFF Stitch internal clip_up thresholds generation.
//            When being 0, all the internal clip_up thresholds will be equal to mcoff_l/m_max exactly for all the exposures, and exactly same for Bayer RGGB.
//            When being 1, extra gains related with gain_r/gain_b/mcoff_wb_offset will be added to mcoff_l/m_max for the internal clip_up thresholds generation. 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_BWB_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_BWB_SELECT_DATASIZE (1)
#define ACAMERA_ISP_FRAME_STITCH_BWB_SELECT_OFFSET (0x1c4)
#define ACAMERA_ISP_FRAME_STITCH_BWB_SELECT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_frame_stitch_bwb_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1904c);
    system_sw_write_32(base + 0x1904c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_frame_stitch_bwb_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1904c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: use_3x3_max
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            To generate the selected smax_3x3 in wdr_analyse_3x5.
//            If being 1, the max3x3 will be selected as smax_3x3, otherwise, just select the clipped black level clean shorter exposure data, which is the max3x3 input.
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_USE_3X3_MAX_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_USE_3X3_MAX_DATASIZE (1)
#define ACAMERA_ISP_FRAME_STITCH_USE_3X3_MAX_OFFSET (0x1c4)
#define ACAMERA_ISP_FRAME_STITCH_USE_3X3_MAX_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_frame_stitch_use_3x3_max_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1904c);
    system_sw_write_32(base + 0x1904c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_frame_stitch_use_3x3_max_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1904c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: mcoff mode enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0 = Normal Stitch out. 1 = MCOFF Stitch out.
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_MODE_ENABLE_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_MODE_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_MODE_ENABLE_OFFSET (0x1c4)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_MODE_ENABLE_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_frame_stitch_mcoff_mode_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1904c);
    system_sw_write_32(base + 0x1904c, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_frame_stitch_mcoff_mode_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1904c) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff NC Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Used in MCOFF Stitch, to enable Noise Coring method.
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_ENABLE_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_ENABLE_OFFSET (0x1c4)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_ENABLE_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_frame_stitch_mcoff_nc_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1904c);
    system_sw_write_32(base + 0x1904c, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_frame_stitch_mcoff_nc_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1904c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff L max
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Used in MCOFF Stitch, for the internal long exposure clip_up threshold generation.
//            Format: u12.0
//            Range: [0, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_MAX_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_MAX_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_MAX_OFFSET (0x1c8)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_MAX_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_l_max_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19050);
    system_sw_write_32(base + 0x19050, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_l_max_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19050) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff M max
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Used in MCOFF Stitch, for the internal medium exposure clip_up threshold generation.
//            Format: u12.0
//            Range: [0, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_M_MAX_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_M_MAX_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_M_MAX_OFFSET (0x1c8)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_M_MAX_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_m_max_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19050);
    system_sw_write_32(base + 0x19050, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_m_max_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19050) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff L scaler
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Scaling factor used in 2 exposures scenarios in MCOFF mode.
//            Format: u1.11
//            Range: [0, 2048].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_OFFSET (0x1d0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_l_scaler_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19058);
    system_sw_write_32(base + 0x19058, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_l_scaler_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19058) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff NC thresh low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            In Noise Coring method, if the black adjusted exposures are less than mcoff_nc_thresh_low, they will be set to 0, and unchanged if they are no smaller than mcoff_nc_thresh_high.
//            For the values between thresholds low and high, there is a ramp up to mcoff_nc_thresh_high to create a smooth transistion between the noise-coring region, and the unchanged region.
//            The ramp gradient is defined by mcoff_nc_scale. 
//            Format: u12.0
//            Range [0, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_LOW_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_LOW_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_LOW_OFFSET (0x1d4)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_LOW_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_nc_thresh_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1905c);
    system_sw_write_32(base + 0x1905c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_nc_thresh_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1905c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff NC thresh high
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise Coring method high threshold
//            Format: u12.0
//            Range [mcoff_nc_thresh_low+1, 4095].
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_HIGH_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_HIGH_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_HIGH_OFFSET (0x1d8)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_THRESH_HIGH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_nc_thresh_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19060);
    system_sw_write_32(base + 0x19060, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_nc_thresh_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19060) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: MCoff NC scale
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise Coring method scale
//            Format: u12.0
//            Range [0, 4095]
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_SCALE_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_SCALE_DATASIZE (12)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_SCALE_OFFSET (0x1d8)
#define ACAMERA_ISP_FRAME_STITCH_MCOFF_NC_SCALE_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_frame_stitch_mcoff_nc_scale_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19060);
    system_sw_write_32(base + 0x19060, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_frame_stitch_mcoff_nc_scale_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19060) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: frame stitch NP LUT L
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile for long exposure data at frame stitch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Weight lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile LUT.  Calculated during calibration process.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FRAME_STITCH_NP_LUT_L_WEIGHT_LUT_DEFAULT (0x0)
#define ACAMERA_ISP_FRAME_STITCH_NP_LUT_L_WEIGHT_LUT_DATASIZE (8)
#define ACAMERA_ISP_FRAME_STITCH_NP_LUT_L_WEIGHT_LUT_OFFSET (0x35c)
#define ACAMERA_ISP_FRAME_STITCH_NP_LUT_L_WEIGHT_LUT_MASK (0xff)

// index (0-127), args: data (8-bit)
static __inline void acamera_isp_frame_stitch_np_lut_l_weight_lut_write( uintptr_t base, uint32_t index,uint8_t data ) {
    uintptr_t addr = base + 0x191e4 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    uint32_t curr = system_sw_read_32( addr );
    system_sw_write_32( addr, ( (uint32_t)data << offset ) | ( curr & ~( 0xFF << offset ) ) );
}
static __inline uint8_t acamera_isp_frame_stitch_np_lut_l_weight_lut_read( uintptr_t base, uint32_t index ) {
    uintptr_t addr = base + 0x191e4 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    return (uint8_t)( system_sw_read_32( addr ) >> offset );
}
// ------------------------------------------------------------------------------ //
// Group: decompander0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Frontend lookup (for companded WDR sensor inputs)
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Frontend lookup0 enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DECOMPANDER0_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_DECOMPANDER0_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_DECOMPANDER0_ENABLE_OFFSET (0x3dc)
#define ACAMERA_ISP_DECOMPANDER0_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_decompander0_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19264);
    system_sw_write_32(base + 0x19264, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_decompander0_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19264) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Offset Mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          Lookup0 reflection mode for black offset region
//          0 = Manual curve reflection
//          1 = Automatic curve reflection
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DECOMPANDER0_OFFSET_MODE_DEFAULT (0)
#define ACAMERA_ISP_DECOMPANDER0_OFFSET_MODE_DATASIZE (1)
#define ACAMERA_ISP_DECOMPANDER0_OFFSET_MODE_OFFSET (0x3dc)
#define ACAMERA_ISP_DECOMPANDER0_OFFSET_MODE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_decompander0_offset_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19264);
    system_sw_write_32(base + 0x19264, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_decompander0_offset_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19264) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Group: decompander1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Frontend lookup (for companded WDR sensor inputs)
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Frontend lookup0 enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DECOMPANDER1_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_DECOMPANDER1_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_DECOMPANDER1_ENABLE_OFFSET (0x3e0)
#define ACAMERA_ISP_DECOMPANDER1_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_decompander1_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19268);
    system_sw_write_32(base + 0x19268, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_decompander1_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19268) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Offset Mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          Lookup0 reflection mode for black offset region
//          0 = Manual curve reflection
//          1 = Automatic curve reflection
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DECOMPANDER1_OFFSET_MODE_DEFAULT (0)
#define ACAMERA_ISP_DECOMPANDER1_OFFSET_MODE_DATASIZE (1)
#define ACAMERA_ISP_DECOMPANDER1_OFFSET_MODE_OFFSET (0x3e0)
#define ACAMERA_ISP_DECOMPANDER1_OFFSET_MODE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_decompander1_offset_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19268);
    system_sw_write_32(base + 0x19268, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_decompander1_offset_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19268) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Group: digital gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Digital gain for RAW sensor data
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gain applied to data in 5.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DIGITAL_GAIN_GAIN_DEFAULT (0x100)
#define ACAMERA_ISP_DIGITAL_GAIN_GAIN_DATASIZE (13)
#define ACAMERA_ISP_DIGITAL_GAIN_GAIN_OFFSET (0x3e4)
#define ACAMERA_ISP_DIGITAL_GAIN_GAIN_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_digital_gain_gain_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1926c);
    system_sw_write_32(base + 0x1926c, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_digital_gain_gain_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1926c) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DIGITAL_GAIN_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_DIGITAL_GAIN_OFFSET_DATASIZE (20)
#define ACAMERA_ISP_DIGITAL_GAIN_OFFSET_OFFSET (0x3e8)
#define ACAMERA_ISP_DIGITAL_GAIN_OFFSET_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_digital_gain_offset_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19270);
    system_sw_write_32(base + 0x19270, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_digital_gain_offset_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19270) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: sensor offset fe
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset subtraction for each color channel and exposure
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: offset 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_00_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_00_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_00_OFFSET (0x3ec)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_00_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_fe_offset_00_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19274);
    system_sw_write_32(base + 0x19274, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_fe_offset_00_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19274) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_01_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_01_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_01_OFFSET (0x3f0)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_01_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_fe_offset_01_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19278);
    system_sw_write_32(base + 0x19278, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_fe_offset_01_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19278) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_10_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_10_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_10_OFFSET (0x3f4)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_10_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_fe_offset_10_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1927c);
    system_sw_write_32(base + 0x1927c, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_fe_offset_10_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1927c) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_11_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_11_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_11_OFFSET (0x3f8)
#define ACAMERA_ISP_SENSOR_OFFSET_FE_OFFSET_11_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_fe_offset_11_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19280);
    system_sw_write_32(base + 0x19280, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_fe_offset_11_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19280) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: sqrt
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sensor offset for the sqrt module
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: black_level_in
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// input Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQRT_BLACK_LEVEL_IN_DEFAULT (0x000)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_IN_DATASIZE (20)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_IN_OFFSET (0x3fc)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_IN_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sqrt_black_level_in_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19284);
    system_sw_write_32(base + 0x19284, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sqrt_black_level_in_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19284) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: black_level_out
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// output Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQRT_BLACK_LEVEL_OUT_DEFAULT (0x000)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_OUT_DATASIZE (12)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_OUT_OFFSET (0x400)
#define ACAMERA_ISP_SQRT_BLACK_LEVEL_OUT_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sqrt_black_level_out_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19288);
    system_sw_write_32(base + 0x19288, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sqrt_black_level_out_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19288) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: normalization
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Normalization
//        The normalization coefficient input to be multiplied on the converted linear data. The format is u1.16.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQRT_NORMALIZATION_DEFAULT (0x10000)
#define ACAMERA_ISP_SQRT_NORMALIZATION_DATASIZE (17)
#define ACAMERA_ISP_SQRT_NORMALIZATION_OFFSET (0x400)
#define ACAMERA_ISP_SQRT_NORMALIZATION_MASK (0xffff8000)

// args: data (17-bit)
static __inline void acamera_isp_sqrt_normalization_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19288);
    system_sw_write_32(base + 0x19288, (((uint32_t) (data & 0x1ffff)) << 15) | (curr & 0x7fff));
}
static __inline uint32_t acamera_isp_sqrt_normalization_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x19288) & 0xffff8000) >> 15);
}
// ------------------------------------------------------------------------------ //
// Group: raw frontend
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// RAW frontend processing
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: dp enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Dynamic Defect Pixel enable: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_DP_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_RAW_FRONTEND_DP_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_RAW_FRONTEND_DP_ENABLE_OFFSET (0x404)
#define ACAMERA_ISP_RAW_FRONTEND_DP_ENABLE_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_raw_frontend_dp_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1928c);
    system_sw_write_32(base + 0x1928c, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_raw_frontend_dp_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1928c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: show dynamic defect pixel
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Show Defect Pixel: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_SHOW_DYNAMIC_DEFECT_PIXEL_DEFAULT (0)
#define ACAMERA_ISP_RAW_FRONTEND_SHOW_DYNAMIC_DEFECT_PIXEL_DATASIZE (1)
#define ACAMERA_ISP_RAW_FRONTEND_SHOW_DYNAMIC_DEFECT_PIXEL_OFFSET (0x404)
#define ACAMERA_ISP_RAW_FRONTEND_SHOW_DYNAMIC_DEFECT_PIXEL_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_raw_frontend_show_dynamic_defect_pixel_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1928c);
    system_sw_write_32(base + 0x1928c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_raw_frontend_show_dynamic_defect_pixel_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1928c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: dark disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Disable detection of dark pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_DARK_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_RAW_FRONTEND_DARK_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_RAW_FRONTEND_DARK_DISABLE_OFFSET (0x404)
#define ACAMERA_ISP_RAW_FRONTEND_DARK_DISABLE_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_raw_frontend_dark_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1928c);
    system_sw_write_32(base + 0x1928c, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_raw_frontend_dark_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1928c) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: bright disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Disable detection of bright pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_BRIGHT_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_RAW_FRONTEND_BRIGHT_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_RAW_FRONTEND_BRIGHT_DISABLE_OFFSET (0x404)
#define ACAMERA_ISP_RAW_FRONTEND_BRIGHT_DISABLE_MASK (0x80)

// args: data (1-bit)
static __inline void acamera_isp_raw_frontend_bright_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1928c);
    system_sw_write_32(base + 0x1928c, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_raw_frontend_bright_disable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1928c) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: dp slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Slope for HP Mask function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_DP_SLOPE_DEFAULT (0x200)
#define ACAMERA_ISP_RAW_FRONTEND_DP_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_RAW_FRONTEND_DP_SLOPE_OFFSET (0x40c)
#define ACAMERA_ISP_RAW_FRONTEND_DP_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_raw_frontend_dp_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19294);
    system_sw_write_32(base + 0x19294, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_raw_frontend_dp_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19294) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: dp threshold
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Defect pixel threshold. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_DEFAULT (0x040)
#define ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_DATASIZE (12)
#define ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_OFFSET (0x40c)
#define ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_raw_frontend_dp_threshold_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19294);
    system_sw_write_32(base + 0x19294, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_raw_frontend_dp_threshold_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19294) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: dpdev threshold
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Controls the aggressiveness of the dynamic defect pixel correction near edges. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_HPDEV_THRESHOLD_DEFAULT (0x800)
#define ACAMERA_ISP_RAW_FRONTEND_HPDEV_THRESHOLD_DATASIZE (12)
#define ACAMERA_ISP_RAW_FRONTEND_HPDEV_THRESHOLD_OFFSET (0x410)
#define ACAMERA_ISP_RAW_FRONTEND_HPDEV_THRESHOLD_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_raw_frontend_hpdev_threshold_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19298);
    system_sw_write_32(base + 0x19298, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_raw_frontend_hpdev_threshold_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19298) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: dp blend
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Controls blending between non-directional and directional replacement values in dynamic defect pixel correction.
//        0x00 Replace detected defects with non-directional replacement value
//        0xFF Replace detected defects with directional replacement value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_HP_BLEND_DEFAULT (0x00)
#define ACAMERA_ISP_RAW_FRONTEND_HP_BLEND_DATASIZE (8)
#define ACAMERA_ISP_RAW_FRONTEND_HP_BLEND_OFFSET (0x410)
#define ACAMERA_ISP_RAW_FRONTEND_HP_BLEND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_raw_frontend_hp_blend_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19298);
    system_sw_write_32(base + 0x19298, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_raw_frontend_hp_blend_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19298) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: line thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Controls the directional nature of the dynamic defect pixel correction near edges..
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_LINE_THRESH_DEFAULT (0x0)
#define ACAMERA_ISP_RAW_FRONTEND_LINE_THRESH_DATASIZE (12)
#define ACAMERA_ISP_RAW_FRONTEND_LINE_THRESH_OFFSET (0x41c)
#define ACAMERA_ISP_RAW_FRONTEND_LINE_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_raw_frontend_line_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x192a4);
    system_sw_write_32(base + 0x192a4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_raw_frontend_line_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x192a4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Sigma In
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Manual override of noise estimation 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_RAW_FRONTEND_SIGMA_IN_DEFAULT (0x00)
#define ACAMERA_ISP_RAW_FRONTEND_SIGMA_IN_DATASIZE (12)
#define ACAMERA_ISP_RAW_FRONTEND_SIGMA_IN_OFFSET (0x41c)
#define ACAMERA_ISP_RAW_FRONTEND_SIGMA_IN_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_raw_frontend_sigma_in_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x192a4);
    system_sw_write_32(base + 0x192a4, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_raw_frontend_sigma_in_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x192a4) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: sinter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Spatial noise reduction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Config1
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_CONFIG1_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_CONFIG1_DATASIZE (8)
#define ACAMERA_ISP_SINTER_CONFIG1_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_CONFIG1_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_config1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_config1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sinter enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_SINTER_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_SINTER_ENABLE_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_ENABLE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_sinter_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_sinter_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: View Filter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// For debug purposes only. Set to zero for normal operation
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_VIEW_FILTER_DEFAULT (0)
#define ACAMERA_ISP_SINTER_VIEW_FILTER_DATASIZE (2)
#define ACAMERA_ISP_SINTER_VIEW_FILTER_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_VIEW_FILTER_MASK (0x3)

// args: data (2-bit)
static __inline void acamera_isp_sinter_view_filter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x3)) << 0) | (curr & 0xfffffffc));
}
static __inline uint8_t acamera_isp_sinter_view_filter_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0x3) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Scale Mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// For debug purposes only. Set to 3 for normal operation
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_SCALE_MODE_DEFAULT (3)
#define ACAMERA_ISP_SINTER_SCALE_MODE_DATASIZE (2)
#define ACAMERA_ISP_SINTER_SCALE_MODE_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_SCALE_MODE_MASK (0xc)
#define ACAMERA_ISP_SINTER_SCALE_MODE_USE_FILTER_0_ONLY (0)
#define ACAMERA_ISP_SINTER_SCALE_MODE_USE_FILTERS_0_AND_2_ONLY (1)
#define ACAMERA_ISP_SINTER_SCALE_MODE_USE_FILTERS_0_2_AND_4_ONLY (2)
#define ACAMERA_ISP_SINTER_SCALE_MODE_USE_ALL_FILTERS (3)

// args: data (2-bit)
static __inline void acamera_isp_sinter_scale_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x3)) << 2) | (curr & 0xfffffff3));
}
static __inline uint8_t acamera_isp_sinter_scale_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0xc) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Filter select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sinter filter fine tuning.  Should not be modified from suggested values.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_FILTER_SELECT_DEFAULT (0)
#define ACAMERA_ISP_SINTER_FILTER_SELECT_DATASIZE (1)
#define ACAMERA_ISP_SINTER_FILTER_SELECT_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_FILTER_SELECT_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_sinter_filter_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_sinter_filter_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: Int select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Select intensity filter.  Should not be modified from suggested values.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_INT_SELECT_DEFAULT (1)
#define ACAMERA_ISP_SINTER_INT_SELECT_DATASIZE (1)
#define ACAMERA_ISP_SINTER_INT_SELECT_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_INT_SELECT_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_sinter_int_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_sinter_int_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: rm_enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Adjusts sinter strength radially from centre to compensate for Lens shading correction.
//            enable: 0=off, 1=on
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_RM_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_SINTER_RM_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_SINTER_RM_ENABLE_OFFSET (0x4c0)
#define ACAMERA_ISP_SINTER_RM_ENABLE_MASK (0x80)

// args: data (1-bit)
static __inline void acamera_isp_sinter_rm_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19348);
    system_sw_write_32(base + 0x19348, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_sinter_rm_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19348) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: Config2
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_CONFIG2_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_CONFIG2_DATASIZE (8)
#define ACAMERA_ISP_SINTER_CONFIG2_OFFSET (0x4c4)
#define ACAMERA_ISP_SINTER_CONFIG2_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_config2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1934c);
    system_sw_write_32(base + 0x1934c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_config2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1934c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: int_config
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Intensity blending with mosaic raw
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_INT_CONFIG_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_INT_CONFIG_DATASIZE (4)
#define ACAMERA_ISP_SINTER_INT_CONFIG_OFFSET (0x4c4)
#define ACAMERA_ISP_SINTER_INT_CONFIG_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_sinter_int_config_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1934c);
    system_sw_write_32(base + 0x1934c, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_sinter_int_config_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1934c) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rm_center_x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Centre x coordinate of shading map
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_RM_CENTER_X_DEFAULT (0x3C0)
#define ACAMERA_ISP_SINTER_RM_CENTER_X_DATASIZE (16)
#define ACAMERA_ISP_SINTER_RM_CENTER_X_OFFSET (0x4c8)
#define ACAMERA_ISP_SINTER_RM_CENTER_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_sinter_rm_center_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19350);
    system_sw_write_32(base + 0x19350, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_sinter_rm_center_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19350) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rm_center_y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Centre y coordinate of shading map
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_RM_CENTER_Y_DEFAULT (0x21C)
#define ACAMERA_ISP_SINTER_RM_CENTER_Y_DATASIZE (16)
#define ACAMERA_ISP_SINTER_RM_CENTER_Y_OFFSET (0x4c8)
#define ACAMERA_ISP_SINTER_RM_CENTER_Y_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_sinter_rm_center_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19350);
    system_sw_write_32(base + 0x19350, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_sinter_rm_center_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19350) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: rm_off_center_mult
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          Normalizing factor which scales the radial table to the edge of the image.
//          Calculated as 2^31/R^2 where R is the furthest distance from the centre coordinate to the edge of the image in pixels.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_RM_OFF_CENTER_MULT_DEFAULT (0x0100)
#define ACAMERA_ISP_SINTER_RM_OFF_CENTER_MULT_DATASIZE (16)
#define ACAMERA_ISP_SINTER_RM_OFF_CENTER_MULT_OFFSET (0x4cc)
#define ACAMERA_ISP_SINTER_RM_OFF_CENTER_MULT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_sinter_rm_off_center_mult_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19354);
    system_sw_write_32(base + 0x19354, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_sinter_rm_off_center_mult_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19354) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh 1h
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise threshold for high horizontal spatial frequencies
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_THRESH_1H_DEFAULT (20)
#define ACAMERA_ISP_SINTER_THRESH_1H_DATASIZE (8)
#define ACAMERA_ISP_SINTER_THRESH_1H_OFFSET (0x4d0)
#define ACAMERA_ISP_SINTER_THRESH_1H_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_thresh_1h_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19358);
    system_sw_write_32(base + 0x19358, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_thresh_1h_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19358) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh 4h
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise threshold for low horizontal spatial frequencies. If sinter_lite version has been selected (controlled by toplevel parameter SINTER_LITE = 1), set this config to 0.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_THRESH_4H_DEFAULT (20)
#define ACAMERA_ISP_SINTER_THRESH_4H_DATASIZE (8)
#define ACAMERA_ISP_SINTER_THRESH_4H_OFFSET (0x4d0)
#define ACAMERA_ISP_SINTER_THRESH_4H_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_sinter_thresh_4h_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19358);
    system_sw_write_32(base + 0x19358, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_sinter_thresh_4h_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19358) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh 1v
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise threshold for high vertical spatial frequencies
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_THRESH_1V_DEFAULT (20)
#define ACAMERA_ISP_SINTER_THRESH_1V_DATASIZE (8)
#define ACAMERA_ISP_SINTER_THRESH_1V_OFFSET (0x4d0)
#define ACAMERA_ISP_SINTER_THRESH_1V_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_thresh_1v_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19358);
    system_sw_write_32(base + 0x19358, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_sinter_thresh_1v_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19358) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh 4v
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise threshold for low vertical spatial frequencies. If sinter_lite version has been selected (controlled by toplevel parameter SINTER_LITE = 1), set this config to 0.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_THRESH_4V_DEFAULT (20)
#define ACAMERA_ISP_SINTER_THRESH_4V_DATASIZE (8)
#define ACAMERA_ISP_SINTER_THRESH_4V_OFFSET (0x4d0)
#define ACAMERA_ISP_SINTER_THRESH_4V_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_thresh_4v_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19358);
    system_sw_write_32(base + 0x19358, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_sinter_thresh_4v_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19358) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: Strength 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise reduction effect for high spatial frequencies
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_STRENGTH_1_DEFAULT (0xC8)
#define ACAMERA_ISP_SINTER_STRENGTH_1_DATASIZE (8)
#define ACAMERA_ISP_SINTER_STRENGTH_1_OFFSET (0x4d4)
#define ACAMERA_ISP_SINTER_STRENGTH_1_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_strength_1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1935c);
    system_sw_write_32(base + 0x1935c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_strength_1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1935c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Strength 4
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise reduction effect for low spatial frequencies. If sinter_lite version has been selected (controlled by toplevel parameter SINTER_LITE = 1), set this config to 0.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_STRENGTH_4_DEFAULT (0xFF)
#define ACAMERA_ISP_SINTER_STRENGTH_4_DATASIZE (8)
#define ACAMERA_ISP_SINTER_STRENGTH_4_OFFSET (0x4d4)
#define ACAMERA_ISP_SINTER_STRENGTH_4_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_sinter_strength_4_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1935c);
    system_sw_write_32(base + 0x1935c, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_sinter_strength_4_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1935c) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Group: sinter Noise Profile
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile controls for Sinter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Black Reflect
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Specifies how to deal with data below black level. 0: Clip to zero, 1: Reflect.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_REFLECT_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_REFLECT_DATASIZE (1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_REFLECT_OFFSET (0x4d8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_REFLECT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_sinter_noise_profile_black_reflect_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19360);
    system_sw_write_32(base + 0x19360, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_black_reflect_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19360) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: global offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// A global offset that will be added to each of the hlog... values above..
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_GLOBAL_OFFSET_DEFAULT (0x08)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_GLOBAL_OFFSET_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_GLOBAL_OFFSET_OFFSET (0x4d8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_GLOBAL_OFFSET_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_global_offset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19360);
    system_sw_write_32(base + 0x19360, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_global_offset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19360) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Black Level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Black level offset for Mode 0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_LEVEL_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_LEVEL_DATASIZE (12)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_LEVEL_OFFSET (0x4dc)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_BLACK_LEVEL_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sinter_noise_profile_black_level_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19364);
    system_sw_write_32(base + 0x19364, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sinter_noise_profile_black_level_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19364) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//		  Exposure thresholds. Used to determine which exposure generated the current pixel.
//		  Pixels with a value greater than or equal to a given threshold will be deemed to have been generated by the shorter exposure.
//		  Pixels with a value less than a given threshold will be deemed to have been generated by the longer exposure.
//		  
//		  For example, where 4 exposures are used:
//		    VS >= Thresh 3 > S >= Thresh 2 > M >= Thresh 1 > L
//		    
//		  For 3 exposures set Thresh 1 to 0
//		  For 2 exposures set Thresh 1 and Thresh 2 to 0
//		  For 1 exposures set all exposure thresholds to 0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH1_DEFAULT (0x400)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH1_DATASIZE (12)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH1_OFFSET (0x4dc)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH1_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sinter_noise_profile_thresh1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19364);
    system_sw_write_32(base + 0x19364, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sinter_noise_profile_thresh1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19364) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// See above (thresh1 description).
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH2_DEFAULT (0x800)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH2_DATASIZE (12)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH2_OFFSET (0x4e0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH2_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_sinter_noise_profile_thresh2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19368);
    system_sw_write_32(base + 0x19368, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_sinter_noise_profile_thresh2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19368) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// See above (thresh1 description).
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH3_DEFAULT (0xC00)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH3_DATASIZE (12)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH3_OFFSET (0x4e0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_THRESH3_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_sinter_noise_profile_thresh3_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19368);
    system_sw_write_32(base + 0x19368, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_sinter_noise_profile_thresh3_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x19368) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// noise_level_r
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_R_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_R_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_R_OFFSET (0x4e4)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_R_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_noise_level_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1936c);
    system_sw_write_32(base + 0x1936c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_noise_level_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1936c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// noise_level_b
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_B_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_B_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_B_OFFSET (0x4e4)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_NOISE_LEVEL_B_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_noise_level_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1936c);
    system_sw_write_32(base + 0x1936c, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_noise_level_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1936c) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: add_lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0 = Do not add LUT
//            1 = Add LUT
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_LUT_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_LUT_DATASIZE (1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_LUT_OFFSET (0x4e8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_LUT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_sinter_noise_profile_add_lut_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19370);
    system_sw_write_32(base + 0x19370, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_add_lut_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19370) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: exp_mask_from_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0 = Use 2-bit mask for exposure, zero the motion_offset
//            1 = Use 2-bit mask for motion, thresholds for exposure.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_MASK_FROM_THRESH_DEFAULT (0x1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_MASK_FROM_THRESH_DATASIZE (1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_MASK_FROM_THRESH_OFFSET (0x4e8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_MASK_FROM_THRESH_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_sinter_noise_profile_exp_mask_from_thresh_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19370);
    system_sw_write_32(base + 0x19370, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_exp_mask_from_thresh_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19370) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: add_exp_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0 = Do not add exposure offset
//            1 = Add exposure offset
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_EXP_OFFSET_DEFAULT (0x1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_EXP_OFFSET_DATASIZE (1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_EXP_OFFSET_OFFSET (0x4e8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_EXP_OFFSET_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_sinter_noise_profile_add_exp_offset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19370);
    system_sw_write_32(base + 0x19370, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_add_exp_offset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19370) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: add_motion_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0 = Do not add motion offset
//            1 = Add motion offset
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_MOTION_OFFSET_DEFAULT (0x1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_MOTION_OFFSET_DATASIZE (1)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_MOTION_OFFSET_OFFSET (0x4e8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_ADD_MOTION_OFFSET_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_sinter_noise_profile_add_motion_offset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19370);
    system_sw_write_32(base + 0x19370, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_add_motion_offset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19370) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: exp_offset_0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise level of short exposure (u4.4 format)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_0_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_0_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_0_OFFSET (0x4ec)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_0_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_exp_offset_0_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19374);
    system_sw_write_32(base + 0x19374, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_exp_offset_0_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19374) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: exp_offset_1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise level of long exposure (u4.4 format)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_1_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_1_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_1_OFFSET (0x4ec)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_1_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_exp_offset_1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19374);
    system_sw_write_32(base + 0x19374, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_exp_offset_1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19374) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: exp_offset_2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise level of short exposure in dark motion regions.(u4.4 format)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_2_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_2_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_2_OFFSET (0x4ec)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_2_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_exp_offset_2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19374);
    system_sw_write_32(base + 0x19374, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_exp_offset_2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19374) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: exp_offset_3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            exp_offset_3
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_3_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_3_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_3_OFFSET (0x4ec)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_EXP_OFFSET_3_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_exp_offset_3_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19374);
    system_sw_write_32(base + 0x19374, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_exp_offset_3_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19374) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: motion_offset_0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise offset for highest motion level.(u4.4 format)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_0_DEFAULT (0xA)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_0_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_0_OFFSET (0x4f0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_0_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_motion_offset_0_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19378);
    system_sw_write_32(base + 0x19378, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_motion_offset_0_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19378) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: motion_offset_1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            motion_offset_1
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_1_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_1_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_1_OFFSET (0x4f0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_1_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_motion_offset_1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19378);
    system_sw_write_32(base + 0x19378, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_motion_offset_1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19378) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: motion_offset_2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            motion_offset_2
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_2_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_2_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_2_OFFSET (0x4f0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_2_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_motion_offset_2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19378);
    system_sw_write_32(base + 0x19378, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_motion_offset_2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19378) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: motion_offset_3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Noise offset for lowest motion level.(u4.4 format)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_3_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_3_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_3_OFFSET (0x4f0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_MOTION_OFFSET_3_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_motion_offset_3_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x19378);
    system_sw_write_32(base + 0x19378, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_sinter_noise_profile_motion_offset_3_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x19378) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Group: sinter Noise Profile LUT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Weight lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile LUT.  Calculated during calibration process.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_NOISE_PROFILE_LUT_WEIGHT_LUT_DEFAULT (0x0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_LUT_WEIGHT_LUT_DATASIZE (8)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_LUT_WEIGHT_LUT_OFFSET (0x5b0)
#define ACAMERA_ISP_SINTER_NOISE_PROFILE_LUT_WEIGHT_LUT_MASK (0xff)

// index (0-127), args: data (8-bit)
static __inline void acamera_isp_sinter_noise_profile_lut_weight_lut_write( uintptr_t base, uint32_t index,uint8_t data ) {
    uintptr_t addr = base + 0x19438 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    uint32_t curr = system_sw_read_32( addr );
    system_sw_write_32( addr, ( (uint32_t)data << offset ) | ( curr & ~( 0xFF << offset ) ) );
}
static __inline uint8_t acamera_isp_sinter_noise_profile_lut_weight_lut_read( uintptr_t base, uint32_t index ) {
    uintptr_t addr = base + 0x19438 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    return (uint8_t)( system_sw_read_32( addr ) >> offset );
}
// ------------------------------------------------------------------------------ //
// Group: sinter shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// LUT: rm_shading_lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Radial Sinter LUT.  See Arm ISP Technical Reference Manual for more details
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SINTER_SHADING_RM_SHADING_LUT_NODES (33)
#define ACAMERA_ISP_SINTER_SHADING_RM_SHADING_LUT_ADDRBITS (6)
#define ACAMERA_ISP_SINTER_SHADING_RM_SHADING_LUT_DATASIZE (8)
#define ACAMERA_ISP_SINTER_SHADING_RM_SHADING_LUT_OFFSET (0x1a9f8)

// args: index (0-32), data (8-bit)
static __inline void acamera_isp_sinter_shading_rm_shading_lut_write( uintptr_t base, uint8_t index,uint8_t data) {
    uintptr_t addr = base + 0x1a9f8 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    uint32_t curr = system_sw_read_32(addr);
    system_sw_write_32(addr, ((uint32_t)data << offset) | (curr & ~(0xFF << offset)));
}
static __inline uint8_t acamera_isp_sinter_shading_rm_shading_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1a9f8 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    return (uint8_t)(system_sw_read_32(addr) >> offset);
}
// ------------------------------------------------------------------------------ //
// Group: temper
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//				Temporal noise reduction
//			
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//					Temper enable: 0=off 1=on
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_ENABLE_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_temper_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_temper_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Show alpha
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//				         0 = Normal operation
//                                         1 = Output alpha channel for debug
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_SHOW_ALPHA_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_SHOW_ALPHA_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_SHOW_ALPHA_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_SHOW_ALPHA_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_temper_show_alpha_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_temper_show_alpha_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Mixer select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                                   Debug mixer select(Only active when Temper disabled): 0=Input video stream, 1=Frame buffer video stream		         
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_MIXER_SELECT_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_MIXER_SELECT_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_MIXER_SELECT_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_MIXER_SELECT_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_temper_mixer_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_temper_mixer_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Compress pixel data
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                                   0=No compression on pixel data , 1=Compression on pixel data		         
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_COMPRESS_PIXEL_DATA_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_COMPRESS_PIXEL_DATA_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_COMPRESS_PIXEL_DATA_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_COMPRESS_PIXEL_DATA_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_temper_compress_pixel_data_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_temper_compress_pixel_data_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Compress meta data
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                                   If temper_mode is configured to 0 or 1:
//                                     0=No compression on meta data , 1=Compression on meta data
//                                   If temper_mode is configured to 2 or 3 (finite-mode), the value of this register is ignored		         
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_COMPRESS_META_DATA_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_COMPRESS_META_DATA_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_COMPRESS_META_DATA_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_COMPRESS_META_DATA_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_temper_compress_meta_data_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_temper_compress_meta_data_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Show motion
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                                    0 = Normal operation
//                                    1 = Output motion mask for debug
//                                
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_SHOW_MOTION_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_SHOW_MOTION_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_SHOW_MOTION_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_SHOW_MOTION_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_temper_show_motion_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_temper_show_motion_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: Mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                                   0= Normal processing mode for Temper
//                                   1= Low-Latency-Mode: Low latency temporal noise reduction, accumulates many (infinite) frames.
//                                   2= Finite-Mode: Low latency temporal noise reduction mode, minimum level of accumulated frames
//                                   3= Reserved (behaves same as mode = 2)         
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_MODE_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_MODE_DATASIZE (2)
#define ACAMERA_ISP_TEMPER_MODE_OFFSET (0x1b94)
#define ACAMERA_ISP_TEMPER_MODE_MASK (0x300)

// args: data (2-bit)
static __inline void acamera_isp_temper_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa1c);
    system_sw_write_32(base + 0x1aa1c, (((uint32_t) (data & 0x3)) << 8) | (curr & 0xfffffcff));
}
static __inline uint8_t acamera_isp_temper_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa1c) & 0x300) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Recursion Limit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//					 Controls length of filter history. Low values result in longer history and stronger temporal filtering.
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_RECURSION_LIMIT_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_RECURSION_LIMIT_DATASIZE (6)
#define ACAMERA_ISP_TEMPER_RECURSION_LIMIT_OFFSET (0x1b98)
#define ACAMERA_ISP_TEMPER_RECURSION_LIMIT_MASK (0x3f)

// args: data (6-bit)
static __inline void acamera_isp_temper_recursion_limit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa20);
    system_sw_write_32(base + 0x1aa20, (((uint32_t) (data & 0x3f)) << 0) | (curr & 0xffffffc0));
}
static __inline uint8_t acamera_isp_temper_recursion_limit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa20) & 0x3f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mot thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//					 U10.0 format. Controls how much difference between current frame(Fc) and Previous frame(Fp) is tolerated before being considered motion.
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_MOT_THRESH_DEFAULT (0x12C)
#define ACAMERA_ISP_TEMPER_MOT_THRESH_DATASIZE (10)
#define ACAMERA_ISP_TEMPER_MOT_THRESH_OFFSET (0x1b9c)
#define ACAMERA_ISP_TEMPER_MOT_THRESH_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_temper_mot_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa24);
    system_sw_write_32(base + 0x1aa24, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_temper_mot_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa24) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mot slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//					 U8.4 format. Controls how strongly to respond to motion once the difference between Fc and Fp is above mot_thresh
//				
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_MOT_SLOPE_DEFAULT (0X3C)
#define ACAMERA_ISP_TEMPER_MOT_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_TEMPER_MOT_SLOPE_OFFSET (0x1b9c)
#define ACAMERA_ISP_TEMPER_MOT_SLOPE_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_temper_mot_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa24);
    system_sw_write_32(base + 0x1aa24, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_temper_mot_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa24) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: temper Noise Profile
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile controls for Temper
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: use LUT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            1 = use LUT data
//	    0 = use exposure mask provided by Frame stitching or threshold
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_LUT_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_LUT_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_LUT_OFFSET (0x1ba0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_LUT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_temper_noise_profile_use_lut_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa28);
    system_sw_write_32(base + 0x1aa28, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_temper_noise_profile_use_lut_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa28) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: use_exp_mask
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Determines whether to use external exp_mask_in input (Exposure mask mode) or create one internally (threshold mode) 
//            0=Use threshold mode 
//            1=Use Exposure mask 
//            Ignored if use_lut=1	
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_EXP_MASK_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_EXP_MASK_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_EXP_MASK_OFFSET (0x1ba0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_USE_EXP_MASK_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_temper_noise_profile_use_exp_mask_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa28);
    system_sw_write_32(base + 0x1aa28, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_temper_noise_profile_use_exp_mask_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa28) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Black Reflect
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Determines how negative values are treated after black level subtraction. 
//            0: Negative values are treated as zero 
//            1: Negative values are multiplied by -1
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_REFLECT_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_REFLECT_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_REFLECT_OFFSET (0x1ba0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_REFLECT_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_temper_noise_profile_black_reflect_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa28);
    system_sw_write_32(base + 0x1aa28, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_temper_noise_profile_black_reflect_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa28) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: global offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// A global offset that will be added to each of the hlog... values above..
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_GLOBAL_OFFSET_DEFAULT (0x08)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_GLOBAL_OFFSET_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_GLOBAL_OFFSET_OFFSET (0x1ba0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_GLOBAL_OFFSET_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_temper_noise_profile_global_offset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa28);
    system_sw_write_32(base + 0x1aa28, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_global_offset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa28) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Black Level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Value to subtract from pixels before lookup in LUT mode
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_LEVEL_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_LEVEL_DATASIZE (12)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_LEVEL_OFFSET (0x1ba0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_BLACK_LEVEL_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_temper_noise_profile_black_level_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa28);
    system_sw_write_32(base + 0x1aa28, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_temper_noise_profile_black_level_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa28) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//		 The threshold that determines the lower bound of the pixel value range considered to be exposure 2(3rd shortest), when in Thresholds Mode. Only used for 4 exposures. 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH1_DEFAULT (1024)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH1_DATASIZE (12)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH1_OFFSET (0x1ba4)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH1_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_temper_noise_profile_thresh1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa2c);
    system_sw_write_32(base + 0x1aa2c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_temper_noise_profile_thresh1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa2c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The threshold that determines the lower bound of the pixel value range considered to be exposure 1(2nd shortest), when in Thresholds Mode. Only used for 3 or more exposures.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH2_DEFAULT (2048)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH2_DATASIZE (12)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH2_OFFSET (0x1ba4)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH2_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_temper_noise_profile_thresh2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa2c);
    system_sw_write_32(base + 0x1aa2c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_temper_noise_profile_thresh2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa2c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Thresh3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The threshold that determines the lower bound of the pixel value range considered to be exposure 0(shortest), when in Thresholds Mode. Only used for 2 or more exposures.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH3_DEFAULT (3072)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH3_DATASIZE (12)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH3_OFFSET (0x1ba8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_THRESH3_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_temper_noise_profile_thresh3_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa30);
    system_sw_write_32(base + 0x1aa30, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_temper_noise_profile_thresh3_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aa30) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            The noise level value to use when the exposure mask has value 0 (in Exposure Mask Mode), or when the pixel value is greater than thresh3 (in Thresholds Mode).
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_0_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_0_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_0_OFFSET (0x1bac)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_0_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_temper_noise_profile_noise_level_0_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa34);
    system_sw_write_32(base + 0x1aa34, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_temper_noise_profile_noise_level_0_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa34) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The noise level value to use when the exposure mask has value 1 (in Exposure Mask Mode), or when the pixel value is greater than thresh2, but less than thresh3 (in Thresholds Mode).
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_1_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_1_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_1_OFFSET (0x1bac)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_1_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_temper_noise_profile_noise_level_1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa34);
    system_sw_write_32(base + 0x1aa34, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_noise_level_1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa34) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The noise level value to use when the exposure mask has value 2 (in Exposure Mask Mode), or when the pixel value is greater than thresh1, but less than thresh2 (in Thresholds Mode).
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_2_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_2_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_2_OFFSET (0x1bac)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_2_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_temper_noise_profile_noise_level_2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa34);
    system_sw_write_32(base + 0x1aa34, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_noise_level_2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa34) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: noise_level_3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// The noise level value to use when the exposure mask has value 3 (in Exposure Mask Mode), or when the pixel value is less than thresh1 (in Thresholds Mode).
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_3_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_3_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_3_OFFSET (0x1bac)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_NOISE_LEVEL_3_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_temper_noise_profile_noise_level_3_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa34);
    system_sw_write_32(base + 0x1aa34, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_noise_level_3_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa34) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: Rggb mode enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0= Reserved 
//             1= 3 channel CFA with 2 values channels (eg RGGB)		         
//	
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RGGB_MODE_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RGGB_MODE_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RGGB_MODE_ENABLE_OFFSET (0x1bb0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RGGB_MODE_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_temper_noise_profile_rggb_mode_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa38);
    system_sw_write_32(base + 0x1aa38, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_temper_noise_profile_rggb_mode_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa38) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Sqrt mode enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0= input data is in linear domain 
//             1= input data is in square-root domain		         
//	
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SQRT_MODE_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SQRT_MODE_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SQRT_MODE_ENABLE_OFFSET (0x1bb0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SQRT_MODE_ENABLE_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_temper_noise_profile_sqrt_mode_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa38);
    system_sw_write_32(base + 0x1aa38, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_temper_noise_profile_sqrt_mode_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa38) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Recursion strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sets the strength of the IIR part of the motion detection algorithm. Higher values will enforce more contiguous motion detection regions, but will be more likely to leave the top row or two of pixels of a motion region uncorrected.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RECURSION_STRENGTH_DEFAULT (6)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RECURSION_STRENGTH_DATASIZE (3)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RECURSION_STRENGTH_OFFSET (0x1bb0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_RECURSION_STRENGTH_MASK (0x700)

// args: data (3-bit)
static __inline void acamera_isp_temper_noise_profile_recursion_strength_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa38);
    system_sw_write_32(base + 0x1aa38, (((uint32_t) (data & 0x7)) << 8) | (curr & 0xfffff8ff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_recursion_strength_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa38) & 0x700) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Smoothness
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Artificially limits motion detection to introduce unnecessary ghosting. This may be preferred in some cases as it blurs the transition from motion-correction region to non-motion-correction region. 0 means no effect
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SMOOTHNESS_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SMOOTHNESS_DATASIZE (6)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SMOOTHNESS_OFFSET (0x1bb0)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_SMOOTHNESS_MASK (0x3f0000)

// args: data (6-bit)
static __inline void acamera_isp_temper_noise_profile_smoothness_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa38);
    system_sw_write_32(base + 0x1aa38, (((uint32_t) (data & 0x3f)) << 16) | (curr & 0xffc0ffff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_smoothness_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa38) & 0x3f0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Motion thresh 0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// These three thresholds divide the range of the 6-bit number of accumulated frames counter into 4 sections. Requires that: motion_thresh_2 < motion_thresh_1 < motion_thresh_0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_0_DEFAULT (61)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_0_DATASIZE (6)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_0_OFFSET (0x1bb4)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_0_MASK (0x3f)

// args: data (6-bit)
static __inline void acamera_isp_temper_noise_profile_motion_thresh_0_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa3c);
    system_sw_write_32(base + 0x1aa3c, (((uint32_t) (data & 0x3f)) << 0) | (curr & 0xffffffc0));
}
static __inline uint8_t acamera_isp_temper_noise_profile_motion_thresh_0_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa3c) & 0x3f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Motion thresh 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// See above (motion thresh 0 description)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_1_DEFAULT (58)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_1_DATASIZE (6)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_1_OFFSET (0x1bb4)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_1_MASK (0x3f00)

// args: data (6-bit)
static __inline void acamera_isp_temper_noise_profile_motion_thresh_1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa3c);
    system_sw_write_32(base + 0x1aa3c, (((uint32_t) (data & 0x3f)) << 8) | (curr & 0xffffc0ff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_motion_thresh_1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa3c) & 0x3f00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Motion thresh 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// See above (motion thresh 0 description)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_2_DEFAULT (53)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_2_DATASIZE (6)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_2_OFFSET (0x1bb4)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_MOTION_THRESH_2_MASK (0x3f0000)

// args: data (6-bit)
static __inline void acamera_isp_temper_noise_profile_motion_thresh_2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aa3c);
    system_sw_write_32(base + 0x1aa3c, (((uint32_t) (data & 0x3f)) << 16) | (curr & 0xffc0ffff));
}
static __inline uint8_t acamera_isp_temper_noise_profile_motion_thresh_2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aa3c) & 0x3f0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: temper Noise Profile LUT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// LUT: Weight lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Noise profile LUT.  Calculated during calibration process.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_LUT_WEIGHT_LUT_NODES (128)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_LUT_WEIGHT_LUT_ADDRBITS (7)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_LUT_WEIGHT_LUT_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_NOISE_PROFILE_LUT_WEIGHT_LUT_OFFSET (0x1aaf8)

// args: index (0-127), data (8-bit)
static __inline void acamera_isp_temper_noise_profile_lut_weight_lut_write( uintptr_t base, uint8_t index,uint8_t data) {
    uintptr_t addr = base + 0x1aaf8 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    uint32_t curr = system_sw_read_32(addr);
    system_sw_write_32(addr, ((uint32_t)data << offset) | (curr & ~(0xFF << offset)));
}
static __inline uint8_t acamera_isp_temper_noise_profile_lut_weight_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1aaf8 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    return (uint8_t)(system_sw_read_32(addr) >> offset);
}
// ------------------------------------------------------------------------------ //
// Group: temper dma
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Frame write on dma
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Temper 4 dma writes on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_FRAME_WRITE_ON_DMA_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_WRITE_ON_DMA_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_WRITE_ON_DMA_OFFSET (0x1cf0)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_WRITE_ON_DMA_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_frame_write_on_dma_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab78);
    system_sw_write_32(base + 0x1ab78, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_temper_dma_frame_write_on_dma_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ab78) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Frame read on dma
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Temper 4 dma reads on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_FRAME_READ_ON_DMA_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_READ_ON_DMA_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_READ_ON_DMA_OFFSET (0x1cf0)
#define ACAMERA_ISP_TEMPER_DMA_FRAME_READ_ON_DMA_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_frame_read_on_dma_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab78);
    system_sw_write_32(base + 0x1ab78, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_temper_dma_frame_read_on_dma_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ab78) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: format
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Compressions format can only be configured when compression has been fitted.
//        case {temper_mode, temper_compress_pixel_data, temper_compress_meta_data}
//        begin
//            0000: configure to 0x14 (hex)
//            0001: configure to 0x06 (hex)
//            0010: configure to 0x06 (hex)
//            0011: configure to 0x11 (hex)
//            0100: configure to 0x14 (hex)
//            0101: configure to 0x06 (hex)
//            0110: configure to 0x06 (hex)
//            0111: configure to 0x11 (hex)
//            1000: configure to 0x07 (hex)
//            1001: configure to 0x07 (hex)
//            1010: configure to 0x0D (hex)
//            1011: configure to 0x0D (hex)
//            1100: configure to 0x07 (hex)
//            1101: configure to 0x07 (hex)
//            1110: configure to 0x0D (hex)
//            1111: configure to 0x0D (hex)
//        end
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_FORMAT_DEFAULT (20)
#define ACAMERA_ISP_TEMPER_DMA_FORMAT_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_DMA_FORMAT_OFFSET (0x1cf4)
#define ACAMERA_ISP_TEMPER_DMA_FORMAT_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_temper_dma_format_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab7c);
    system_sw_write_32(base + 0x1ab7c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_temper_dma_format_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ab7c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: blk_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          The bits are defined as follows:
//          0     Write FIFO Fail (Full)
//          1     Write FIFO Fail (Empty)
//          2     Read FIFO Fail (Full)
//          3     Read FIFO Fail (Empty)
//          4     Pack Fail (Overflow)
//          5     Unpack Fail (Overflow)
//          6     Writer fail (Active Width)
//          7     Writer fail (Active Height)
//          8     Writer fail (Interline blanking)
//          9     Writer fail (Interframe blanking)
//          10    Reader fail (Active Width)
//          11    Reader fail (Active Height)
//          12    Reader fail (Interline blanking)
//          13    Reader fail (Interframe blanking)
//          14    0
//          15    0
//          16    Writer fail (A resp)
//          17    Writer fail (AW wait)
//          18    Writer fail (W wait)
//          19    Writer fail (Outstanding Transactions)
//          20    Reader fail (AR wait)
//          21    Reader fail (R resp)
//          22    Reader fail (Outstanding Transfers)
//          23    0
//          24    intw_fail_user_intfc_sig
//          25    intr_fail_user_intfc_sig
//          26    0
//          27    0
//          28    0
//          29    0
//          30    0
//          31    0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_BLK_STATUS_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_BLK_STATUS_DATASIZE (32)
#define ACAMERA_ISP_TEMPER_DMA_BLK_STATUS_OFFSET (0x1cf8)
#define ACAMERA_ISP_TEMPER_DMA_BLK_STATUS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_temper_dma_blk_status_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1ab80);
}
// ------------------------------------------------------------------------------ //
// Register: bank_base_writer
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            base address for frame buffer, should be word-aligned. 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_WRITER_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_WRITER_DATASIZE (32)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_WRITER_OFFSET (0x1cfc)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_WRITER_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_temper_dma_bank_base_writer_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1ab84, data);
}
static __inline uint32_t acamera_isp_temper_dma_bank_base_writer_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1ab84);
}
// ------------------------------------------------------------------------------ //
// Register: bank_base_reader
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            base address for frame buffer, should be word-aligned.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_READER_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_READER_DATASIZE (32)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_READER_OFFSET (0x1d04)
#define ACAMERA_ISP_TEMPER_DMA_BANK_BASE_READER_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_temper_dma_bank_base_reader_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1ab8c, data);
}
static __inline uint32_t acamera_isp_temper_dma_bank_base_reader_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1ab8c);
}
// ------------------------------------------------------------------------------ //
// Register: Line_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          Indicates the offset in bytes from the start of one line to the next line.  
//          This value should be equal to or larger than one line of image data and should be word-aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_LINE_OFFSET_DEFAULT (0x1000)
#define ACAMERA_ISP_TEMPER_DMA_LINE_OFFSET_DATASIZE (32)
#define ACAMERA_ISP_TEMPER_DMA_LINE_OFFSET_OFFSET (0x1d0c)
#define ACAMERA_ISP_TEMPER_DMA_LINE_OFFSET_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_temper_dma_line_offset_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1ab94, data);
}
static __inline uint32_t acamera_isp_temper_dma_line_offset_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1ab94);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_eol
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// linetick start/end of line control. 0 = use start of line, 1 = use end of line
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_LINETICK_EOL_DEFAULT (1)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_EOL_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_EOL_OFFSET (0x1d10)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_EOL_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_linetick_eol_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab98);
    system_sw_write_32(base + 0x1ab98, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_temper_dma_linetick_eol_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ab98) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Writer lines_wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// number of lines to write from base address before wrapping back to base address. Debug only 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_LINES_WRAPPED_OFFSET (0x1d14)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_LINES_WRAPPED_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_writer_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab9c);
    system_sw_write_32(base + 0x1ab9c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_temper_dma_writer_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ab9c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Reader lines wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// number of lines to read from base address before wrapping back to base address. Debug only 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_READER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_READER_LINES_WRAPPED_OFFSET (0x1d14)
#define ACAMERA_ISP_TEMPER_DMA_READER_LINES_WRAPPED_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_reader_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ab9c);
    system_sw_write_32(base + 0x1ab9c, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_temper_dma_reader_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ab9c) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_first
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// line number of first linetick. 0  = no linetick 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_LINETICK_FIRST_DEFAULT (0x0040)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_FIRST_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_FIRST_OFFSET (0x1d18)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_FIRST_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_linetick_first_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba0);
    system_sw_write_32(base + 0x1aba0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_temper_dma_linetick_first_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aba0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_repeat
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// line number of first linetick. 0 = no repeat
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_LINETICK_REPEAT_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_REPEAT_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_REPEAT_OFFSET (0x1d18)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_REPEAT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_linetick_repeat_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba0);
    system_sw_write_32(base + 0x1aba0, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_temper_dma_linetick_repeat_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aba0) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_delay
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// linetick delay in vcke cycles to add
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_LINETICK_DELAY_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_DELAY_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_DELAY_OFFSET (0x1d1c)
#define ACAMERA_ISP_TEMPER_DMA_LINETICK_DELAY_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_linetick_delay_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba4);
    system_sw_write_32(base + 0x1aba4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_temper_dma_linetick_delay_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aba4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: fifo_maxfill
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// max fill level of fifo to allow (if set less than 16, internally it uses 2**fifo_aw to have a sensible minimum value)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_FIFO_MAXFILL_DEFAULT (0x0000)
#define ACAMERA_ISP_TEMPER_DMA_FIFO_MAXFILL_DATASIZE (16)
#define ACAMERA_ISP_TEMPER_DMA_FIFO_MAXFILL_OFFSET (0x1d1c)
#define ACAMERA_ISP_TEMPER_DMA_FIFO_MAXFILL_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_temper_dma_fifo_maxfill_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba4);
    system_sw_write_32(base + 0x1aba4, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_temper_dma_fifo_maxfill_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aba4) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_VALUE_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_writer_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_id_multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0= static value (axi_id_value) for awid/wid, 1 = incrementing value per transaction for awid/wid wrapping to 0 after axi_id_value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_MULTI_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_MULTI_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_MULTI_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_ID_MULTI_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_writer_axi_id_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_id_multi_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 11
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_BURSTSPLIT_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_BURSTSPLIT_MASK (0x600)

// args: data (2-bit)
static __inline void acamera_isp_temper_dma_writer_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0x3)) << 9) | (curr & 0xfffff9ff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0x600) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 1111
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_CACHE_VALUE_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_CACHE_VALUE_MASK (0x7800)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_writer_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0xf)) << 11) | (curr & 0xffff87ff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0x7800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding write transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAXOSTAND_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_temper_dma_writer_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: writer_axi_max_awlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for awlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAX_AWLEN_DEFAULT (0xf)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAX_AWLEN_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAX_AWLEN_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_AXI_MAX_AWLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_writer_axi_max_awlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_axi_max_awlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: writer_pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//           Reserved
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_WRITER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_PAGEWARM_ON_OFFSET (0x1d20)
#define ACAMERA_ISP_TEMPER_DMA_WRITER_PAGEWARM_ON_MASK (0x10000000)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_writer_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aba8);
    system_sw_write_32(base + 0x1aba8, (((uint32_t) (data & 0x1)) << 28) | (curr & 0xefffffff));
}
static __inline uint8_t acamera_isp_temper_dma_writer_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aba8) & 0x10000000) >> 28);
}
// ------------------------------------------------------------------------------ //
// Register: reader_axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid. Good default = "0000" 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_ID_VALUE_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_reader_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_temper_dma_reader_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: reader_axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 11
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_BURSTSPLIT_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_BURSTSPLIT_MASK (0x600)

// args: data (2-bit)
static __inline void acamera_isp_temper_dma_reader_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0x3)) << 9) | (curr & 0xfffff9ff));
}
static __inline uint8_t acamera_isp_temper_dma_reader_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0x600) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: reader_axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 1111
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_CACHE_VALUE_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_CACHE_VALUE_MASK (0x7800)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_reader_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0xf)) << 11) | (curr & 0xffff87ff));
}
static __inline uint8_t acamera_isp_temper_dma_reader_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0x7800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: reader_axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding read transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAXOSTAND_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_temper_dma_reader_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_temper_dma_reader_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: reader_axi_max_arlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for arlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAX_ARLEN_DEFAULT (0xf)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAX_ARLEN_DATASIZE (4)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAX_ARLEN_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_AXI_MAX_ARLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_temper_dma_reader_axi_max_arlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_temper_dma_reader_axi_max_arlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: reader_pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//           Reserved
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TEMPER_DMA_READER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_TEMPER_DMA_READER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_TEMPER_DMA_READER_PAGEWARM_ON_OFFSET (0x1d24)
#define ACAMERA_ISP_TEMPER_DMA_READER_PAGEWARM_ON_MASK (0x10000000)

// args: data (1-bit)
static __inline void acamera_isp_temper_dma_reader_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abac);
    system_sw_write_32(base + 0x1abac, (((uint32_t) (data & 0x1)) << 28) | (curr & 0xefffffff));
}
static __inline uint8_t acamera_isp_temper_dma_reader_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abac) & 0x10000000) >> 28);
}
// ------------------------------------------------------------------------------ //
// Group: square be
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// sensor offset for the square module
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: black_level_in
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// input Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_IN_DEFAULT (0x000)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_IN_DATASIZE (12)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_IN_OFFSET (0x1d38)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_IN_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_square_be_black_level_in_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abc0);
    system_sw_write_32(base + 0x1abc0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_square_be_black_level_in_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1abc0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: black_level_out
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// output Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_OUT_DEFAULT (0x000)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_OUT_DATASIZE (20)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_OUT_OFFSET (0x1d3c)
#define ACAMERA_ISP_SQUARE_BE_BLACK_LEVEL_OUT_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_square_be_black_level_out_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abc4);
    system_sw_write_32(base + 0x1abc4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_square_be_black_level_out_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abc4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: normalization
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Normalization
//        The normalization coefficient input to be multiplied on the linear data. The format is u1.16.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SQUARE_BE_NORMALIZATION_DEFAULT (0x10000)
#define ACAMERA_ISP_SQUARE_BE_NORMALIZATION_DATASIZE (17)
#define ACAMERA_ISP_SQUARE_BE_NORMALIZATION_OFFSET (0x1d40)
#define ACAMERA_ISP_SQUARE_BE_NORMALIZATION_MASK (0x1ffff)

// args: data (17-bit)
static __inline void acamera_isp_square_be_normalization_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abc8);
    system_sw_write_32(base + 0x1abc8, (((uint32_t) (data & 0x1ffff)) << 0) | (curr & 0xfffe0000));
}
static __inline uint32_t acamera_isp_square_be_normalization_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abc8) & 0x1ffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: sensor offset pre shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset subtraction for each color channel and exposure
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: offset 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_00_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_00_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_00_OFFSET (0x1d44)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_00_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_pre_shading_offset_00_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abcc);
    system_sw_write_32(base + 0x1abcc, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_pre_shading_offset_00_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abcc) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_01_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_01_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_01_OFFSET (0x1d48)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_01_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_pre_shading_offset_01_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abd0);
    system_sw_write_32(base + 0x1abd0, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_pre_shading_offset_01_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abd0) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_10_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_10_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_10_OFFSET (0x1d4c)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_10_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_pre_shading_offset_10_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abd4);
    system_sw_write_32(base + 0x1abd4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_pre_shading_offset_10_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abd4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// offset for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_11_DEFAULT (0x00)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_11_DATASIZE (20)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_11_OFFSET (0x1d50)
#define ACAMERA_ISP_SENSOR_OFFSET_PRE_SHADING_OFFSET_11_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_sensor_offset_pre_shading_offset_11_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abd8);
    system_sw_write_32(base + 0x1abd8, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_sensor_offset_pre_shading_offset_11_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1abd8) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: mesh shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Mesh Lens shading correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Lens shading correction enable: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_MESH_SHADING_ENABLE_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_mesh_shading_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_mesh_shading_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh show
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Lens shading correction debug: 0=off, 1=on (show mesh data)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_SHOW_DEFAULT (1)
#define ACAMERA_ISP_MESH_SHADING_MESH_SHOW_DATASIZE (1)
#define ACAMERA_ISP_MESH_SHADING_MESH_SHOW_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_SHOW_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_mesh_shading_mesh_show_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_show_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh scale
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Selects the precision and maximal gain range of mesh shading correction
//        Gain range:    00- 0..2; 01- 0..4; 02- 0..8; 03- 0..16; 04- 1..2; 05- 1..3; 06- 1..5; 07- 1..9(float)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_SCALE_DEFAULT (1)
#define ACAMERA_ISP_MESH_SHADING_MESH_SCALE_DATASIZE (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_SCALE_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_SCALE_MASK (0x1c)

// args: data (3-bit)
static __inline void acamera_isp_mesh_shading_mesh_scale_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x7)) << 2) | (curr & 0xffffffe3));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_scale_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x1c) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh page R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Selects memory page for red pixels correction. Only 0, 1, 2 supported (3 is reserved). See ISP guide for further details
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_R_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_R_DATASIZE (2)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_R_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_R_MASK (0x300)

// args: data (2-bit)
static __inline void acamera_isp_mesh_shading_mesh_page_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3)) << 8) | (curr & 0xfffffcff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_page_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x300) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh page G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Selects memory page for green pixels correction. Only 0, 1, 2 supported (3 is reserved). See ISP guide for further details
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_G_DEFAULT (1)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_G_DATASIZE (2)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_G_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_G_MASK (0xc00)

// args: data (2-bit)
static __inline void acamera_isp_mesh_shading_mesh_page_g_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3)) << 10) | (curr & 0xfffff3ff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_page_g_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0xc00) >> 10);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh page B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Selects memory page for blue pixels correction. Only 0, 1, 2 supported (3 is reserved). See ISP guide for further details
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_B_DEFAULT (2)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_B_DATASIZE (2)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_B_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_B_MASK (0x3000)

// args: data (2-bit)
static __inline void acamera_isp_mesh_shading_mesh_page_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3)) << 12) | (curr & 0xffffcfff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_page_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x3000) >> 12);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh page Ir
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Reserved
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_IR_DEFAULT (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_IR_DATASIZE (2)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_IR_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_PAGE_IR_MASK (0xc000)

// args: data (2-bit)
static __inline void acamera_isp_mesh_shading_mesh_page_ir_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3)) << 14) | (curr & 0xffff3fff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_page_ir_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0xc000) >> 14);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of horizontal nodes minus 1. Only 31 and 15 supported. Others debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_WIDTH_DEFAULT (31)
#define ACAMERA_ISP_MESH_SHADING_MESH_WIDTH_DATASIZE (6)
#define ACAMERA_ISP_MESH_SHADING_MESH_WIDTH_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_WIDTH_MASK (0x3f0000)

// args: data (6-bit)
static __inline void acamera_isp_mesh_shading_mesh_width_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3f)) << 16) | (curr & 0xffc0ffff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_width_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x3f0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of vertical nodes minus 1. Only 31 and 15 supported. Others debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_HEIGHT_DEFAULT (31)
#define ACAMERA_ISP_MESH_SHADING_MESH_HEIGHT_DATASIZE (6)
#define ACAMERA_ISP_MESH_SHADING_MESH_HEIGHT_OFFSET (0x1d74)
#define ACAMERA_ISP_MESH_SHADING_MESH_HEIGHT_MASK (0x3f000000)

// args: data (6-bit)
static __inline void acamera_isp_mesh_shading_mesh_height_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1abfc);
    system_sw_write_32(base + 0x1abfc, (((uint32_t) (data & 0x3f)) << 24) | (curr & 0xc0ffffff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_height_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1abfc) & 0x3f000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh reload
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0-1 triggers cache reload. Debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_RELOAD_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_RELOAD_DATASIZE (1)
#define ACAMERA_ISP_MESH_SHADING_MESH_RELOAD_OFFSET (0x1d78)
#define ACAMERA_ISP_MESH_SHADING_MESH_RELOAD_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_mesh_shading_mesh_reload_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac00);
    system_sw_write_32(base + 0x1ac00, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_reload_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac00) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha bank R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bank selection for R blend: 0: 0+1; 1: 1+2; 2: reserved; 3: reserved; 4:0+2; 5: reserved; 6,7: reserved
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_R_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_R_DATASIZE (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_R_OFFSET (0x1d7c)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_R_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_bank_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac04);
    system_sw_write_32(base + 0x1ac04, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_bank_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac04) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha bank G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bank selection for G blend: 0: 0+1; 1: 1+2; 2: reserved; 3: reserved; 4:0+2; 5: reserved; 6,7: reserved: 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_G_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_G_DATASIZE (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_G_OFFSET (0x1d7c)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_G_MASK (0x38)

// args: data (3-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_bank_g_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac04);
    system_sw_write_32(base + 0x1ac04, (((uint32_t) (data & 0x7)) << 3) | (curr & 0xffffffc7));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_bank_g_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac04) & 0x38) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha bank B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bank selection for B blend: 0: 0+1; 1: 1+2; 2: reserved; 3: reserved; 4:0+2; 5: reserved; 6,7: reserved
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_B_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_B_DATASIZE (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_B_OFFSET (0x1d7c)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_B_MASK (0x1c0)

// args: data (3-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_bank_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac04);
    system_sw_write_32(base + 0x1ac04, (((uint32_t) (data & 0x7)) << 6) | (curr & 0xfffffe3f));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_bank_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac04) & 0x1c0) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha bank Ir
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Reserved
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_IR_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_IR_DATASIZE (3)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_IR_OFFSET (0x1d7c)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_BANK_IR_MASK (0xe00)

// args: data (3-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_bank_ir_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac04);
    system_sw_write_32(base + 0x1ac04, (((uint32_t) (data & 0x7)) << 9) | (curr & 0xfffff1ff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_bank_ir_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac04) & 0xe00) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Alpha blend coeff for R
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_R_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_R_DATASIZE (8)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_R_OFFSET (0x1d80)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_R_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac08);
    system_sw_write_32(base + 0x1ac08, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac08) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Alpha blend coeff for G
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_G_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_G_DATASIZE (8)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_G_OFFSET (0x1d80)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_G_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_g_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac08);
    system_sw_write_32(base + 0x1ac08, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_g_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac08) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Alpha blend coeff for B
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_B_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_B_DATASIZE (8)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_B_OFFSET (0x1d80)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_B_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac08);
    system_sw_write_32(base + 0x1ac08, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac08) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh alpha Ir
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Reserved
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_IR_DEFAULT (0)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_IR_DATASIZE (8)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_IR_OFFSET (0x1d80)
#define ACAMERA_ISP_MESH_SHADING_MESH_ALPHA_IR_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_mesh_shading_mesh_alpha_ir_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac08);
    system_sw_write_32(base + 0x1ac08, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_mesh_shading_mesh_alpha_ir_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac08) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: Mesh strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Mesh strength in 4.12 format, e.g. 0 - no correction, 4096 - correction to match mesh data. Can be used to reduce shading correction based on AE.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MESH_SHADING_MESH_STRENGTH_DEFAULT (0x1000)
#define ACAMERA_ISP_MESH_SHADING_MESH_STRENGTH_DATASIZE (16)
#define ACAMERA_ISP_MESH_SHADING_MESH_STRENGTH_OFFSET (0x1d84)
#define ACAMERA_ISP_MESH_SHADING_MESH_STRENGTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_mesh_shading_mesh_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac0c);
    system_sw_write_32(base + 0x1ac0c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_mesh_shading_mesh_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac0c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: white balance
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Static white balance - independent gain for each color channel
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Gain 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_GAIN_00_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_00_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_00_OFFSET (0x1d88)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_00_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_gain_00_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac10);
    system_sw_write_32(base + 0x1ac10, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_white_balance_gain_00_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac10) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_GAIN_01_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_01_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_01_OFFSET (0x1d88)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_01_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_gain_01_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac10);
    system_sw_write_32(base + 0x1ac10, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_white_balance_gain_01_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac10) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_GAIN_10_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_10_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_10_OFFSET (0x1d8c)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_10_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_gain_10_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac14);
    system_sw_write_32(base + 0x1ac14, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_white_balance_gain_10_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac14) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_GAIN_11_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_11_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_11_OFFSET (0x1d8c)
#define ACAMERA_ISP_WHITE_BALANCE_GAIN_11_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_gain_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac14);
    system_sw_write_32(base + 0x1ac14, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_white_balance_gain_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac14) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: white balance aexp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Static white balance - independent gain for each color channel
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Gain 00
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 00 (R)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_00_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_00_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_00_OFFSET (0x1d90)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_00_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_aexp_gain_00_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac18);
    system_sw_write_32(base + 0x1ac18, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_white_balance_aexp_gain_00_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac18) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 01
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 01 (Gr)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_01_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_01_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_01_OFFSET (0x1d90)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_01_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_aexp_gain_01_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac18);
    system_sw_write_32(base + 0x1ac18, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_white_balance_aexp_gain_01_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac18) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 10
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 10 (Gb)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_10_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_10_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_10_OFFSET (0x1d94)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_10_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_aexp_gain_10_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac1c);
    system_sw_write_32(base + 0x1ac1c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_white_balance_aexp_gain_10_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac1c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Gain 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multiplier for color channel 11 (B)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_11_DEFAULT (0x100)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_11_DATASIZE (12)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_11_OFFSET (0x1d94)
#define ACAMERA_ISP_WHITE_BALANCE_AEXP_GAIN_11_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_white_balance_aexp_gain_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac1c);
    system_sw_write_32(base + 0x1ac1c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_white_balance_aexp_gain_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac1c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: iridix gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Digital gain for RAW sensor data
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Gain
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gain applied to data in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_GAIN_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_GAIN_GAIN_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_GAIN_GAIN_OFFSET (0x1d98)
#define ACAMERA_ISP_IRIDIX_GAIN_GAIN_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_iridix_gain_gain_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac20);
    system_sw_write_32(base + 0x1ac20, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_iridix_gain_gain_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac20) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data black level
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_IRIDIX_GAIN_OFFSET_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_GAIN_OFFSET_OFFSET (0x1d9c)
#define ACAMERA_ISP_IRIDIX_GAIN_OFFSET_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_iridix_gain_offset_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac24);
    system_sw_write_32(base + 0x1ac24, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_iridix_gain_offset_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1ac24) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: iridix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                 Iridix is an adaptive, space-variant tone mapping engine.
//                 It is used to maintain or enhance shadow detail while preserving highlights.
//             
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: iridix_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_ENABLE_DEFAULT (0x1)
#define ACAMERA_ISP_IRIDIX_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_ENABLE_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_iridix_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_iridix_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: max_alg_type
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Max Bayer Algorithm Type.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_MAX_ALG_TYPE_DEFAULT (0x1)
#define ACAMERA_ISP_IRIDIX_MAX_ALG_TYPE_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_MAX_ALG_TYPE_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_MAX_ALG_TYPE_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_iridix_max_alg_type_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_iridix_max_alg_type_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: black_level_amp0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1=Ignore Black level (set to zero) in amplificator. 0=Use Black level value.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_AMP0_DEFAULT (0x1)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_AMP0_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_AMP0_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_AMP0_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_iridix_black_level_amp0_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_iridix_black_level_amp0_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: postgamma_pos
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Post Gamma application  0=gain 1=data
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_POSTGAMMA_POS_DEFAULT (0x0)
#define ACAMERA_ISP_IRIDIX_POSTGAMMA_POS_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_POSTGAMMA_POS_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_POSTGAMMA_POS_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_iridix_postgamma_pos_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_iridix_postgamma_pos_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: collect_ovl
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_COLLECT_OVL_DEFAULT (0x0)
#define ACAMERA_ISP_IRIDIX_COLLECT_OVL_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_COLLECT_OVL_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_COLLECT_OVL_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_iridix_collect_ovl_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_iridix_collect_ovl_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: collect_rnd
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_COLLECT_RND_DEFAULT (0x1)
#define ACAMERA_ISP_IRIDIX_COLLECT_RND_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_COLLECT_RND_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_COLLECT_RND_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_iridix_collect_rnd_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_iridix_collect_rnd_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: stat_mult
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  
//                     Horizontal and vertical sampling rate control
//                     0: min width 480 min height 240
//                     1: min width 960 min height 240
//                     2: min width 960 min height 480
//                     3: min width 1920 min height 480
//                 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_STAT_MULT_DEFAULT (0x1)
#define ACAMERA_ISP_IRIDIX_STAT_MULT_DATASIZE (2)
#define ACAMERA_ISP_IRIDIX_STAT_MULT_OFFSET (0x1da0)
#define ACAMERA_ISP_IRIDIX_STAT_MULT_MASK (0xc000)

// args: data (2-bit)
static __inline void acamera_isp_iridix_stat_mult_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac28);
    system_sw_write_32(base + 0x1ac28, (((uint32_t) (data & 0x3)) << 14) | (curr & 0xffff3fff));
}
static __inline uint8_t acamera_isp_iridix_stat_mult_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac28) & 0xc000) >> 14);
}
// ------------------------------------------------------------------------------ //
// Register: ivariance1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_IVARIANCE1_DEFAULT (0x0)
#define ACAMERA_ISP_IRIDIX_IVARIANCE1_DATASIZE (4)
#define ACAMERA_ISP_IRIDIX_IVARIANCE1_OFFSET (0x1da4)
#define ACAMERA_ISP_IRIDIX_IVARIANCE1_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_iridix_ivariance1_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac2c);
    system_sw_write_32(base + 0x1ac2c, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_iridix_ivariance1_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac2c) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ivariance2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// ivariance control. Usable value 0-10
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_IVARIANCE2_DEFAULT (0x5)
#define ACAMERA_ISP_IRIDIX_IVARIANCE2_DATASIZE (4)
#define ACAMERA_ISP_IRIDIX_IVARIANCE2_OFFSET (0x1da4)
#define ACAMERA_ISP_IRIDIX_IVARIANCE2_MASK (0xf0)

// args: data (4-bit)
static __inline void acamera_isp_iridix_ivariance2_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac2c);
    system_sw_write_32(base + 0x1ac2c, (((uint32_t) (data & 0xf)) << 4) | (curr & 0xffffff0f));
}
static __inline uint8_t acamera_isp_iridix_ivariance2_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac2c) & 0xf0) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: black_level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix black level. Values below this will not be affected by Iridix.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_DEFAULT (0x0000)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_OFFSET (0x1da8)
#define ACAMERA_ISP_IRIDIX_BLACK_LEVEL_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_iridix_black_level_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac30);
    system_sw_write_32(base + 0x1ac30, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_iridix_black_level_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1ac30) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: white_level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix white level. Values above this will not be affected by Iridix.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_WHITE_LEVEL_DEFAULT (0xD9999)
#define ACAMERA_ISP_IRIDIX_WHITE_LEVEL_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_WHITE_LEVEL_OFFSET (0x1dac)
#define ACAMERA_ISP_IRIDIX_WHITE_LEVEL_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_iridix_white_level_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac34);
    system_sw_write_32(base + 0x1ac34, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_iridix_white_level_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1ac34) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: collection_correction
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_OFFSET (0x1db0)
#define ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_iridix_collection_correction_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac38);
    system_sw_write_32(base + 0x1ac38, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_iridix_collection_correction_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac38) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: fwd_percept_control
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix gamma processing select: 0=pass through 1=gamma_dl 2=sqrt 3=gamma_lut.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_FWD_PERCEPT_CONTROL_DEFAULT (0x2)
#define ACAMERA_ISP_IRIDIX_FWD_PERCEPT_CONTROL_DATASIZE (2)
#define ACAMERA_ISP_IRIDIX_FWD_PERCEPT_CONTROL_OFFSET (0x1db4)
#define ACAMERA_ISP_IRIDIX_FWD_PERCEPT_CONTROL_MASK (0x3)

// args: data (2-bit)
static __inline void acamera_isp_iridix_fwd_percept_control_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac3c);
    system_sw_write_32(base + 0x1ac3c, (((uint32_t) (data & 0x3)) << 0) | (curr & 0xfffffffc));
}
static __inline uint8_t acamera_isp_iridix_fwd_percept_control_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac3c) & 0x3) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rev_percept_control
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix gamma processing select: 0=pass through 1=gamma_dl 2=sqrt 3=gamma_lut.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_REV_PERCEPT_CONTROL_DEFAULT (0x2)
#define ACAMERA_ISP_IRIDIX_REV_PERCEPT_CONTROL_DATASIZE (2)
#define ACAMERA_ISP_IRIDIX_REV_PERCEPT_CONTROL_OFFSET (0x1db4)
#define ACAMERA_ISP_IRIDIX_REV_PERCEPT_CONTROL_MASK (0x300)

// args: data (2-bit)
static __inline void acamera_isp_iridix_rev_percept_control_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac3c);
    system_sw_write_32(base + 0x1ac3c, (((uint32_t) (data & 0x3)) << 8) | (curr & 0xfffffcff));
}
static __inline uint8_t acamera_isp_iridix_rev_percept_control_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac3c) & 0x300) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: strength_inroi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Manual Strength value for inside of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_STRENGTH_INROI_DEFAULT (0x200)
#define ACAMERA_ISP_IRIDIX_STRENGTH_INROI_DATASIZE (10)
#define ACAMERA_ISP_IRIDIX_STRENGTH_INROI_OFFSET (0x1db4)
#define ACAMERA_ISP_IRIDIX_STRENGTH_INROI_MASK (0x3ff0000)

// args: data (10-bit)
static __inline void acamera_isp_iridix_strength_inroi_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac3c);
    system_sw_write_32(base + 0x1ac3c, (((uint32_t) (data & 0x3ff)) << 16) | (curr & 0xfc00ffff));
}
static __inline uint16_t acamera_isp_iridix_strength_inroi_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac3c) & 0x3ff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: strength_outroi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Manual Strength value for outside of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_STRENGTH_OUTROI_DEFAULT (0x200)
#define ACAMERA_ISP_IRIDIX_STRENGTH_OUTROI_DATASIZE (10)
#define ACAMERA_ISP_IRIDIX_STRENGTH_OUTROI_OFFSET (0x1db8)
#define ACAMERA_ISP_IRIDIX_STRENGTH_OUTROI_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_iridix_strength_outroi_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac40);
    system_sw_write_32(base + 0x1ac40, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_iridix_strength_outroi_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac40) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: roi_hor_start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal starting point of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_ROI_HOR_START_DEFAULT (0x0000)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_START_DATASIZE (16)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_START_OFFSET (0x1dbc)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_START_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_iridix_roi_hor_start_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac44);
    system_sw_write_32(base + 0x1ac44, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_iridix_roi_hor_start_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac44) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: roi_hor_end
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal ending point of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_ROI_HOR_END_DEFAULT (0xFFFF)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_END_DATASIZE (16)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_END_OFFSET (0x1dbc)
#define ACAMERA_ISP_IRIDIX_ROI_HOR_END_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_iridix_roi_hor_end_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac44);
    system_sw_write_32(base + 0x1ac44, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_iridix_roi_hor_end_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac44) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: roi_ver_start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical starting point of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_ROI_VER_START_DEFAULT (0x0000)
#define ACAMERA_ISP_IRIDIX_ROI_VER_START_DATASIZE (16)
#define ACAMERA_ISP_IRIDIX_ROI_VER_START_OFFSET (0x1dc0)
#define ACAMERA_ISP_IRIDIX_ROI_VER_START_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_iridix_roi_ver_start_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac48);
    system_sw_write_32(base + 0x1ac48, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_iridix_roi_ver_start_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac48) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: roi_ver_end
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical ending point of ROI 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_ROI_VER_END_DEFAULT (0xFFFF)
#define ACAMERA_ISP_IRIDIX_ROI_VER_END_DATASIZE (16)
#define ACAMERA_ISP_IRIDIX_ROI_VER_END_OFFSET (0x1dc0)
#define ACAMERA_ISP_IRIDIX_ROI_VER_END_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_iridix_roi_ver_end_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac48);
    system_sw_write_32(base + 0x1ac48, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_iridix_roi_ver_end_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac48) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: svariance
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix8 transform sensitivity to different areas of image 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_SVARIANCE_DEFAULT (0x8)
#define ACAMERA_ISP_IRIDIX_SVARIANCE_DATASIZE (4)
#define ACAMERA_ISP_IRIDIX_SVARIANCE_OFFSET (0x1dc4)
#define ACAMERA_ISP_IRIDIX_SVARIANCE_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_iridix_svariance_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac4c);
    system_sw_write_32(base + 0x1ac4c, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_iridix_svariance_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac4c) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: bright_pr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Manual Bright_Preserve value to control Iridix core 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_BRIGHT_PR_DEFAULT (0xDC)
#define ACAMERA_ISP_IRIDIX_BRIGHT_PR_DATASIZE (8)
#define ACAMERA_ISP_IRIDIX_BRIGHT_PR_OFFSET (0x1dc4)
#define ACAMERA_ISP_IRIDIX_BRIGHT_PR_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_iridix_bright_pr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac4c);
    system_sw_write_32(base + 0x1ac4c, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_iridix_bright_pr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac4c) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: contrast
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix8 contrast control parameter 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_CONTRAST_DEFAULT (0xC8)
#define ACAMERA_ISP_IRIDIX_CONTRAST_DATASIZE (8)
#define ACAMERA_ISP_IRIDIX_CONTRAST_OFFSET (0x1dc4)
#define ACAMERA_ISP_IRIDIX_CONTRAST_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_iridix_contrast_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac4c);
    system_sw_write_32(base + 0x1ac4c, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_iridix_contrast_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac4c) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: dark_enh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Manual Dark_Enhance value to control Iridix core 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_DARK_ENH_DEFAULT (0x800)
#define ACAMERA_ISP_IRIDIX_DARK_ENH_DATASIZE (16)
#define ACAMERA_ISP_IRIDIX_DARK_ENH_OFFSET (0x1dc8)
#define ACAMERA_ISP_IRIDIX_DARK_ENH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_iridix_dark_enh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac50);
    system_sw_write_32(base + 0x1ac50, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_iridix_dark_enh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac50) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: context_no
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Context id of a input Frame
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_CONTEXT_NO_DEFAULT (0x0)
#define ACAMERA_ISP_IRIDIX_CONTEXT_NO_DATASIZE (3)
#define ACAMERA_ISP_IRIDIX_CONTEXT_NO_OFFSET (0x1dd4)
#define ACAMERA_ISP_IRIDIX_CONTEXT_NO_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_iridix_context_no_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac5c);
    system_sw_write_32(base + 0x1ac5c, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_iridix_context_no_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac5c) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: wb_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// White balance offset 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_WB_OFFSET_DEFAULT (0x0000)
#define ACAMERA_ISP_IRIDIX_WB_OFFSET_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_WB_OFFSET_OFFSET (0x1dd8)
#define ACAMERA_ISP_IRIDIX_WB_OFFSET_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_iridix_wb_offset_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac60);
    system_sw_write_32(base + 0x1ac60, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_iridix_wb_offset_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1ac60) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// White balance gain for R 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_R_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_GAIN_R_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_GAIN_R_OFFSET (0x1ddc)
#define ACAMERA_ISP_IRIDIX_GAIN_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_iridix_gain_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac64);
    system_sw_write_32(base + 0x1ac64, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_iridix_gain_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac64) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_gr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// White balance gain for GR 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_GR_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_GAIN_GR_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_GAIN_GR_OFFSET (0x1ddc)
#define ACAMERA_ISP_IRIDIX_GAIN_GR_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_iridix_gain_gr_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac64);
    system_sw_write_32(base + 0x1ac64, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_iridix_gain_gr_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac64) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: gain_gb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// White balance gain for GB 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_GB_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_GAIN_GB_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_GAIN_GB_OFFSET (0x1de0)
#define ACAMERA_ISP_IRIDIX_GAIN_GB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_iridix_gain_gb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac68);
    system_sw_write_32(base + 0x1ac68, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_iridix_gain_gb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac68) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// White balance gain for B 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GAIN_B_DEFAULT (0x100)
#define ACAMERA_ISP_IRIDIX_GAIN_B_DATASIZE (12)
#define ACAMERA_ISP_IRIDIX_GAIN_B_OFFSET (0x1de0)
#define ACAMERA_ISP_IRIDIX_GAIN_B_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_iridix_gain_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac68);
    system_sw_write_32(base + 0x1ac68, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_iridix_gain_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ac68) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: GTm_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Global Tone map select : 0 : Local TM 1: Full Global TM 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_GTM_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_IRIDIX_GTM_SELECT_DATASIZE (1)
#define ACAMERA_ISP_IRIDIX_GTM_SELECT_OFFSET (0x1de4)
#define ACAMERA_ISP_IRIDIX_GTM_SELECT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_iridix_gtm_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ac6c);
    system_sw_write_32(base + 0x1ac6c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_iridix_gtm_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ac6c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: iridix LUT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// LUT: Asymmetry LUT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Iridix target curve. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_LUT_ASYMMETRY_LUT_NODES (65)
#define ACAMERA_ISP_IRIDIX_LUT_ASYMMETRY_LUT_ADDRBITS (7)
#define ACAMERA_ISP_IRIDIX_LUT_ASYMMETRY_LUT_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_LUT_ASYMMETRY_LUT_OFFSET (0x1ac70)

// args: index (0-64), data (20-bit)
static __inline void acamera_isp_iridix_lut_asymmetry_lut_write( uintptr_t base, uint8_t index,uint32_t data) {
    uintptr_t addr = base + 0x1ac70 + (index << 2);
    system_sw_write_32(addr, data);
}
static __inline uint32_t acamera_isp_iridix_lut_asymmetry_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1ac70 + (index << 2);
    return system_sw_read_32(addr);
}
// ------------------------------------------------------------------------------ //
// LUT: GlobalTM X LUT
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_X_LUT_NODES (33)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_X_LUT_ADDRBITS (6)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_X_LUT_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_X_LUT_OFFSET (0x1ad74)

// args: index (0-32), data (20-bit)
static __inline void acamera_isp_iridix_lut_globaltm_x_lut_write( uintptr_t base, uint8_t index,uint32_t data) {
    uintptr_t addr = base + 0x1ad74 + (index << 2);
    system_sw_write_32(addr, data);
}
static __inline uint32_t acamera_isp_iridix_lut_globaltm_x_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1ad74 + (index << 2);
    return system_sw_read_32(addr);
}
// ------------------------------------------------------------------------------ //
// LUT: GlobalTM Y LUT
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_Y_LUT_NODES (33)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_Y_LUT_ADDRBITS (6)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_Y_LUT_DATASIZE (20)
#define ACAMERA_ISP_IRIDIX_LUT_GLOBALTM_Y_LUT_OFFSET (0x1adf8)

// args: index (0-32), data (20-bit)
static __inline void acamera_isp_iridix_lut_globaltm_y_lut_write( uintptr_t base, uint8_t index,uint32_t data) {
    uintptr_t addr = base + 0x1adf8 + (index << 2);
    system_sw_write_32(addr, data);
}
static __inline uint32_t acamera_isp_iridix_lut_globaltm_y_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1adf8 + (index << 2);
    return system_sw_read_32(addr);
}
// ------------------------------------------------------------------------------ //
// Group: demosaic rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Bayer Demosaic
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: UU Slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Slope of undefined blending threshold in 4.4 logarithmic format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SLOPE_DEFAULT (0xAD)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SLOPE_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SLOPE_OFFSET (0x1ff4)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SLOPE_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_uu_slope_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ae7c);
    system_sw_write_32(base + 0x1ae7c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_demosaic_rgb_uu_slope_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1ae7c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: UU Thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Threshold for the range of undefined blending
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_UU_THRESH_DEFAULT (0xFA)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_THRESH_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_THRESH_OFFSET (0x2000)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_uu_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1ae88);
    system_sw_write_32(base + 0x1ae88, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_uu_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1ae88) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Dmsc config
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Debug output select. Set to 0x00 for normal operation.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_DMSC_CONFIG_DEFAULT (0x00)
#define ACAMERA_ISP_DEMOSAIC_RGB_DMSC_CONFIG_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_DMSC_CONFIG_OFFSET (0x2018)
#define ACAMERA_ISP_DEMOSAIC_RGB_DMSC_CONFIG_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_dmsc_config_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aea0);
    system_sw_write_32(base + 0x1aea0, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_demosaic_rgb_dmsc_config_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aea0) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: FC Slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Slope (strength) of false color correction
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_FC_SLOPE_DEFAULT (0x80)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_SLOPE_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_SLOPE_OFFSET (0x2020)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_SLOPE_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_fc_slope_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aea8);
    system_sw_write_32(base + 0x1aea8, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_demosaic_rgb_fc_slope_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aea8) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: FC Alias Slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Slope (strength) of false colour correction after blending with saturation value in 2.6 unsigned format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_FC_ALIAS_SLOPE_DEFAULT (0x40)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_ALIAS_SLOPE_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_ALIAS_SLOPE_OFFSET (0x2020)
#define ACAMERA_ISP_DEMOSAIC_RGB_FC_ALIAS_SLOPE_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_fc_alias_slope_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aea8);
    system_sw_write_32(base + 0x1aea8, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_fc_alias_slope_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aea8) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: sharp_alt_ld
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpen strength for L_Ld in unsigned 4.4 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LD_DEFAULT (0x10)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LD_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LD_OFFSET (0x2028)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LD_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_sharp_alt_ld_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb0);
    system_sw_write_32(base + 0x1aeb0, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_demosaic_rgb_sharp_alt_ld_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aeb0) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sharp_alt_ldu
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpen strength for L_Ldu in unsigned 4.4 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LDU_DEFAULT (0x10)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LDU_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LDU_OFFSET (0x2028)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LDU_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_sharp_alt_ldu_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb0);
    system_sw_write_32(base + 0x1aeb0, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_sharp_alt_ldu_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aeb0) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: sharp_alt_lu
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpen strength for L_Lu in unsigned 4.4 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LU_DEFAULT (0x10)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LU_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LU_OFFSET (0x2028)
#define ACAMERA_ISP_DEMOSAIC_RGB_SHARP_ALT_LU_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_sharp_alt_lu_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb0);
    system_sw_write_32(base + 0x1aeb0, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_sharp_alt_lu_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aeb0) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: sad_amp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sad amplifier in unsigned 4.4 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_SAD_AMP_DEFAULT (0x10)
#define ACAMERA_ISP_DEMOSAIC_RGB_SAD_AMP_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_SAD_AMP_OFFSET (0x2028)
#define ACAMERA_ISP_DEMOSAIC_RGB_SAD_AMP_MASK (0xff000000)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_sad_amp_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb0);
    system_sw_write_32(base + 0x1aeb0, (((uint32_t) (data & 0xff)) << 24) | (curr & 0xffffff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_sad_amp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aeb0) & 0xff000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: min_d_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Min threshold for the directional L_L in signed 2's complement s.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_D_STRENGTH_DEFAULT (0x1F85)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_D_STRENGTH_DATASIZE (13)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_D_STRENGTH_OFFSET (0x202c)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_D_STRENGTH_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_demosaic_rgb_min_d_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb4);
    system_sw_write_32(base + 0x1aeb4, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_min_d_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aeb4) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: min_ud_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Min threshold for the un-directional L_Lu in signed 2's complement s.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_UD_STRENGTH_DEFAULT (0x1F85)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_UD_STRENGTH_DATASIZE (13)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_UD_STRENGTH_OFFSET (0x2030)
#define ACAMERA_ISP_DEMOSAIC_RGB_MIN_UD_STRENGTH_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_demosaic_rgb_min_ud_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeb8);
    system_sw_write_32(base + 0x1aeb8, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_min_ud_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aeb8) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: UU SH Slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Slope of undefined blending threshold in 4.4 logarithmic format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_SLOPE_DEFAULT (0xAD)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_SLOPE_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_SLOPE_OFFSET (0x2038)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_SLOPE_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_uu_sh_slope_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aec0);
    system_sw_write_32(base + 0x1aec0, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_demosaic_rgb_uu_sh_slope_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aec0) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: UU SH Thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Threshold for the range of undefined blending
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_THRESH_DEFAULT (0xFA)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_THRESH_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_THRESH_OFFSET (0x203c)
#define ACAMERA_ISP_DEMOSAIC_RGB_UU_SH_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_uu_sh_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aec4);
    system_sw_write_32(base + 0x1aec4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_uu_sh_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aec4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: max_d_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Max threshold for the directional L_L in signed 2's complement s1+0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_D_STRENGTH_DEFAULT (0x333)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_D_STRENGTH_DATASIZE (13)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_D_STRENGTH_OFFSET (0x2044)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_D_STRENGTH_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_demosaic_rgb_max_d_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aecc);
    system_sw_write_32(base + 0x1aecc, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_max_d_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aecc) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: max_ud_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Max threshold for the undirectional L_Lu in signed 2's complement s1+0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_UD_STRENGTH_DEFAULT (0x333)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_UD_STRENGTH_DATASIZE (13)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_UD_STRENGTH_OFFSET (0x2044)
#define ACAMERA_ISP_DEMOSAIC_RGB_MAX_UD_STRENGTH_MASK (0x1fff0000)

// args: data (13-bit)
static __inline void acamera_isp_demosaic_rgb_max_ud_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aecc);
    system_sw_write_32(base + 0x1aecc, (((uint32_t) (data & 0x1fff)) << 16) | (curr & 0xe000ffff));
}
static __inline uint16_t acamera_isp_demosaic_rgb_max_ud_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aecc) & 0x1fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma_thresh_low_d
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Intensity values above this value will be sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_D_DEFAULT (0x8)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_D_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_D_OFFSET (0x2048)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_D_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_luma_thresh_low_d_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aed0);
    system_sw_write_32(base + 0x1aed0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_luma_thresh_low_d_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aed0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_offset_low_d
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold offset corresponding to luma_thresh_low_d
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_D_DEFAULT (0x0)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_D_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_D_OFFSET (0x2048)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_D_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_luma_offset_low_d_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aed0);
    system_sw_write_32(base + 0x1aed0, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_luma_offset_low_d_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aed0) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma_slope_low_d
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold slope corresponding to luma_thresh_low_d
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_D_DEFAULT (0x4000)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_D_DATASIZE (20)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_D_OFFSET (0x204c)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_D_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_demosaic_rgb_luma_slope_low_d_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aed4);
    system_sw_write_32(base + 0x1aed4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_demosaic_rgb_luma_slope_low_d_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1aed4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_thresh_high_d
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Intensity values below this value will be sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_D_DEFAULT (0xFA0)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_D_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_D_OFFSET (0x2050)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_D_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_luma_thresh_high_d_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aed8);
    system_sw_write_32(base + 0x1aed8, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_demosaic_rgb_luma_thresh_high_d_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aed8) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma_slope_high_d
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold slope corresponding to luma_thresh_high_d
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_D_DEFAULT (0x4000)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_D_DATASIZE (20)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_D_OFFSET (0x2054)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_D_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_demosaic_rgb_luma_slope_high_d_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aedc);
    system_sw_write_32(base + 0x1aedc, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_demosaic_rgb_luma_slope_high_d_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1aedc) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_thresh_low_ud
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Intensity values above this value will be sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_UD_DEFAULT (0x8)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_UD_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_UD_OFFSET (0x2058)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_LOW_UD_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_luma_thresh_low_ud_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aee0);
    system_sw_write_32(base + 0x1aee0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_luma_thresh_low_ud_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aee0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_offset_low_ud
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold offset corresponding to luma_thresh_low_ud
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_UD_DEFAULT (0x0)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_UD_DATASIZE (8)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_UD_OFFSET (0x2058)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_OFFSET_LOW_UD_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_demosaic_rgb_luma_offset_low_ud_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aee0);
    system_sw_write_32(base + 0x1aee0, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_demosaic_rgb_luma_offset_low_ud_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1aee0) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma_slope_low_ud
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold slope corresponding to luma_thresh_low_ud
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_UD_DEFAULT (0x4000)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_UD_DATASIZE (20)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_UD_OFFSET (0x205c)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_LOW_UD_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_demosaic_rgb_luma_slope_low_ud_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aee4);
    system_sw_write_32(base + 0x1aee4, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_demosaic_rgb_luma_slope_low_ud_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1aee4) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_thresh_high_ud
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Intensity values below this value will be sharpen
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_UD_DEFAULT (0xFA0)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_UD_DATASIZE (12)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_UD_OFFSET (0x2060)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_THRESH_HIGH_UD_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_demosaic_rgb_luma_thresh_high_ud_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aee8);
    system_sw_write_32(base + 0x1aee8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_demosaic_rgb_luma_thresh_high_ud_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aee8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_slope_high_ud
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linear threshold slope corresponding to luma_thresh_high_ud
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_UD_DEFAULT (0x4000)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_UD_DATASIZE (20)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_UD_OFFSET (0x2064)
#define ACAMERA_ISP_DEMOSAIC_RGB_LUMA_SLOPE_HIGH_UD_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_demosaic_rgb_luma_slope_high_ud_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aeec);
    system_sw_write_32(base + 0x1aeec, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_demosaic_rgb_luma_slope_high_ud_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1aeec) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: pf correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// purple fringing correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: use_color_corrected_rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        This signal decides if the input data will be corrected through CCM or used directly
//        0: Use the input data directly
//        1: Apply 3x3 CCM on the input data
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_USE_COLOR_CORRECTED_RGB_DEFAULT (1)
#define ACAMERA_ISP_PF_CORRECTION_USE_COLOR_CORRECTED_RGB_DATASIZE (1)
#define ACAMERA_ISP_PF_CORRECTION_USE_COLOR_CORRECTED_RGB_OFFSET (0x2140)
#define ACAMERA_ISP_PF_CORRECTION_USE_COLOR_CORRECTED_RGB_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_pf_correction_use_color_corrected_rgb_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afc8);
    system_sw_write_32(base + 0x1afc8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_pf_correction_use_color_corrected_rgb_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1afc8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hue_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Hue strength control signal in 3.9 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_STRENGTH_DEFAULT (0x200)
#define ACAMERA_ISP_PF_CORRECTION_HUE_STRENGTH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_STRENGTH_OFFSET (0x2144)
#define ACAMERA_ISP_PF_CORRECTION_HUE_STRENGTH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afcc);
    system_sw_write_32(base + 0x1afcc, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hue_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afcc) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sat_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        saturation check strength control in 3.9 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_STRENGTH_DEFAULT (0x200)
#define ACAMERA_ISP_PF_CORRECTION_SAT_STRENGTH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_STRENGTH_OFFSET (0x2148)
#define ACAMERA_ISP_PF_CORRECTION_SAT_STRENGTH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afd0);
    system_sw_write_32(base + 0x1afd0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sat_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afd0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Luma strength control in 3.9 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA_STRENGTH_DEFAULT (0x400)
#define ACAMERA_ISP_PF_CORRECTION_LUMA_STRENGTH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA_STRENGTH_OFFSET (0x2148)
#define ACAMERA_ISP_PF_CORRECTION_LUMA_STRENGTH_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afd0);
    system_sw_write_32(base + 0x1afd0, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_luma_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afd0) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: purple_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        final purple decision strength in 3.9 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_PURPLE_STRENGTH_DEFAULT (0x400)
#define ACAMERA_ISP_PF_CORRECTION_PURPLE_STRENGTH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_PURPLE_STRENGTH_OFFSET (0x214c)
#define ACAMERA_ISP_PF_CORRECTION_PURPLE_STRENGTH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_purple_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afd4);
    system_sw_write_32(base + 0x1afd4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_purple_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afd4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: saturation_strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Saturation matrix strength matrix in u0.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SATURATION_STRENGTH_DEFAULT (0x0)
#define ACAMERA_ISP_PF_CORRECTION_SATURATION_STRENGTH_DATASIZE (8)
#define ACAMERA_ISP_PF_CORRECTION_SATURATION_STRENGTH_OFFSET (0x214c)
#define ACAMERA_ISP_PF_CORRECTION_SATURATION_STRENGTH_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_pf_correction_saturation_strength_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afd4);
    system_sw_write_32(base + 0x1afd4, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_pf_correction_saturation_strength_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1afd4) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: off_center_mult
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Normalizing factor which scales the radial table to the edge of the image.
//        Calculated as 2^31/R^2 where R is the furthest distance from the center coordinate to the edge of the image in pixels.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_OFF_CENTER_MULT_DEFAULT (0xF8F)
#define ACAMERA_ISP_PF_CORRECTION_OFF_CENTER_MULT_DATASIZE (16)
#define ACAMERA_ISP_PF_CORRECTION_OFF_CENTER_MULT_OFFSET (0x2150)
#define ACAMERA_ISP_PF_CORRECTION_OFF_CENTER_MULT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_pf_correction_off_center_mult_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afd8);
    system_sw_write_32(base + 0x1afd8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_pf_correction_off_center_mult_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afd8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: center_x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Center x coordinate of shading map
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CENTER_X_DEFAULT (0x168)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_X_DATASIZE (16)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_X_OFFSET (0x2154)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_pf_correction_center_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afdc);
    system_sw_write_32(base + 0x1afdc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_pf_correction_center_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afdc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: center_y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Center y coordinate of shading map
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CENTER_Y_DEFAULT (0x280)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_Y_DATASIZE (16)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_Y_OFFSET (0x2154)
#define ACAMERA_ISP_PF_CORRECTION_CENTER_Y_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_pf_correction_center_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afdc);
    system_sw_write_32(base + 0x1afdc, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_pf_correction_center_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afdc) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_rr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for red-red multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RR_DEFAULT (0x01CB)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RR_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RR_OFFSET (0x2158)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RR_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_rr_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afe0);
    system_sw_write_32(base + 0x1afe0, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_rr_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afe0) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_rg
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for red-green multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RG_DEFAULT (0x10c1)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RG_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RG_OFFSET (0x215c)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RG_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_rg_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afe4);
    system_sw_write_32(base + 0x1afe4, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_rg_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afe4) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_rb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for red-blue multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RB_DEFAULT (0x100A)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RB_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RB_OFFSET (0x2160)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_RB_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_rb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afe8);
    system_sw_write_32(base + 0x1afe8, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_rb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afe8) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_gr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for green-red multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GR_DEFAULT (0x1028)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GR_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GR_OFFSET (0x2164)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GR_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_gr_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1afec);
    system_sw_write_32(base + 0x1afec, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_gr_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1afec) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_gg
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for green-green multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GG_DEFAULT (0x16D)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GG_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GG_OFFSET (0x2168)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GG_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_gg_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aff0);
    system_sw_write_32(base + 0x1aff0, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_gg_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aff0) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_gb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for green-blue multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GB_DEFAULT (0x1045)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GB_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GB_OFFSET (0x216c)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_GB_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_gb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aff4);
    system_sw_write_32(base + 0x1aff4, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_gb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aff4) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_br
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for blue-red multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BR_DEFAULT (0x012)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BR_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BR_OFFSET (0x2170)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BR_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_br_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1aff8);
    system_sw_write_32(base + 0x1aff8, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_br_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1aff8) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_bg
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for blue-green multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BG_DEFAULT (0x10AC)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BG_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BG_OFFSET (0x2174)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BG_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_bg_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1affc);
    system_sw_write_32(base + 0x1affc, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_bg_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1affc) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ccm_coeff_bb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Matrix coefficient for blue-blue multiplier in s4.8 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BB_DEFAULT (0x19A)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BB_DATASIZE (13)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BB_OFFSET (0x2178)
#define ACAMERA_ISP_PF_CORRECTION_CCM_COEFF_BB_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_pf_correction_ccm_coeff_bb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b000);
    system_sw_write_32(base + 0x1b000, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_pf_correction_ccm_coeff_bb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b000) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sad_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Slope of the SAD linear threshold in u7.5 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAD_SLOPE_DEFAULT (0x001)
#define ACAMERA_ISP_PF_CORRECTION_SAD_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAD_SLOPE_OFFSET (0x217c)
#define ACAMERA_ISP_PF_CORRECTION_SAD_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sad_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b004);
    system_sw_write_32(base + 0x1b004, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sad_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b004) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sad_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Offset of the sad linear threshold in u0.12 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAD_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_SAD_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAD_OFFSET_OFFSET (0x217c)
#define ACAMERA_ISP_PF_CORRECTION_SAD_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sad_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b004);
    system_sw_write_32(base + 0x1b004, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_sad_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b004) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: sad_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Threshold of the SAD linear threshold in u0.12 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAD_THRESH_DEFAULT (0x148)
#define ACAMERA_ISP_PF_CORRECTION_SAD_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAD_THRESH_OFFSET (0x2180)
#define ACAMERA_ISP_PF_CORRECTION_SAD_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sad_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b008);
    system_sw_write_32(base + 0x1b008, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sad_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b008) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hue_low_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_SLOPE_DEFAULT (0x131)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_SLOPE_OFFSET (0x2184)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_low_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b00c);
    system_sw_write_32(base + 0x1b00c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hue_low_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b00c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hue_low_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_OFFSET_OFFSET (0x2184)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_low_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b00c);
    system_sw_write_32(base + 0x1b00c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_hue_low_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b00c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: hue_low_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u3.9 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_THRESH_DEFAULT (0x733)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_THRESH_OFFSET (0x2188)
#define ACAMERA_ISP_PF_CORRECTION_HUE_LOW_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_low_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b010);
    system_sw_write_32(base + 0x1b010, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hue_low_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b010) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hue_high_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_SLOPE_DEFAULT (0x855)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_SLOPE_OFFSET (0x218c)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_high_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b014);
    system_sw_write_32(base + 0x1b014, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hue_high_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b014) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hue_high_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_OFFSET_OFFSET (0x218c)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_high_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b014);
    system_sw_write_32(base + 0x1b014, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_hue_high_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b014) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: hue_high_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u3.9 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_THRESH_DEFAULT (0x8E1)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_THRESH_OFFSET (0x2190)
#define ACAMERA_ISP_PF_CORRECTION_HUE_HIGH_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hue_high_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b018);
    system_sw_write_32(base + 0x1b018, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hue_high_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b018) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sat_low_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_SLOPE_DEFAULT (0x021)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_SLOPE_OFFSET (0x2194)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_low_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b01c);
    system_sw_write_32(base + 0x1b01c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sat_low_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b01c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sat_low_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_OFFSET_OFFSET (0x2194)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_low_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b01c);
    system_sw_write_32(base + 0x1b01c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_sat_low_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b01c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: sat_low_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_THRESH_DEFAULT (0x0A4)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_THRESH_OFFSET (0x2198)
#define ACAMERA_ISP_PF_CORRECTION_SAT_LOW_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_low_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b020);
    system_sw_write_32(base + 0x1b020, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sat_low_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b020) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sat_high_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_SLOPE_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_SLOPE_OFFSET (0x219c)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_high_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b024);
    system_sw_write_32(base + 0x1b024, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sat_high_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b024) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: sat_high_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_OFFSET_DEFAULT (0xFFF)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_OFFSET_OFFSET (0x219c)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_high_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b024);
    system_sw_write_32(base + 0x1b024, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_sat_high_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b024) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: sat_high_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 fromat
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_THRESH_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_THRESH_OFFSET (0x21a0)
#define ACAMERA_ISP_PF_CORRECTION_SAT_HIGH_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_sat_high_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b028);
    system_sw_write_32(base + 0x1b028, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_sat_high_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b028) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_low_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_SLOPE_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_SLOPE_OFFSET (0x21a4)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_low_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b02c);
    system_sw_write_32(base + 0x1b02c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_low_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b02c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_low_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 fromat
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_OFFSET_OFFSET (0x21a4)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_low_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b02c);
    system_sw_write_32(base + 0x1b02c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_low_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b02c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_low_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u12.0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_THRESH_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_THRESH_OFFSET (0x21a8)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_LOW_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_low_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b030);
    system_sw_write_32(base + 0x1b030, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_low_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b030) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_high_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_SLOPE_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_SLOPE_OFFSET (0x21ac)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_high_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b034);
    system_sw_write_32(base + 0x1b034, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_high_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b034) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_high_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_OFFSET_OFFSET (0x21ac)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_high_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b034);
    system_sw_write_32(base + 0x1b034, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_high_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b034) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma1_high_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u12.0 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_THRESH_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_THRESH_OFFSET (0x21b0)
#define ACAMERA_ISP_PF_CORRECTION_LUMA1_HIGH_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma1_high_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b038);
    system_sw_write_32(base + 0x1b038, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma1_high_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b038) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_low_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_SLOPE_DEFAULT (0x140)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_SLOPE_OFFSET (0x21b4)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_low_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b03c);
    system_sw_write_32(base + 0x1b03c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_low_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b03c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_low_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_OFFSET_OFFSET (0x21b4)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_low_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b03c);
    system_sw_write_32(base + 0x1b03c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_low_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b03c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_low_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u12.0 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_THRESH_DEFAULT (0x0CD)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_THRESH_OFFSET (0x21b8)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_LOW_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_low_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b040);
    system_sw_write_32(base + 0x1b040, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_low_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b040) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_high_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_SLOPE_DEFAULT (0x026)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_SLOPE_OFFSET (0x21bc)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_high_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b044);
    system_sw_write_32(base + 0x1b044, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_high_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b044) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_high_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_OFFSET_OFFSET (0x21bc)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_high_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b044);
    system_sw_write_32(base + 0x1b044, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_high_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b044) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: luma2_high_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u12.0 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_THRESH_DEFAULT (0x1A0)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_THRESH_OFFSET (0x21c0)
#define ACAMERA_ISP_PF_CORRECTION_LUMA2_HIGH_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_luma2_high_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b048);
    system_sw_write_32(base + 0x1b048, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_luma2_high_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b048) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hsl_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u7.5 fromat
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HSL_SLOPE_DEFAULT (0x024)
#define ACAMERA_ISP_PF_CORRECTION_HSL_SLOPE_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HSL_SLOPE_OFFSET (0x21c4)
#define ACAMERA_ISP_PF_CORRECTION_HSL_SLOPE_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hsl_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b04c);
    system_sw_write_32(base + 0x1b04c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hsl_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b04c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: hsl_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HSL_OFFSET_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_HSL_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HSL_OFFSET_OFFSET (0x21c4)
#define ACAMERA_ISP_PF_CORRECTION_HSL_OFFSET_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hsl_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b04c);
    system_sw_write_32(base + 0x1b04c, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_pf_correction_hsl_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b04c) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: hsl_thresh
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u0.12 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_HSL_THRESH_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_HSL_THRESH_DATASIZE (12)
#define ACAMERA_ISP_PF_CORRECTION_HSL_THRESH_OFFSET (0x21c8)
#define ACAMERA_ISP_PF_CORRECTION_HSL_THRESH_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_pf_correction_hsl_thresh_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b050);
    system_sw_write_32(base + 0x1b050, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_pf_correction_hsl_thresh_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b050) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: debug_sel
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: normal operation
//        1: radial weight in 0.8 format
//        2: sad_mask in 0.12 format
//        3: hue mask in 0.12 format
//        4: saturation mask in 0.12 format
//        5: luma mask in 12.0 format
//        6: pf mask in 12.0 format
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_DEBUG_SEL_DEFAULT (0x000)
#define ACAMERA_ISP_PF_CORRECTION_DEBUG_SEL_DATASIZE (8)
#define ACAMERA_ISP_PF_CORRECTION_DEBUG_SEL_OFFSET (0x21cc)
#define ACAMERA_ISP_PF_CORRECTION_DEBUG_SEL_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_pf_correction_debug_sel_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b054);
    system_sw_write_32(base + 0x1b054, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_pf_correction_debug_sel_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b054) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: pf correction Shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// LUT: shading_lut
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Radial Purple Fringe Correction LUT.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_PF_CORRECTION_SHADING_SHADING_LUT_NODES (33)
#define ACAMERA_ISP_PF_CORRECTION_SHADING_SHADING_LUT_ADDRBITS (6)
#define ACAMERA_ISP_PF_CORRECTION_SHADING_SHADING_LUT_DATASIZE (8)
#define ACAMERA_ISP_PF_CORRECTION_SHADING_SHADING_LUT_OFFSET (0x1b058)

// args: index (0-32), data (8-bit)
static __inline void acamera_isp_pf_correction_shading_shading_lut_write( uintptr_t base, uint8_t index,uint8_t data) {
    uintptr_t addr = base + 0x1b058 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    uint32_t curr = system_sw_read_32(addr);
    system_sw_write_32(addr, ((uint32_t)data << offset) | (curr & ~(0xFF << offset)));
}
static __inline uint8_t acamera_isp_pf_correction_shading_shading_lut_read( uintptr_t base, uint8_t index) {
    uintptr_t addr = base + 0x1b058 + (index & 0xFFFFFFFC);
    uint8_t offset = (index & 3) << 3;
    return (uint8_t)(system_sw_read_32(addr) >> offset);
}
// ------------------------------------------------------------------------------ //
// Group: ccm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Color correction on RGB data using a 3x3 color matrix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Color matrix enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_CCM_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_CCM_ENABLE_OFFSET (0x21f4)
#define ACAMERA_ISP_CCM_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ccm_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b07c);
    system_sw_write_32(base + 0x1b07c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ccm_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b07c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft R-R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for red-red multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_R_R_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_R_R_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_R_R_OFFSET (0x21f8)
#define ACAMERA_ISP_CCM_COEFFT_R_R_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_r_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b080);
    system_sw_write_32(base + 0x1b080, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_r_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b080) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft R-G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for red-green multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_R_G_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_R_G_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_R_G_OFFSET (0x21fc)
#define ACAMERA_ISP_CCM_COEFFT_R_G_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_r_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b084);
    system_sw_write_32(base + 0x1b084, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_r_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b084) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft R-B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for red-blue multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_R_B_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_R_B_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_R_B_OFFSET (0x2200)
#define ACAMERA_ISP_CCM_COEFFT_R_B_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_r_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b088);
    system_sw_write_32(base + 0x1b088, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_r_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b088) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft G-R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for green-red multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_G_R_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_G_R_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_G_R_OFFSET (0x2208)
#define ACAMERA_ISP_CCM_COEFFT_G_R_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_g_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b090);
    system_sw_write_32(base + 0x1b090, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_g_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b090) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft G-G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for green-green multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_G_G_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_G_G_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_G_G_OFFSET (0x220c)
#define ACAMERA_ISP_CCM_COEFFT_G_G_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_g_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b094);
    system_sw_write_32(base + 0x1b094, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_g_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b094) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft G-B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for green-blue multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_G_B_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_G_B_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_G_B_OFFSET (0x2210)
#define ACAMERA_ISP_CCM_COEFFT_G_B_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_g_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b098);
    system_sw_write_32(base + 0x1b098, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_g_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b098) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft B-R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for blue-red multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_B_R_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_B_R_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_B_R_OFFSET (0x2218)
#define ACAMERA_ISP_CCM_COEFFT_B_R_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_b_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0a0);
    system_sw_write_32(base + 0x1b0a0, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_b_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0a0) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft B-G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for blue-green multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_B_G_DEFAULT (0x0000)
#define ACAMERA_ISP_CCM_COEFFT_B_G_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_B_G_OFFSET (0x221c)
#define ACAMERA_ISP_CCM_COEFFT_B_G_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_b_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0a4);
    system_sw_write_32(base + 0x1b0a4, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_b_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0a4) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft B-B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for blue-blue multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_B_B_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_B_B_DATASIZE (13)
#define ACAMERA_ISP_CCM_COEFFT_B_B_OFFSET (0x2220)
#define ACAMERA_ISP_CCM_COEFFT_B_B_MASK (0x1fff)

// args: data (13-bit)
static __inline void acamera_isp_ccm_coefft_b_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0a8);
    system_sw_write_32(base + 0x1b0a8, (((uint32_t) (data & 0x1fff)) << 0) | (curr & 0xffffe000));
}
static __inline uint16_t acamera_isp_ccm_coefft_b_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0a8) & 0x1fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft WB R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain for Red channel for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_WB_R_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_WB_R_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_WB_R_OFFSET (0x2228)
#define ACAMERA_ISP_CCM_COEFFT_WB_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_wb_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0b0);
    system_sw_write_32(base + 0x1b0b0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_wb_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0b0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft WB G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain for Green channel for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_WB_G_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_WB_G_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_WB_G_OFFSET (0x222c)
#define ACAMERA_ISP_CCM_COEFFT_WB_G_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_wb_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0b4);
    system_sw_write_32(base + 0x1b0b4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_wb_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0b4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft WB B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain for Blue channel for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_WB_B_DEFAULT (0x0100)
#define ACAMERA_ISP_CCM_COEFFT_WB_B_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_WB_B_OFFSET (0x2230)
#define ACAMERA_ISP_CCM_COEFFT_WB_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_wb_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0b8);
    system_sw_write_32(base + 0x1b0b8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_wb_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0b8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft fog offset R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset R for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_R_DEFAULT (0x000)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_R_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_R_OFFSET (0x2238)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_fog_offset_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0c0);
    system_sw_write_32(base + 0x1b0c0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_fog_offset_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0c0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft fog offset G
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset G for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_G_DEFAULT (0x000)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_G_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_G_OFFSET (0x223c)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_G_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_fog_offset_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0c4);
    system_sw_write_32(base + 0x1b0c4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_fog_offset_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0c4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft fog offset B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset B for antifog function
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_B_DEFAULT (0x000)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_B_DATASIZE (12)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_B_OFFSET (0x2240)
#define ACAMERA_ISP_CCM_COEFFT_FOG_OFFSET_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ccm_coefft_fog_offset_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0c8);
    system_sw_write_32(base + 0x1b0c8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ccm_coefft_fog_offset_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0c8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: cnr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Colour Noise Reduction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: square_root_enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// pre-CNR square root and the post-CNR square modules enable condition enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_SQUARE_ROOT_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_CNR_SQUARE_ROOT_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_CNR_SQUARE_ROOT_ENABLE_OFFSET (0x2248)
#define ACAMERA_ISP_CNR_SQUARE_ROOT_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_cnr_square_root_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0d0);
    system_sw_write_32(base + 0x1b0d0, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_cnr_square_root_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b0d0) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// CNR enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_CNR_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_CNR_ENABLE_OFFSET (0x224c)
#define ACAMERA_ISP_CNR_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_cnr_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0d4);
    system_sw_write_32(base + 0x1b0d4, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_cnr_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b0d4) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: debug_reg
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// CNR Debug selection. By default 0x0000, it ouputs normal processed data.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_DEBUG_REG_DEFAULT (0x0000)
#define ACAMERA_ISP_CNR_DEBUG_REG_DATASIZE (16)
#define ACAMERA_ISP_CNR_DEBUG_REG_OFFSET (0x2250)
#define ACAMERA_ISP_CNR_DEBUG_REG_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_cnr_debug_reg_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0d8);
    system_sw_write_32(base + 0x1b0d8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_cnr_debug_reg_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0d8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: delta_factor
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Factor for UV Delta.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_DELTA_FACTOR_DEFAULT (0x277)
#define ACAMERA_ISP_CNR_DELTA_FACTOR_DATASIZE (12)
#define ACAMERA_ISP_CNR_DELTA_FACTOR_OFFSET (0x2258)
#define ACAMERA_ISP_CNR_DELTA_FACTOR_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_delta_factor_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0e0);
    system_sw_write_32(base + 0x1b0e0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_delta_factor_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0e0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_seg1_min
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minium value of uv_seg 1,2 mask
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_SEG1_MIN_DEFAULT (0x333)
#define ACAMERA_ISP_CNR_UV_SEG1_MIN_DATASIZE (12)
#define ACAMERA_ISP_CNR_UV_SEG1_MIN_OFFSET (0x225c)
#define ACAMERA_ISP_CNR_UV_SEG1_MIN_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_uv_seg1_min_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0e4);
    system_sw_write_32(base + 0x1b0e4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_uv_seg1_min_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0e4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_seg1_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_seg1 offset
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_SEG1_OFFSET_DEFAULT (0x0AE)
#define ACAMERA_ISP_CNR_UV_SEG1_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_CNR_UV_SEG1_OFFSET_OFFSET (0x2260)
#define ACAMERA_ISP_CNR_UV_SEG1_OFFSET_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_uv_seg1_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0e8);
    system_sw_write_32(base + 0x1b0e8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_uv_seg1_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0e8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_seg1_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_seg1 slope
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_SEG1_SLOPE_DEFAULT (0xFBD8)
#define ACAMERA_ISP_CNR_UV_SEG1_SLOPE_DATASIZE (16)
#define ACAMERA_ISP_CNR_UV_SEG1_SLOPE_OFFSET (0x2264)
#define ACAMERA_ISP_CNR_UV_SEG1_SLOPE_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_cnr_uv_seg1_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0ec);
    system_sw_write_32(base + 0x1b0ec, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_cnr_uv_seg1_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0ec) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_mean_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u/v mean offset
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_MEAN_OFFSET_DEFAULT (0x03E)
#define ACAMERA_ISP_CNR_UV_MEAN_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_CNR_UV_MEAN_OFFSET_OFFSET (0x2268)
#define ACAMERA_ISP_CNR_UV_MEAN_OFFSET_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_uv_mean_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0f0);
    system_sw_write_32(base + 0x1b0f0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_uv_mean_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0f0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_mean_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// u/v mean slope
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_MEAN_SLOPE_DEFAULT (0xE7B4)
#define ACAMERA_ISP_CNR_UV_MEAN_SLOPE_DATASIZE (16)
#define ACAMERA_ISP_CNR_UV_MEAN_SLOPE_OFFSET (0x226c)
#define ACAMERA_ISP_CNR_UV_MEAN_SLOPE_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_cnr_uv_mean_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0f4);
    system_sw_write_32(base + 0x1b0f4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_cnr_uv_mean_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0f4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_var_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_var offset
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_VAR_OFFSET_DEFAULT (0x3FF)
#define ACAMERA_ISP_CNR_UV_VAR_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_CNR_UV_VAR_OFFSET_OFFSET (0x2270)
#define ACAMERA_ISP_CNR_UV_VAR_OFFSET_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_uv_var_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0f8);
    system_sw_write_32(base + 0x1b0f8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_uv_var_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0f8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_var_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_var slope
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_VAR_SLOPE_DEFAULT (0xFFFF)
#define ACAMERA_ISP_CNR_UV_VAR_SLOPE_DATASIZE (16)
#define ACAMERA_ISP_CNR_UV_VAR_SLOPE_OFFSET (0x2274)
#define ACAMERA_ISP_CNR_UV_VAR_SLOPE_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_cnr_uv_var_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b0fc);
    system_sw_write_32(base + 0x1b0fc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_cnr_uv_var_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b0fc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_delta_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_delta offset
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_DELTA_OFFSET_DEFAULT (0x0B9)
#define ACAMERA_ISP_CNR_UV_DELTA_OFFSET_DATASIZE (12)
#define ACAMERA_ISP_CNR_UV_DELTA_OFFSET_OFFSET (0x2278)
#define ACAMERA_ISP_CNR_UV_DELTA_OFFSET_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_cnr_uv_delta_offset_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b100);
    system_sw_write_32(base + 0x1b100, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_cnr_uv_delta_offset_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b100) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: uv_delta_slope
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// uv_delta slope
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_CNR_UV_DELTA_SLOPE_DEFAULT (0x0600)
#define ACAMERA_ISP_CNR_UV_DELTA_SLOPE_DATASIZE (16)
#define ACAMERA_ISP_CNR_UV_DELTA_SLOPE_OFFSET (0x227c)
#define ACAMERA_ISP_CNR_UV_DELTA_SLOPE_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_cnr_uv_delta_slope_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b104);
    system_sw_write_32(base + 0x1b104, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_cnr_uv_delta_slope_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b104) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: targetaddr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: target1_addr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            The ISP generates an interrupt when the metering_awb module has written statistics in memory up to the configured value address. If this register is set to 0, this feature is disabled.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TARGETADDR_TARGET1_ADDR_DEFAULT (0)
#define ACAMERA_ISP_TARGETADDR_TARGET1_ADDR_DATASIZE (16)
#define ACAMERA_ISP_TARGETADDR_TARGET1_ADDR_OFFSET (0x23ec)
#define ACAMERA_ISP_TARGETADDR_TARGET1_ADDR_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_targetaddr_target1_addr_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b274);
    system_sw_write_32(base + 0x1b274, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_targetaddr_target1_addr_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b274) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: target2_addr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            The ISP generates an interrupt when the metering_awb module has written statistics in memory up to the configured value address. If this register is set to 0, this feature is disabled.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_TARGETADDR_TARGET2_ADDR_DEFAULT (0)
#define ACAMERA_ISP_TARGETADDR_TARGET2_ADDR_DATASIZE (16)
#define ACAMERA_ISP_TARGETADDR_TARGET2_ADDR_OFFSET (0x23ec)
#define ACAMERA_ISP_TARGETADDR_TARGET2_ADDR_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_targetaddr_target2_addr_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b274);
    system_sw_write_32(base + 0x1b274, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_targetaddr_target2_addr_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b274) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: metering aexp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Derives information for use by the AE and AWB modules
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Hist Thresh 0 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram threshold for bin 0/1 boundary
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_0_1_DEFAULT (0x10)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_0_1_DATASIZE (12)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_0_1_OFFSET (0x23f0)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_0_1_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_aexp_hist_thresh_0_1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b278);
    system_sw_write_32(base + 0x1b278, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_aexp_hist_thresh_0_1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b278) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Hist Thresh 1 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram threshold for bin 1/2 boundary
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_1_2_DEFAULT (0x20)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_1_2_DATASIZE (12)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_1_2_OFFSET (0x23f4)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_1_2_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_aexp_hist_thresh_1_2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b27c);
    system_sw_write_32(base + 0x1b27c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_aexp_hist_thresh_1_2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b27c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Hist Thresh 3 4
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram threshold for bin 2/3 boundary
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_3_4_DEFAULT (0xD0)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_3_4_DATASIZE (12)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_3_4_OFFSET (0x23f8)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_3_4_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_aexp_hist_thresh_3_4_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b280);
    system_sw_write_32(base + 0x1b280, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_aexp_hist_thresh_3_4_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b280) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Hist Thresh 4 5
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram threshold for bin 3/4 boundary
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_4_5_DEFAULT (0xE0)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_4_5_DATASIZE (12)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_4_5_OFFSET (0x23fc)
#define ACAMERA_ISP_METERING_AEXP_HIST_THRESH_4_5_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_aexp_hist_thresh_4_5_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b284);
    system_sw_write_32(base + 0x1b284, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_aexp_hist_thresh_4_5_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b284) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones horizontally for AE stats collection
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_NODES_USED_HORIZ_DEFAULT (15)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_HORIZ_DATASIZE (8)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_HORIZ_OFFSET (0x2410)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_HORIZ_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_metering_aexp_nodes_used_horiz_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b298);
    system_sw_write_32(base + 0x1b298, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_metering_aexp_nodes_used_horiz_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b298) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones vertically for AE stats collection
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AEXP_NODES_USED_VERT_DEFAULT (15)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_VERT_DATASIZE (8)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_VERT_OFFSET (0x2410)
#define ACAMERA_ISP_METERING_AEXP_NODES_USED_VERT_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_metering_aexp_nodes_used_vert_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b298);
    system_sw_write_32(base + 0x1b298, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_metering_aexp_nodes_used_vert_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b298) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Group: metering awb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: stats mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Statistics mode: 0 - legacy(G/R,B/R), 1 - current (R/G, B/G) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_STATS_MODE_DEFAULT (0)
#define ACAMERA_ISP_METERING_AWB_STATS_MODE_DATASIZE (1)
#define ACAMERA_ISP_METERING_AWB_STATS_MODE_OFFSET (0x2414)
#define ACAMERA_ISP_METERING_AWB_STATS_MODE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_metering_awb_stats_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b29c);
    system_sw_write_32(base + 0x1b29c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_metering_awb_stats_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b29c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: White Level AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Upper limit of valid data for AWB
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_WHITE_LEVEL_AWB_DEFAULT (0x3ff)
#define ACAMERA_ISP_METERING_AWB_WHITE_LEVEL_AWB_DATASIZE (10)
#define ACAMERA_ISP_METERING_AWB_WHITE_LEVEL_AWB_OFFSET (0x2418)
#define ACAMERA_ISP_METERING_AWB_WHITE_LEVEL_AWB_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_metering_awb_white_level_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2a0);
    system_sw_write_32(base + 0x1b2a0, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_metering_awb_white_level_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2a0) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Black Level AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Lower limit of valid data for AWB
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_BLACK_LEVEL_AWB_DEFAULT (0)
#define ACAMERA_ISP_METERING_AWB_BLACK_LEVEL_AWB_DATASIZE (10)
#define ACAMERA_ISP_METERING_AWB_BLACK_LEVEL_AWB_OFFSET (0x241c)
#define ACAMERA_ISP_METERING_AWB_BLACK_LEVEL_AWB_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_metering_awb_black_level_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2a4);
    system_sw_write_32(base + 0x1b2a4, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_metering_awb_black_level_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2a4) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cr Ref Max AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximum value of R/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CR_REF_MAX_AWB_DEFAULT (0x1FF)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MAX_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MAX_AWB_OFFSET (0x2420)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MAX_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cr_ref_max_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2a8);
    system_sw_write_32(base + 0x1b2a8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cr_ref_max_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2a8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cr Ref Min AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimum value of R/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CR_REF_MIN_AWB_DEFAULT (0x040)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MIN_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MIN_AWB_OFFSET (0x2424)
#define ACAMERA_ISP_METERING_AWB_CR_REF_MIN_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cr_ref_min_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2ac);
    system_sw_write_32(base + 0x1b2ac, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cr_ref_min_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2ac) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cb Ref Max AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximum value of B/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CB_REF_MAX_AWB_DEFAULT (0x1FF)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MAX_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MAX_AWB_OFFSET (0x2428)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MAX_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cb_ref_max_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2b0);
    system_sw_write_32(base + 0x1b2b0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cb_ref_max_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2b0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cb Ref Min AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimum value of B/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CB_REF_MIN_AWB_DEFAULT (0x040)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MIN_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MIN_AWB_OFFSET (0x242c)
#define ACAMERA_ISP_METERING_AWB_CB_REF_MIN_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cb_ref_min_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2b4);
    system_sw_write_32(base + 0x1b2b4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cb_ref_min_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2b4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones horizontally for AWB stats
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_NODES_USED_HORIZ_DEFAULT (15)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_HORIZ_DATASIZE (8)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_HORIZ_OFFSET (0x243c)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_HORIZ_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_metering_awb_nodes_used_horiz_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2c4);
    system_sw_write_32(base + 0x1b2c4, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_metering_awb_nodes_used_horiz_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b2c4) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones vertically for AWB stats
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_NODES_USED_VERT_DEFAULT (15)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_VERT_DATASIZE (8)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_VERT_OFFSET (0x243c)
#define ACAMERA_ISP_METERING_AWB_NODES_USED_VERT_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_metering_awb_nodes_used_vert_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2c4);
    system_sw_write_32(base + 0x1b2c4, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_metering_awb_nodes_used_vert_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b2c4) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Cr Ref High AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximum value of R/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CR_REF_HIGH_AWB_DEFAULT (0x1FF)
#define ACAMERA_ISP_METERING_AWB_CR_REF_HIGH_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CR_REF_HIGH_AWB_OFFSET (0x2440)
#define ACAMERA_ISP_METERING_AWB_CR_REF_HIGH_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cr_ref_high_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2c8);
    system_sw_write_32(base + 0x1b2c8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cr_ref_high_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2c8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cr Ref Low AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimum value of R/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CR_REF_LOW_AWB_DEFAULT (0x040)
#define ACAMERA_ISP_METERING_AWB_CR_REF_LOW_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CR_REF_LOW_AWB_OFFSET (0x2444)
#define ACAMERA_ISP_METERING_AWB_CR_REF_LOW_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cr_ref_low_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2cc);
    system_sw_write_32(base + 0x1b2cc, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cr_ref_low_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2cc) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cb Ref High AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximum value of B/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CB_REF_HIGH_AWB_DEFAULT (0x1FF)
#define ACAMERA_ISP_METERING_AWB_CB_REF_HIGH_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CB_REF_HIGH_AWB_OFFSET (0x2448)
#define ACAMERA_ISP_METERING_AWB_CB_REF_HIGH_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cb_ref_high_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2d0);
    system_sw_write_32(base + 0x1b2d0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cb_ref_high_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2d0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Cb Ref Low AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimum value of B/G for white region
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AWB_CB_REF_LOW_AWB_DEFAULT (0x040)
#define ACAMERA_ISP_METERING_AWB_CB_REF_LOW_AWB_DATASIZE (12)
#define ACAMERA_ISP_METERING_AWB_CB_REF_LOW_AWB_OFFSET (0x244c)
#define ACAMERA_ISP_METERING_AWB_CB_REF_LOW_AWB_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_metering_awb_cb_ref_low_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b2d4);
    system_sw_write_32(base + 0x1b2d4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_metering_awb_cb_ref_low_awb_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b2d4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: metering af
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: ROI Horiz Start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal starting coordinate of the Region of Interest (ROI)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_START_DEFAULT (0)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_START_DATASIZE (16)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_START_OFFSET (0x2880)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_START_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_metering_af_roi_horiz_start_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b708);
    system_sw_write_32(base + 0x1b708, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_metering_af_roi_horiz_start_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b708) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ROI Horiz End
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal ending coordinate of the Region of Interest (ROI)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_END_DEFAULT (0x77F)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_END_DATASIZE (16)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_END_OFFSET (0x2880)
#define ACAMERA_ISP_METERING_AF_ROI_HORIZ_END_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_metering_af_roi_horiz_end_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b708);
    system_sw_write_32(base + 0x1b708, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_metering_af_roi_horiz_end_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b708) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: ROI Vert Start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical starting coordinate of the Region of Interest (ROI)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_ROI_VERT_START_DEFAULT (0)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_START_DATASIZE (16)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_START_OFFSET (0x2884)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_START_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_metering_af_roi_vert_start_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b70c);
    system_sw_write_32(base + 0x1b70c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_metering_af_roi_vert_start_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b70c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ROI Vert End
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical ending coordinate of the Region of Interest (ROI)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_ROI_VERT_END_DEFAULT (0x437)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_END_DATASIZE (16)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_END_OFFSET (0x2884)
#define ACAMERA_ISP_METERING_AF_ROI_VERT_END_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_metering_af_roi_vert_end_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b70c);
    system_sw_write_32(base + 0x1b70c, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_metering_af_roi_vert_end_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b70c) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones horizontally for AF5 stats
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_NODES_USED_HORIZ_DEFAULT (15)
#define ACAMERA_ISP_METERING_AF_NODES_USED_HORIZ_DATASIZE (8)
#define ACAMERA_ISP_METERING_AF_NODES_USED_HORIZ_OFFSET (0x2888)
#define ACAMERA_ISP_METERING_AF_NODES_USED_HORIZ_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_metering_af_nodes_used_horiz_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b710);
    system_sw_write_32(base + 0x1b710, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_metering_af_nodes_used_horiz_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b710) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones vertically for AF5 stats
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_NODES_USED_VERT_DEFAULT (15)
#define ACAMERA_ISP_METERING_AF_NODES_USED_VERT_DATASIZE (8)
#define ACAMERA_ISP_METERING_AF_NODES_USED_VERT_OFFSET (0x2888)
#define ACAMERA_ISP_METERING_AF_NODES_USED_VERT_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_metering_af_nodes_used_vert_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b710);
    system_sw_write_32(base + 0x1b710, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_metering_af_nodes_used_vert_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b710) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Channel Mask
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             Mask for discarding selected color channels.
//             For example 
//             R  Gr
//             Gb B
//             Bit[3] corresponds to top left color of CFA pattern (R in the example CFA above)
//             Bit[2] corresponds to top right color of CFA pattern (Gr in the example CFA above)
//             Bit[1] corresponds to bottom left color of CFA pattern (Gb in the example CFA above)
//             Bit[0] corresponds to bottom right color of CFA pattern (B in the example CFA above)
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_CHANNEL_MASK_DEFAULT (0xF)
#define ACAMERA_ISP_METERING_AF_CHANNEL_MASK_DATASIZE (4)
#define ACAMERA_ISP_METERING_AF_CHANNEL_MASK_OFFSET (0x288c)
#define ACAMERA_ISP_METERING_AF_CHANNEL_MASK_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_metering_af_channel_mask_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b714);
    system_sw_write_32(base + 0x1b714, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_metering_af_channel_mask_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b714) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Black Level
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Black level for AF module
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_BLACK_LEVEL_DEFAULT (0xF000)
#define ACAMERA_ISP_METERING_AF_BLACK_LEVEL_DATASIZE (20)
#define ACAMERA_ISP_METERING_AF_BLACK_LEVEL_OFFSET (0x2890)
#define ACAMERA_ISP_METERING_AF_BLACK_LEVEL_MASK (0xfffff)

// args: data (20-bit)
static __inline void acamera_isp_metering_af_black_level_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b718);
    system_sw_write_32(base + 0x1b718, (((uint32_t) (data & 0xfffff)) << 0) | (curr & 0xfff00000));
}
static __inline uint32_t acamera_isp_metering_af_black_level_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1b718) & 0xfffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: FIR Coeffs Center
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Center column (c) coefficients of 3x9 AF5 Kernel (signed 2's complement)
//              [ s[ 1:0 ] s[ 3:2 ] s[ 5:4 ] s[ 7:6 ] c[6:0] s[ 9:8 ] s[11:10] s[13:12] s[15:14] ]
//              [     0        0        0        0        0      0        0        0        0    ]
//              [ s[17:16] s[19:18] s[21:20] s[23:22] c[8:7] s[25:24] s[27:26] s[29:28] s[31:30] ]
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_CENTER_DEFAULT (0x185)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_CENTER_DATASIZE (9)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_CENTER_OFFSET (0x2894)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_CENTER_MASK (0x1ff)

// args: data (9-bit)
static __inline void acamera_isp_metering_af_fir_coeffs_center_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b71c);
    system_sw_write_32(base + 0x1b71c, (((uint32_t) (data & 0x1ff)) << 0) | (curr & 0xfffffe00));
}
static __inline uint16_t acamera_isp_metering_af_fir_coeffs_center_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b71c) & 0x1ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: FIR Coeffs Sides
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//              Side column (s) coefficients of 3x9 AF5 Kernel (signed 2's complement)
//              [ s[ 1:0 ] s[ 3:2 ] s[ 5:4 ] s[ 7:6 ] c[6:0] s[ 9:8 ] s[11:10] s[13:12] s[15:14] ]
//              [     0        0        0        0        0      0        0        0        0    ]
//              [ s[17:16] s[19:18] s[21:20] s[23:22] c[8:7] s[25:24] s[27:26] s[29:28] s[31:30] ]
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SIDES_DEFAULT (0xC003C003)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SIDES_DATASIZE (32)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SIDES_OFFSET (0x2898)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SIDES_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_metering_af_fir_coeffs_sides_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1b720, data);
}
static __inline uint32_t acamera_isp_metering_af_fir_coeffs_sides_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b720);
}
// ------------------------------------------------------------------------------ //
// Register: FIR Coeffs Shift
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Shift amount of FIR filtering result
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SHIFT_DEFAULT (0x3)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SHIFT_DATASIZE (3)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SHIFT_OFFSET (0x289c)
#define ACAMERA_ISP_METERING_AF_FIR_COEFFS_SHIFT_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_metering_af_fir_coeffs_shift_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b724);
    system_sw_write_32(base + 0x1b724, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_metering_af_fir_coeffs_shift_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b724) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: AR Coeffs Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AR coefficients on horizontal direction (a1:[7:0] format signed 2's complement 2.6, a2:[13:8] format unsigned 0.6) (feedback part of IIR)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_AR_COEFFS_HORIZ_DEFAULT (0x1FA6)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_HORIZ_DATASIZE (14)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_HORIZ_OFFSET (0x28a0)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_HORIZ_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_metering_af_ar_coeffs_horiz_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b728);
    system_sw_write_32(base + 0x1b728, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_metering_af_ar_coeffs_horiz_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b728) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: AR Coeffs Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// AR coefficients on vertical direction (a1:[7:0] format signed 2's complement 2.6, a2:[13:8] format unsigned 0.6) (feedback part of IIR)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_AF_AR_COEFFS_VERT_DEFAULT (0x1FAA)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_VERT_DATASIZE (14)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_VERT_OFFSET (0x28a4)
#define ACAMERA_ISP_METERING_AF_AR_COEFFS_VERT_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_metering_af_ar_coeffs_vert_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b72c);
    system_sw_write_32(base + 0x1b72c, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_metering_af_ar_coeffs_vert_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1b72c) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: metering hist aexp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: skip x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram decimation in horizontal direction: 0=every 2nd pixel; 1=every 3rd pixel; 2=every 4th pixel; 3=every 5th pixel; 4=every 8th pixel ; 5+=every 9th pixel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_X_DEFAULT (1)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_X_DATASIZE (3)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_X_OFFSET (0x28a8)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_X_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_metering_hist_aexp_skip_x_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b730);
    system_sw_write_32(base + 0x1b730, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_skip_x_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b730) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: skip y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram decimation in vertical direction: 0=every pixel; 1=every 2nd pixel; 2=every 3rd pixel; 3=every 4th pixel; 4=every 5th pixel; 5=every 8th pixel ; 6+=every 9th pixel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_Y_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_Y_DATASIZE (3)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_Y_OFFSET (0x28a8)
#define ACAMERA_ISP_METERING_HIST_AEXP_SKIP_Y_MASK (0x70)

// args: data (3-bit)
static __inline void acamera_isp_metering_hist_aexp_skip_y_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b730);
    system_sw_write_32(base + 0x1b730, (((uint32_t) (data & 0x7)) << 4) | (curr & 0xffffff8f));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_skip_y_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b730) & 0x70) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: offset x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= start from the first column;  1=start from second column
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_X_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_X_DATASIZE (1)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_X_OFFSET (0x28a8)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_X_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_metering_hist_aexp_offset_x_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b730);
    system_sw_write_32(base + 0x1b730, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_offset_x_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b730) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: offset y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= start from the first row; 1= start from second row
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_Y_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_Y_DATASIZE (1)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_Y_OFFSET (0x28a8)
#define ACAMERA_ISP_METERING_HIST_AEXP_OFFSET_Y_MASK (0x80)

// args: data (1-bit)
static __inline void acamera_isp_metering_hist_aexp_offset_y_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b730);
    system_sw_write_32(base + 0x1b730, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_offset_y_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b730) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: scale bottom
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// scale of bottom half of the range: 0=1x ,1=2x, 2=4x, 4=8x, 4=16x
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_BOTTOM_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_BOTTOM_DATASIZE (4)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_BOTTOM_OFFSET (0x28ac)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_BOTTOM_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_metering_hist_aexp_scale_bottom_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b734);
    system_sw_write_32(base + 0x1b734, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_scale_bottom_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b734) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: scale top
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// scale of top half of the range: 0=1x ,1=2x, 2=4x, 4=8x, 4=16x
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_TOP_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_TOP_DATASIZE (4)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_TOP_OFFSET (0x28ac)
#define ACAMERA_ISP_METERING_HIST_AEXP_SCALE_TOP_MASK (0xf0)

// args: data (4-bit)
static __inline void acamera_isp_metering_hist_aexp_scale_top_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b734);
    system_sw_write_32(base + 0x1b734, (((uint32_t) (data & 0xf)) << 4) | (curr & 0xffffff0f));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_scale_top_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b734) & 0xf0) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Total Pixels
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total number of pixels processed (skip x and skip y are taken into account)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_TOTAL_PIXELS_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_TOTAL_PIXELS_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_TOTAL_PIXELS_OFFSET (0x28b0)
#define ACAMERA_ISP_METERING_HIST_AEXP_TOTAL_PIXELS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_total_pixels_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b738);
}
// ------------------------------------------------------------------------------ //
// Register: Counted Pixels
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of pixels accumulated (with nonzero weight) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_COUNTED_PIXELS_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_COUNTED_PIXELS_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_COUNTED_PIXELS_OFFSET (0x28b4)
#define ACAMERA_ISP_METERING_HIST_AEXP_COUNTED_PIXELS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_counted_pixels_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b73c);
}
// ------------------------------------------------------------------------------ //
// Register: Plane mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane separation mode
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_DEFAULT (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_DATASIZE (3)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_OFFSET (0x28b8)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_MASK (0x7)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_ALL_THE_PLANES_IN_ONE_HISTOGRAM (0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_4_BAYER_PLANES_INTO_4_SEPARATE_BANKS (1)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_RESERVED_2 (2)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_RESERVED_3 (3)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_ODD__X_ODD__Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (4)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_EVEN_X_ODD__Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (5)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_ODD__X_EVEN_Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (6)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_MODE_COLLECT_EVEN_X_EVEN_Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (7)

// args: data (3-bit)
static __inline void acamera_isp_metering_hist_aexp_plane_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b740);
    system_sw_write_32(base + 0x1b740, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_plane_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b740) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_0_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_0_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_0_OFFSET (0x28bc)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_0_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_total_0_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b744);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 1
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_1_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_1_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_1_OFFSET (0x28c0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_1_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_total_1_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b748);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 2
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_2_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_2_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_2_OFFSET (0x28c4)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_2_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_total_2_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b74c);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 3
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_3_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_3_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_3_OFFSET (0x28c8)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_TOTAL_3_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_total_3_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b750);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_0_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_0_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_0_OFFSET (0x28cc)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_0_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_counted_0_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b754);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 1
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_1_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_1_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_1_OFFSET (0x28d0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_1_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_counted_1_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b758);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 2
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_2_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_2_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_2_OFFSET (0x28d4)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_2_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_counted_2_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b75c);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 3
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_3_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_3_DATASIZE (32)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_3_OFFSET (0x28d8)
#define ACAMERA_ISP_METERING_HIST_AEXP_PLANE_COUNTED_3_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_hist_aexp_plane_counted_3_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1b760);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones horizontally for Histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DEFAULT (15)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_DATASIZE (8)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_OFFSET (0x28dc)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_HORIZ_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_metering_hist_aexp_nodes_used_horiz_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b764);
    system_sw_write_32(base + 0x1b764, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_nodes_used_horiz_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b764) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones vertically for Histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_DEFAULT (15)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_DATASIZE (8)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_OFFSET (0x28dc)
#define ACAMERA_ISP_METERING_HIST_AEXP_NODES_USED_VERT_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_metering_hist_aexp_nodes_used_vert_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1b764);
    system_sw_write_32(base + 0x1b764, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_metering_hist_aexp_nodes_used_vert_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1b764) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Zones Weight
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sets zone weighting for Histogram. Index is (row,col) where (0,0) is top-left zone
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_HIST_AEXP_ZONES_WEIGHT_DEFAULT (0xF)
#define ACAMERA_ISP_METERING_HIST_AEXP_ZONES_WEIGHT_DATASIZE (4)
#define ACAMERA_ISP_METERING_HIST_AEXP_ZONES_WEIGHT_OFFSET (0x28e0)
#define ACAMERA_ISP_METERING_HIST_AEXP_ZONES_WEIGHT_MASK (0xf)

// index (0-224), args: data (4-bit)
static __inline void acamera_isp_metering_hist_aexp_zones_weight_write( uintptr_t base, uint32_t index,uint8_t data ) {
    uintptr_t addr = base + 0x1b768 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    uint32_t curr = system_sw_read_32( addr );
    system_sw_write_32( addr, ( (uint32_t)data << offset ) | ( curr & ~( 0xFF << offset ) ) );
}
static __inline uint8_t acamera_isp_metering_hist_aexp_zones_weight_read( uintptr_t base, uint32_t index ) {
    uintptr_t addr = base + 0x1b768 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    return (uint8_t)( system_sw_read_32( addr ) >> offset );
}
// ------------------------------------------------------------------------------ //
// Group: metering ihist
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: skip x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram decimation in horizontal direction: 0=every 2nd pixel; 1=every 3rd pixel; 2=every 4th pixel; 3=every 5th pixel; 4=every 8th pixel ; 5+=every 9th pixel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_SKIP_X_DEFAULT (1)
#define ACAMERA_ISP_METERING_IHIST_SKIP_X_DATASIZE (3)
#define ACAMERA_ISP_METERING_IHIST_SKIP_X_OFFSET (0x2d24)
#define ACAMERA_ISP_METERING_IHIST_SKIP_X_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_metering_ihist_skip_x_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbac);
    system_sw_write_32(base + 0x1bbac, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_metering_ihist_skip_x_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbac) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: skip y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Histogram decimation in vertical direction: 0=every pixel; 1=every 2nd pixel; 2=every 3rd pixel; 3=every 4th pixel; 4=every 5th pixel; 5=every 8th pixel ; 6+=every 9th pixel
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_SKIP_Y_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_SKIP_Y_DATASIZE (3)
#define ACAMERA_ISP_METERING_IHIST_SKIP_Y_OFFSET (0x2d24)
#define ACAMERA_ISP_METERING_IHIST_SKIP_Y_MASK (0x70)

// args: data (3-bit)
static __inline void acamera_isp_metering_ihist_skip_y_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbac);
    system_sw_write_32(base + 0x1bbac, (((uint32_t) (data & 0x7)) << 4) | (curr & 0xffffff8f));
}
static __inline uint8_t acamera_isp_metering_ihist_skip_y_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbac) & 0x70) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: offset x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= start from the first column;  1=start from second column
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_OFFSET_X_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_X_DATASIZE (1)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_X_OFFSET (0x2d24)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_X_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_metering_ihist_offset_x_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbac);
    system_sw_write_32(base + 0x1bbac, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_metering_ihist_offset_x_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbac) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: offset y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= start from the first row; 1= start from second row
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_OFFSET_Y_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_Y_DATASIZE (1)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_Y_OFFSET (0x2d24)
#define ACAMERA_ISP_METERING_IHIST_OFFSET_Y_MASK (0x80)

// args: data (1-bit)
static __inline void acamera_isp_metering_ihist_offset_y_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbac);
    system_sw_write_32(base + 0x1bbac, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_metering_ihist_offset_y_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbac) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: scale bottom
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// scale of bottom half of the range: 0=1x ,1=2x, 2=4x, 4=8x, 4=16x
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_SCALE_BOTTOM_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_SCALE_BOTTOM_DATASIZE (4)
#define ACAMERA_ISP_METERING_IHIST_SCALE_BOTTOM_OFFSET (0x2d28)
#define ACAMERA_ISP_METERING_IHIST_SCALE_BOTTOM_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_metering_ihist_scale_bottom_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbb0);
    system_sw_write_32(base + 0x1bbb0, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_metering_ihist_scale_bottom_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbb0) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: scale top
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// scale of top half of the range: 0=1x ,1=2x, 2=4x, 4=8x, 4=16x
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_SCALE_TOP_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_SCALE_TOP_DATASIZE (4)
#define ACAMERA_ISP_METERING_IHIST_SCALE_TOP_OFFSET (0x2d28)
#define ACAMERA_ISP_METERING_IHIST_SCALE_TOP_MASK (0xf0)

// args: data (4-bit)
static __inline void acamera_isp_metering_ihist_scale_top_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbb0);
    system_sw_write_32(base + 0x1bbb0, (((uint32_t) (data & 0xf)) << 4) | (curr & 0xffffff0f));
}
static __inline uint8_t acamera_isp_metering_ihist_scale_top_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbb0) & 0xf0) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Total Pixels
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total number of pixels processed (skip x and skip y are taken into account)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_TOTAL_PIXELS_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_TOTAL_PIXELS_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_TOTAL_PIXELS_OFFSET (0x2d2c)
#define ACAMERA_ISP_METERING_IHIST_TOTAL_PIXELS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_total_pixels_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbb4);
}
// ------------------------------------------------------------------------------ //
// Register: Counted Pixels
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of pixels accumulated (with nonzero weight) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_COUNTED_PIXELS_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_COUNTED_PIXELS_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_COUNTED_PIXELS_OFFSET (0x2d30)
#define ACAMERA_ISP_METERING_IHIST_COUNTED_PIXELS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_counted_pixels_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbb8);
}
// ------------------------------------------------------------------------------ //
// Register: Plane mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane separation mode
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_DEFAULT (0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_DATASIZE (3)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_OFFSET (0x2d34)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_MASK (0x7)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_ALL_THE_PLANES_IN_ONE_HISTOGRAM (0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_4_BAYER_PLANES_INTO_4_SEPARATE_BANKS (1)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_RESERVED_2 (2)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_RESERVED_3 (3)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_ODD__X_ODD__Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (4)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_EVEN_X_ODD__Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (5)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_ODD__X_EVEN_Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (6)
#define ACAMERA_ISP_METERING_IHIST_PLANE_MODE_COLLECT_EVEN_X_EVEN_Y_PLANE_TO_BANK_0_REST_TO_BANK_1 (7)

// args: data (3-bit)
static __inline void acamera_isp_metering_ihist_plane_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbbc);
    system_sw_write_32(base + 0x1bbbc, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_metering_ihist_plane_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbbc) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_0_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_0_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_0_OFFSET (0x2d38)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_0_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_total_0_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbc0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 1
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_1_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_1_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_1_OFFSET (0x2d3c)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_1_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_total_1_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbc4);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 2
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_2_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_2_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_2_OFFSET (0x2d40)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_2_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_total_2_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbc8);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Total 3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels processed for plane 3
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_3_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_3_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_3_OFFSET (0x2d44)
#define ACAMERA_ISP_METERING_IHIST_PLANE_TOTAL_3_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_total_3_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbcc);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 0
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_0_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_0_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_0_OFFSET (0x2d48)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_0_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_counted_0_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbd0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 1
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_1_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_1_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_1_OFFSET (0x2d4c)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_1_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_counted_1_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbd4);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 2
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_2_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_2_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_2_OFFSET (0x2d50)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_2_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_counted_2_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbd8);
}
// ------------------------------------------------------------------------------ //
// Register: Plane Counted 3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Total pixels accumulated for plane 3
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_3_DEFAULT (0x0)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_3_DATASIZE (32)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_3_OFFSET (0x2d54)
#define ACAMERA_ISP_METERING_IHIST_PLANE_COUNTED_3_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_metering_ihist_plane_counted_3_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1bbdc);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Horiz
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones horizontally for Histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_NODES_USED_HORIZ_DEFAULT (15)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_HORIZ_DATASIZE (8)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_HORIZ_OFFSET (0x2d58)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_HORIZ_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_metering_ihist_nodes_used_horiz_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbe0);
    system_sw_write_32(base + 0x1bbe0, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_metering_ihist_nodes_used_horiz_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbe0) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Nodes Used Vert
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Number of active zones vertically for Histogram
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_NODES_USED_VERT_DEFAULT (15)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_VERT_DATASIZE (8)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_VERT_OFFSET (0x2d58)
#define ACAMERA_ISP_METERING_IHIST_NODES_USED_VERT_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_metering_ihist_nodes_used_vert_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1bbe0);
    system_sw_write_32(base + 0x1bbe0, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_metering_ihist_nodes_used_vert_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1bbe0) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Zones Weight
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sets zone weighting for Histogram. Index is (row,col) where (0,0) is top-left zone
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_METERING_IHIST_ZONES_WEIGHT_DEFAULT (0xF)
#define ACAMERA_ISP_METERING_IHIST_ZONES_WEIGHT_DATASIZE (4)
#define ACAMERA_ISP_METERING_IHIST_ZONES_WEIGHT_OFFSET (0x2d5c)
#define ACAMERA_ISP_METERING_IHIST_ZONES_WEIGHT_MASK (0xf)

// index (0-224), args: data (4-bit)
static __inline void acamera_isp_metering_ihist_zones_weight_write( uintptr_t base, uint32_t index,uint8_t data ) {
    uintptr_t addr = base + 0x1bbe4 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    uint32_t curr = system_sw_read_32( addr );
    system_sw_write_32( addr, ( (uint32_t)data << offset ) | ( curr & ~( 0xFF << offset ) ) );
}
static __inline uint8_t acamera_isp_metering_ihist_zones_weight_read( uintptr_t base, uint32_t index ) {
    uintptr_t addr = base + 0x1bbe4 + ( index & 0xFFFFFFFC );
    uint8_t offset = ( index & 3 ) << 3;
    return (uint8_t)( system_sw_read_32( addr ) >> offset );
}
// ------------------------------------------------------------------------------ //
// Group: fr crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Crop for full resolution output
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Crop enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CROP_ENABLE_CROP_DEFAULT (0)
#define ACAMERA_ISP_FR_CROP_ENABLE_CROP_DATASIZE (1)
#define ACAMERA_ISP_FR_CROP_ENABLE_CROP_OFFSET (0x31a0)
#define ACAMERA_ISP_FR_CROP_ENABLE_CROP_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_crop_enable_crop_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c028);
    system_sw_write_32(base + 0x1c028, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_crop_enable_crop_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c028) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: start x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal offset from left side of image in pixels for output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CROP_START_X_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_CROP_START_X_DATASIZE (16)
#define ACAMERA_ISP_FR_CROP_START_X_OFFSET (0x31a4)
#define ACAMERA_ISP_FR_CROP_START_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_crop_start_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c02c);
    system_sw_write_32(base + 0x1c02c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_crop_start_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c02c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: start y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical offset from top of image in lines for output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CROP_START_Y_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_CROP_START_Y_DATASIZE (16)
#define ACAMERA_ISP_FR_CROP_START_Y_OFFSET (0x31a8)
#define ACAMERA_ISP_FR_CROP_START_Y_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_crop_start_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c030);
    system_sw_write_32(base + 0x1c030, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_crop_start_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c030) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: size x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// width of output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CROP_SIZE_X_DEFAULT (0xffff)
#define ACAMERA_ISP_FR_CROP_SIZE_X_DATASIZE (16)
#define ACAMERA_ISP_FR_CROP_SIZE_X_OFFSET (0x31ac)
#define ACAMERA_ISP_FR_CROP_SIZE_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_crop_size_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c034);
    system_sw_write_32(base + 0x1c034, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_crop_size_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c034) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: size y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// height of output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CROP_SIZE_Y_DEFAULT (0xffff)
#define ACAMERA_ISP_FR_CROP_SIZE_Y_DATASIZE (16)
#define ACAMERA_ISP_FR_CROP_SIZE_Y_OFFSET (0x31b0)
#define ACAMERA_ISP_FR_CROP_SIZE_Y_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_crop_size_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c038);
    system_sw_write_32(base + 0x1c038, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_crop_size_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c038) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr scaler
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Timeout Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 : Timeout disabled.  
//        1 : Timeout enabled.  Automatic frame reset if frame has not completed after anticipated time.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_TIMEOUT_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_ENABLE_OFFSET (0x31b8)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_ENABLE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_fr_scaler_timeout_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c040);
    system_sw_write_32(base + 0x1c040, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_fr_scaler_timeout_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c040) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Timeout Value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Timeout count in vcke cycles, from field. Configure to min( 65535, 8*(output_width+32) ) 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_TIMEOUT_VALUE_DEFAULT (0x2900)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_VALUE_DATASIZE (16)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_VALUE_OFFSET (0x31b8)
#define ACAMERA_ISP_FR_SCALER_TIMEOUT_VALUE_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_scaler_timeout_value_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c040);
    system_sw_write_32(base + 0x1c040, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_scaler_timeout_value_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c040) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: WIDTH
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Input frame width in pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_FR_SCALER_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_FR_SCALER_WIDTH_OFFSET (0x31bc)
#define ACAMERA_ISP_FR_SCALER_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_scaler_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c044);
    system_sw_write_32(base + 0x1c044, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_scaler_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c044) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HEIGHT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Input frame height in lines
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_FR_SCALER_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_FR_SCALER_HEIGHT_OFFSET (0x31c0)
#define ACAMERA_ISP_FR_SCALER_HEIGHT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_scaler_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c048);
    system_sw_write_32(base + 0x1c048, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_scaler_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c048) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: OWIDTH
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Output frame width in pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_OWIDTH_DEFAULT (0x500)
#define ACAMERA_ISP_FR_SCALER_OWIDTH_DATASIZE (16)
#define ACAMERA_ISP_FR_SCALER_OWIDTH_OFFSET (0x31c4)
#define ACAMERA_ISP_FR_SCALER_OWIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_scaler_owidth_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c04c);
    system_sw_write_32(base + 0x1c04c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_scaler_owidth_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c04c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: OHEIGHT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Output frame height in lines
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_OHEIGHT_DEFAULT (0x2D0)
#define ACAMERA_ISP_FR_SCALER_OHEIGHT_DATASIZE (16)
#define ACAMERA_ISP_FR_SCALER_OHEIGHT_OFFSET (0x31c8)
#define ACAMERA_ISP_FR_SCALER_OHEIGHT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_scaler_oheight_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c050);
    system_sw_write_32(base + 0x1c050, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_scaler_oheight_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c050) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HFILT_TINC
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal scaling factor
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_HFILT_TINC_DEFAULT (0x180000)
#define ACAMERA_ISP_FR_SCALER_HFILT_TINC_DATASIZE (24)
#define ACAMERA_ISP_FR_SCALER_HFILT_TINC_OFFSET (0x31cc)
#define ACAMERA_ISP_FR_SCALER_HFILT_TINC_MASK (0xffffff)

// args: data (24-bit)
static __inline void acamera_isp_fr_scaler_hfilt_tinc_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c054);
    system_sw_write_32(base + 0x1c054, (((uint32_t) (data & 0xffffff)) << 0) | (curr & 0xff000000));
}
static __inline uint32_t acamera_isp_fr_scaler_hfilt_tinc_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1c054) & 0xffffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HFILT_COEFSET
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        HFILT Coeff. control.  
//        HFILT_COEFSET[3:0] - Selects horizontal Coef set for scaler.
//            0000 : use set 0
//            0001 : use set 1
//            ...... 
//            0111 : use set 7
//            ...... 
//            1111 : use set 15
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_HFILT_COEFSET_DEFAULT (0x00)
#define ACAMERA_ISP_FR_SCALER_HFILT_COEFSET_DATASIZE (4)
#define ACAMERA_ISP_FR_SCALER_HFILT_COEFSET_OFFSET (0x31d0)
#define ACAMERA_ISP_FR_SCALER_HFILT_COEFSET_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_fr_scaler_hfilt_coefset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c058);
    system_sw_write_32(base + 0x1c058, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_fr_scaler_hfilt_coefset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c058) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: VFILT_TINC
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// VFILT TINC
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_VFILT_TINC_DEFAULT (0x180000)
#define ACAMERA_ISP_FR_SCALER_VFILT_TINC_DATASIZE (24)
#define ACAMERA_ISP_FR_SCALER_VFILT_TINC_OFFSET (0x31d4)
#define ACAMERA_ISP_FR_SCALER_VFILT_TINC_MASK (0xffffff)

// args: data (24-bit)
static __inline void acamera_isp_fr_scaler_vfilt_tinc_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c05c);
    system_sw_write_32(base + 0x1c05c, (((uint32_t) (data & 0xffffff)) << 0) | (curr & 0xff000000));
}
static __inline uint32_t acamera_isp_fr_scaler_vfilt_tinc_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1c05c) & 0xffffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: VFILT_COEFSET
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        VFILT Coeff. control
//        FILT_COEFSET[3:0] - Selects vertical Coef set for scaler
//            0000 : use set 0
//            0001 : use set 1
//            ...... 
//            0111 : use set 7
//            ...... 
//            1111 : use set 15
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SCALER_VFILT_COEFSET_DEFAULT (0x00)
#define ACAMERA_ISP_FR_SCALER_VFILT_COEFSET_DATASIZE (4)
#define ACAMERA_ISP_FR_SCALER_VFILT_COEFSET_OFFSET (0x31d8)
#define ACAMERA_ISP_FR_SCALER_VFILT_COEFSET_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_fr_scaler_vfilt_coefset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c060);
    system_sw_write_32(base + 0x1c060, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_fr_scaler_vfilt_coefset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c060) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr gamma rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gamma correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gamma enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_FR_GAMMA_RGB_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_FR_GAMMA_RGB_ENABLE_OFFSET (0x31dc)
#define ACAMERA_ISP_FR_GAMMA_RGB_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_gamma_rgb_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c064);
    system_sw_write_32(base + 0x1c064, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_gamma_rgb_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c064) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the R chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_R_DEFAULT (0x100)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_R_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_R_OFFSET (0x31e0)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_gain_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c068);
    system_sw_write_32(base + 0x1c068, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_gain_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c068) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_g
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the G chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_G_DEFAULT (0x100)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_G_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_G_OFFSET (0x31e0)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_G_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_gain_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c068);
    system_sw_write_32(base + 0x1c068, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_gain_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c068) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: gain_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the B chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_B_DEFAULT (0x100)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_B_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_B_OFFSET (0x31e4)
#define ACAMERA_ISP_FR_GAMMA_RGB_GAIN_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_gain_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c06c);
    system_sw_write_32(base + 0x1c06c, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_gain_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c06c) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the R chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_R_DEFAULT (0)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_R_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_R_OFFSET (0x31e8)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_offset_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c070);
    system_sw_write_32(base + 0x1c070, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_offset_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c070) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset_g
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the G chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_G_DEFAULT (0)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_G_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_G_OFFSET (0x31e8)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_G_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_offset_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c070);
    system_sw_write_32(base + 0x1c070, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_offset_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c070) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: offset_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the B chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_B_DEFAULT (0)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_B_DATASIZE (12)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_B_OFFSET (0x31ec)
#define ACAMERA_ISP_FR_GAMMA_RGB_OFFSET_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_fr_gamma_rgb_offset_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c074);
    system_sw_write_32(base + 0x1c074, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_fr_gamma_rgb_offset_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c074) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpening enable: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_FR_SHARPEN_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_FR_SHARPEN_ENABLE_OFFSET (0x31f0)
#define ACAMERA_ISP_FR_SHARPEN_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_sharpen_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c078);
    system_sw_write_32(base + 0x1c078, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_sharpen_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c078) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Controls strength of sharpening effect. u5.4
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_STRENGTH_DEFAULT (0x10)
#define ACAMERA_ISP_FR_SHARPEN_STRENGTH_DATASIZE (9)
#define ACAMERA_ISP_FR_SHARPEN_STRENGTH_OFFSET (0x31f4)
#define ACAMERA_ISP_FR_SHARPEN_STRENGTH_MASK (0x1ff)

// args: data (9-bit)
static __inline void acamera_isp_fr_sharpen_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c07c);
    system_sw_write_32(base + 0x1c07c, (((uint32_t) (data & 0x1ff)) << 0) | (curr & 0xfffffe00));
}
static __inline uint16_t acamera_isp_fr_sharpen_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c07c) & 0x1ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Control R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma transform red coefficient. u0.8 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_CONTROL_R_DEFAULT (0x4C)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_R_DATASIZE (8)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_R_OFFSET (0x31f8)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_R_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_fr_sharpen_control_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c080);
    system_sw_write_32(base + 0x1c080, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_fr_sharpen_control_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c080) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Control B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma transform blue coefficient. u0.8 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_CONTROL_B_DEFAULT (0x1E)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_B_DATASIZE (8)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_B_OFFSET (0x31f8)
#define ACAMERA_ISP_FR_SHARPEN_CONTROL_B_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_fr_sharpen_control_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c080);
    system_sw_write_32(base + 0x1c080, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_fr_sharpen_control_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c080) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Alpha Undershoot
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Alpha blending of undershoot and overshoot u0.7, 0 = only undershoot, 255 = only overshoot
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_ALPHA_UNDERSHOOT_DEFAULT (0x13)
#define ACAMERA_ISP_FR_SHARPEN_ALPHA_UNDERSHOOT_DATASIZE (8)
#define ACAMERA_ISP_FR_SHARPEN_ALPHA_UNDERSHOOT_OFFSET (0x31f8)
#define ACAMERA_ISP_FR_SHARPEN_ALPHA_UNDERSHOOT_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_fr_sharpen_alpha_undershoot_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c080);
    system_sw_write_32(base + 0x1c080, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_fr_sharpen_alpha_undershoot_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c080) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Thresh Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma threshold below this value, no sharpening will be applied. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_LOW_DEFAULT (0x000)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_LOW_DATASIZE (10)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_LOW_OFFSET (0x31fc)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_LOW_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_sharpen_luma_thresh_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c084);
    system_sw_write_32(base + 0x1c084, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_sharpen_luma_thresh_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c084) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Offset Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma offset (min value) of the region of less than Luma Thresh Low.  
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_LOW_DEFAULT (0x000)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_LOW_DATASIZE (8)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_LOW_OFFSET (0x31fc)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_LOW_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_fr_sharpen_luma_offset_low_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c084);
    system_sw_write_32(base + 0x1c084, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_fr_sharpen_luma_offset_low_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c084) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Slope Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma linear threshold slope at dark luminance region 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_LOW_DEFAULT (0x03FC)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_LOW_DATASIZE (16)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_LOW_OFFSET (0x3200)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_LOW_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_sharpen_luma_slope_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c088);
    system_sw_write_32(base + 0x1c088, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_sharpen_luma_slope_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c088) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Thresh High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma threshold above this value, sharpening level will be decreased. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_HIGH_DEFAULT (0x332)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_HIGH_DATASIZE (10)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_HIGH_OFFSET (0x3200)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_THRESH_HIGH_MASK (0x3ff0000)

// args: data (10-bit)
static __inline void acamera_isp_fr_sharpen_luma_thresh_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c088);
    system_sw_write_32(base + 0x1c088, (((uint32_t) (data & 0x3ff)) << 16) | (curr & 0xfc00ffff));
}
static __inline uint16_t acamera_isp_fr_sharpen_luma_thresh_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c088) & 0x3ff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Offset High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma offset (min value) of the region of more than Luma Thresh High.  
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_HIGH_DEFAULT (0x000)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_HIGH_DATASIZE (8)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_HIGH_OFFSET (0x3204)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_OFFSET_HIGH_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_fr_sharpen_luma_offset_high_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c08c);
    system_sw_write_32(base + 0x1c08c, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_fr_sharpen_luma_offset_high_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c08c) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Slope High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma linear threshold slope at bright luminance region 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_HIGH_DEFAULT (0x06A4)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_HIGH_DATASIZE (16)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_HIGH_OFFSET (0x3204)
#define ACAMERA_ISP_FR_SHARPEN_LUMA_SLOPE_HIGH_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_sharpen_luma_slope_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c08c);
    system_sw_write_32(base + 0x1c08c, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_sharpen_luma_slope_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c08c) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Clip Str Max
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clips sharpening mask of max value. This will control overshoot. U0.14. (0 ~ 16383) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MAX_DEFAULT (0x3FFF)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MAX_DATASIZE (14)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MAX_OFFSET (0x3208)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MAX_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_fr_sharpen_clip_str_max_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c090);
    system_sw_write_32(base + 0x1c090, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_fr_sharpen_clip_str_max_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c090) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip Str Min
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clips sharpening mask of min value. This will control undershoot. U0.14. It is used as negative value. (0 ~ -16383)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MIN_DEFAULT (0x00CD)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MIN_DATASIZE (14)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MIN_OFFSET (0x3208)
#define ACAMERA_ISP_FR_SHARPEN_CLIP_STR_MIN_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_fr_sharpen_clip_str_min_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c090);
    system_sw_write_32(base + 0x1c090, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_fr_sharpen_clip_str_min_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c090) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Debug
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  To support different debug output. 0 = normal operation, 1 = luma, 2 = sharpening mask 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_SHARPEN_DEBUG_DEFAULT (0)
#define ACAMERA_ISP_FR_SHARPEN_DEBUG_DATASIZE (4)
#define ACAMERA_ISP_FR_SHARPEN_DEBUG_OFFSET (0x320c)
#define ACAMERA_ISP_FR_SHARPEN_DEBUG_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_fr_sharpen_debug_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c094);
    system_sw_write_32(base + 0x1c094, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_fr_sharpen_debug_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c094) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr cs conv
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Conversion of RGB to YUV data using a 3x3 color matrix plus offsets
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable matrix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Color matrix enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_ENABLE_MATRIX_DEFAULT (0)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_MATRIX_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_MATRIX_OFFSET (0x3210)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_MATRIX_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_enable_matrix_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c098);
    system_sw_write_32(base + 0x1c098, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_cs_conv_enable_matrix_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c098) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Enable filter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Filter enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_ENABLE_FILTER_DEFAULT (0)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_FILTER_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_FILTER_OFFSET (0x3210)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_FILTER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_enable_filter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c098);
    system_sw_write_32(base + 0x1c098, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_fr_cs_conv_enable_filter_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c098) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Enable horizontal downsample
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal Downsampling Enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_DEFAULT (0)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_OFFSET (0x3210)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_enable_horizontal_downsample_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c098);
    system_sw_write_32(base + 0x1c098, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_fr_cs_conv_enable_horizontal_downsample_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c098) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Enable vertical downsample
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical Downsampling Enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_DEFAULT (0)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_OFFSET (0x3210)
#define ACAMERA_ISP_FR_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_enable_vertical_downsample_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c098);
    system_sw_write_32(base + 0x1c098, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_fr_cs_conv_enable_vertical_downsample_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c098) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_11_DEFAULT (0x002f)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_11_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_11_OFFSET (0x3214)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_11_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c09c);
    system_sw_write_32(base + 0x1c09c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c09c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 12
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_12_DEFAULT (0x009d)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_12_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_12_OFFSET (0x3218)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_12_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_12_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0a0);
    system_sw_write_32(base + 0x1c0a0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_12_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0a0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 13
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_13_DEFAULT (0x0010)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_13_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_13_OFFSET (0x321c)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_13_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_13_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0a4);
    system_sw_write_32(base + 0x1c0a4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_13_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0a4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 21
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_21_DEFAULT (0x801a)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_21_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_21_OFFSET (0x3220)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_21_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_21_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0a8);
    system_sw_write_32(base + 0x1c0a8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_21_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0a8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 22
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_22_DEFAULT (0x8057)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_22_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_22_OFFSET (0x3224)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_22_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_22_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ac);
    system_sw_write_32(base + 0x1c0ac, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_22_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0ac) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 23
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_23_DEFAULT (0x0070)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_23_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_23_OFFSET (0x3228)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_23_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_23_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0b0);
    system_sw_write_32(base + 0x1c0b0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_23_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0b0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 31
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_31_DEFAULT (0x0070)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_31_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_31_OFFSET (0x322c)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_31_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_31_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0b4);
    system_sw_write_32(base + 0x1c0b4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_31_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0b4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 32
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_32_DEFAULT (0x8066)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_32_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_32_OFFSET (0x3230)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_32_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_32_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0b8);
    system_sw_write_32(base + 0x1c0b8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_32_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0b8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 33
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_33_DEFAULT (0x800a)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_33_DATASIZE (16)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_33_OFFSET (0x3234)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_33_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_33_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0bc);
    system_sw_write_32(base + 0x1c0bc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_33_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0bc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Y
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O1_DEFAULT (0x000)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O1_DATASIZE (11)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O1_OFFSET (0x3238)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O1_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_o1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0c0);
    system_sw_write_32(base + 0x1c0c0, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_o1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0c0) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Cb
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O2_DEFAULT (0x200)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O2_DATASIZE (11)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O2_OFFSET (0x323c)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O2_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_o2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0c4);
    system_sw_write_32(base + 0x1c0c4, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_o2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0c4) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Cr
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O3_DEFAULT (0x200)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O3_DATASIZE (11)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O3_OFFSET (0x3240)
#define ACAMERA_ISP_FR_CS_CONV_COEFFT_O3_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_fr_cs_conv_coefft_o3_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0c8);
    system_sw_write_32(base + 0x1c0c8, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_fr_cs_conv_coefft_o3_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0c8) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip min Y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimal value for Y.  Values below this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_Y_DEFAULT (0x000)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_Y_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_Y_OFFSET (0x3244)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_Y_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_clip_min_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0cc);
    system_sw_write_32(base + 0x1c0cc, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_clip_min_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0cc) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip max Y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximal value for Y.  Values above this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_Y_DEFAULT (0x3FF)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_Y_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_Y_OFFSET (0x3248)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_Y_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_clip_max_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0d0);
    system_sw_write_32(base + 0x1c0d0, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_clip_max_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0d0) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip min UV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimal value for Cb, Cr.  Values below this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_UV_DEFAULT (0x000)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_UV_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_UV_OFFSET (0x324c)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MIN_UV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_clip_min_uv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0d4);
    system_sw_write_32(base + 0x1c0d4, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_clip_min_uv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0d4) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip max UV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximal value for Cb, Cr.  Values above this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_UV_DEFAULT (0x3FF)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_UV_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_UV_OFFSET (0x3250)
#define ACAMERA_ISP_FR_CS_CONV_CLIP_MAX_UV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_clip_max_uv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0d8);
    system_sw_write_32(base + 0x1c0d8, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_clip_max_uv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0d8) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask RY
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 1 (R or Y).  Bit-wise and of this value and video data. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_RY_DEFAULT (0x3FF)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_RY_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_RY_OFFSET (0x3254)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_RY_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_data_mask_ry_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0dc);
    system_sw_write_32(base + 0x1c0dc, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_data_mask_ry_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0dc) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask GU
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 2 (G or U).  Bit-wise and of this value and video data.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_GU_DEFAULT (0x3FF)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_GU_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_GU_OFFSET (0x3258)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_GU_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_data_mask_gu_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0e0);
    system_sw_write_32(base + 0x1c0e0, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_data_mask_gu_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0e0) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask BV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 3 (B or V).  Bit-wise and of this value and video data.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_BV_DEFAULT (0x3FF)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_BV_DATASIZE (10)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_BV_OFFSET (0x325c)
#define ACAMERA_ISP_FR_CS_CONV_DATA_MASK_BV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_fr_cs_conv_data_mask_bv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0e4);
    system_sw_write_32(base + 0x1c0e4, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_fr_cs_conv_data_mask_bv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0e4) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr cs conv dither
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable dither
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Enables dithering module
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DITHER_ENABLE_DITHER_DEFAULT (0x0)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_ENABLE_DITHER_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_ENABLE_DITHER_OFFSET (0x3260)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_ENABLE_DITHER_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_dither_enable_dither_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0e8);
    system_sw_write_32(base + 0x1c0e8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_cs_conv_dither_enable_dither_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0e8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Dither amount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= dither to 9 bits; 1=dither to 8 bits; 2=dither to 7 bits; 3=dither to 6 bits 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DITHER_DITHER_AMOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_DITHER_AMOUNT_DATASIZE (2)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_DITHER_AMOUNT_OFFSET (0x3260)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_DITHER_AMOUNT_MASK (0x6)

// args: data (2-bit)
static __inline void acamera_isp_fr_cs_conv_dither_dither_amount_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0e8);
    system_sw_write_32(base + 0x1c0e8, (((uint32_t) (data & 0x3)) << 1) | (curr & 0xfffffff9));
}
static __inline uint8_t acamera_isp_fr_cs_conv_dither_dither_amount_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0e8) & 0x6) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Shift mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= output is LSB aligned; 1=output is MSB aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_CS_CONV_DITHER_SHIFT_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_SHIFT_MODE_DATASIZE (1)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_SHIFT_MODE_OFFSET (0x3260)
#define ACAMERA_ISP_FR_CS_CONV_DITHER_SHIFT_MODE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_fr_cs_conv_dither_shift_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0e8);
    system_sw_write_32(base + 0x1c0e8, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_fr_cs_conv_dither_shift_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0e8) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Group: fr dma writer
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// DMA writer controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Format
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_FORMAT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_FORMAT_DATASIZE (8)
#define ACAMERA_ISP_FR_DMA_WRITER_FORMAT_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_FORMAT_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_fr_dma_writer_format_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_fr_dma_writer_format_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Base mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Base DMA packing mode for RGB/RAW/YUV etc (see ISP guide)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BASE_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BASE_MODE_DATASIZE (5)
#define ACAMERA_ISP_FR_DMA_WRITER_BASE_MODE_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_BASE_MODE_MASK (0x1f)

// args: data (5-bit)
static __inline void acamera_isp_fr_dma_writer_base_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0x1f)) << 0) | (curr & 0xffffffe0));
}
static __inline uint8_t acamera_isp_fr_dma_writer_base_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0x1f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane select for planar/semi-planar base modes.  Only used if planar/semi-planar outputs required
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_PLANE_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_PLANE_SELECT_DATASIZE (2)
#define ACAMERA_ISP_FR_DMA_WRITER_PLANE_SELECT_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_PLANE_SELECT_MASK (0xc0)

// args: data (2-bit)
static __inline void acamera_isp_fr_dma_writer_plane_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0x3)) << 6) | (curr & 0xffffff3f));
}
static __inline uint8_t acamera_isp_fr_dma_writer_plane_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0xc0) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: single frame
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = All frames are written(after frame_write_on= 1), 1= only 1st frame written ( after frame_write_on =1) debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_SINGLE_FRAME_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_SINGLE_FRAME_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_SINGLE_FRAME_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_SINGLE_FRAME_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_single_frame_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_single_frame_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: frame write on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 = no frames written(when switched from 1, current frame completes writing before stopping),
//        1= write frame(s) (write single or continous frame(s) )
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WRITE_ON_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WRITE_ON_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WRITE_ON_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WRITE_ON_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_frame_write_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_frame_write_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: axi xact comp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = dont wait for axi transaction completion at end of frame(just all transfers accepted). 1 = wait for all transactions completed
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_XACT_COMP_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_XACT_COMP_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_XACT_COMP_OFFSET (0x3264)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_XACT_COMP_MASK (0x800)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_axi_xact_comp_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0ec);
    system_sw_write_32(base + 0x1c0ec, (((uint32_t) (data & 0x1)) << 11) | (curr & 0xfffff7ff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_xact_comp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c0ec) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: active width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video width in pixels 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_WIDTH_OFFSET (0x3268)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_active_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0f0);
    system_sw_write_32(base + 0x1c0f0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_dma_writer_active_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0f0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: active height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video height in lines 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_HEIGHT_OFFSET (0x3268)
#define ACAMERA_ISP_FR_DMA_WRITER_ACTIVE_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_active_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c0f0);
    system_sw_write_32(base + 0x1c0f0, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_dma_writer_active_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c0f0) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: bank0_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 0 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_BASE_OFFSET (0x326c)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_bank0_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c0f4, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_bank0_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c0f4);
}
// ------------------------------------------------------------------------------ //
// Register: bank1_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 1 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK1_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK1_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK1_BASE_OFFSET (0x3270)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK1_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_bank1_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c0f8, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_bank1_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c0f8);
}
// ------------------------------------------------------------------------------ //
// Register: bank2_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 2 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK2_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK2_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK2_BASE_OFFSET (0x3274)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK2_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_bank2_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c0fc, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_bank2_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c0fc);
}
// ------------------------------------------------------------------------------ //
// Register: bank3_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 3 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK3_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK3_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK3_BASE_OFFSET (0x3278)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK3_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_bank3_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c100, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_bank3_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c100);
}
// ------------------------------------------------------------------------------ //
// Register: bank4_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 4 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK4_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK4_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK4_BASE_OFFSET (0x327c)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK4_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_bank4_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c104, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_bank4_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c104);
}
// ------------------------------------------------------------------------------ //
// Register: max bank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// highest bank*_base to use for frame writes before recycling to bank0_base, only 0 to 4 are valid
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_MAX_BANK_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_MAX_BANK_DATASIZE (3)
#define ACAMERA_ISP_FR_DMA_WRITER_MAX_BANK_OFFSET (0x3280)
#define ACAMERA_ISP_FR_DMA_WRITER_MAX_BANK_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_fr_dma_writer_max_bank_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c108);
    system_sw_write_32(base + 0x1c108, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_fr_dma_writer_max_bank_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c108) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bank0 restart
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = normal operation, 1= restart bank counter to bank0 for next frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_RESTART_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_RESTART_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_RESTART_OFFSET (0x3280)
#define ACAMERA_ISP_FR_DMA_WRITER_BANK0_RESTART_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_bank0_restart_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c108);
    system_sw_write_32(base + 0x1c108, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_fr_dma_writer_bank0_restart_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c108) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Line_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Indicates the offset in bytes from the start of one line to the next line.  
//        This value should be equal to or larger than one line of image data and should be word-aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINE_OFFSET_DEFAULT (0x1000)
#define ACAMERA_ISP_FR_DMA_WRITER_LINE_OFFSET_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_LINE_OFFSET_OFFSET (0x3284)
#define ACAMERA_ISP_FR_DMA_WRITER_LINE_OFFSET_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_dma_writer_line_offset_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c10c, data);
}
static __inline uint32_t acamera_isp_fr_dma_writer_line_offset_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c10c);
}
// ------------------------------------------------------------------------------ //
// Register: wbank curr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// write bank currently active. valid values =0-4. updated at start of frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_CURR_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_CURR_DATASIZE (3)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_CURR_OFFSET (0x3288)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_CURR_MASK (0xe)

// args: data (3-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_wbank_curr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c110) & 0xe) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: wbank active
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = wbank_curr is being written to. Goes high at start of writes, low at last write transfer/completion on axi. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_ACTIVE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_ACTIVE_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_ACTIVE_OFFSET (0x3288)
#define ACAMERA_ISP_FR_DMA_WRITER_WBANK_ACTIVE_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_wbank_active_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c110) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame icount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of incomming frames (starts) to vdma_writer on video input, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_ICOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_ICOUNT_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_ICOUNT_OFFSET (0x3294)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_ICOUNT_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_fr_dma_writer_frame_icount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c11c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame wcount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of outgoing frame writes (starts) from vdma_writer sent to AXI output, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WCOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WCOUNT_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WCOUNT_OFFSET (0x3294)
#define ACAMERA_ISP_FR_DMA_WRITER_FRAME_WCOUNT_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_fr_dma_writer_frame_wcount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c11c) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_bresp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate bad  bresp captured 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_BRESP_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_BRESP_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_BRESP_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_BRESP_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_axi_fail_bresp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_awmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when awmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_AWMAXWAIT_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_AWMAXWAIT_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_axi_fail_awmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WMAXWAIT_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WMAXWAIT_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_axi_fail_wmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wxact_ostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wxact_ostand_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_axi_fail_wxact_ostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_width detected 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_vi_fail_active_width_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_height detected ( also raised on missing field!) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_vi_fail_active_height_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interline_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interline blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_vi_fail_interline_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interframe_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interframe blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_vi_fail_interframe_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: video_alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  active high, problem found on video port(s) ( active width/height or interline/frame blanks failure) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_VIDEO_ALARM_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_VIDEO_ALARM_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_VIDEO_ALARM_OFFSET (0x329c)
#define ACAMERA_ISP_FR_DMA_WRITER_VIDEO_ALARM_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_dma_writer_video_alarm_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c124) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: blk_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        block status output (reserved)
//                          -- blk_status(0) = wfifo_fail_full
//                          -- blk_status(1) = wfifo_fail_empty
//                          -- blk_status(4) = pack_fail_overflow
//                          -- blk_status(24) = intw_fail_user_intfc_sig
//                          -- blk_status(others) =  zero     
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_BLK_STATUS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_BLK_STATUS_DATASIZE (32)
#define ACAMERA_ISP_FR_DMA_WRITER_BLK_STATUS_OFFSET (0x32a0)
#define ACAMERA_ISP_FR_DMA_WRITER_BLK_STATUS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_fr_dma_writer_blk_status_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c128);
}
// ------------------------------------------------------------------------------ //
// Register: lines_wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Number of lines to write from base address before wrapping back to base address. 0 = no wrapping, >0 = last line written before wrapping
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_DMA_WRITER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_LINES_WRAPPED_OFFSET (0x32a4)
#define ACAMERA_ISP_FR_DMA_WRITER_LINES_WRAPPED_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c12c);
    system_sw_write_32(base + 0x1c12c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_dma_writer_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c12c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_first
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line number of first linetick. 0  = no linetick, >0 = line number to generate linetick 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_FIRST_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_FIRST_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_FIRST_OFFSET (0x32a8)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_FIRST_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_linetick_first_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c130);
    system_sw_write_32(base + 0x1c130, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_dma_writer_linetick_first_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c130) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_repeat
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line repeat interval of linetick. 0 = no repeat, >0 = repeat interval in lines 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_REPEAT_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_REPEAT_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_REPEAT_OFFSET (0x32ac)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_REPEAT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_linetick_repeat_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c134);
    system_sw_write_32(base + 0x1c134, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_dma_writer_linetick_repeat_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c134) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_eol
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linetick start/end of line control. 0 = use start of line, 1 = use end of line to generate linetick
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_EOL_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_EOL_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_EOL_OFFSET (0x32b0)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_EOL_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_linetick_eol_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c138);
    system_sw_write_32(base + 0x1c138, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_dma_writer_linetick_eol_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c138) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_delay
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Linetick delay in vcke cycles to add to min 3 cycle latency from acl_vi. 0-65535.
//        Must be less than next linetick generation time or count will not mature and no linetick is not produced.
//          --NOTE: linetick delay  can run past end of frame/field and also into next frame!
//          --      Take care maturity time is less than next configured linetick generation postion!
//          --      Take care when changing config between frame too! 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_DELAY_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_DELAY_DATASIZE (16)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_DELAY_OFFSET (0x32b0)
#define ACAMERA_ISP_FR_DMA_WRITER_LINETICK_DELAY_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_dma_writer_linetick_delay_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c138);
    system_sw_write_32(base + 0x1c138, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_dma_writer_linetick_delay_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c138) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        active high (debug only), enables posting of pagewarm dummy writes to SMMU for early page translation of upcomming 4K pages. 
//        Recommend SMMU has min 8 page cache to avoid translation miss. Pagewarms are posted as dummy writes with wstrb= 0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_PAGEWARM_ON_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_PAGEWARM_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_dma_writer_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0= static value (axi_id_value) for awid/wid, 1 = incrementing value per transaction for awid/wid wrapping to 0 after axi_id_value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_MULTI_DEFAULT (0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_MULTI_DATASIZE (1)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_MULTI_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_MULTI_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_fr_dma_writer_axi_id_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_id_multi_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 0x3
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_BURSTSPLIT_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_BURSTSPLIT_MASK (0xc)

// args: data (2-bit)
static __inline void acamera_isp_fr_dma_writer_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0x3)) << 2) | (curr & 0xfffffff3));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0xc) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 0xf
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_CACHE_VALUE_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_CACHE_VALUE_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_fr_dma_writer_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding write transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAXOSTAND_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_fr_dma_writer_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_max_awlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for awlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAX_AWLEN_DEFAULT (0xf)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAX_AWLEN_DATASIZE (4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAX_AWLEN_OFFSET (0x32b4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_MAX_AWLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_fr_dma_writer_axi_max_awlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c13c);
    system_sw_write_32(base + 0x1c13c, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_max_awlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c13c) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid. Good default = 0000
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_VALUE_OFFSET (0x32b8)
#define ACAMERA_ISP_FR_DMA_WRITER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_fr_dma_writer_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c140);
    system_sw_write_32(base + 0x1c140, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_fr_dma_writer_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c140) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: fr uv dma writer
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// DMA writer controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Format
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_FORMAT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FORMAT_DATASIZE (8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FORMAT_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FORMAT_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_fr_uv_dma_writer_format_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_format_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Base mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Base DMA packing mode for RGB/RAW/YUV etc (see ISP guide)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BASE_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BASE_MODE_DATASIZE (5)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BASE_MODE_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BASE_MODE_MASK (0x1f)

// args: data (5-bit)
static __inline void acamera_isp_fr_uv_dma_writer_base_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0x1f)) << 0) | (curr & 0xffffffe0));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_base_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0x1f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane select for planar/semi-planar base modes.  Only used if planar/semi-planar outputs required.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_PLANE_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PLANE_SELECT_DATASIZE (2)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PLANE_SELECT_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PLANE_SELECT_MASK (0xc0)

// args: data (2-bit)
static __inline void acamera_isp_fr_uv_dma_writer_plane_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0x3)) << 6) | (curr & 0xffffff3f));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_plane_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0xc0) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: single frame
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = All frames are written(after frame_write_on= 1), 1= only 1st frame written ( after frame_write_on =1) debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_SINGLE_FRAME_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_SINGLE_FRAME_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_SINGLE_FRAME_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_SINGLE_FRAME_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_single_frame_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_single_frame_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: frame write on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 = no frames written(when switched from 1, current frame completes writing before stopping),
//        1= write frame(s) (write single or continous frame(s) )
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WRITE_ON_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WRITE_ON_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WRITE_ON_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WRITE_ON_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_frame_write_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_frame_write_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: axi xact comp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = dont wait for axi transaction completion at end of frame(just all transfers accepted). 1 = wait for all transactions completed
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_XACT_COMP_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_XACT_COMP_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_XACT_COMP_OFFSET (0x32bc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_XACT_COMP_MASK (0x800)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_xact_comp_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c144);
    system_sw_write_32(base + 0x1c144, (((uint32_t) (data & 0x1)) << 11) | (curr & 0xfffff7ff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_xact_comp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c144) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: active width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video width in pixels 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_WIDTH_OFFSET (0x32c0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_active_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c148);
    system_sw_write_32(base + 0x1c148, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_active_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c148) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: active height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video height in lines 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_HEIGHT_OFFSET (0x32c0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_ACTIVE_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_active_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c148);
    system_sw_write_32(base + 0x1c148, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_active_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c148) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: bank0_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 0 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_BASE_OFFSET (0x32c4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank0_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c14c, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_bank0_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c14c);
}
// ------------------------------------------------------------------------------ //
// Register: bank1_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 1 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK1_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK1_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK1_BASE_OFFSET (0x32c8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK1_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank1_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c150, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_bank1_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c150);
}
// ------------------------------------------------------------------------------ //
// Register: bank2_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 2 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK2_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK2_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK2_BASE_OFFSET (0x32cc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK2_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank2_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c154, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_bank2_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c154);
}
// ------------------------------------------------------------------------------ //
// Register: bank3_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 3 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK3_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK3_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK3_BASE_OFFSET (0x32d0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK3_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank3_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c158, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_bank3_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c158);
}
// ------------------------------------------------------------------------------ //
// Register: bank4_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 4 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK4_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK4_BASE_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK4_BASE_OFFSET (0x32d4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK4_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank4_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c15c, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_bank4_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c15c);
}
// ------------------------------------------------------------------------------ //
// Register: max bank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// highest bank*_base to use for frame writes before recycling to bank0_base, only 0 to 4 are valid
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_MAX_BANK_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_MAX_BANK_DATASIZE (3)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_MAX_BANK_OFFSET (0x32d8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_MAX_BANK_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_fr_uv_dma_writer_max_bank_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c160);
    system_sw_write_32(base + 0x1c160, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_max_bank_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c160) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bank0 restart
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = normal operation, 1= restart bank counter to bank0 for next frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_RESTART_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_RESTART_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_RESTART_OFFSET (0x32d8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BANK0_RESTART_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_bank0_restart_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c160);
    system_sw_write_32(base + 0x1c160, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_bank0_restart_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c160) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Line_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Indicates the offset in bytes from the start of one line to the next line.  
//        This value should be equal to or larger than one line of image data and should be word-aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINE_OFFSET_DEFAULT (0x1000)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINE_OFFSET_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINE_OFFSET_OFFSET (0x32dc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINE_OFFSET_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_fr_uv_dma_writer_line_offset_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c164, data);
}
static __inline uint32_t acamera_isp_fr_uv_dma_writer_line_offset_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c164);
}
// ------------------------------------------------------------------------------ //
// Register: wbank curr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// write bank currently active. valid values =0-4. updated at start of frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_CURR_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_CURR_DATASIZE (3)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_CURR_OFFSET (0x32e0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_CURR_MASK (0xe)

// args: data (3-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_wbank_curr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c168) & 0xe) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: wbank active
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = wbank_curr is being written to. Goes high at start of writes, low at last write transfer/completion on axi. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_ACTIVE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_ACTIVE_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_ACTIVE_OFFSET (0x32e0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_WBANK_ACTIVE_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_wbank_active_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c168) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame icount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of incomming frames (starts) to vdma_writer on video input, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_ICOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_ICOUNT_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_ICOUNT_OFFSET (0x32ec)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_ICOUNT_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_fr_uv_dma_writer_frame_icount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c174) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame wcount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of outgoing frame writes (starts) from vdma_writer sent to AXI output, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WCOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WCOUNT_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WCOUNT_OFFSET (0x32ec)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_FRAME_WCOUNT_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_fr_uv_dma_writer_frame_wcount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c174) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_bresp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate bad  bresp captured 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_BRESP_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_BRESP_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_BRESP_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_BRESP_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_fail_bresp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_awmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when awmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_fail_awmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_fail_wmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wxact_ostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wxact_ostand_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_fail_wxact_ostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_width detected 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_vi_fail_active_width_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_height detected ( also raised on missing field!) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_vi_fail_active_height_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interline_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interline blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_vi_fail_interline_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interframe_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interframe blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_vi_fail_interframe_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: video_alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  active high, problem found on video port(s) ( active width/height or interline/frame blanks failure) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_VIDEO_ALARM_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VIDEO_ALARM_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VIDEO_ALARM_OFFSET (0x32f4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_VIDEO_ALARM_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_fr_uv_dma_writer_video_alarm_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c17c) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: blk_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        block status output (reserved)
//                          -- blk_status(0) = wfifo_fail_full
//                          -- blk_status(1) = wfifo_fail_empty
//                          -- blk_status(4) = pack_fail_overflow
//                          -- blk_status(24) = intw_fail_user_intfc_sig
//                          -- blk_status(others) =  zero     
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_BLK_STATUS_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BLK_STATUS_DATASIZE (32)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BLK_STATUS_OFFSET (0x32f8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_BLK_STATUS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_fr_uv_dma_writer_blk_status_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c180);
}
// ------------------------------------------------------------------------------ //
// Register: lines_wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Number of lines to write from base address before wrapping back to base address. 0 = no wrapping, >0 = last line written before wrapping
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINES_WRAPPED_OFFSET (0x32fc)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINES_WRAPPED_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c184);
    system_sw_write_32(base + 0x1c184, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c184) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_first
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line number of first linetick. 0  = no linetick, >0 = line number to generate linetick 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_FIRST_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_FIRST_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_FIRST_OFFSET (0x3300)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_FIRST_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_linetick_first_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c188);
    system_sw_write_32(base + 0x1c188, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_linetick_first_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c188) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_repeat
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line repeat interval of linetick. 0 = no repeat, >0 = repeat interval in lines 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_REPEAT_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_REPEAT_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_REPEAT_OFFSET (0x3304)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_REPEAT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_linetick_repeat_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c18c);
    system_sw_write_32(base + 0x1c18c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_linetick_repeat_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c18c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_eol
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linetick start/end of line control. 0 = use start of line, 1 = use end of line to generate linetick
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_EOL_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_EOL_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_EOL_OFFSET (0x3308)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_EOL_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_linetick_eol_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c190);
    system_sw_write_32(base + 0x1c190, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_linetick_eol_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c190) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_delay
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Linetick delay in vcke cycles to add to min 3 cycle latency from acl_vi. 0-65535.
//        Must be less than next linetick generation time or count will not mature and no linetick is not produced.
//          --NOTE: linetick delay  can run past end of frame/field and also into next frame!
//          --      Take care maturity time is less than next configured linetick generation postion!
//          --      Take care when changing config between frame too! 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_DELAY_DEFAULT (0x0000)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_DELAY_DATASIZE (16)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_DELAY_OFFSET (0x3308)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_LINETICK_DELAY_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_fr_uv_dma_writer_linetick_delay_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c190);
    system_sw_write_32(base + 0x1c190, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_fr_uv_dma_writer_linetick_delay_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c190) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        active high (debug only), enables posting of pagewarm dummy writes to SMMU for early page translation of upcomming 4K pages. 
//        Recommend SMMU has min 8 page cache to avoid translation miss. Pagewarms are posted as dummy writes with wstrb= 0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PAGEWARM_ON_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_PAGEWARM_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0= static value (axi_id_value) for awid/wid, 1 = incrementing value per transaction for awid/wid wrapping to 0 after axi_id_value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_MULTI_DEFAULT (0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_MULTI_DATASIZE (1)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_MULTI_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_MULTI_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_id_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_id_multi_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 0x3
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_BURSTSPLIT_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_BURSTSPLIT_MASK (0xc)

// args: data (2-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0x3)) << 2) | (curr & 0xfffffff3));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0xc) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 0xf
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_CACHE_VALUE_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_CACHE_VALUE_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding write transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAXOSTAND_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_max_awlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for awlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAX_AWLEN_DEFAULT (0xf)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAX_AWLEN_DATASIZE (4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAX_AWLEN_OFFSET (0x330c)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_MAX_AWLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_max_awlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c194);
    system_sw_write_32(base + 0x1c194, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_max_awlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c194) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid. Good default = 0000
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_VALUE_OFFSET (0x3310)
#define ACAMERA_ISP_FR_UV_DMA_WRITER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_fr_uv_dma_writer_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c198);
    system_sw_write_32(base + 0x1c198, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_fr_uv_dma_writer_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c198) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Crop for full resolution output
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable crop
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Crop enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CROP_ENABLE_CROP_DEFAULT (0)
#define ACAMERA_ISP_DS1_CROP_ENABLE_CROP_DATASIZE (1)
#define ACAMERA_ISP_DS1_CROP_ENABLE_CROP_OFFSET (0x3314)
#define ACAMERA_ISP_DS1_CROP_ENABLE_CROP_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_crop_enable_crop_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c19c);
    system_sw_write_32(base + 0x1c19c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_crop_enable_crop_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c19c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: start x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal offset from left side of image in pixels for output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CROP_START_X_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_CROP_START_X_DATASIZE (16)
#define ACAMERA_ISP_DS1_CROP_START_X_OFFSET (0x3318)
#define ACAMERA_ISP_DS1_CROP_START_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_crop_start_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1a0);
    system_sw_write_32(base + 0x1c1a0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_crop_start_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1a0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: start y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical offset from top of image in lines for output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CROP_START_Y_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_CROP_START_Y_DATASIZE (16)
#define ACAMERA_ISP_DS1_CROP_START_Y_OFFSET (0x331c)
#define ACAMERA_ISP_DS1_CROP_START_Y_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_crop_start_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1a4);
    system_sw_write_32(base + 0x1c1a4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_crop_start_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1a4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: size x
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// width of output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CROP_SIZE_X_DEFAULT (0xffff)
#define ACAMERA_ISP_DS1_CROP_SIZE_X_DATASIZE (16)
#define ACAMERA_ISP_DS1_CROP_SIZE_X_OFFSET (0x3320)
#define ACAMERA_ISP_DS1_CROP_SIZE_X_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_crop_size_x_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1a8);
    system_sw_write_32(base + 0x1c1a8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_crop_size_x_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1a8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: size y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// height of output crop window
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CROP_SIZE_Y_DEFAULT (0xffff)
#define ACAMERA_ISP_DS1_CROP_SIZE_Y_DATASIZE (16)
#define ACAMERA_ISP_DS1_CROP_SIZE_Y_OFFSET (0x3324)
#define ACAMERA_ISP_DS1_CROP_SIZE_Y_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_crop_size_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1ac);
    system_sw_write_32(base + 0x1c1ac, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_crop_size_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1ac) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds scaler
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Timeout Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 : Timeout disabled.  
//        1 : Timeout enabled.  Automatic frame reset if frame has not completed after anticipated time.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_ENABLE_OFFSET (0x332c)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_ENABLE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_ds1_scaler_timeout_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1b4);
    system_sw_write_32(base + 0x1c1b4, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_ds1_scaler_timeout_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1b4) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Timeout Value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Timeout count in vcke cycles, from field. Configure to min( 65535, 8*(output_width+32) ) 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_VALUE_DEFAULT (0x2900)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_VALUE_DATASIZE (16)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_VALUE_OFFSET (0x332c)
#define ACAMERA_ISP_DS1_SCALER_TIMEOUT_VALUE_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_scaler_timeout_value_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1b4);
    system_sw_write_32(base + 0x1c1b4, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_scaler_timeout_value_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1b4) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: WIDTH
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Input frame width in pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_DS1_SCALER_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_DS1_SCALER_WIDTH_OFFSET (0x3330)
#define ACAMERA_ISP_DS1_SCALER_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_scaler_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1b8);
    system_sw_write_32(base + 0x1c1b8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_scaler_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1b8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HEIGHT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Input frame height in lines
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_DS1_SCALER_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_DS1_SCALER_HEIGHT_OFFSET (0x3334)
#define ACAMERA_ISP_DS1_SCALER_HEIGHT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_scaler_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1bc);
    system_sw_write_32(base + 0x1c1bc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_scaler_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1bc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: OWIDTH
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Output frame width in pixels
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_OWIDTH_DEFAULT (0x500)
#define ACAMERA_ISP_DS1_SCALER_OWIDTH_DATASIZE (16)
#define ACAMERA_ISP_DS1_SCALER_OWIDTH_OFFSET (0x3338)
#define ACAMERA_ISP_DS1_SCALER_OWIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_scaler_owidth_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1c0);
    system_sw_write_32(base + 0x1c1c0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_scaler_owidth_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1c0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: OHEIGHT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Output frame height in lines
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_OHEIGHT_DEFAULT (0x2D0)
#define ACAMERA_ISP_DS1_SCALER_OHEIGHT_DATASIZE (16)
#define ACAMERA_ISP_DS1_SCALER_OHEIGHT_OFFSET (0x333c)
#define ACAMERA_ISP_DS1_SCALER_OHEIGHT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_scaler_oheight_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1c4);
    system_sw_write_32(base + 0x1c1c4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_scaler_oheight_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1c4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HFILT_TINC
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal scaling factor
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_HFILT_TINC_DEFAULT (0x180000)
#define ACAMERA_ISP_DS1_SCALER_HFILT_TINC_DATASIZE (24)
#define ACAMERA_ISP_DS1_SCALER_HFILT_TINC_OFFSET (0x3340)
#define ACAMERA_ISP_DS1_SCALER_HFILT_TINC_MASK (0xffffff)

// args: data (24-bit)
static __inline void acamera_isp_ds1_scaler_hfilt_tinc_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1c8);
    system_sw_write_32(base + 0x1c1c8, (((uint32_t) (data & 0xffffff)) << 0) | (curr & 0xff000000));
}
static __inline uint32_t acamera_isp_ds1_scaler_hfilt_tinc_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1c1c8) & 0xffffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: HFILT_COEFSET
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        HFILT Coeff. control.  
//        HFILT_COEFSET[3:0] - Selects horizontal Coef set for scaler.
//            0000 : use set 0
//            0001 : use set 1
//            ...... 
//            0111 : use set 7
//            ...... 
//            1111 : use set 15
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_HFILT_COEFSET_DEFAULT (0x00)
#define ACAMERA_ISP_DS1_SCALER_HFILT_COEFSET_DATASIZE (4)
#define ACAMERA_ISP_DS1_SCALER_HFILT_COEFSET_OFFSET (0x3344)
#define ACAMERA_ISP_DS1_SCALER_HFILT_COEFSET_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_ds1_scaler_hfilt_coefset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1cc);
    system_sw_write_32(base + 0x1c1cc, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_ds1_scaler_hfilt_coefset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1cc) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: VFILT_TINC
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// VFILT TINC
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_VFILT_TINC_DEFAULT (0x180000)
#define ACAMERA_ISP_DS1_SCALER_VFILT_TINC_DATASIZE (24)
#define ACAMERA_ISP_DS1_SCALER_VFILT_TINC_OFFSET (0x3348)
#define ACAMERA_ISP_DS1_SCALER_VFILT_TINC_MASK (0xffffff)

// args: data (24-bit)
static __inline void acamera_isp_ds1_scaler_vfilt_tinc_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1d0);
    system_sw_write_32(base + 0x1c1d0, (((uint32_t) (data & 0xffffff)) << 0) | (curr & 0xff000000));
}
static __inline uint32_t acamera_isp_ds1_scaler_vfilt_tinc_read(uintptr_t base) {
    return (uint32_t)((system_sw_read_32(base + 0x1c1d0) & 0xffffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: VFILT_COEFSET
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        VFILT Coeff. control
//        FILT_COEFSET[3:0] - Selects vertical Coef set for scaler
//            0000 : use set 0
//            0001 : use set 1
//            ...... 
//            0111 : use set 7
//            ...... 
//            1111 : use set 15
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SCALER_VFILT_COEFSET_DEFAULT (0x00)
#define ACAMERA_ISP_DS1_SCALER_VFILT_COEFSET_DATASIZE (4)
#define ACAMERA_ISP_DS1_SCALER_VFILT_COEFSET_OFFSET (0x334c)
#define ACAMERA_ISP_DS1_SCALER_VFILT_COEFSET_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_ds1_scaler_vfilt_coefset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1d4);
    system_sw_write_32(base + 0x1c1d4, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_ds1_scaler_vfilt_coefset_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1d4) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds gamma rgb
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gamma correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Gamma enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_ENABLE_DEFAULT (1)
#define ACAMERA_ISP_DS1_GAMMA_RGB_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_DS1_GAMMA_RGB_ENABLE_OFFSET (0x3350)
#define ACAMERA_ISP_DS1_GAMMA_RGB_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_gamma_rgb_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1d8);
    system_sw_write_32(base + 0x1c1d8, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_gamma_rgb_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1d8) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the R chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_R_DEFAULT (0x100)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_R_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_R_OFFSET (0x3354)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_gain_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1dc);
    system_sw_write_32(base + 0x1c1dc, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_gain_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1dc) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gain_g
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the G chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_G_DEFAULT (0x100)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_G_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_G_OFFSET (0x3354)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_G_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_gain_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1dc);
    system_sw_write_32(base + 0x1c1dc, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_gain_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1dc) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: gain_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// gain applied to the B chanel in 4.8 format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_B_DEFAULT (0x100)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_B_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_B_OFFSET (0x3358)
#define ACAMERA_ISP_DS1_GAMMA_RGB_GAIN_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_gain_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1e0);
    system_sw_write_32(base + 0x1c1e0, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_gain_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1e0) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset_r
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the R chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_R_DEFAULT (0)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_R_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_R_OFFSET (0x335c)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_R_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_offset_r_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1e4);
    system_sw_write_32(base + 0x1c1e4, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_offset_r_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1e4) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: offset_g
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the G chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_G_DEFAULT (0)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_G_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_G_OFFSET (0x335c)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_G_MASK (0xfff0000)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_offset_g_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1e4);
    system_sw_write_32(base + 0x1c1e4, (((uint32_t) (data & 0xfff)) << 16) | (curr & 0xf000ffff));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_offset_g_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1e4) & 0xfff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: offset_b
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset subtracted from the B chanel 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_B_DEFAULT (0)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_B_DATASIZE (12)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_B_OFFSET (0x3360)
#define ACAMERA_ISP_DS1_GAMMA_RGB_OFFSET_B_MASK (0xfff)

// args: data (12-bit)
static __inline void acamera_isp_ds1_gamma_rgb_offset_b_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1e8);
    system_sw_write_32(base + 0x1c1e8, (((uint32_t) (data & 0xfff)) << 0) | (curr & 0xfffff000));
}
static __inline uint16_t acamera_isp_ds1_gamma_rgb_offset_b_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1e8) & 0xfff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Sharpening enable: 0=off, 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_ENABLE_DEFAULT (0)
#define ACAMERA_ISP_DS1_SHARPEN_ENABLE_DATASIZE (1)
#define ACAMERA_ISP_DS1_SHARPEN_ENABLE_OFFSET (0x3364)
#define ACAMERA_ISP_DS1_SHARPEN_ENABLE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_sharpen_enable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1ec);
    system_sw_write_32(base + 0x1c1ec, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_sharpen_enable_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1ec) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Strength
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Controls strength of sharpening effect. u5.4
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_STRENGTH_DEFAULT (0x10)
#define ACAMERA_ISP_DS1_SHARPEN_STRENGTH_DATASIZE (9)
#define ACAMERA_ISP_DS1_SHARPEN_STRENGTH_OFFSET (0x3368)
#define ACAMERA_ISP_DS1_SHARPEN_STRENGTH_MASK (0x1ff)

// args: data (9-bit)
static __inline void acamera_isp_ds1_sharpen_strength_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f0);
    system_sw_write_32(base + 0x1c1f0, (((uint32_t) (data & 0x1ff)) << 0) | (curr & 0xfffffe00));
}
static __inline uint16_t acamera_isp_ds1_sharpen_strength_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1f0) & 0x1ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Control R
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma transform red coefficient. u0.8 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_R_DEFAULT (0x4C)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_R_DATASIZE (8)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_R_OFFSET (0x336c)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_R_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_ds1_sharpen_control_r_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f4);
    system_sw_write_32(base + 0x1c1f4, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_ds1_sharpen_control_r_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1f4) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Control B
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma transform blue coefficient. u0.8 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_B_DEFAULT (0x1E)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_B_DATASIZE (8)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_B_OFFSET (0x336c)
#define ACAMERA_ISP_DS1_SHARPEN_CONTROL_B_MASK (0xff00)

// args: data (8-bit)
static __inline void acamera_isp_ds1_sharpen_control_b_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f4);
    system_sw_write_32(base + 0x1c1f4, (((uint32_t) (data & 0xff)) << 8) | (curr & 0xffff00ff));
}
static __inline uint8_t acamera_isp_ds1_sharpen_control_b_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1f4) & 0xff00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Alpha Undershoot
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Alpha blending of undershoot and overshoot u0.7, 0 = only undershoot, 255 = only overshoot
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_ALPHA_UNDERSHOOT_DEFAULT (0x13)
#define ACAMERA_ISP_DS1_SHARPEN_ALPHA_UNDERSHOOT_DATASIZE (8)
#define ACAMERA_ISP_DS1_SHARPEN_ALPHA_UNDERSHOOT_OFFSET (0x336c)
#define ACAMERA_ISP_DS1_SHARPEN_ALPHA_UNDERSHOOT_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_ds1_sharpen_alpha_undershoot_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f4);
    system_sw_write_32(base + 0x1c1f4, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_ds1_sharpen_alpha_undershoot_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1f4) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Thresh Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma threshold below this value, no sharpening will be applied. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_LOW_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_LOW_DATASIZE (10)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_LOW_OFFSET (0x3370)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_LOW_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_sharpen_luma_thresh_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f8);
    system_sw_write_32(base + 0x1c1f8, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_sharpen_luma_thresh_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1f8) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Offset Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma offset (min value) of the region of less than Luma Thresh Low.  
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_LOW_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_LOW_DATASIZE (8)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_LOW_OFFSET (0x3370)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_LOW_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_ds1_sharpen_luma_offset_low_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1f8);
    system_sw_write_32(base + 0x1c1f8, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_ds1_sharpen_luma_offset_low_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c1f8) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Slope Low
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma linear threshold slope at dark luminance region 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_LOW_DEFAULT (0x03FC)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_LOW_DATASIZE (16)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_LOW_OFFSET (0x3374)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_LOW_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_sharpen_luma_slope_low_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1fc);
    system_sw_write_32(base + 0x1c1fc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_sharpen_luma_slope_low_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1fc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Thresh High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma threshold above this value, sharpening level will be decreased. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_HIGH_DEFAULT (0x332)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_HIGH_DATASIZE (10)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_HIGH_OFFSET (0x3374)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_THRESH_HIGH_MASK (0x3ff0000)

// args: data (10-bit)
static __inline void acamera_isp_ds1_sharpen_luma_thresh_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c1fc);
    system_sw_write_32(base + 0x1c1fc, (((uint32_t) (data & 0x3ff)) << 16) | (curr & 0xfc00ffff));
}
static __inline uint16_t acamera_isp_ds1_sharpen_luma_thresh_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c1fc) & 0x3ff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Offset High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma offset (min value) of the region of more than Luma Thresh High.  
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_HIGH_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_HIGH_DATASIZE (8)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_HIGH_OFFSET (0x3378)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_OFFSET_HIGH_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_ds1_sharpen_luma_offset_high_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c200);
    system_sw_write_32(base + 0x1c200, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_ds1_sharpen_luma_offset_high_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c200) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Luma Slope High
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Luma linear threshold slope at bright luminance region 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_HIGH_DEFAULT (0x06A4)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_HIGH_DATASIZE (16)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_HIGH_OFFSET (0x3378)
#define ACAMERA_ISP_DS1_SHARPEN_LUMA_SLOPE_HIGH_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_sharpen_luma_slope_high_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c200);
    system_sw_write_32(base + 0x1c200, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_sharpen_luma_slope_high_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c200) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Clip Str Max
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clips sharpening mask of max value. This will control overshoot. U0.14. (0 ~ 16383) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MAX_DEFAULT (0x3FFF)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MAX_DATASIZE (14)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MAX_OFFSET (0x337c)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MAX_MASK (0x3fff)

// args: data (14-bit)
static __inline void acamera_isp_ds1_sharpen_clip_str_max_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c204);
    system_sw_write_32(base + 0x1c204, (((uint32_t) (data & 0x3fff)) << 0) | (curr & 0xffffc000));
}
static __inline uint16_t acamera_isp_ds1_sharpen_clip_str_max_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c204) & 0x3fff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip Str Min
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clips sharpening mask of min value. This will control undershoot. U0.14. It is used as negative value. (0 ~ -16383)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MIN_DEFAULT (0x00CD)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MIN_DATASIZE (14)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MIN_OFFSET (0x337c)
#define ACAMERA_ISP_DS1_SHARPEN_CLIP_STR_MIN_MASK (0x3fff0000)

// args: data (14-bit)
static __inline void acamera_isp_ds1_sharpen_clip_str_min_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c204);
    system_sw_write_32(base + 0x1c204, (((uint32_t) (data & 0x3fff)) << 16) | (curr & 0xc000ffff));
}
static __inline uint16_t acamera_isp_ds1_sharpen_clip_str_min_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c204) & 0x3fff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Debug
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  To support different debug output. 0 = normal operation, 1 = luma, 2 = sharpening mask 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_SHARPEN_DEBUG_DEFAULT (0)
#define ACAMERA_ISP_DS1_SHARPEN_DEBUG_DATASIZE (4)
#define ACAMERA_ISP_DS1_SHARPEN_DEBUG_OFFSET (0x3380)
#define ACAMERA_ISP_DS1_SHARPEN_DEBUG_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_ds1_sharpen_debug_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c208);
    system_sw_write_32(base + 0x1c208, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_ds1_sharpen_debug_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c208) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds cs conv
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Conversion of RGB to YUV data using a 3x3 color matrix plus offsets
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable matrix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Color matrix enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_MATRIX_DEFAULT (0)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_MATRIX_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_MATRIX_OFFSET (0x3384)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_MATRIX_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_enable_matrix_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c20c);
    system_sw_write_32(base + 0x1c20c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_enable_matrix_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c20c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Enable filter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Filter enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_FILTER_DEFAULT (0)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_FILTER_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_FILTER_OFFSET (0x3384)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_FILTER_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_enable_filter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c20c);
    system_sw_write_32(base + 0x1c20c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_enable_filter_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c20c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Enable horizontal downsample
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal Downsampling Enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_DEFAULT (0)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_OFFSET (0x3384)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_HORIZONTAL_DOWNSAMPLE_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_enable_horizontal_downsample_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c20c);
    system_sw_write_32(base + 0x1c20c, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_enable_horizontal_downsample_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c20c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: Enable vertical downsample
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Vertical Downsampling Enable: 0=off 1=on
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_DEFAULT (0)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_OFFSET (0x3384)
#define ACAMERA_ISP_DS1_CS_CONV_ENABLE_VERTICAL_DOWNSAMPLE_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_enable_vertical_downsample_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c20c);
    system_sw_write_32(base + 0x1c20c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_enable_vertical_downsample_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c20c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 11
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_11_DEFAULT (0x002f)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_11_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_11_OFFSET (0x3388)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_11_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_11_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c210);
    system_sw_write_32(base + 0x1c210, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_11_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c210) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 12
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_12_DEFAULT (0x009d)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_12_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_12_OFFSET (0x338c)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_12_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_12_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c214);
    system_sw_write_32(base + 0x1c214, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_12_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c214) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 13
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Y multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_13_DEFAULT (0x0010)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_13_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_13_OFFSET (0x3390)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_13_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_13_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c218);
    system_sw_write_32(base + 0x1c218, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_13_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c218) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 21
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_21_DEFAULT (0x801a)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_21_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_21_OFFSET (0x3394)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_21_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_21_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c21c);
    system_sw_write_32(base + 0x1c21c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_21_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c21c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 22
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_22_DEFAULT (0x8057)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_22_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_22_OFFSET (0x3398)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_22_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_22_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c220);
    system_sw_write_32(base + 0x1c220, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_22_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c220) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 23
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Cb multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_23_DEFAULT (0x0070)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_23_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_23_OFFSET (0x339c)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_23_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_23_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c224);
    system_sw_write_32(base + 0x1c224, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_23_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c224) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 31
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for R-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_31_DEFAULT (0x0070)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_31_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_31_OFFSET (0x33a0)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_31_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_31_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c228);
    system_sw_write_32(base + 0x1c228, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_31_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c228) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 32
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for G-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_32_DEFAULT (0x8066)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_32_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_32_OFFSET (0x33a4)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_32_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_32_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c22c);
    system_sw_write_32(base + 0x1c22c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_32_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c22c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft 33
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Matrix coefficient for B-Cr multiplier
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_33_DEFAULT (0x800a)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_33_DATASIZE (16)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_33_OFFSET (0x33a8)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_33_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_33_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c230);
    system_sw_write_32(base + 0x1c230, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_33_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c230) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o1
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Y
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O1_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O1_DATASIZE (11)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O1_OFFSET (0x33ac)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O1_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_o1_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c234);
    system_sw_write_32(base + 0x1c234, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_o1_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c234) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o2
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Cb
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O2_DEFAULT (0x200)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O2_DATASIZE (11)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O2_OFFSET (0x33b0)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O2_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_o2_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c238);
    system_sw_write_32(base + 0x1c238, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_o2_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c238) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Coefft o3
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Offset for Cr
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O3_DEFAULT (0x200)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O3_DATASIZE (11)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O3_OFFSET (0x33b4)
#define ACAMERA_ISP_DS1_CS_CONV_COEFFT_O3_MASK (0x7ff)

// args: data (11-bit)
static __inline void acamera_isp_ds1_cs_conv_coefft_o3_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c23c);
    system_sw_write_32(base + 0x1c23c, (((uint32_t) (data & 0x7ff)) << 0) | (curr & 0xfffff800));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_coefft_o3_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c23c) & 0x7ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip min Y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimal value for Y.  Values below this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_Y_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_Y_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_Y_OFFSET (0x33b8)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_Y_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_clip_min_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c240);
    system_sw_write_32(base + 0x1c240, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_clip_min_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c240) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip max Y
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximal value for Y.  Values above this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_Y_DEFAULT (0x3FF)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_Y_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_Y_OFFSET (0x33bc)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_Y_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_clip_max_y_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c244);
    system_sw_write_32(base + 0x1c244, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_clip_max_y_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c244) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip min UV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimal value for Cb, Cr.  Values below this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_UV_DEFAULT (0x000)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_UV_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_UV_OFFSET (0x33c0)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MIN_UV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_clip_min_uv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c248);
    system_sw_write_32(base + 0x1c248, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_clip_min_uv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c248) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Clip max UV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Maximal value for Cb, Cr.  Values above this are clipped.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_UV_DEFAULT (0x3FF)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_UV_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_UV_OFFSET (0x33c4)
#define ACAMERA_ISP_DS1_CS_CONV_CLIP_MAX_UV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_clip_max_uv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c24c);
    system_sw_write_32(base + 0x1c24c, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_clip_max_uv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c24c) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask RY
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 1 (R or Y).  Bit-wise and of this value and video data. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_RY_DEFAULT (0x3FF)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_RY_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_RY_OFFSET (0x33c8)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_RY_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_data_mask_ry_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c250);
    system_sw_write_32(base + 0x1c250, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_data_mask_ry_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c250) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask GU
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 2 (G or U).  Bit-wise and of this value and video data.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_GU_DEFAULT (0x3FF)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_GU_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_GU_OFFSET (0x33cc)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_GU_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_data_mask_gu_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c254);
    system_sw_write_32(base + 0x1c254, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_data_mask_gu_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c254) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Data mask BV
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Data mask for channel 3 (B or V).  Bit-wise and of this value and video data.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_BV_DEFAULT (0x3FF)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_BV_DATASIZE (10)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_BV_OFFSET (0x33d0)
#define ACAMERA_ISP_DS1_CS_CONV_DATA_MASK_BV_MASK (0x3ff)

// args: data (10-bit)
static __inline void acamera_isp_ds1_cs_conv_data_mask_bv_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c258);
    system_sw_write_32(base + 0x1c258, (((uint32_t) (data & 0x3ff)) << 0) | (curr & 0xfffffc00));
}
static __inline uint16_t acamera_isp_ds1_cs_conv_data_mask_bv_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c258) & 0x3ff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds cs conv dither
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Enable dither
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Enables dithering module
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DITHER_ENABLE_DITHER_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_ENABLE_DITHER_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_ENABLE_DITHER_OFFSET (0x33d4)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_ENABLE_DITHER_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_dither_enable_dither_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c25c);
    system_sw_write_32(base + 0x1c25c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_dither_enable_dither_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c25c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Dither amount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= dither to 9 bits; 1=dither to 8 bits; 2=dither to 7 bits; 3=dither to 6 bits 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DITHER_DITHER_AMOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_DITHER_AMOUNT_DATASIZE (2)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_DITHER_AMOUNT_OFFSET (0x33d4)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_DITHER_AMOUNT_MASK (0x6)

// args: data (2-bit)
static __inline void acamera_isp_ds1_cs_conv_dither_dither_amount_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c25c);
    system_sw_write_32(base + 0x1c25c, (((uint32_t) (data & 0x3)) << 1) | (curr & 0xfffffff9));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_dither_dither_amount_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c25c) & 0x6) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: Shift mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0= output is LSB aligned; 1=output is MSB aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_CS_CONV_DITHER_SHIFT_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_SHIFT_MODE_DATASIZE (1)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_SHIFT_MODE_OFFSET (0x33d4)
#define ACAMERA_ISP_DS1_CS_CONV_DITHER_SHIFT_MODE_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_ds1_cs_conv_dither_shift_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c25c);
    system_sw_write_32(base + 0x1c25c, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_ds1_cs_conv_dither_shift_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c25c) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Group: ds dma writer
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// DMA writer controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Format
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_FORMAT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_FORMAT_DATASIZE (8)
#define ACAMERA_ISP_DS1_DMA_WRITER_FORMAT_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_FORMAT_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_ds1_dma_writer_format_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_format_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Base mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Base DMA packing mode for RGB/RAW/YUV etc (see ISP guide)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BASE_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BASE_MODE_DATASIZE (5)
#define ACAMERA_ISP_DS1_DMA_WRITER_BASE_MODE_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_BASE_MODE_MASK (0x1f)

// args: data (5-bit)
static __inline void acamera_isp_ds1_dma_writer_base_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0x1f)) << 0) | (curr & 0xffffffe0));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_base_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0x1f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane select for planar/semi-planar base modes.  Only used if planar/semi-planar outputs required
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_PLANE_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_PLANE_SELECT_DATASIZE (2)
#define ACAMERA_ISP_DS1_DMA_WRITER_PLANE_SELECT_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_PLANE_SELECT_MASK (0xc0)

// args: data (2-bit)
static __inline void acamera_isp_ds1_dma_writer_plane_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0x3)) << 6) | (curr & 0xffffff3f));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_plane_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0xc0) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: single frame
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = All frames are written(after frame_write_on= 1), 1= only 1st frame written ( after frame_write_on =1) debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_SINGLE_FRAME_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_SINGLE_FRAME_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_SINGLE_FRAME_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_SINGLE_FRAME_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_single_frame_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_single_frame_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: frame write on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 = no frames written(when switched from 1, current frame completes writing before stopping),
//        1= write frame(s) (write single or continous frame(s) )
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WRITE_ON_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WRITE_ON_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WRITE_ON_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WRITE_ON_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_frame_write_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_frame_write_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: axi xact comp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = dont wait for axi transaction completion at end of frame(just all transfers accepted). 1 = wait for all transactions completed
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_XACT_COMP_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_XACT_COMP_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_XACT_COMP_OFFSET (0x33d8)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_XACT_COMP_MASK (0x800)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_xact_comp_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c260);
    system_sw_write_32(base + 0x1c260, (((uint32_t) (data & 0x1)) << 11) | (curr & 0xfffff7ff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_xact_comp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c260) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: active width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video width in pixels 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_WIDTH_OFFSET (0x33dc)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_active_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c264);
    system_sw_write_32(base + 0x1c264, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_active_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c264) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: active height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video height in lines 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_HEIGHT_OFFSET (0x33dc)
#define ACAMERA_ISP_DS1_DMA_WRITER_ACTIVE_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_active_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c264);
    system_sw_write_32(base + 0x1c264, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_active_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c264) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: bank0_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 0 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_BASE_OFFSET (0x33e0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_bank0_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c268, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_bank0_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c268);
}
// ------------------------------------------------------------------------------ //
// Register: bank1_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 1 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK1_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK1_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK1_BASE_OFFSET (0x33e4)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK1_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_bank1_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c26c, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_bank1_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c26c);
}
// ------------------------------------------------------------------------------ //
// Register: bank2_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 2 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK2_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK2_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK2_BASE_OFFSET (0x33e8)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK2_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_bank2_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c270, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_bank2_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c270);
}
// ------------------------------------------------------------------------------ //
// Register: bank3_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 3 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK3_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK3_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK3_BASE_OFFSET (0x33ec)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK3_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_bank3_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c274, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_bank3_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c274);
}
// ------------------------------------------------------------------------------ //
// Register: bank4_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 4 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK4_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK4_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK4_BASE_OFFSET (0x33f0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK4_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_bank4_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c278, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_bank4_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c278);
}
// ------------------------------------------------------------------------------ //
// Register: max bank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// highest bank*_base to use for frame writes before recycling to bank0_base, only 0 to 4 are valid
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_MAX_BANK_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_MAX_BANK_DATASIZE (3)
#define ACAMERA_ISP_DS1_DMA_WRITER_MAX_BANK_OFFSET (0x33f4)
#define ACAMERA_ISP_DS1_DMA_WRITER_MAX_BANK_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_ds1_dma_writer_max_bank_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c27c);
    system_sw_write_32(base + 0x1c27c, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_max_bank_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c27c) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bank0 restart
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = normal operation, 1= restart bank counter to bank0 for next frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_RESTART_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_RESTART_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_RESTART_OFFSET (0x33f4)
#define ACAMERA_ISP_DS1_DMA_WRITER_BANK0_RESTART_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_bank0_restart_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c27c);
    system_sw_write_32(base + 0x1c27c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_bank0_restart_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c27c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Line_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Indicates the offset in bytes from the start of one line to the next line.  
//        This value should be equal to or larger than one line of image data and should be word-aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINE_OFFSET_DEFAULT (0x1000)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINE_OFFSET_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINE_OFFSET_OFFSET (0x33f8)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINE_OFFSET_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_dma_writer_line_offset_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c280, data);
}
static __inline uint32_t acamera_isp_ds1_dma_writer_line_offset_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c280);
}
// ------------------------------------------------------------------------------ //
// Register: wbank curr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// write bank currently active. valid values =0-4. updated at start of frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_CURR_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_CURR_DATASIZE (3)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_CURR_OFFSET (0x33fc)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_CURR_MASK (0xe)

// args: data (3-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_wbank_curr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c284) & 0xe) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: wbank active
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = wbank_curr is being written to. Goes high at start of writes, low at last write transfer/completion on axi. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_ACTIVE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_ACTIVE_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_ACTIVE_OFFSET (0x33fc)
#define ACAMERA_ISP_DS1_DMA_WRITER_WBANK_ACTIVE_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_wbank_active_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c284) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame icount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of incomming frames (starts) to vdma_writer on video input, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_ICOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_ICOUNT_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_ICOUNT_OFFSET (0x3408)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_ICOUNT_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_ds1_dma_writer_frame_icount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c290) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame wcount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of outgoing frame writes (starts) from vdma_writer sent to AXI output, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WCOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WCOUNT_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WCOUNT_OFFSET (0x3408)
#define ACAMERA_ISP_DS1_DMA_WRITER_FRAME_WCOUNT_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_ds1_dma_writer_frame_wcount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c290) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_bresp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate bad  bresp captured 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_BRESP_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_BRESP_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_BRESP_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_BRESP_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_fail_bresp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_awmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when awmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_AWMAXWAIT_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_AWMAXWAIT_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_fail_awmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WMAXWAIT_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WMAXWAIT_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_fail_wmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wxact_ostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wxact_ostand_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_fail_wxact_ostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_width detected 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_vi_fail_active_width_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_height detected ( also raised on missing field!) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_vi_fail_active_height_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interline_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interline blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_vi_fail_interline_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interframe_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interframe blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_vi_fail_interframe_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: video_alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  active high, problem found on video port(s) ( active width/height or interline/frame blanks failure) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_VIDEO_ALARM_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_VIDEO_ALARM_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_VIDEO_ALARM_OFFSET (0x3410)
#define ACAMERA_ISP_DS1_DMA_WRITER_VIDEO_ALARM_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_dma_writer_video_alarm_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c298) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: blk_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        block status output (reserved)
//                          -- blk_status(0) = wfifo_fail_full
//                          -- blk_status(1) = wfifo_fail_empty
//                          -- blk_status(4) = pack_fail_overflow
//                          -- blk_status(24) = intw_fail_user_intfc_sig
//                          -- blk_status(others) =  zero     
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_BLK_STATUS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_BLK_STATUS_DATASIZE (32)
#define ACAMERA_ISP_DS1_DMA_WRITER_BLK_STATUS_OFFSET (0x3414)
#define ACAMERA_ISP_DS1_DMA_WRITER_BLK_STATUS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_ds1_dma_writer_blk_status_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c29c);
}
// ------------------------------------------------------------------------------ //
// Register: lines_wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Number of lines to write from base address before wrapping back to base address. 0 = no wrapping, >0 = last line written before wrapping
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINES_WRAPPED_OFFSET (0x3418)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINES_WRAPPED_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2a0);
    system_sw_write_32(base + 0x1c2a0, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2a0) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_first
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line number of first linetick. 0  = no linetick, >0 = line number to generate linetick 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_FIRST_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_FIRST_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_FIRST_OFFSET (0x341c)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_FIRST_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_linetick_first_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2a4);
    system_sw_write_32(base + 0x1c2a4, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_linetick_first_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2a4) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_repeat
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line repeat interval of linetick. 0 = no repeat, >0 = repeat interval in lines 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_REPEAT_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_REPEAT_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_REPEAT_OFFSET (0x3420)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_REPEAT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_linetick_repeat_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2a8);
    system_sw_write_32(base + 0x1c2a8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_linetick_repeat_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2a8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_eol
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linetick start/end of line control. 0 = use start of line, 1 = use end of line to generate linetick
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_EOL_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_EOL_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_EOL_OFFSET (0x3424)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_EOL_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_linetick_eol_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2ac);
    system_sw_write_32(base + 0x1c2ac, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_linetick_eol_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2ac) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_delay
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Linetick delay in vcke cycles to add to min 3 cycle latency from acl_vi. 0-65535.
//        Must be less than next linetick generation time or count will not mature and no linetick is not produced.
//          --NOTE: linetick delay  can run past end of frame/field and also into next frame!
//          --      Take care maturity time is less than next configured linetick generation postion!
//          --      Take care when changing config between frame too! 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_DELAY_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_DELAY_DATASIZE (16)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_DELAY_OFFSET (0x3424)
#define ACAMERA_ISP_DS1_DMA_WRITER_LINETICK_DELAY_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_dma_writer_linetick_delay_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2ac);
    system_sw_write_32(base + 0x1c2ac, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_dma_writer_linetick_delay_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2ac) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        active high (debug only), enables posting of pagewarm dummy writes to SMMU for early page translation of upcomming 4K pages. 
//        Recommend SMMU has min 8 page cache to avoid translation miss. Pagewarms are posted as dummy writes with wstrb= 0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_PAGEWARM_ON_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_PAGEWARM_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0= static value (axi_id_value) for awid/wid, 1 = incrementing value per transaction for awid/wid wrapping to 0 after axi_id_value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_MULTI_DEFAULT (0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_MULTI_DATASIZE (1)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_MULTI_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_MULTI_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_id_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_id_multi_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 0x3
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_BURSTSPLIT_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_BURSTSPLIT_MASK (0xc)

// args: data (2-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0x3)) << 2) | (curr & 0xfffffff3));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0xc) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 0xf
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_CACHE_VALUE_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_CACHE_VALUE_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding write transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAXOSTAND_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_max_awlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for awlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAX_AWLEN_DEFAULT (0xf)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAX_AWLEN_DATASIZE (4)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAX_AWLEN_OFFSET (0x3428)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_MAX_AWLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_max_awlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b0);
    system_sw_write_32(base + 0x1c2b0, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_max_awlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b0) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid. Good default = 0000
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_VALUE_OFFSET (0x342c)
#define ACAMERA_ISP_DS1_DMA_WRITER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_ds1_dma_writer_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b4);
    system_sw_write_32(base + 0x1c2b4, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_ds1_dma_writer_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b4) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: ds uv dma writer
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// DMA writer controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Format
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Format
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FORMAT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FORMAT_DATASIZE (8)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FORMAT_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FORMAT_MASK (0xff)

// args: data (8-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_format_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0xff)) << 0) | (curr & 0xffffff00));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_format_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Base mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Base DMA packing mode for RGB/RAW/YUV etc (see ISP guide)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BASE_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BASE_MODE_DATASIZE (5)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BASE_MODE_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BASE_MODE_MASK (0x1f)

// args: data (5-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_base_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0x1f)) << 0) | (curr & 0xffffffe0));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_base_mode_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0x1f) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Plane select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Plane select for planar/semi-planar base modes.  Only used if planar/semi-planar outputs required.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PLANE_SELECT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PLANE_SELECT_DATASIZE (2)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PLANE_SELECT_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PLANE_SELECT_MASK (0xc0)

// args: data (2-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_plane_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0x3)) << 6) | (curr & 0xffffff3f));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_plane_select_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0xc0) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: single frame
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = All frames are written(after frame_write_on= 1), 1= only 1st frame written ( after frame_write_on =1) debug only
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_SINGLE_FRAME_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_SINGLE_FRAME_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_SINGLE_FRAME_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_SINGLE_FRAME_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_single_frame_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_single_frame_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: frame write on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0 = no frames written(when switched from 1, current frame completes writing before stopping),
//        1= write frame(s) (write single or continous frame(s) )
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WRITE_ON_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WRITE_ON_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WRITE_ON_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WRITE_ON_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_frame_write_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_frame_write_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: axi xact comp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = dont wait for axi transaction completion at end of frame(just all transfers accepted). 1 = wait for all transactions completed
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_XACT_COMP_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_XACT_COMP_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_XACT_COMP_OFFSET (0x3430)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_XACT_COMP_MASK (0x800)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_xact_comp_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2b8);
    system_sw_write_32(base + 0x1c2b8, (((uint32_t) (data & 0x1)) << 11) | (curr & 0xfffff7ff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_xact_comp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2b8) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: active width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video width in pixels 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_WIDTH_DEFAULT (0x780)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_WIDTH_OFFSET (0x3434)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_active_width_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2bc);
    system_sw_write_32(base + 0x1c2bc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_active_width_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2bc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: active height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Active video height in lines 128-8000
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_HEIGHT_DEFAULT (0x438)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_HEIGHT_OFFSET (0x3434)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_ACTIVE_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_active_height_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2bc);
    system_sw_write_32(base + 0x1c2bc, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_active_height_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2bc) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: bank0_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 0 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_BASE_OFFSET (0x3438)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank0_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2c0, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_bank0_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2c0);
}
// ------------------------------------------------------------------------------ //
// Register: bank1_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 1 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK1_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK1_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK1_BASE_OFFSET (0x343c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK1_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank1_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2c4, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_bank1_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2c4);
}
// ------------------------------------------------------------------------------ //
// Register: bank2_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 2 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK2_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK2_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK2_BASE_OFFSET (0x3440)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK2_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank2_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2c8, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_bank2_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2c8);
}
// ------------------------------------------------------------------------------ //
// Register: bank3_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 3 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK3_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK3_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK3_BASE_OFFSET (0x3444)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK3_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank3_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2cc, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_bank3_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2cc);
}
// ------------------------------------------------------------------------------ //
// Register: bank4_base
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// bank 4 base address for frame buffer, should be word-aligned
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK4_BASE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK4_BASE_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK4_BASE_OFFSET (0x3448)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK4_BASE_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank4_base_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2d0, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_bank4_base_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2d0);
}
// ------------------------------------------------------------------------------ //
// Register: max bank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// highest bank*_base to use for frame writes before recycling to bank0_base, only 0 to 4 are valid
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_MAX_BANK_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_MAX_BANK_DATASIZE (3)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_MAX_BANK_OFFSET (0x344c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_MAX_BANK_MASK (0x7)

// args: data (3-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_max_bank_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2d4);
    system_sw_write_32(base + 0x1c2d4, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_max_bank_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2d4) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: bank0 restart
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 0 = normal operation, 1= restart bank counter to bank0 for next frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_RESTART_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_RESTART_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_RESTART_OFFSET (0x344c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BANK0_RESTART_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_bank0_restart_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2d4);
    system_sw_write_32(base + 0x1c2d4, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_bank0_restart_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2d4) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: Line_offset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Indicates the offset in bytes from the start of one line to the next line.  
//        This value should be equal to or larger than one line of image data and should be word-aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINE_OFFSET_DEFAULT (0x1000)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINE_OFFSET_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINE_OFFSET_OFFSET (0x3450)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINE_OFFSET_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_line_offset_write(uintptr_t base, uint32_t data) {
    system_sw_write_32(base + 0x1c2d8, data);
}
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_line_offset_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2d8);
}
// ------------------------------------------------------------------------------ //
// Register: wbank curr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// write bank currently active. valid values =0-4. updated at start of frame write
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_CURR_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_CURR_DATASIZE (3)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_CURR_OFFSET (0x3454)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_CURR_MASK (0xe)

// args: data (3-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_wbank_curr_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2dc) & 0xe) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: wbank active
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = wbank_curr is being written to. Goes high at start of writes, low at last write transfer/completion on axi. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_ACTIVE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_ACTIVE_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_ACTIVE_OFFSET (0x3454)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_WBANK_ACTIVE_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_wbank_active_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2dc) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame icount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of incomming frames (starts) to vdma_writer on video input, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_ICOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_ICOUNT_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_ICOUNT_OFFSET (0x3460)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_ICOUNT_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_frame_icount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2e8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: frame wcount
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// count of outgoing frame writes (starts) from vdma_writer sent to AXI output, non resetable, rolls over, updates at pixel 1 of new frame on video in
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WCOUNT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WCOUNT_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WCOUNT_OFFSET (0x3460)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_FRAME_WCOUNT_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_frame_wcount_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2e8) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_bresp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate bad  bresp captured 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_BRESP_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_BRESP_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_BRESP_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_BRESP_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_fail_bresp_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_awmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when awmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_AWMAXWAIT_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_fail_awmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wmaxwait
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wmaxwait_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WMAXWAIT_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_fail_wmaxwait_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_fail_wxact_ostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high when wxact_ostand_limit reached 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_FAIL_WXACT_OSTAND_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_fail_wxact_ostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_width detected 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_WIDTH_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_vi_fail_active_width_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_active_height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate mismatched active_height detected ( also raised on missing field!) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_ACTIVE_HEIGHT_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_vi_fail_active_height_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interline_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interline blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERLINE_BLANKS_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_vi_fail_interline_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: vi_fail_interframe_blanks
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  clearable alarm, high to indicate interframe blanking below min 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VI_FAIL_INTERFRAME_BLANKS_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_vi_fail_interframe_blanks_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: video_alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  active high, problem found on video port(s) ( active width/height or interline/frame blanks failure) 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VIDEO_ALARM_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VIDEO_ALARM_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VIDEO_ALARM_OFFSET (0x3468)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_VIDEO_ALARM_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_video_alarm_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c2f0) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: blk_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        block status output (reserved)
//                          -- blk_status(0) = wfifo_fail_full
//                          -- blk_status(1) = wfifo_fail_empty
//                          -- blk_status(4) = pack_fail_overflow
//                          -- blk_status(24) = intw_fail_user_intfc_sig
//                          -- blk_status(others) =  zero     
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BLK_STATUS_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BLK_STATUS_DATASIZE (32)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BLK_STATUS_OFFSET (0x346c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_BLK_STATUS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_ds1_uv_dma_writer_blk_status_read(uintptr_t base) {
    return system_sw_read_32(base + 0x1c2f4);
}
// ------------------------------------------------------------------------------ //
// Register: lines_wrapped
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Number of lines to write from base address before wrapping back to base address. 0 = no wrapping, >0 = last line written before wrapping
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINES_WRAPPED_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINES_WRAPPED_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINES_WRAPPED_OFFSET (0x3470)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINES_WRAPPED_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_lines_wrapped_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2f8);
    system_sw_write_32(base + 0x1c2f8, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_lines_wrapped_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2f8) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_first
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line number of first linetick. 0  = no linetick, >0 = line number to generate linetick 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_FIRST_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_FIRST_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_FIRST_OFFSET (0x3474)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_FIRST_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_linetick_first_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c2fc);
    system_sw_write_32(base + 0x1c2fc, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_linetick_first_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c2fc) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_repeat
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Line repeat interval of linetick. 0 = no repeat, >0 = repeat interval in lines 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_REPEAT_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_REPEAT_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_REPEAT_OFFSET (0x3478)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_REPEAT_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_linetick_repeat_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c300);
    system_sw_write_32(base + 0x1c300, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_linetick_repeat_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c300) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_eol
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Linetick start/end of line control. 0 = use start of line, 1 = use end of line to generate linetick
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_EOL_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_EOL_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_EOL_OFFSET (0x347c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_EOL_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_linetick_eol_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c304);
    system_sw_write_32(base + 0x1c304, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_linetick_eol_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c304) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: linetick_delay
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Linetick delay in vcke cycles to add to min 3 cycle latency from acl_vi. 0-65535.
//        Must be less than next linetick generation time or count will not mature and no linetick is not produced.
//          --NOTE: linetick delay  can run past end of frame/field and also into next frame!
//          --      Take care maturity time is less than next configured linetick generation postion!
//          --      Take care when changing config between frame too! 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_DELAY_DEFAULT (0x0000)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_DELAY_DATASIZE (16)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_DELAY_OFFSET (0x347c)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_LINETICK_DELAY_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_linetick_delay_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c304);
    system_sw_write_32(base + 0x1c304, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_ds1_uv_dma_writer_linetick_delay_read(uintptr_t base) {
    return (uint16_t)((system_sw_read_32(base + 0x1c304) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: pagewarm_on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        active high (debug only), enables posting of pagewarm dummy writes to SMMU for early page translation of upcomming 4K pages. 
//        Recommend SMMU has min 8 page cache to avoid translation miss. Pagewarms are posted as dummy writes with wstrb= 0
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PAGEWARM_ON_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PAGEWARM_ON_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PAGEWARM_ON_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_PAGEWARM_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_pagewarm_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_pagewarm_on_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0= static value (axi_id_value) for awid/wid, 1 = incrementing value per transaction for awid/wid wrapping to 0 after axi_id_value
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_MULTI_DEFAULT (0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_MULTI_DATASIZE (1)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_MULTI_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_MULTI_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_id_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_id_multi_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: axi_burstsplit
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        memory boundary that splits bursts: 0=2Transfers,1=4Transfers,2=8Transfers,3=16Transfers. (for axi_data_w=128,  16transfers=256Bytes). Good default = 0x3
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_BURSTSPLIT_DEFAULT (0x3)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_BURSTSPLIT_DATASIZE (2)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_BURSTSPLIT_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_BURSTSPLIT_MASK (0xc)

// args: data (2-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_burstsplit_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0x3)) << 2) | (curr & 0xfffffff3));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_burstsplit_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0xc) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: axi_cache_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awcache. Good default = 0xf
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_CACHE_VALUE_DEFAULT (0xf)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_CACHE_VALUE_DATASIZE (4)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_CACHE_VALUE_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_CACHE_VALUE_MASK (0xf00)

// args: data (4-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_cache_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0xf)) << 8) | (curr & 0xfffff0ff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_cache_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0xf00) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: axi_maxostand
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max outstanding write transactions (bursts) allowed. zero means no maximum(uses internal limit of 2048). 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAXOSTAND_DEFAULT (0x00)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAXOSTAND_DATASIZE (8)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAXOSTAND_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAXOSTAND_MASK (0xff0000)

// args: data (8-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_maxostand_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0xff)) << 16) | (curr & 0xff00ffff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_maxostand_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: axi_max_awlen
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        max value to use for awlen (axi burst length). 0000= max 1 transfer/burst , upto 1111= max 16 transfers/burst
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAX_AWLEN_DEFAULT (0xf)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAX_AWLEN_DATASIZE (4)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAX_AWLEN_OFFSET (0x3480)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_MAX_AWLEN_MASK (0xf000000)

// args: data (4-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_max_awlen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c308);
    system_sw_write_32(base + 0x1c308, (((uint32_t) (data & 0xf)) << 24) | (curr & 0xf0ffffff));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_max_awlen_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c308) & 0xf000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: axi_id_value
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        value to send for awid, wid and expected on bid. Good default = 0000
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_VALUE_DEFAULT (0x0)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_VALUE_DATASIZE (4)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_VALUE_OFFSET (0x3484)
#define ACAMERA_ISP_DS1_UV_DMA_WRITER_AXI_ID_VALUE_MASK (0xf)

// args: data (4-bit)
static __inline void acamera_isp_ds1_uv_dma_writer_axi_id_value_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c30c);
    system_sw_write_32(base + 0x1c30c, (((uint32_t) (data & 0xf)) << 0) | (curr & 0xfffffff0));
}
static __inline uint8_t acamera_isp_ds1_uv_dma_writer_axi_id_value_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c30c) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Group: multi ctx
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Config done
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal is only required in multi-context mode
//            Once configuration for ping/pong address space is done, MCU must write 1 into this address
//            This register is self-clearing. So the read-back will be 0
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_MULTI_CTX_CONFIG_DONE_DEFAULT (0)
#define ACAMERA_ISP_MULTI_CTX_CONFIG_DONE_DATASIZE (1)
#define ACAMERA_ISP_MULTI_CTX_CONFIG_DONE_OFFSET (0x3488)
#define ACAMERA_ISP_MULTI_CTX_CONFIG_DONE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_multi_ctx_config_done_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_sw_read_32(base + 0x1c310);
    system_sw_write_32(base + 0x1c310, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_multi_ctx_config_done_read(uintptr_t base) {
    return (uint8_t)((system_sw_read_32(base + 0x1c310) & 0x1) >> 0);
}

// ------------------------------------------------------------------------------ //
#endif //__ACAMERA_ISP1_CONFIG_H__

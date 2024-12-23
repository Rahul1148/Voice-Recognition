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

#ifndef __ACAMERA_ISP_CONFIG_H__
#define __ACAMERA_ISP_CONFIG_H__


#include "acamera_isp1_config.h"
#include "system_sw_io.h"

#include "system_hw_io.h"

// ------------------------------------------------------------------------------ //
// Instance 'isp' of module 'common_config'
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_BASE_ADDR (0x0)
#define ACAMERA_ISP_SIZE (0x100)

#define ACAMERA_ISP_MAX_ADDR (4 * 0x3ffff)

// ------------------------------------------------------------------------------ //
// Group: id
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: API
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ID_API_DEFAULT (0x0)
#define ACAMERA_ISP_ID_API_DATASIZE (32)
#define ACAMERA_ISP_ID_API_OFFSET (0x0)
#define ACAMERA_ISP_ID_API_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_id_api_read(uintptr_t base) {
    return system_hw_read_32(0x0);
}
// ------------------------------------------------------------------------------ //
// Register: Product
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ID_PRODUCT_DEFAULT (0x0)
#define ACAMERA_ISP_ID_PRODUCT_DATASIZE (32)
#define ACAMERA_ISP_ID_PRODUCT_OFFSET (0x4)
#define ACAMERA_ISP_ID_PRODUCT_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_id_product_read(uintptr_t base) {
    return system_hw_read_32(0x4);
}
// ------------------------------------------------------------------------------ //
// Register: Version
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ID_VERSION_DEFAULT (0x0)
#define ACAMERA_ISP_ID_VERSION_DATASIZE (32)
#define ACAMERA_ISP_ID_VERSION_OFFSET (0x8)
#define ACAMERA_ISP_ID_VERSION_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_id_version_read(uintptr_t base) {
    return system_hw_read_32(0x8);
}
// ------------------------------------------------------------------------------ //
// Register: Revision
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ID_REVISION_DEFAULT (0x0)
#define ACAMERA_ISP_ID_REVISION_DATASIZE (32)
#define ACAMERA_ISP_ID_REVISION_OFFSET (0xc)
#define ACAMERA_ISP_ID_REVISION_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_id_revision_read(uintptr_t base) {
    return system_hw_read_32(0xc);
}
// ------------------------------------------------------------------------------ //
// Group: isp global
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Miscellaneous top-level ISP controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Global FSM reset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            1 = synchronous reset of FSMs in design (additional recovery option after broken frame)
//            when the MCU detects a broken frame or any other abnormal condition, the global_fsm_rest
//            can be used (if self recovery fails).
//            MCU needs to follow a certain sequence for the same
//                1.	Masking interrupts may be needed during the global fsm reset sequence.
//                2.	Ensure vcke is active to the ISP.
//                3.	Configure the input port register ISP_COMMON:input port: mode request to safe_stop mode.
//                4.	Read back the ISP_COMMON:input port: mode status register to see the status of mode request. 
//                    And wait until it shows the correct status (stopped) to ensure sensor is in vblank state.
//                5.	Assert the global fsm reset.
//                6.	Wait until ISP_COMMON:isp global monitor: global_fsm_rst_status read back 1.
//                7.	Clear the global fsm reset
//                8.	Wait until ISP_COMMON:isp global monitor: global_fsm_rst_status finishes (read back 0). Note: there is 1024 clock cycles internal extension.
//                9.	Reconfigure the ISP configuration space.
//                10.	Unmask the necessary interrupt sources.
//                11.	Configure the input port in safe_start mode.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_GLOBAL_FSM_RESET_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_GLOBAL_FSM_RESET_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_GLOBAL_FSM_RESET_OFFSET (0x10)
#define ACAMERA_ISP_ISP_GLOBAL_GLOBAL_FSM_RESET_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_global_fsm_reset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x10);
    system_hw_write_32(0x10, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_global_fsm_reset_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x10) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: fr scaler fsm reset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = synchronous reset of FSMs in fr pipe scaler design
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_FR_SCALER_FSM_RESET_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_FR_SCALER_FSM_RESET_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_FR_SCALER_FSM_RESET_OFFSET (0x10)
#define ACAMERA_ISP_ISP_GLOBAL_FR_SCALER_FSM_RESET_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_fr_scaler_fsm_reset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x10);
    system_hw_write_32(0x10, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_fr_scaler_fsm_reset_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x10) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: ds scaler fsm reset
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 1 = synchronous reset of FSMs in ds pipe scaler design
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DS1_SCALER_FSM_RESET_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_DS1_SCALER_FSM_RESET_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_DS1_SCALER_FSM_RESET_OFFSET (0x10)
#define ACAMERA_ISP_ISP_GLOBAL_DS1_SCALER_FSM_RESET_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_ds1_scaler_fsm_reset_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x10);
    system_hw_write_32(0x10, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_isp_global_ds1_scaler_fsm_reset_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x10) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: dma global config
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        [0]    : check bid
//        [1]    : check rid
//
//        The following signals are diagnostic signals which helps identifying some of the AXI interface
//        error cases. This must be used only as debug signals. You should follow these sequence
//        - Mask the dma error interrupt
//        - clear DMA interrupt if there is an active interrupt
//        - Write appropriate values to these registers
//        - Clear DMA alarms to clear the existing alarm
//        - unmask the DMA error interrpt
//
//
//        [2]    : frame_write_cancel/frame_read_cancel
//        [10:3] : awmaxwait_limit/armaxwait_limit
//        [18:11]: wmaxwait_limit
//        [26:19]: waxct_ostand_limit/rxnfr_ostand_limit
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DMA_GLOBAL_CONFIG_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_DMA_GLOBAL_CONFIG_DATASIZE (27)
#define ACAMERA_ISP_ISP_GLOBAL_DMA_GLOBAL_CONFIG_OFFSET (0x10)
#define ACAMERA_ISP_ISP_GLOBAL_DMA_GLOBAL_CONFIG_MASK (0x7ffffff0)

// args: data (27-bit)
static __inline void acamera_isp_isp_global_dma_global_config_write(uintptr_t base, uint32_t data) {
    uint32_t curr = system_hw_read_32(0x10);
    system_hw_write_32(0x10, (((uint32_t) (data & 0x7ffffff)) << 4) | (curr & 0x8000000f));
}
static __inline uint32_t acamera_isp_isp_global_dma_global_config_read(uintptr_t base) {
    return (uint32_t)((system_hw_read_32(0x10) & 0x7ffffff0) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: Flush hblank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Horizontal blanking interval during regeneration (0=measured input interval)
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_FLUSH_HBLANK_DEFAULT (0x20)
#define ACAMERA_ISP_ISP_GLOBAL_FLUSH_HBLANK_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_FLUSH_HBLANK_OFFSET (0x14)
#define ACAMERA_ISP_ISP_GLOBAL_FLUSH_HBLANK_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_isp_global_flush_hblank_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x14);
    system_hw_write_32(0x14, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_isp_global_flush_hblank_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x14) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: ISP monitor select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_DEFAULT (4)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_DATASIZE (3)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_OFFSET (0x14)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_MASK (0x70000)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_LINEARISED_DATA_AFTER_LINEARISED_CLUSTER_MSB_ALIGNED_DATA190_16D0 (0)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_DATA_AFTER_FRONTEND_CLUSTER_MSB_ALIGNED_DATA190_16D0 (1)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_DATA_AFTER_NR_CLUSTER_MSB_ALIGNED_DATA190_16D0 (2)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_CNR_OUTPUT_B110_G110_R110 (3)
#define ACAMERA_ISP_ISP_GLOBAL_ISP_MONITOR_SELECT_OUTPUT_FORCES_TO_0 (4)

// args: data (3-bit)
static __inline void acamera_isp_isp_global_isp_monitor_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x14);
    system_hw_write_32(0x14, (((uint32_t) (data & 0x7)) << 16) | (curr & 0xfff8ffff));
}
static __inline uint8_t acamera_isp_isp_global_isp_monitor_select_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x14) & 0x70000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: Recovery mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_DEFAULT (0x1)
#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_OFFSET (0x14)
#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_MASK (0x1000000)
#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_MINIMUM_INPUT_FRAME_NUMBER_OF_LINES_FOR_SELF_RECOVERY_UNSPECIFIED (0)
#define ACAMERA_ISP_ISP_GLOBAL_RECOVERY_MODE_MINIMUM_INPUT_FRAME_NUMBER_OF_LINES_FOR_SELF_RECOVERY_0 (1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_recovery_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x14);
    system_hw_write_32(0x14, (((uint32_t) (data & 0x1)) << 24) | (curr & 0xfeffffff));
}
static __inline uint8_t acamera_isp_isp_global_recovery_mode_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x14) & 0x1000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: interline_blanks_min
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimun H-blank. The frame monitor will checke the frame geometry against this value
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERLINE_BLANKS_MIN_DEFAULT (0x20)
#define ACAMERA_ISP_ISP_GLOBAL_INTERLINE_BLANKS_MIN_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_INTERLINE_BLANKS_MIN_OFFSET (0x18)
#define ACAMERA_ISP_ISP_GLOBAL_INTERLINE_BLANKS_MIN_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_isp_global_interline_blanks_min_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x18);
    system_hw_write_32(0x18, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_isp_global_interline_blanks_min_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x18) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: interframe_blanks_min
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Minimun V-blank. The frame monitor will checke the frame geometry against this value
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERFRAME_BLANKS_MIN_DEFAULT (0x28)
#define ACAMERA_ISP_ISP_GLOBAL_INTERFRAME_BLANKS_MIN_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_INTERFRAME_BLANKS_MIN_OFFSET (0x18)
#define ACAMERA_ISP_ISP_GLOBAL_INTERFRAME_BLANKS_MIN_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_isp_global_interframe_blanks_min_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x18);
    system_hw_write_32(0x18, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_isp_global_interframe_blanks_min_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x18) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: watchdog timer max count
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Max count after which watchdog timer should give an interrupt. this count is between frame start and frame end
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_WATCHDOG_TIMER_MAX_COUNT_DEFAULT (0xFFFFFFFF)
#define ACAMERA_ISP_ISP_GLOBAL_WATCHDOG_TIMER_MAX_COUNT_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_WATCHDOG_TIMER_MAX_COUNT_OFFSET (0x1c)
#define ACAMERA_ISP_ISP_GLOBAL_WATCHDOG_TIMER_MAX_COUNT_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_isp_global_watchdog_timer_max_count_write(uintptr_t base, uint32_t data) {
    system_hw_write_32(0x1c, data);
}
static __inline uint32_t acamera_isp_isp_global_watchdog_timer_max_count_read(uintptr_t base) {
    return system_hw_read_32(0x1c);
}
// ------------------------------------------------------------------------------ //
// Register: Mcu override config select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            mcu override config select. When this bit is set, MCU takes control of the ISP ping-pong config swap.
//            when is signal is set to 1, ISP core works in slave mode and selects configuration space based on MCU instruction.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MCU_OVERRIDE_CONFIG_SELECT_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_OVERRIDE_CONFIG_SELECT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_OVERRIDE_CONFIG_SELECT_OFFSET (0x20)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_OVERRIDE_CONFIG_SELECT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_mcu_override_config_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x20);
    system_hw_write_32(0x20, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_mcu_override_config_select_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x20) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: Mcu ping pong config select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                This signal is valid when Mcu_override_config_select is set to 1.
//                when mcu takes control of the config select, this signal indicated whether to use ping and pong config space
//                If this signal is changed during active active frame, the hardware makes sure that the config space is changed 
//                in the next vertical blanking
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_OFFSET (0x20)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_MASK (0x2)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_USE_PONG_ADDRESS_SPACE (0)
#define ACAMERA_ISP_ISP_GLOBAL_MCU_PING_PONG_CONFIG_SELECT_USE_PING_ADDRESS_SPACE (1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_mcu_ping_pong_config_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x20);
    system_hw_write_32(0x20, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_mcu_ping_pong_config_select_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x20) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: multi context mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Multi-context control mode
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_OFFSET (0x20)
#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_MASK (0x100)
#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_DEFAULT_MODE_THIS_IS_FOR_SINGLE_CONTEXT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MULTI_CONTEXT_MODE_MULTICONTEXT_MODE (1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_multi_context_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x20);
    system_hw_write_32(0x20, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_isp_global_multi_context_mode_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x20) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: ping locked
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// context swap status. when a address space is locked, all write to that address space will be rejected internally
//                       This signal is set when the 1st pixel comes out of input port and gets cleared when the last pixel comes out of ISp in streaming channels
//            1: ping locked
//            0: ping free
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PING_LOCKED_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_PING_LOCKED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PING_LOCKED_OFFSET (0x24)
#define ACAMERA_ISP_ISP_GLOBAL_PING_LOCKED_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_ping_locked_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x24) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: pong locked
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// context swap status. when a address space is locked, all write to that address space will be rejected internally.
//                       This signal is set when the 1st pixel comes out of input port and gets cleared when the last pixel comes out of ISp in streaming channels
//            1: pong locked
//            0: pong free
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PONG_LOCKED_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_PONG_LOCKED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PONG_LOCKED_OFFSET (0x24)
#define ACAMERA_ISP_ISP_GLOBAL_PONG_LOCKED_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_pong_locked_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x24) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: ping pong config select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            this signal indicates which of the PING/PONG config is being used by ISP. when MCU takes control of the config management through
//            Mcu_override_config_select signal, then this signal is just a reflection of what MCU has instructed through Mcu_ping_pong_config_select
//            signal. 
//
//            This signal is a good point to synchronize with hardware. MCU should read this signal in a regular interval to synchronize with its
//            internal state.
//
//            This signal is changed when the 1st pixel comes in. So this signal must be sampled at the frame_start interrupt.
//
//            0: pong in use by ISP
//            1: ping in use by ISP
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PING_PONG_CONFIG_SELECT_DEFAULT (1)
#define ACAMERA_ISP_ISP_GLOBAL_PING_PONG_CONFIG_SELECT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PING_PONG_CONFIG_SELECT_OFFSET (0x24)
#define ACAMERA_ISP_ISP_GLOBAL_PING_PONG_CONFIG_SELECT_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_ping_pong_config_select_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x24) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Group: isp global metering base addr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// pragrammable base adressed for metering stats
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: AWB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// base address for AWB stats. Set to 464 if number of zones greater than 5x5. Otherwise can be set to 64.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AWB_DEFAULT (464)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AWB_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AWB_OFFSET (0x28)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AWB_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_isp_global_metering_base_addr_awb_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x28);
    system_hw_write_32(0x28, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_isp_global_metering_base_addr_awb_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x28) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: AF
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// base address for AF stats.  Set to 928 if number of zones greater than 5x5. Otherwise can be set to 128.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AF_DEFAULT (928)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AF_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AF_OFFSET (0x28)
#define ACAMERA_ISP_ISP_GLOBAL_METERING_BASE_ADDR_AF_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_isp_global_metering_base_addr_af_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x28);
    system_hw_write_32(0x28, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_isp_global_metering_base_addr_af_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x28) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: isp global interrupt
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// interrupt controls
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: mask_vector
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Interrupt mask vector
//        0: Interrupt is enabled
//        1: interrupt is masked
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_MASK_VECTOR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_MASK_VECTOR_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_MASK_VECTOR_OFFSET (0x30)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_MASK_VECTOR_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_isp_global_interrupt_mask_vector_write(uintptr_t base, uint32_t data) {
    system_hw_write_32(0x30, data);
}
static __inline uint32_t acamera_isp_isp_global_interrupt_mask_vector_read(uintptr_t base) {
    return system_hw_read_32(0x30);
}
// ------------------------------------------------------------------------------ //
// Register: clear_vector
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Interrupt clear vector. its bitwise cleared. When a bit is set to 1. that interrupt
//        bit in the status register is cleared
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_VECTOR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_VECTOR_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_VECTOR_OFFSET (0x34)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_VECTOR_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_isp_global_interrupt_clear_vector_write(uintptr_t base, uint32_t data) {
    system_hw_write_32(0x34, data);
}
static __inline uint32_t acamera_isp_isp_global_interrupt_clear_vector_read(uintptr_t base) {
    return system_hw_read_32(0x34);
}
// ------------------------------------------------------------------------------ //
// Register: shadow_disable_vector
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Interrupt shadow disable vector. 
//        To disable shadow feature for the specific interrupt event by setting the related bit to 1.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_SHADOW_DISABLE_VECTOR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_SHADOW_DISABLE_VECTOR_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_SHADOW_DISABLE_VECTOR_OFFSET (0x38)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_SHADOW_DISABLE_VECTOR_MASK (0xffffffff)

// args: data (32-bit)
static __inline void acamera_isp_isp_global_interrupt_shadow_disable_vector_write(uintptr_t base, uint32_t data) {
    system_hw_write_32(0x38, data);
}
static __inline uint32_t acamera_isp_isp_global_interrupt_shadow_disable_vector_read(uintptr_t base) {
    return system_hw_read_32(0x38);
}
// ------------------------------------------------------------------------------ //
// Register: pulse_mode
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        When set to 1, the output interrupt will be a pulse. Otherwise it should be level.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_PULSE_MODE_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_PULSE_MODE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_PULSE_MODE_OFFSET (0x3c)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_PULSE_MODE_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_interrupt_pulse_mode_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x3c);
    system_hw_write_32(0x3c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_interrupt_pulse_mode_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x3c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: clear
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        Interrupt clear vector register qualifier. First the vector must be written. Then this bit must be set to 1 and then cleared
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_OFFSET (0x40)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_CLEAR_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_interrupt_clear_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x40);
    system_hw_write_32(0x40, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_interrupt_clear_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x40) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: status_vector
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            bit[0]  : Isp_start 
//            bit[1]  : Isp_done
//            bit[2]  : Context management error
//            bit[3]  : Broken frame error
//            bit[4]  : Metering AF done
//            bit[5]  : Metering aexp done
//            bit[6]  : Metering awb done
//            bit[7]  : Metering aexp 1024 bin hist done
//            bit[8]  : Metering antifog hist done
//            bit[9]  : Lut init done
//            bit[10] : FR y-dma write done
//            bit[11] : FR uv-dma write done
//            bit[12] : DS y-dma write done
//            bit[13] : DS uv-dma write done
//            bit[14] : Linearization done
//            bit[15] : Static dpc done
//            bit[16] : Ca correction done
//            bit[17] : Iridix done
//            bit[18] : 3d LIUT done
//            bit[19] : Watchdog timer timed out
//            bit[20] : Frame collision error
//            bit[21] : Reserved
//            bit[22] : DMA error interrupt
//            bit[23] : Input port safely stopped
//            bit[24] : Metering awb done up to target1_addr
//            bit[25] : Metering awb done up to target2_addr
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_STATUS_VECTOR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_STATUS_VECTOR_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_STATUS_VECTOR_OFFSET (0x44)
#define ACAMERA_ISP_ISP_GLOBAL_INTERRUPT_STATUS_VECTOR_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_isp_global_interrupt_status_vector_read(uintptr_t base) {
    return system_hw_read_32(0x44);
}
// ------------------------------------------------------------------------------ //
// Group: isp global lp
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: CG Dis frame_stitch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for WDR path channels.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FRAME_STITCH_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FRAME_STITCH_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FRAME_STITCH_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FRAME_STITCH_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_frame_stitch_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_frame_stitch_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis raw frontend
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for raw frontend.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RAW_FRONTEND_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RAW_FRONTEND_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RAW_FRONTEND_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RAW_FRONTEND_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_raw_frontend_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_raw_frontend_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis Sinter
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for Sinter.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SINTER_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SINTER_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SINTER_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SINTER_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_sinter_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_sinter_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis Temper
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for Temper.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_TEMPER_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_TEMPER_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_TEMPER_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_TEMPER_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_temper_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_temper_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis mesh shading
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for mesh shading.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_MESH_SHADING_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_MESH_SHADING_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_MESH_SHADING_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_MESH_SHADING_MASK (0x80)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_mesh_shading_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_mesh_shading_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis Iridix
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for Iridix.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_IRIDIX_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_IRIDIX_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_IRIDIX_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_IRIDIX_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_iridix_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_iridix_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis demosaic RGGB
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for Demosaic RGGB.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_DEMOSAIC_RGGB_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_DEMOSAIC_RGGB_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_DEMOSAIC_RGGB_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_DEMOSAIC_RGGB_MASK (0x200)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_demosaic_rggb_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 9) | (curr & 0xfffffdff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_demosaic_rggb_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis PF correction
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for PF correction.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_PF_CORRECTION_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_PF_CORRECTION_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_PF_CORRECTION_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_PF_CORRECTION_MASK (0x800)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_pf_correction_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 11) | (curr & 0xfffff7ff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_pf_correction_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis CNR
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for CNR and pre-square root and post-square.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_CNR_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_CNR_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_CNR_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_CNR_MASK (0x1000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_cnr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 12) | (curr & 0xffffefff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_cnr_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x1000) >> 12);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis RGB Scaler FR
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for fr pipe RGB scaler.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_FR_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_FR_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_FR_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_FR_MASK (0x2000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_rgb_scaler_fr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 13) | (curr & 0xffffdfff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_rgb_scaler_fr_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x2000) >> 13);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis RGB Scaler DS
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for ds pipe RGB scaler.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_DS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_DS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_DS_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_RGB_SCALER_DS_MASK (0x4000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_rgb_scaler_ds_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 14) | (curr & 0xffffbfff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_rgb_scaler_ds_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x4000) >> 14);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis Sharpen FR
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for sharpen in FR pipeline.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FR_SHARPEN_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FR_SHARPEN_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FR_SHARPEN_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_FR_SHARPEN_MASK (0x20000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_fr_sharpen_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 17) | (curr & 0xfffdffff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_fr_sharpen_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x20000) >> 17);
}
// ------------------------------------------------------------------------------ //
// Register: CG Dis Sharpen DS
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// when set, this will disable Bypass Clock gating for sharpen in DS pipeline.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SHARPEN_DS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SHARPEN_DS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SHARPEN_DS_OFFSET (0x4c)
#define ACAMERA_ISP_ISP_GLOBAL_LP_CG_DIS_SHARPEN_DS_MASK (0x40000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_lp_cg_dis_sharpen_ds_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x4c);
    system_hw_write_32(0x4c, (((uint32_t) (data & 0x1)) << 18) | (curr & 0xfffbffff));
}
static __inline uint8_t acamera_isp_isp_global_lp_cg_dis_sharpen_ds_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x4c) & 0x40000) >> 18);
}
// ------------------------------------------------------------------------------ //
// Group: isp global monitor
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: broken_frame status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            bit[0] : active width mismatch
//            bit[1] : active_height mismatch
//            bit[2] : minimum v-blank violated
//            bit[3] : minimum h-blank violated
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_STATUS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_STATUS_DATASIZE (4)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_STATUS_OFFSET (0x50)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_STATUS_MASK (0xf)

// args: data (4-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_broken_frame_status_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x50) & 0xf) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: global_fsm_rst_status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0: global_fsm_rst not active in the pipeline
//             1: global_fsm_rst is active
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_GLOBAL_FSM_RST_STATUS_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_GLOBAL_FSM_RST_STATUS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_GLOBAL_FSM_RST_STATUS_OFFSET (0x50)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_GLOBAL_FSM_RST_STATUS_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_global_fsm_rst_status_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x50) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: main_pipeline_busy
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal indicates if ISP pipeline (full resolution/downscaler/iridix) is busy or not. This signal is asserted by the first pixel entering the ISP. This signal doesnt include the metering modules.
//                0: ISP main pipeline (excluding metering) is free
//                1: ISP main pipeline (excluding metering) is busy
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAIN_PIPELINE_BUSY_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAIN_PIPELINE_BUSY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAIN_PIPELINE_BUSY_OFFSET (0x50)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAIN_PIPELINE_BUSY_MASK (0x10000)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_main_pipeline_busy_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x50) & 0x10000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: isp_busy
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal indicates if ISP pipeline (full resolution/downscaler/iridix) is busy or not. This signal is asserted by VVALID going high. This signal includes the metering modules.
//                0: ISP is free
//                1: ISP is busy
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_ISP_BUSY_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_ISP_BUSY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_ISP_BUSY_OFFSET (0x50)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_ISP_BUSY_MASK (0x1000000)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_isp_busy_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x50) & 0x1000000) >> 24);
}
// ------------------------------------------------------------------------------ //
// Register: FR Y DMA WFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_FULL_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_fr_y_dma_wfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: FR Y DMA WFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_Y_DMA_WFIFO_FAIL_EMPTY_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_fr_y_dma_wfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: FR UV DMA WFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_FULL_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_fr_uv_dma_wfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: FR UV DMA WFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_UV_DMA_WFIFO_FAIL_EMPTY_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_fr_uv_dma_wfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: DS Y DMA WFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_FULL_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_y_dma_wfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: DS Y DMA WFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_Y_DMA_WFIFO_FAIL_EMPTY_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_y_dma_wfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: DS UV DMA WFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_FULL_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_uv_dma_wfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: DS UV DMA WFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_UV_DMA_WFIFO_FAIL_EMPTY_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_uv_dma_wfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: Temper DMA WFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_EMPTY_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_temper_dma_wfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: Temper DMA WFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_WFIFO_FAIL_FULL_MASK (0x200)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_temper_dma_wfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: Temper DMA RFIFO fail empty
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_EMPTY_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_EMPTY_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_EMPTY_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_EMPTY_MASK (0x400)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_temper_dma_rfifo_fail_empty_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x400) >> 10);
}
// ------------------------------------------------------------------------------ //
// Register: Temper DMA RFIFO fail full
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_FULL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_FULL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_FULL_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_RFIFO_FAIL_FULL_MASK (0x800)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_temper_dma_rfifo_fail_full_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x54) & 0x800) >> 11);
}
// ------------------------------------------------------------------------------ //
// Register: DMA alarms
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            [0] : temper_dma_wtr_axi_alarm
//            [1] : temper_dma_rdr_axi_alarm
//            [2] : Temper dma frame dropped
//            [3] : FR UV dma axi alarm
//            [4] : FR dma axi alarm
//            [5] : DS UV dma axi alarm
//            [6] : DS dma axi alarm
//            [7] : FR UV-DMA frame dropped
//            [8] : FR Y-DMA frame dropped
//            [9] : DS UV-DMA frame dropped
//            [10]: DS Y-DMA frame dropped
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DMA_ALARMS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DMA_ALARMS_DATASIZE (11)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DMA_ALARMS_OFFSET (0x54)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DMA_ALARMS_MASK (0x7ff0000)

// args: data (11-bit)
static __inline uint16_t acamera_isp_isp_global_monitor_dma_alarms_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x54) & 0x7ff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER IRQSTAT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Ds pipe Downscaler status
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_IRQSTAT_DEFAULT (0x00)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_IRQSTAT_DATASIZE (8)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_IRQSTAT_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_IRQSTAT_MASK (0xff)

// args: data (8-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_irqstat_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0xff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER Field err IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : Field out not asserted
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIELD_ERR_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIELD_ERR_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIELD_ERR_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIELD_ERR_IRQ_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_field_err_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_field_err_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER Geom IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : Input frame geometry error
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_GEOM_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_GEOM_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_GEOM_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_GEOM_IRQ_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_geom_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_geom_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER HBlank IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : HBlank smaller than supported 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_HBLANK_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_HBLANK_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_HBLANK_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_HBLANK_IRQ_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_hblank_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_hblank_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER Timeout IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No timeout 
//             1 : Timeout on frame done 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_TIMEOUT_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_TIMEOUT_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_TIMEOUT_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_TIMEOUT_IRQ_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_timeout_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_timeout_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: DS SCALER Fifo overflow IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No fifo overflow happened
//             1 : Unexpected fifo overflow happened
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIFO_OVERFLOW_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIFO_OVERFLOW_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIFO_OVERFLOW_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_FIFO_OVERFLOW_IRQ_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_fifo_overflow_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_fifo_overflow_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER IRQSTAT
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// FR pipe Downscaler status
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_IRQSTAT_DEFAULT (0x00)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_IRQSTAT_DATASIZE (8)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_IRQSTAT_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_IRQSTAT_MASK (0xff0000)

// args: data (8-bit)
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_irqstat_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0xff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER Field err IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : Field out not asserted
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIELD_ERR_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIELD_ERR_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIELD_ERR_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIELD_ERR_IRQ_MASK (0x40)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_field_err_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 6) | (curr & 0xffffffbf));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_field_err_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER Geom IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : Input frame geometry error
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_GEOM_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_GEOM_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_GEOM_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_GEOM_IRQ_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_geom_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_geom_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER HBlank IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No error
//             1 : HBlank smaller than supported 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_HBLANK_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_HBLANK_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_HBLANK_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_HBLANK_IRQ_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_hblank_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_hblank_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER Timeout IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No timeout 
//             1 : Timeout on frame done 
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_TIMEOUT_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_TIMEOUT_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_TIMEOUT_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_TIMEOUT_IRQ_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_timeout_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_timeout_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: FR SCALER Fifo overflow IRQ
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//             0 : No fifo overflow happened
//             1 : Unexpected fifo overflow happened
//            
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIFO_OVERFLOW_IRQ_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIFO_OVERFLOW_IRQ_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIFO_OVERFLOW_IRQ_OFFSET (0x58)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_FIFO_OVERFLOW_IRQ_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_fifo_overflow_irq_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x58);
    system_hw_write_32(0x58, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_fifo_overflow_irq_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x58) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: broken_frame error clear
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal must be asserted when the MCu gets broken frame interrupt.
//            this signal must be 0->1->0 pulse. The duration of the pulse is not relevant. This rising edge will clear the
//            broken frame error status signal
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_ERROR_CLEAR_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_ERROR_CLEAR_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_ERROR_CLEAR_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_BROKEN_FRAME_ERROR_CLEAR_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_broken_frame_error_clear_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_monitor_broken_frame_error_clear_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: context error clr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal must be asserted when the MCU gets the context error interrupt.
//            this signal must be 0->1->0 pulse. The duration of the pulse is not relevant. This rising edge will clear the
//            context error status signal
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_CONTEXT_ERROR_CLR_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_CONTEXT_ERROR_CLR_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_CONTEXT_ERROR_CLR_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_CONTEXT_ERROR_CLR_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_context_error_clr_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_monitor_context_error_clr_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: output dma clr alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal must be asserted when the MCU gets the DMA error interrupt.
//            This signal will clear all DMA error status signals for all the output DMA writers (Y/UV DMAs in both of the output channels)
//            MCU must follow the following sequance to clear the alarms
//            step-1: set this bit to 1
//            step-2: Read back the alarm signals
//            step-3: If the alarms are cleared, then clear the clr_alarm signal back to 0.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_OUTPUT_DMA_CLR_ALARM_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_OUTPUT_DMA_CLR_ALARM_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_OUTPUT_DMA_CLR_ALARM_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_OUTPUT_DMA_CLR_ALARM_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_output_dma_clr_alarm_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_isp_global_monitor_output_dma_clr_alarm_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: temper dma clr alarm
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            This signal must be asserted when the MCU gets the DMA error interrupt.
//            This signal will clear all DMA error status signals for all the Temper DMA writers/readers
//            MCU must follow the following sequance to clear the alarms
//            step-1: set this bit to 1
//            step-2: Read back the alarm signals
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_CLR_ALARM_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_CLR_ALARM_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_CLR_ALARM_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_TEMPER_DMA_CLR_ALARM_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_temper_dma_clr_alarm_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_isp_global_monitor_temper_dma_clr_alarm_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: ds scaler Clear Alarms
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          DS pipe Scaler control
//          IRQ CLR bit 
//           0 : In-active 
//           1 : 0 ->1 transiction clear-off ds scaler IRQ status to 0 
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_CLEAR_ALARMS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_CLEAR_ALARMS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_CLEAR_ALARMS_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_DS1_SCALER_CLEAR_ALARMS_MASK (0x10)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_ds1_scaler_clear_alarms_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 4) | (curr & 0xffffffef));
}
static __inline uint8_t acamera_isp_isp_global_monitor_ds1_scaler_clear_alarms_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: fr scaler Clear Alarms
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//          FR pipe Scaler control
//          IRQ CLR bit 
//           0 : In-active 
//           1 : 0 ->1 transiction clear-off fr scaler IRQ status to 0 
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_CLEAR_ALARMS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_CLEAR_ALARMS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_CLEAR_ALARMS_OFFSET (0x5c)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_FR_SCALER_CLEAR_ALARMS_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_monitor_fr_scaler_clear_alarms_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x5c);
    system_hw_write_32(0x5c, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_isp_global_monitor_fr_scaler_clear_alarms_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x5c) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: MAX address delay line fr
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Delay line max address value for the full resolution ISP set outside ISP
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_FR_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_FR_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_FR_OFFSET (0x60)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_FR_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_isp_global_monitor_max_address_delay_line_fr_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x60) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: MAX address delay line ds
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Delay line max address value for the DS pipeline set outside ISP
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_DS_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_DS_DATASIZE (16)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_DS_OFFSET (0x60)
#define ACAMERA_ISP_ISP_GLOBAL_MONITOR_MAX_ADDRESS_DELAY_LINE_DS_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_isp_global_monitor_max_address_delay_line_ds_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x60) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Group: isp global select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: frame_end_select
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: Only ISP main pipeline, ds pipeline and iridix filtering is used to generate the frame_done interrupt
//           None of the metering done signals are considered here
//        1: all metering done is taken into account to generate the frame done interrupt
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_SELECT_FRAME_END_SELECT_DEFAULT (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_FRAME_END_SELECT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_FRAME_END_SELECT_OFFSET (0x64)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_FRAME_END_SELECT_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_select_frame_end_select_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x64);
    system_hw_write_32(0x64, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_select_frame_end_select_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x64) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: rd_start_sel
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0: temper dma reader will start reading based on the frame start
//        1: temper dma reader will start reading based on linetick of the dma writer (this option is not compatible with multi-context modes due to expected base address changes)
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_SELECT_RD_START_SEL_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_RD_START_SEL_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_RD_START_SEL_OFFSET (0x64)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_RD_START_SEL_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_select_rd_start_sel_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x64);
    system_hw_write_32(0x64, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_isp_global_select_rd_start_sel_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x64) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: input_alignment
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0=LSB aligned (debug only) 
//        1=MSB aligned
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_SELECT_INPUT_ALIGNMENT_DEFAULT (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_INPUT_ALIGNMENT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_INPUT_ALIGNMENT_OFFSET (0x64)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_INPUT_ALIGNMENT_MASK (0x4)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_select_input_alignment_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x64);
    system_hw_write_32(0x64, (((uint32_t) (data & 0x1)) << 2) | (curr & 0xfffffffb));
}
static __inline uint8_t acamera_isp_isp_global_select_input_alignment_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x64) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: watchdog_timer_dis
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0=Watch dog timer enabled
//        1=watch dog timer disabled
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_SELECT_WATCHDOG_TIMER_DIS_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_WATCHDOG_TIMER_DIS_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_WATCHDOG_TIMER_DIS_OFFSET (0x64)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_WATCHDOG_TIMER_DIS_MASK (0x8)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_select_watchdog_timer_dis_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x64);
    system_hw_write_32(0x64, (((uint32_t) (data & 0x1)) << 3) | (curr & 0xfffffff7));
}
static __inline uint8_t acamera_isp_isp_global_select_watchdog_timer_dis_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x64) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: dma_writer_timeout_disable
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        0=timeout enabled. At the end of the frame, if the last data is not drained out from DMA writer within 4000
//          AXI clock, cycle, DMA will flush the FIFO and ignore the remainign data.
//
//        1=timeout is disabled. If the last data is not drained out and the next frame starts coming in, DMA will drop the next frame and
//          give an interrupt.
//          If the timeout is disabled, its S/W responsibility to cancel the frame in all dma engines if frame drop interrupt comes.
//        
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_SELECT_DMA_WRITER_TIMEOUT_DISABLE_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_DMA_WRITER_TIMEOUT_DISABLE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_DMA_WRITER_TIMEOUT_DISABLE_OFFSET (0x64)
#define ACAMERA_ISP_ISP_GLOBAL_SELECT_DMA_WRITER_TIMEOUT_DISABLE_MASK (0x20)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_select_dma_writer_timeout_disable_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x64);
    system_hw_write_32(0x64, (((uint32_t) (data & 0x1)) << 5) | (curr & 0xffffffdf));
}
static __inline uint8_t acamera_isp_isp_global_select_dma_writer_timeout_disable_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x64) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Group: isp global parameter status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//        ISP provides few parameters through which certain modules can be removed from ISP.
//        This register indicates the status of these parameters
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: pong_config_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Pong configuration space, with the exception of pong statistics memories, is statically removed from ISP and the address space relative to pong config space is not writeable and reading back the address space will return 0
//            1: Pong configuration space is present in the design
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_PONG_CONFIG_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_PONG_CONFIG_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_PONG_CONFIG_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_PONG_CONFIG_FITTED_MASK (0x1)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_pong_config_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: wdr_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: wdr framestich, offset and gain and the relative config registers are statically removed from ISP.
//            1: wdr framestich, offset and gain are present in the design. 
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_WDR_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_WDR_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_WDR_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_WDR_FITTED_MASK (0x2)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_wdr_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: compression_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Temper compression is statically removed from ISP.
//            1: Temper compression is present in the design          
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_COMPRESSION_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_COMPRESSION_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_COMPRESSION_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_COMPRESSION_FITTED_MASK (0x4)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_compression_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x4) >> 2);
}
// ------------------------------------------------------------------------------ //
// Register: temper_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Temper and the relative config space are statically removed from the ISP. The temper config address space is not writeable and reading back it will return 0.
//            1: Temper is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_TEMPER_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_TEMPER_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_TEMPER_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_TEMPER_FITTED_MASK (0x8)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_temper_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x8) >> 3);
}
// ------------------------------------------------------------------------------ //
// Register: sinter_lite
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Full sinter version used.
//            1: Sinter lite version used.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_LITE_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_LITE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_LITE_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_LITE_MASK (0x10)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_sinter_lite_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x10) >> 4);
}
// ------------------------------------------------------------------------------ //
// Register: sinter_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Sinter and the relative config space are statically removed from the ISP. The sinter config address space is not writeable and reading back it will return 0.
//            1: Sinter is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SINTER_FITTED_MASK (0x20)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_sinter_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x20) >> 5);
}
// ------------------------------------------------------------------------------ //
// Register: iridix_ltm_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Iridix local tone mapping is removed from ISP.
//            1: Iridix local tone mapping is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_LTM_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_LTM_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_LTM_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_LTM_FITTED_MASK (0x40)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_iridix_ltm_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x40) >> 6);
}
// ------------------------------------------------------------------------------ //
// Register: iridix_gtm_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Iridix global tone mapping is removed from ISP.
//            1: Iridix global tone mapping is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_GTM_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_GTM_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_GTM_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_IRIDIX_GTM_FITTED_MASK (0x80)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_iridix_gtm_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: cnr_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: CNR and its square/sqrt and the relative config space are statically removed from the ISP. The CNR and its square/sqrt config address space is not writeable and reading back it will return 0.
//            1: CNR and its square/sqrt are present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_CNR_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_CNR_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_CNR_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_CNR_FITTED_MASK (0x100)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_cnr_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: frscaler_fitted
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Full resolution pipe scaler and the relative config space are statically removed from the ISP. The full resolution pipe scaler config address space is not writeable and reading back it will return 0.
//            1: FUll resolution pipe scaler is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_FRSCALER_FITTED_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_FRSCALER_FITTED_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_FRSCALER_FITTED_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_FRSCALER_FITTED_MASK (0x200)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_frscaler_fitted_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x200) >> 9);
}
// ------------------------------------------------------------------------------ //
// Register: ds_pipe
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: Downscale pipe and the relative config space are statically removed from the ISP. The downscale pipe config address space is not writeable and reading back it will return 0.
//            1: Downscale pipe is present in the design.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_DS1_PIPE_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_DS1_PIPE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_DS1_PIPE_OFFSET (0x68)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_DS1_PIPE_MASK (0x400)

// args: data (1-bit)
static __inline uint8_t acamera_isp_isp_global_parameter_status_ds1_pipe_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x68) & 0x400) >> 10);
}
// ------------------------------------------------------------------------------ //
// Register: scaler_coef_sets
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            Number of scaler coef sets available.
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SCALER_COEF_SETS_DEFAULT (0x0)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SCALER_COEF_SETS_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SCALER_COEF_SETS_OFFSET (0x6c)
#define ACAMERA_ISP_ISP_GLOBAL_PARAMETER_STATUS_SCALER_COEF_SETS_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_isp_global_parameter_status_scaler_coef_sets_read(uintptr_t base) {
    return system_hw_read_32(0x6c);
}
// ------------------------------------------------------------------------------ //
// Group: isp global dbg
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//         The configs under this section are for debug only operation. Do not change from default values during normal operation.
//      
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: mode_en
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: debug frame counters are disabled
//            1: debug frame counters are valid
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DBG_MODE_EN_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_MODE_EN_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_MODE_EN_OFFSET (0x70)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_MODE_EN_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_dbg_mode_en_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x70);
    system_hw_write_32(0x70, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_isp_global_dbg_mode_en_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x70) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: clear_frame_cnt
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            must be 0->1->0 to clear the debug counters
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DBG_CLEAR_FRAME_CNT_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_CLEAR_FRAME_CNT_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_CLEAR_FRAME_CNT_OFFSET (0x70)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_CLEAR_FRAME_CNT_MASK (0x100)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_dbg_clear_frame_cnt_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x70);
    system_hw_write_32(0x70, (((uint32_t) (data & 0x1)) << 8) | (curr & 0xfffffeff));
}
static __inline uint8_t acamera_isp_isp_global_dbg_clear_frame_cnt_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x70) & 0x100) >> 8);
}
// ------------------------------------------------------------------------------ //
// Register: unlock_config_space
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//            0: normal operation of ping_locked and pong_locked
//            1: unlock ping and pong config space (set this register to 1 for debug only). Pong config space will be unlocked just if toplevel parameter pong_config_fitted is set to 1
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DBG_UNLOCK_CONFIG_SPACE_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_UNLOCK_CONFIG_SPACE_DATASIZE (1)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_UNLOCK_CONFIG_SPACE_OFFSET (0x70)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_UNLOCK_CONFIG_SPACE_MASK (0x10000)

// args: data (1-bit)
static __inline void acamera_isp_isp_global_dbg_unlock_config_space_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x70);
    system_hw_write_32(0x70, (((uint32_t) (data & 0x1)) << 16) | (curr & 0xfffeffff));
}
static __inline uint8_t acamera_isp_isp_global_dbg_unlock_config_space_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x70) & 0x10000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: frame_cnt
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//                when debug mode is enabled, this register will show a frame count
//          
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_ISP_GLOBAL_DBG_FRAME_CNT_DEFAULT (0)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_FRAME_CNT_DATASIZE (32)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_FRAME_CNT_OFFSET (0x74)
#define ACAMERA_ISP_ISP_GLOBAL_DBG_FRAME_CNT_MASK (0xffffffff)

// args: data (32-bit)
static __inline uint32_t acamera_isp_isp_global_dbg_frame_cnt_read(uintptr_t base) {
    return system_hw_read_32(0x74);
}
// ------------------------------------------------------------------------------ //
// Group: input port
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Controls video input port.  
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: gen video on
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  0: Input port will process the input frame from sensor. If this config has been set back to 0 after an internal video source generation request, before sending the next frame
//                       you must wait until the ISP flushed the current frame.
//                    1: starts an internal video source generation. Before setting to 1, should wait until the ISP flushed the current frame and after that, the input port should be safely stopped. 
//                       To stop the frame generation, set this register back to 0 at anytime and wait until the ISP flushed the current frame before sending another frame.
//                       The generation will stop at the end of the frame.
//      
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_ON_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_ON_DATASIZE (1)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_ON_OFFSET (0x80)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_ON_MASK (0x1)

// args: data (1-bit)
static __inline void acamera_isp_input_port_gen_video_on_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x80);
    system_hw_write_32(0x80, (((uint32_t) (data & 0x1)) << 0) | (curr & 0xfffffffe));
}
static __inline uint8_t acamera_isp_input_port_gen_video_on_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x80) & 0x1) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gen video multi
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  0: If requested internal video source generation, the ISP will generate one test frame. 
//                    1: If requested internal video source generation, the ISP will generate test frames until this register will be set to 0 or gen_video_on will be set to 0.
//      
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_MULTI_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_MULTI_DATASIZE (1)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_MULTI_OFFSET (0x80)
#define ACAMERA_ISP_INPUT_PORT_GEN_VIDEO_MULTI_MASK (0x2)

// args: data (1-bit)
static __inline void acamera_isp_input_port_gen_video_multi_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x80);
    system_hw_write_32(0x80, (((uint32_t) (data & 0x1)) << 1) | (curr & 0xfffffffd));
}
static __inline uint8_t acamera_isp_input_port_gen_video_multi_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x80) & 0x2) >> 1);
}
// ------------------------------------------------------------------------------ //
// Register: gen prefetch
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Set this register to number of clock cycles required to allow DMA prefetch to complete before the first pixel.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_GEN_PREFETCH_DEFAULT (0x7D0)
#define ACAMERA_ISP_INPUT_PORT_GEN_PREFETCH_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_GEN_PREFETCH_OFFSET (0x80)
#define ACAMERA_ISP_INPUT_PORT_GEN_PREFETCH_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_input_port_gen_prefetch_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x80);
    system_hw_write_32(0x80, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_input_port_gen_prefetch_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x80) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: gen hblank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Set this register to number of horizontal blanking clock cycles wanted for the internal generated source frame.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_GEN_HBLANK_DEFAULT (0x20)
#define ACAMERA_ISP_INPUT_PORT_GEN_HBLANK_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_GEN_HBLANK_OFFSET (0x84)
#define ACAMERA_ISP_INPUT_PORT_GEN_HBLANK_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_input_port_gen_hblank_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x84);
    system_hw_write_32(0x84, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_input_port_gen_hblank_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x84) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: gen vblank
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
//  Set this register to number of vertical blanking lines (active_width + horizontal_blanking) wanted for the internal generated source frame.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_GEN_VBLANK_DEFAULT (0x50)
#define ACAMERA_ISP_INPUT_PORT_GEN_VBLANK_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_GEN_VBLANK_OFFSET (0x84)
#define ACAMERA_ISP_INPUT_PORT_GEN_VBLANK_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_input_port_gen_vblank_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x84);
    system_hw_write_32(0x84, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_input_port_gen_vblank_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x84) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: hc start0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// window0 start for ACL gate.  See the ISP Technical Reference Manual for further details.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_HC_START0_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_HC_START0_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_HC_START0_OFFSET (0x88)
#define ACAMERA_ISP_INPUT_PORT_HC_START0_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_input_port_hc_start0_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x88);
    system_hw_write_32(0x88, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_input_port_hc_start0_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x88) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: hc size0
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// window0 size for ACL gate.  See the ISP Technical Reference Manual for further details.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_HC_SIZE0_DEFAULT (0xFFFF)
#define ACAMERA_ISP_INPUT_PORT_HC_SIZE0_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_HC_SIZE0_OFFSET (0x8c)
#define ACAMERA_ISP_INPUT_PORT_HC_SIZE0_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_input_port_hc_size0_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x8c);
    system_hw_write_32(0x8c, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_input_port_hc_size0_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x8c) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: vc start
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// window2 start for ACL gate.  See the ISP Technical Reference Manual for further details.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_VC_START_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_VC_START_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_VC_START_OFFSET (0x94)
#define ACAMERA_ISP_INPUT_PORT_VC_START_MASK (0xffff)

// args: data (16-bit)
static __inline void acamera_isp_input_port_vc_start_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x94);
    system_hw_write_32(0x94, (((uint32_t) (data & 0xffff)) << 0) | (curr & 0xffff0000));
}
static __inline uint16_t acamera_isp_input_port_vc_start_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x94) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: vc size
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// window2 size for ACL gate.  See the ISP Technical Reference Manual for further details.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_VC_SIZE_DEFAULT (0xFFFF)
#define ACAMERA_ISP_INPUT_PORT_VC_SIZE_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_VC_SIZE_OFFSET (0x94)
#define ACAMERA_ISP_INPUT_PORT_VC_SIZE_MASK (0xffff0000)

// args: data (16-bit)
static __inline void acamera_isp_input_port_vc_size_write(uintptr_t base, uint16_t data) {
    uint32_t curr = system_hw_read_32(0x94);
    system_hw_write_32(0x94, (((uint32_t) (data & 0xffff)) << 16) | (curr & 0xffff));
}
static __inline uint16_t acamera_isp_input_port_vc_size_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x94) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: det frame width
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Detected frame width.  Read only value.
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_WIDTH_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_WIDTH_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_WIDTH_OFFSET (0x98)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_WIDTH_MASK (0xffff)

// args: data (16-bit)
static __inline uint16_t acamera_isp_input_port_det_frame_width_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x98) & 0xffff) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: det frame height
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Detected frame height.  Read only value.  
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_HEIGHT_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_HEIGHT_DATASIZE (16)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_HEIGHT_OFFSET (0x98)
#define ACAMERA_ISP_INPUT_PORT_DET_FRAME_HEIGHT_MASK (0xffff0000)

// args: data (16-bit)
static __inline uint16_t acamera_isp_input_port_det_frame_height_read(uintptr_t base) {
    return (uint16_t)((system_hw_read_32(0x98) & 0xffff0000) >> 16);
}
// ------------------------------------------------------------------------------ //
// Register: freeze config
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Used to freeze input port configuration.  Used when multiple register writes are required to change input port configuration. 
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_DATASIZE (1)
#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_OFFSET (0x9c)
#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_MASK (0x80)
#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_NORMAL_OPERATION (0)
#define ACAMERA_ISP_INPUT_PORT_FREEZE_CONFIG_HOLD_PREVIOUS_INPUT_PORT_CONFIG_STATE (1)

// args: data (1-bit)
static __inline void acamera_isp_input_port_freeze_config_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x9c);
    system_hw_write_32(0x9c, (((uint32_t) (data & 0x1)) << 7) | (curr & 0xffffff7f));
}
static __inline uint8_t acamera_isp_input_port_freeze_config_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x9c) & 0x80) >> 7);
}
// ------------------------------------------------------------------------------ //
// Register: mode request
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Used to stop and start input port.  See the ISP Technical Reference Manual for further details. 
//        Only modes-0 and 1 are used. All other values are reserved
//      
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_DATASIZE (3)
#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_OFFSET (0x9c)
#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_MASK (0x7)
#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_SAFE_STOP (0)
#define ACAMERA_ISP_INPUT_PORT_MODE_REQUEST_SAFE_START (1)

// args: data (3-bit)
static __inline void acamera_isp_input_port_mode_request_write(uintptr_t base, uint8_t data) {
    uint32_t curr = system_hw_read_32(0x9c);
    system_hw_write_32(0x9c, (((uint32_t) (data & 0x7)) << 0) | (curr & 0xfffffff8));
}
static __inline uint8_t acamera_isp_input_port_mode_request_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0x9c) & 0x7) >> 0);
}
// ------------------------------------------------------------------------------ //
// Register: mode status
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// 
//      Used to monitor input port status:
//      bit 0: 1=running, 0=stopped, bits 1,2-reserved
//      
// ------------------------------------------------------------------------------ //

#define ACAMERA_ISP_INPUT_PORT_MODE_STATUS_DEFAULT (0)
#define ACAMERA_ISP_INPUT_PORT_MODE_STATUS_DATASIZE (3)
#define ACAMERA_ISP_INPUT_PORT_MODE_STATUS_OFFSET (0xa0)
#define ACAMERA_ISP_INPUT_PORT_MODE_STATUS_MASK (0x7)

// args: data (3-bit)
static __inline uint8_t acamera_isp_input_port_mode_status_read(uintptr_t base) {
    return (uint8_t)((system_hw_read_32(0xa0) & 0x7) >> 0);
}

// ------------------------------------------------------------------------------ //
#endif //__ACAMERA_ISP_CONFIG_H__

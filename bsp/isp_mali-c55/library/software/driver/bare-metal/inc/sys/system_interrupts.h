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

#ifndef __SYSTEM_INTERRUPTS_H__
#define __SYSTEM_INTERRUPTS_H__

#include "acamera_types.h"

#define ACAMERA_IRQ_COUNT 32

#define ACAMERA_IRQ_MASK( num ) ( 1 << num )

typedef uint32_t system_fw_interrupt_mask_t;

typedef void ( *system_interrupt_handler_t )( void *ptr, uint32_t mask );


/**
 *   Initialize system interrupts
 *
 *   This function initializes system dependent interrupt functionality
 *
 *   @return none
 */
void system_interrupts_init( void );


/**
 *   Set an interrupt handler
 *
 *   This function is used by application to set an interrupt handler for all ISP related interrupt events.
 *
 *   @param
 *          handler - a callback to handle interrupts
 *          param - pointer to a context which must be send to interrupt handler
 *
 *   @return none
 */
void system_interrupt_set_handler( system_interrupt_handler_t handler, void *param );


/**
 *   Enable system interrupts
 *
 *   This function is used by firmware to enable system interrupts in a case if they were disabled before
 *
 *   @return none
 */
void system_interrupts_enable( void );


/**
 *   Disable system interrupts
 *
 *   This function is used by firmware to disable system interrupts for a short period of time.
 *   Usually IRQ register is updated by new interrupts but main interrupt handler is not called by a system.
 *
 *   @return none
 */
void system_interrupts_disable( void );

#endif /* __SYSTEM_INTERRUPTS_H__ */

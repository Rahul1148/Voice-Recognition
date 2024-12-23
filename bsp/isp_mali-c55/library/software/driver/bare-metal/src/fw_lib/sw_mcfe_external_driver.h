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

#ifndef __SW_MCFE_EXTERNAL_DRIVER_H__
#define __SW_MCFE_EXTERNAL_DRIVER_H__

#include "acamera_types.h"
#include "acamera_fw.h"
#include "acamera.h"
#include "system_log.h"

/**
 *   Initialize the driver
 *
 *   @param  g_fw - Pointer to the ACamera firmware instance
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_external_driver_init( acamera_firmware_t *g_fw );

/**
 *   Deinitialize the driver
 *
 *   @param  none
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_external_driver_deinit( void );

/**
 *   Interrupt handler routine to process interrupts from DMA writers
 *
 *   @param  none
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_external_driver_interrupt_handler( uint32_t event_mask );

/**
 *   Request to process v4l2 input buffer at nested context
 *
 *   @param  ctx_id - context number
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_external_process_request_v4l2( uint32_t ctx_id );

#endif // __SW_MCFE_EXTERNAL_DRIVER_H__

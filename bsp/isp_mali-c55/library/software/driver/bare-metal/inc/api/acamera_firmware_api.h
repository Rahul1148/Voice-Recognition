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

#ifndef __ACAMERA_FIRMWARE_API_H__
#define __ACAMERA_FIRMWARE_API_H__

#include "acamera_types.h"
#include "acamera_sensor_api.h"
#include "acamera_lens_api.h"
#include "acamera_command_api.h"
#include "acamera_firmware_settings.h"

/**
 *   Initialize one instance of firmware context
 *
 *   The firmware can control several context at the same time. Each context must be initialized with its own
 *   set of setting and independently from all other contexts. A pointer will be returned on valid context on
 *   successful initialization.
 *
 *   @param  settings - a structure with setting for context to be initialized with
 *   @param  ctx_num - number of contexts to be initialized
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t acamera_init( acamera_settings *settings, uint32_t ctx_num );


/**
 *   Terminate the firmware
 *
 *   The function will close the firmware and free all previously allocated resources
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t acamera_terminate( void );


/**
 *   Process one instance of firmware context
 *
 *   The firmware can control several context at the same time. Each context must be given a CPU time to fulfil
 *   all tasks it has at the moment. This function has to be called for all contexts as frequent as possible to avoid
 *   delays.
 *
 *   @param  ctx - context pointer which was returned by acamera_init
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t acamera_process( void );


/**
 *   Process interrupts
 *
 *   This function must be called when any of interrupts happen. It will process interrupts properly to guarantee
 *   the correct firmware behaviour.
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t acamera_interrupt_handler( void );


#endif // __ACAMERA_FIRMWARE_API_H__

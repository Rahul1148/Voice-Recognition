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

#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

#include "acamera_types.h"


/**
 *   Initialize system timer
 *
 *   The function system_timer_init() can be called at application level to
 *   initialise the timestamp facility.
 *
 *   @return  0 - on success
 *           -1 - on error
 */
void system_timer_init( void );


/**
 *   Return the current timer value
 *
 *   The function must return the current timer value.
 *
 *   @return  current timestamp
 */
uint32_t system_timer_timestamp( void );


/**
 *   Return the system timer frequency
 *
 *   This function must return a number of ticks per second for a system timer
 *   For example in the case if the timer uses microseconds this function should return
 *   1000000
 *
 *   @return positive number - timer frequency
 *           0 - on error
 */
uint32_t system_timer_frequency( void );


/**
 *   Usleep implementation for the current platform
 *
 *   This function must suspend execution of the calling thread
 *   by specified number of microseconds. The implementation of this function
 *   depends on the current platfrom.
 *
 *   @param   usec - time to sleep in microseconds
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int32_t system_timer_usleep( uint32_t usec );


#endif /* __SYSTEM_TIMER_H__ */

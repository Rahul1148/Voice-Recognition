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

#ifndef __SYSTEM_SEMAPHORE_H__
#define __SYSTEM_SEMAPHORE_H__
//-----------------------------------------------------------------------------
#include "acamera_types.h"
//-----------------------------------------------------------------------------
typedef void *semaphore_t;

//-----------------------------------------------------------------------------

/**
 *   Initialize system semaphore
 *
 *   The function initializes a system dependent semaphore
 *
 *   @param void ** sem - the pointer to system semaphore will be returned
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int32_t system_semaphore_init( semaphore_t *sem );


/**
 *   Unlock the semaphore pointed to by sem
 *
 *   The function increments (unlocks) the semaphore.
 *   If the semaphore value becomes greater than zero, then
 *   another process which is blocked by system_semaphore_wait will be
 *   woken up
 *
 *   @param   sem - pointer to semaphore returned by system_semaphore_init
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int32_t system_semaphore_raise( semaphore_t sem );


/**
 *   Locks the semaphore pointed to by sem
 *
 *   The function decrements (locks) the semaphore.
 *   If the semaphore value is greater than zero, then
 *   the decrement proceeds, and the function returns.
 *
 *   @param   sem - pointer to semaphore returned by system_semaphore_init
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int32_t system_semaphore_wait( semaphore_t sem, uint32_t timeout_ms );


/**
 *   Destroy semaphore
 *
 *   The function destroys semaphore which was created by system_semaphore_init
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int32_t system_semaphore_destroy( semaphore_t sem );

//-----------------------------------------------------------------------------
#endif //__SYSTEM_SEMAPHORE_H__

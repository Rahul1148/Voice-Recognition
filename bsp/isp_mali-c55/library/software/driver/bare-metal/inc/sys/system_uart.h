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

#ifndef __SYSTEM_UART_H__
#define __SYSTEM_UART_H__

#include "acamera_types.h"


/**
 *   Initialize uart connection
 *
 *   The function is called before any uart communication is run to
 *   initialise uart connection.
 *
 *   @return  fd - on success
 *           -1 - on error
 */
int32_t system_uart_init( void );


/**
 *   Write data with uart connection
 *
 *   The function writes specified amount of data
 *   to a given uart descriptor fd
 *
 *   @param   fd  - uard descriptor which was returned by system_uart_init
 *            p   - pointer to a data to be written
 *            len - amount of bytes to write
 *
 *   @return  >=0 - amount of written bytes on success
 *           -1 - on error
 */
int32_t system_uart_write( int32_t fd, const uint8_t *p, int32_t len );


/**
 *   Read data from uart connection
 *
 *   The function reads specified amount of data
 *   from a given uart descriptor fd
 *
 *   @param   fd  - uard descriptor which was returned by system_uart_init
 *            p   - pointer to a memory block to save input data
 *            len - amount of bytes to read
 *
 *   @return  >=0 - amount of read bytes on success
 *           -1 - on error
 */
int32_t system_uart_read( int32_t fd, uint8_t *p, int32_t len );

#endif // __SYSTEM_UART_H__

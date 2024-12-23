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

#ifndef __system_sw_io_H__
#define __system_sw_io_H__

#include "acamera_types.h"

void *system_sw_alloc( uint32_t size, void* rtrack_arr );
void system_sw_free( void *ptr );
/**
 *   Read 32 bit word from isp memory
 *
 *   This function returns a 32 bits word from ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to read 32 bits word.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR
 *
 *   @return 32 bits memory value
 */
uint32_t system_sw_read_32( uintptr_t addr );


/**
 *   Read 16 bit word from isp memory
 *
 *   This function returns a 16 bits word from ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to read 16 bits word.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR
 *
 *   @return 16 bits memory value
 */
uint16_t system_sw_read_16( uintptr_t addr );


/**
 *   Read 8 bit word from isp memory
 *
 *   This function returns a 8 bits word from ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to read 8 bits word.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR
 *
 *   @return 8 bits memory value
 */
uint8_t system_sw_read_8( uintptr_t addr );


/**
 *   Write 32 bits word to isp memory
 *
 *   This function writes a 32 bits word to ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to write data.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR.
 *   @param data - data to be written
 */
void system_sw_write_32( uintptr_t addr, uint32_t data );


/**
 *   Write 16 bits word to isp memory
 *
 *   This function writes a 16 bits word to ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to write data.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR.
 *   @param data - data to be written
 */
void system_sw_write_16( uintptr_t addr, uint16_t data );


/**
 *   Write 8 bits word to isp memory
 *
 *   This function writes a 8 bits word to ISP memory with a given offset.
 *
 *   @param addr - the offset in ISP memory to write data.
 *                 Correct values from 0 to ACAMERA_sw_MAX_ADDR.
 *   @param data - data to be written
 */
void system_sw_write_8( uintptr_t addr, uint8_t data );


#endif /* __system_sw_io_H__ */

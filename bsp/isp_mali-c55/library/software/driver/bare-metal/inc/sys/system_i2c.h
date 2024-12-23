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

#ifndef __SYSTEM_I2C_H__
#define __SYSTEM_I2C_H__

#include "acamera_types.h"

#define I2C_NOCONNECT ( -1 )
#define I2C_OK ( 0 )
#define I2C_ACK ( 0 )
#define I2C_NOACK ( 1 )
#define I2C_ABITRATION_LOST ( 2 )

/**
 *   Initialize i2c channel
 *
 *   This function is called by firmware to establish i2c communication.
 *
 *   @return none
 */
void system_i2c_init( uint32_t bus );


/**
 *   Close i2c connections
 *
 *   This function is used by firmware to close i2c connection
 *
 *   @return none
 */
void system_i2c_deinit( uint32_t bus );


/**
 *   Write a data through i2c channel
 *
 *   This function is used by firmware to write specified amount of data
 *   to a specific device.
 *
 *   @param address - i2c address
 *          data - pointer to the start of the memory block
 *          size - amount of bytes to write
 *
 *   @return I2C_NOCONNECT - no connection
 *           I2C_OK - success
 *           I2C_NOACK - no acknowledge from a device
 */
uint8_t system_i2c_write( uint32_t bus, uint32_t address, uint8_t *data, uint32_t size );


/**
 *   Read data from i2c channel
 *
 *   This function is used by firmware to read specified amount of data
 *   from a specific device.
 *
 *   @param address - i2c address
 *          data - pointer to the start of the memory block
 *          size - amount of bytes to write
 *
 *   @return I2C_NOCONNECT - no connection
 *           I2C_OK - success
 *           I2C_NOACK - no acknowledge from a device
 */
uint8_t system_i2c_read( uint32_t bus, uint32_t address, uint8_t *data, uint32_t size );


#endif /* __SYSTEM_I2C_H__ */

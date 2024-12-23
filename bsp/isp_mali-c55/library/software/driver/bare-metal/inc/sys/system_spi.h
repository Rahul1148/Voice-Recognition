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

#ifndef __SYSTEM_SPI_H__
#define __SYSTEM_SPI_H__

#include "acamera_types.h"


#define AUTO_CPHA_CPOL 0x4000
#define AUTO_SS_MSK 0x2000
#define IE_MSK 0x1000
#define LSB_MSK 0x0800
#define TX_NEG_MSK 0x0400
#define RX_NEG_MSK 0x0200
#define GO_BUSY_MSK 0x0100
#define CHAR_LEN_MSK 0x007F


/**
 *   Initialize spi connection
 *
 *   The function is called before any uart communication is run to
 *   initialise uart connection.
 *
 *   @return  fd - on success
 *           -1 - on error
 */
int32_t system_spi_init( void );


/**
 *   Read data
 *
 *   The function reads 32 bit data from spi channel
 *
 *   @param sel_mask
 *   @param control
 *   @param data
 *   @param data_size
 *
 */
uint32_t system_spi_rw32( uint32_t sel_mask, uint32_t control, uint32_t data, uint8_t data_size );


/**
 *   Read data
 *
 *   The function reads 32 bit data from spi channel
 *
 *   @param sel_mask
 *   @param control
 *   @param data
 *   @param data_size
 *
 */
uint32_t system_spi_rw48( uint32_t sel_mask, uint32_t control, uint32_t addr, uint8_t addr_size, uint32_t data, uint8_t data_size );


#endif /* __SYSTEM_SPI_H__ */

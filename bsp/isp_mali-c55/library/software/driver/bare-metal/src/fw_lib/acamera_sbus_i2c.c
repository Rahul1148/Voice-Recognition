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

#include "acamera_types.h"
#include "acamera_sbus_i2c.h"
#if ISP_FW_BUILD
#include "acamera_fw.h"
#endif
#include "system_i2c.h"

#include "acamera_logger.h"

static uint32_t fill_address( uint8_t *buf, uint32_t mask, uintptr_t addr )
{
    uint32_t i, size;

    if ( mask & SBUS_MASK_ADDR_SKIP )
        return 0;
    if ( mask & SBUS_MASK_ADDR_16BITS )
        size = 2;
    else if ( mask & SBUS_MASK_ADDR_32BITS )
        size = 4;
    else
        size = 1;

    for ( i = 0; i < size; i++ ) {
        // buffer is in little-endian format by default
        *buf++ = ( uint8_t )( addr & 0xFF );
        addr >>= 8;
    }
    return size;
}

static void i2c_io_write_sample( acamera_sbus_t *p_bus, uintptr_t addr, uint32_t sample, uint8_t sample_size )
{
#if ISP_FW_BUILD
    const acamera_context_ptr_t p_ctx = (const acamera_context_ptr_t)p_bus->p_control;
#endif
    uint8_t buf[4 + 4]; // maximum address and data
    uint32_t buf_size = fill_address( buf, p_bus->mask, addr );
    uint8_t i;

    while ( sample_size-- ) {
        // buffer is in little-endian format by default
        buf[buf_size++] = ( uint8_t )( sample & 0xFF );
        sample >>= 8;
    }
#if ISP_FW_BUILD
    if ( p_ctx )
        acamera_fw_interrupts_disable( p_ctx );
#endif
    i = system_i2c_write( p_bus->bus, p_bus->device, buf, buf_size );
    if ( i != I2C_OK ) {
        LOG( LOG_ERR, "I2C not ok" );
    }
#if ISP_FW_BUILD
    if ( p_ctx )
        acamera_fw_interrupts_enable( p_ctx );
#endif
}

static uint32_t i2c_io_read_sample( acamera_sbus_t *p_bus, uintptr_t addr, uint8_t sample_size )
{
    uint32_t res = 0;
#if ISP_FW_BUILD
    const acamera_context_ptr_t p_ctx = (const acamera_context_ptr_t)p_bus->p_control;
#endif
    uint8_t buf[4]; // maximum buffer size;
    uint32_t buf_size = fill_address( buf, p_bus->mask, addr );
    uint8_t i;

    if ( p_bus->bus == 0 ) {
        LOG( LOG_ERR, "I2C bus address is zero. Please check the configuration of sensor connection " );
    }
#if ISP_FW_BUILD
    if ( p_ctx )
        acamera_fw_interrupts_disable( p_ctx );
#endif
    if ( !buf_size || ( i = system_i2c_write( p_bus->bus, p_bus->device | ( p_bus->mask & SBUS_MASK_NO_STOP ), buf, buf_size ) ) == I2C_OK ) {
        i = system_i2c_read( p_bus->bus, p_bus->device, buf, sample_size );
        if ( i != I2C_OK ) {
            LOG( LOG_ERR, "I2C not ok" );
        }
    }
#if ISP_FW_BUILD
    if ( p_ctx )
        acamera_fw_interrupts_enable( p_ctx );
#endif
    if ( i == I2C_OK ) {
        for ( i = sample_size; i--; ) {
            // buffer is in little-endian format by default
            res <<= 8;
            res += buf[i];
        }
    }
    return res;
}

void acamera_sbus_i2c_init( acamera_sbus_t *p_bus )
{
    p_bus->read_sample = i2c_io_read_sample;
    p_bus->write_sample = i2c_io_write_sample;
    system_i2c_init( p_bus->bus );
}

void acamera_sbus_i2c_deinit( acamera_sbus_t *p_bus )
{
    system_i2c_deinit( p_bus->bus );
}

void i2c_init_access( void )
{
    LOG( LOG_ERR, "I2C INIT ACCESS IS DISABLED" );
}

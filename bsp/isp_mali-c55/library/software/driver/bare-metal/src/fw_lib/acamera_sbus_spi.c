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

#include "acamera_sbus_spi.h"
#include "system_spi.h"
#if ISP_FW_BUILD
#include "acamera_fw.h"
#endif
static void spi_io_write_sample( acamera_sbus_t *p_sbus, uintptr_t addr, uint32_t sample, uint8_t sample_size )
{
    uint32_t mask = p_sbus->mask;
    uint32_t sel_mask = 1 << p_sbus->device;
    uint32_t data = 0x0;
#if ISP_FW_BUILD
    const acamera_context_ptr_t p_ctx = (const acamera_context_ptr_t)p_sbus->p_control;
#endif
    if ( sample_size == 4 ) {
        uint8_t addr_size = 0;
        if ( mask & SBUS_MASK_ADDR_8BITS )
            addr_size = 1;
        else if ( mask & SBUS_MASK_ADDR_16BITS )
            addr_size = 2;
        else if ( mask & SBUS_MASK_ADDR_32BITS )
            addr_size = 4;
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_disable( p_ctx );
#endif
        system_spi_rw48( sel_mask, p_sbus->control, addr, addr_size, sample, sample_size );
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_enable( p_ctx );
#endif

    } else {
        if ( ( mask & SBUS_MASK_SPI_HALF_ADDR ) && !( mask & SBUS_MASK_ADDR_SWAP_BYTES ) ) // divide addr by 2 if possible
        {
            addr >>= 1;
        }
        if ( mask & SBUS_MASK_SPI_LSB ) // LSB sending first
        {
            data = sample;
            if ( ( mask & SBUS_MASK_ADDR_BITS_MASK ) == SBUS_MASK_ADDR_16BITS ) {
                data <<= 16;
                data |= addr;
            } else if ( ( mask & SBUS_MASK_ADDR_BITS_MASK ) == SBUS_MASK_ADDR_8BITS ) {
                data <<= 8;
                data |= addr;
            } else if ( ( mask & SBUS_MASK_ADDR_BITS_MASK ) == SBUS_MASK_ADDR_24BITS ) {
                data <<= 16;
                data |= addr;
                data <<= 8;
                data |= p_sbus->device_id;
            } else {
                // 32-bits address for SPI is required special treatment
                return;
            }
        } else {
            data = 0;
            if ( mask & SBUS_MASK_ADDR_24BITS ) {
                data |= p_sbus->device_id;
                data <<= 8;
            }
            data |= addr;
            if ( mask & SBUS_MASK_SAMPLE_16BITS )
                data <<= 16;
            else if ( mask & SBUS_MASK_SAMPLE_8BITS )
                data <<= 8;
            else {
                // 32-bits samples for SPI is required special treatment
                return;
            }
            data |= sample;
        }
        if ( mask & SBUS_MASK_SPI_INVERSE_DATA ) {
            data = ~data;
        }
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_disable( p_ctx );
#endif
        system_spi_rw32( sel_mask, p_sbus->control, data, sample_size );
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_enable( p_ctx );
#endif
    }
}

static uint32_t spi_io_read_sample( acamera_sbus_t *p_sbus, uintptr_t addr, uint8_t sample_size )
{
    uint32_t mask = p_sbus->mask;
    uint32_t sel_mask = 1 << p_sbus->device;
    uint32_t data = 0x0;
#if ISP_FW_BUILD
    const acamera_context_ptr_t p_ctx = (const acamera_context_ptr_t)p_sbus->p_control;
#endif
    if ( ( mask & SBUS_MASK_SPI_HALF_ADDR ) && !( mask & SBUS_MASK_ADDR_SWAP_BYTES ) ) // divide addr by 2 if required
    {
        addr >>= 1;
    }
    // Set MSB of address
    if ( mask & SBUS_MASK_SPI_READ_MSB_SET ) {

        if ( ( mask & SBUS_MASK_ADDR_8BITS ) || ( ( mask & SBUS_MASK_ADDR_16BITS ) && ( mask & SBUS_MASK_ADDR_SWAP_BYTES ) ) ) {
            addr |= 0x80;
        } else if ( ( mask & SBUS_MASK_ADDR_16BITS ) && !( mask & SBUS_MASK_ADDR_SWAP_BYTES ) ) {
            addr |= 0x8000;
        }
        // 32-bit address is not supported yet
    }

    if ( sample_size == 4 ) {
        uint8_t addr_size = 0;
        if ( mask & SBUS_MASK_ADDR_8BITS )
            addr_size = 1;
        else if ( mask & SBUS_MASK_ADDR_16BITS )
            addr_size = 2;
        else if ( mask & SBUS_MASK_ADDR_32BITS )
            addr_size = 4;
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_disable( p_ctx );
#endif
        data = system_spi_rw48( sel_mask, p_sbus->control, addr, addr_size, data, sample_size );
#if ISP_FW_BUILD
        if ( p_ctx )
            acamera_fw_interrupts_enable( p_ctx );
#endif
    } else {
        if ( ( mask & SBUS_MASK_ADDR_BITS_MASK ) == SBUS_MASK_ADDR_24BITS ) {
            addr <<= 8;
            addr |= p_sbus->device_id_read;
        }
        if ( mask & SBUS_MASK_SPI_LSB ) {

            if ( mask & SBUS_MASK_SPI_INVERSE_DATA ) {
                addr = ~addr;
            }
            if ( mask & SBUS_MASK_ADDR_16BITS ) {
#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_disable( p_ctx );
#endif
                data = system_spi_rw32( sel_mask, p_sbus->control, addr, sample_size ) >> 16;

#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_enable( p_ctx );
#endif
            } else if ( mask & SBUS_MASK_ADDR_8BITS ) {
#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_disable( p_ctx );
#endif
                data = system_spi_rw32( sel_mask, p_sbus->control, addr, sample_size ) >> 8;


#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_enable( p_ctx );
#endif
            } else {
                // 32-bits address for SPI is required special treatment
                data = 0xFFFFFFFF;
            }
        } else {

            if ( mask & ( SBUS_MASK_SAMPLE_16BITS | SBUS_MASK_SAMPLE_8BITS ) ) {
                if ( mask & SBUS_MASK_SAMPLE_16BITS ) {
                    addr <<= 16;
                } else if ( mask & SBUS_MASK_SAMPLE_8BITS ) {
                    addr <<= 8;
                }
                if ( mask & SBUS_MASK_SPI_INVERSE_DATA ) {
                    addr = ~addr;
                }
#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_disable( p_ctx );
#endif
                data = system_spi_rw32( sel_mask, p_sbus->control, addr, sample_size );
#if ISP_FW_BUILD
                if ( p_ctx )
                    acamera_fw_interrupts_enable( p_ctx );
#endif
            } else {
                // 32-bits samples for SPI are required special treatment

                data = 0xFFFFFFFF;
            }
        }
        if ( data != 0xFFFFFFFF ) {
            if ( sample_size == 1 )
                data &= 0xFF;
            else if ( sample_size == 2 )
                data &= 0xFFFF;
        }
    }

    return data;
}

void acamera_sbus_spi_init( acamera_sbus_ptr_t p_sbus )
{
    p_sbus->read_sample = spi_io_read_sample;
    p_sbus->write_sample = spi_io_write_sample;
    system_spi_init();
}

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

#include "acamera_sbus_api.h"
#include "acamera_logger.h"
#include "system_sw_io.h"

static uint32_t isp_io_read_sample( acamera_sbus_t *p_bus, uintptr_t addr, uint8_t sample_size )
{
    if ( ( sample_size == 2 && ( addr & 1 ) ) || ( sample_size == 4 && ( addr & 3 ) ) ) {
        LOG( LOG_ERR, "Missaligned access to ISP" );
        return 0xFFFFFFFF;
    }
    switch ( sample_size ) {
    case 1:
        return system_sw_read_8( addr );
    case 2:
        return system_sw_read_16( addr );
    }
    return system_sw_read_32( addr );
}


static void isp_io_write_sample( acamera_sbus_t *p_bus, uintptr_t addr, uint32_t sample, uint8_t sample_size )
{
    if ( ( sample_size == 2 && ( addr & 1 ) ) || ( sample_size == 4 && ( addr & 3 ) ) ) {
        LOG( LOG_ERR, "Missaligned access to ISP" );
        return;
    }
    uintptr_t align_mask = (uintptr_t)~3;
    uintptr_t addr_aligned = addr & align_mask;
    switch ( sample_size ) {
    case 1:
        system_sw_write_32( addr_aligned, ( system_sw_read_32( addr_aligned ) & ~( 0xFF << 8 * ( addr & 3 ) ) ) | ( sample << ( 8 * ( addr & 3 ) ) ) );
        break;
    case 2:
        system_sw_write_32( addr_aligned, ( system_sw_read_32( addr_aligned ) & ~( 0xFFFF << 8 * ( addr & 2 ) ) ) | ( sample << ( 8 * ( addr & 2 ) ) ) );
        break;
    default:
        system_sw_write_32( addr, sample );
        break;
    }
}

void acamera_sbus_isp_sw_init( acamera_sbus_t *p_bus )
{
    p_bus->read_sample = isp_io_read_sample;
    p_bus->write_sample = isp_io_write_sample;
}

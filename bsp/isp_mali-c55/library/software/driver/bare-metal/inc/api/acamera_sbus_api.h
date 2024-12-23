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

#ifndef __ACAMERA_SBUS_H__
#define __ACAMERA_SBUS_H__


#include "acamera_types.h"

typedef struct _acamera_sbus_t acamera_sbus_t;
typedef struct _acamera_sbus_t *acamera_sbus_ptr_t;
typedef const struct _acamera_sbus_t *acamera_sbus_const_ptr_t;

#define SBUS_MASK_SAMPLE_8BITS 0x01
#define SBUS_MASK_SAMPLE_16BITS 0x02
#define SBUS_MASK_SAMPLE_32BITS 0x04
#define SBUS_MASK_ADDR_8BITS 0x08
#define SBUS_MASK_ADDR_16BITS 0x10
#define SBUS_MASK_ADDR_24BITS 0x30
#define SBUS_MASK_ADDR_32BITS 0x20
#define SBUS_MASK_ADDR_BITS_MASK 0x38
#define SBUS_MASK_ADDR_STEP_16BITS 0x40
#define SBUS_MASK_ADDR_STEP_32BITS 0x80
#define SBUS_MASK_SAMPLE_SWAP_BYTES 0x100
#define SBUS_MASK_SAMPLE_SWAP_WORDS 0x200
#define SBUS_MASK_ADDR_SWAP_BYTES 0x400
#define SBUS_MASK_ADDR_SWAP_WORDS 0x800
#define SBUS_MASK_ADDR_SKIP 0x1000
#define SBUS_MASK_SPI_READ_MSB_SET 0x2000
#define SBUS_MASK_SPI_INVERSE_DATA 0x4000
#define SBUS_MASK_SPI_HALF_ADDR 0x8000
#define SBUS_MASK_SPI_LSB 0x10000
#define SBUS_MASK_NO_STOP 0x20000

typedef enum _sbus_type_t {
    sbus_i2c = 0,
    sbus_spi,
    sbus_isp,
    sbus_isp_sw
} sbus_type_t;

struct _acamera_sbus_t {
    uint32_t mask;
    uint32_t bus;
    uint8_t device;
    uint8_t device_id;      // If device is used for SPI CS, and device number is still required
    uint8_t device_id_read; // If device is used for SPI CS, and device number is still required
    uint32_t control;
    void *p_control;
    uint32_t ( *read_sample )( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint8_t sample_size );
    void ( *write_sample )( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint32_t sample, uint8_t sample_size );
};


uint8_t acamera_sbus_read_u8( acamera_sbus_ptr_t p_bus, uintptr_t addr );
uint16_t acamera_sbus_read_u16( acamera_sbus_ptr_t p_bus, uintptr_t addr );
uint32_t acamera_sbus_read_u32( acamera_sbus_ptr_t p_bus, uintptr_t addr );
void acamera_sbus_read_data_u8( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint8_t *p_data, int n_count );
void acamera_sbus_read_data_u16( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint16_t *p_data, int n_count );
void acamera_sbus_read_data_u32( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint32_t *p_data, int n_count );
void acamera_sbus_write_u8( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint8_t sample );
void acamera_sbus_write_u16( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint16_t sample );
void acamera_sbus_write_u32( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint32_t sample );
void acamera_sbus_write_data_u8( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint8_t *p_data, int n_count );
void acamera_sbus_write_data_u16( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint16_t *p_data, int n_count );
void acamera_sbus_write_data_u32( acamera_sbus_ptr_t p_bus, uintptr_t addr, uint32_t *p_data, int n_count );
void acamera_sbus_write_data( acamera_sbus_ptr_t p_bus, uintptr_t addr, void *p_data, int n_size );
void acamera_sbus_copy( acamera_sbus_t *p_bus_to, uintptr_t addr_to, acamera_sbus_t *p_bus_from, uint32_t addr_from, int n_size );

void acamera_sbus_init( acamera_sbus_t *p_bus, sbus_type_t interface_type );
void acamera_sbus_deinit( acamera_sbus_t *p_bus, sbus_type_t interface_type );
void acamera_sbus_reset( sbus_type_t interface_type );


#endif /* __ACAMERA_SBUS_H__ */

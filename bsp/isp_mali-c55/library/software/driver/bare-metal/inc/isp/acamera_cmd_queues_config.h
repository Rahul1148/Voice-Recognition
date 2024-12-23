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

#ifndef __ACAMERA_CMD_QUEUES_CONFIG_H__
#define __ACAMERA_CMD_QUEUES_CONFIG_H__


#include "system_sw_io.h"

#include "system_hw_io.h"

// ------------------------------------------------------------------------------ //
// Instance 'cmd_queues' of module 'cmd_queues'
// ------------------------------------------------------------------------------ //

#define ACAMERA_CMD_QUEUES_BASE_ADDR (0x108)
#define ACAMERA_CMD_QUEUES_SIZE (0x400)

#define ACAMERA_CMD_QUEUES_ARRAY_DATA_DEFAULT (0x0)
#define ACAMERA_CMD_QUEUES_ARRAY_DATA_DATASIZE (32)
#define ACAMERA_CMD_QUEUES_ARRAY_DATA_OFFSET (0x108)

// args: index (0-255), data (32-bit)
static __inline void acamera_cmd_queues_array_data_write( uintptr_t base, uint32_t index, uint32_t data) {
    system_hw_write_32(0x108 + (index << 2), data);
}
static __inline uint32_t acamera_cmd_queues_array_data_read( uintptr_t base, uint32_t index) {
    return system_hw_read_32(0x108 + (index << 2));
}

// ------------------------------------------------------------------------------ //
#endif //__ACAMERA_CMD_QUEUES_CONFIG_H__

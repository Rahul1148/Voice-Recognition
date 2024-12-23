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

#ifndef __ACAMERA_AEXP_HIST_STATS_MEM_CONFIG_H__
#define __ACAMERA_AEXP_HIST_STATS_MEM_CONFIG_H__


#include "system_sw_io.h"

#include "system_hw_io.h"

// ------------------------------------------------------------------------------ //
// Instance 'aexp_hist_stats_mem' of module 'aexp_hist_stats_mem'
// ------------------------------------------------------------------------------ //

#define ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR (0x54a8)
#define ACAMERA_AEXP_HIST_STATS_MEM_SIZE (0x800)

// ------------------------------------------------------------------------------ //
// Group: aexp hist stats mem
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Register: Data
// ------------------------------------------------------------------------------ //

// ------------------------------------------------------------------------------ //
// Please see other documentation for a description of the contents of this array.
// ------------------------------------------------------------------------------ //

#define ACAMERA_AEXP_HIST_STATS_MEM_ARRAY_DATA_DEFAULT (0x0)
#define ACAMERA_AEXP_HIST_STATS_MEM_ARRAY_DATA_DATASIZE (32)
#define ACAMERA_AEXP_HIST_STATS_MEM_ARRAY_DATA_OFFSET (0x0)
#define ACAMERA_AEXP_HIST_STATS_MEM_ARRAY_DATA_MASK (0xffffffff)

// index (0-511), args: data (32-bit)
static __inline uint32_t acamera_aexp_hist_stats_mem_array_data_read( uintptr_t base, uint32_t index ) {
    return system_sw_read_32( base + 0x54a8 + ( index << 2 ) );
}

// ------------------------------------------------------------------------------ //
#endif //__ACAMERA_AEXP_HIST_STATS_MEM_CONFIG_H__

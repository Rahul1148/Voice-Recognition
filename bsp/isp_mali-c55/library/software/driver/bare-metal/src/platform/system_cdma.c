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
#include "acamera_logger.h"
#include "system_cdma.h"

int cdma_mode = 0;

int32_t system_cdma_init( void **ctx, uint8_t mode, void **ping_only_reg_chg_track_mem )
{
    return 0;
}


int32_t system_cdma_destroy( void *ctx )
{
    return 0;
}

int32_t system_cdma_copy_device_to_memory( void *ctx, void *dst_mem, uint32_t dev_phy_addr, uint32_t size_to_copy )
{
    return 0;
}


int32_t system_cdma_copy_memory_to_device( void *ctx, void *src_mem, uint32_t dev_phy_addr, uint32_t size_to_copy )
{
    return 0;
}


int32_t system_cdma_copy_device_to_memory_async( void *ctx, void *dst_mem, uint32_t dev_phy_addr, uint32_t size_to_copy, dma_completion_callback complete_func, void *arg )
{
    return 0;
}


int32_t system_cdma_copy_memory_to_device_async( void *ctx, void *src_mem, uint32_t dev_phy_addr, uint32_t size_to_copy, dma_completion_callback complete_func, void *arg )
{
    return 0;
}

int32_t system_cdma_sg_device_setup( void *ctx, int32_t buff_loc, dma_addr_pair_t *device_addr_pair, int32_t addr_pairs, uint32_t fw_ctx_id )
{
    return 0;
}

int32_t system_cdma_sg_fwmem_setup( void *ctx, int32_t buff_loc, fwmem_addr_pair_t *fwmem_pair, int32_t addr_pairs, uint32_t fw_ctx_id )
{
    return 0;
}

void system_cdma_unmap_sg( void *ctx )
{
}

int32_t system_cdma_copy_sg( void *ctx, int32_t buff_loc, uint32_t direction, dma_completion_callback complete_func, uint32_t fw_ctx_id )
{
    return 0;
}

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

#ifndef __SYSTEM_DMA_H__
#define __SYSTEM_DMA_H__

#include "acamera_types.h"

#define SYS_DMA_TO_DEVICE 0
#define SYS_DMA_FROM_DEVICE 1

enum {
    CDMA_MODE_HWDMA = 0,
    CDMA_MODE_MEMCPY,
    CDMA_MODE_RTRACK
};
extern int cdma_mode;

typedef struct {
    uint32_t address;
    uint32_t size;
} dma_addr_pair_t;

typedef struct {
    void *address;
    uint32_t size;
} fwmem_addr_pair_t;


#define SYSTEM_DMA_TOGGLE_COUNT 2
#define SYSTEM_DMA_MAX_CHANNEL 2

typedef void ( *dma_completion_callback )( void * , uint32_t );

/**
 *   Initialize dma channel
 *
 *   This function requests an exclusive dma channel from the system and return a pointer to it
 *
 *   @param ctx - pointer to dma channel or NULL if error.
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_init( void **priv, uint8_t mode, void **ping_only_reg_chg_track_mem );

/**
 *   Destroy dma channel
 *
 *   This function destroys previously allocated by system_cdma_init channel.
 *
 *   @param ctx - pointer to dma channel.
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_destroy( void *ctx );


/**
 *   Copy data from memory to the device asynchronously
 *
 *   This function copies memory allocated by kmalloc to the device physical memory.
 *   Please note that dst_mem MUST be a kernel virtual pointer.
 *
 *   @param ctx - pointer to dma channel.
 *   @param dst_mem - virtual pointer to the memory region
 *   @param dev_phy_addr - device physical address
 *   @param size_to_copy - data size to copy in bytes
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_copy_device_to_memory_async( void *ctx, void *dst_mem, uint32_t dev_phy_addr, uint32_t size_to_copy, dma_completion_callback complete_func, void *args );


/**
 *   Copy data from dev to memory asynchronously
 *
 *   This function copies device physical memory to memory allocated by kmalloc.
 *   Please note that src_mem MUST be a kernel virtual pointer.
 *
 *   @param ctx - pointer to dma channel.
 *   @param src_mem - virtual pointer to the memory region
 *   @param dev_phy_addr - device physical address
 *   @param size_to_copy - data size to copy in bytes
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_copy_memory_to_device_async( void *ctx, void *src_mem, uint32_t dev_phy_addr, uint32_t size_to_copy, dma_completion_callback complete_func, void *args );


/**
 *   Copy data from memory to the device
 *
 *   This function copies memory allocated by kmalloc to the device physical memory.
 *   Please note that dst_mem MUST be a kernel virtual pointer.
 *
 *   @param ctx - pointer to dma channel.
 *   @param dst_mem - virtual pointer to the memory region
 *   @param dev_phy_addr - device physical address
 *   @param size_to_copy - data size to copy in bytes
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_copy_device_to_memory( void *ctx, void *dst_mem, uint32_t dev_phy_addr, uint32_t size_to_copy );


/**
 *   Copy data from dev to memory
 *
 *   This function copies device physical memory to memory allocated by kmalloc.
 *   Please note that src_mem MUST be a kernel virtual pointer.
 *
 *   @param ctx - pointer to dma channel.
 *   @param src_mem - virtual pointer to the memory region
 *   @param dev_phy_addr - device physical address
 *   @param size_to_copy - data size to copy in bytes
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_copy_memory_to_device( void *ctx, void *src_mem, uint32_t dev_phy_addr, uint32_t size_to_copy );


/**
 *   Setup firmware memory for scatter and gather dma feature from fw memory pairs of virtual address and lenght
 *
 *
 *   @param ctx - pointer to dma channel data or NULL if error.
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_sg_fwmem_setup( void *ctx, int32_t buff_loc, fwmem_addr_pair_t *fwmem_pair, int32_t addr_pairs, uint32_t fw_ctx_id );

/**
 *   Setup isp device memory for scatter and gather dma feature from pairs of dma bus address and lenght
 *
 *   @param ctx - pointer to dma channel data or NULL if error.
 *   @param buff_loc - points to ping or pong buffer.
 *   @param fwmem_pair - fw memory pairs of virtual address and lenght.
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_sg_device_setup( void *ctx, int32_t buff_loc, dma_addr_pair_t *device_addr_pair, int32_t addr_pairs, uint32_t fw_ctx_id );

/**
 *   Needed to unmap the virtual address after dma completes
 *
 *   @param ctx - pointer to dma channel data or NULL if error.
 *   @param buff_loc - points to ping or pong buffer.
 *   @param device_addr_pair - pairs of dma bus address and lenght.
 *
 *   @return 0 - on success or -1 on error
 */
void system_cdma_unmap_sg( void *ctx );

/**
 *   Setup dma and run it
 *
 *   @param ctx - pointer to dma channel data or NULL if error.
 *   @param buff_loc - points to ping or pong buffer.
 *   @param direction - to the device or from the device.
 *   @param complete_func - function to be called after dma; ctx will be passed to this function for system_cdma_destroy
 *
 *   @return 0 - on success or -1 on error
 */
int32_t system_cdma_copy_sg( void *ctx, int32_t buff_loc, uint32_t direction, dma_completion_callback complete_func, uint32_t fw_ctx_id );


#endif // __SYSTEM_DMA_H__

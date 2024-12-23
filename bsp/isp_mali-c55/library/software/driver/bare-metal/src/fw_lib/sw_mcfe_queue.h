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

#ifndef __SW_MCFE_QUEUE_H__
#define __SW_MCFE_QUEUE_H__

#include "acamera_types.h"
#include "acamera_fw.h"
#include "acamera.h"
#include "system_log.h"
#include "system_spinlock.h"

#define SW_MCFE_Q_MAX_ENTRIES ( FIRMWARE_CONTEXT_NUMBER * 3 )

#define NO_ERROR 0

typedef struct {
    uint32_t ctx_id;   // Context id
    uint32_t ctx_type; // Context type
    void *private;     // frame metadata maintained by external driver
} mcfe_frame_t;

// Data structure to represent a circular queue with max size of MAX_ENTRIES
typedef struct {
    mcfe_frame_t entries[SW_MCFE_Q_MAX_ENTRIES]; // array to store queue elements
    int head;                                    // front points to the front element in the queue (if any)
    int tail;                                    // rear points to the last element in the queue
    uint32_t size;                               // Current size of the queue
    sys_spinlock queue_lock;                     // lock to protect queue concurrency
} mcfe_queue_t;

/**
 *   Initialize the MCFE queue.
 *
 *   @param  none
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_queue_init( void );

/**
 *   Deinitialize the MCFE queue.
 *
 *   @param  none
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_queue_deinit( void );

/**
 *   Enqueue a frame to the queue
 *
 *   @param  frame_ptr - pointer to the frame enqueued
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_enqueue( mcfe_frame_t *frame_ptr );

/**
 *   Dequeue a frame from the head of the queue
 *
 *   @param  frame_ptr - pointer to the frame dequeued
 *
 *   @return 0 - success
 *          -1 - fail.
 */
int32_t sw_mcfe_dequeue( mcfe_frame_t *frame_ptr );

#endif // __SW_MCFE_QUEUE_H__
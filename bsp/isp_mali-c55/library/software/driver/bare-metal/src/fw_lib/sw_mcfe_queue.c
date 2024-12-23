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

#include "sw_mcfe_queue.h"

// Global queue handle
static mcfe_queue_t g_mcfe_q;

static void reset( void )
{
    system_memset( g_mcfe_q.entries, 0, sizeof( g_mcfe_q.entries ) );
    g_mcfe_q.head = -1;
    g_mcfe_q.tail = -1;
    g_mcfe_q.size = 0;
}


/* Check if the queue is full */
static uint8_t _is_full( void )
{
    return ( g_mcfe_q.size == SW_MCFE_Q_MAX_ENTRIES );
}

/* Check if the queue is empty */
static uint8_t _is_empty( void )
{
    return ( g_mcfe_q.size == 0 );
}

/* Initialize the queue here */
int32_t sw_mcfe_queue_init()
{
    reset();
    system_spinlock_init( &g_mcfe_q.queue_lock );
    return 0;
}

/* Deinitialize the queue here */
int32_t sw_mcfe_queue_deinit( void )
{
    unsigned long flags = system_spinlock_lock( g_mcfe_q.queue_lock );
    reset();
    system_spinlock_unlock( g_mcfe_q.queue_lock, flags );
    system_spinlock_destroy( g_mcfe_q.queue_lock );
    return 0;
}

/* Enqueue a frame to the queue */
int32_t sw_mcfe_enqueue( mcfe_frame_t *frame_ptr )
{
    int32_t ret = NO_ERROR;
    unsigned long flags = system_spinlock_lock( g_mcfe_q.queue_lock );
    if ( _is_full() ) {
        LOG( LOG_ERR, "Failed to enqueue frame, all %d entries are in use", SW_MCFE_Q_MAX_ENTRIES );
        ret = -1;
    } else {
        if ( g_mcfe_q.head == -1 ) {
            g_mcfe_q.head = 0;
        }
        g_mcfe_q.tail = ( g_mcfe_q.tail + 1 ) % SW_MCFE_Q_MAX_ENTRIES;
        g_mcfe_q.entries[g_mcfe_q.tail] = *frame_ptr;
        g_mcfe_q.size++;
    }
    system_spinlock_unlock( g_mcfe_q.queue_lock, flags );
    return ret;
}

/* Dequeue a frame from the queue */
int32_t sw_mcfe_dequeue( mcfe_frame_t *frame_ptr )
{
    int32_t ret = NO_ERROR;
    unsigned long flags = system_spinlock_lock( g_mcfe_q.queue_lock );
    if ( _is_empty() || ( frame_ptr == NULL ) ) {
        ret = -1;
    } else {
        *frame_ptr = g_mcfe_q.entries[g_mcfe_q.head];
        if ( g_mcfe_q.head == g_mcfe_q.tail ) {
            g_mcfe_q.head = -1;
            g_mcfe_q.tail = -1;
        } else {
            g_mcfe_q.head = ( g_mcfe_q.head + 1 ) % SW_MCFE_Q_MAX_ENTRIES;
        }
        g_mcfe_q.size--;
    }
    system_spinlock_unlock( g_mcfe_q.queue_lock, flags );
    return ret;
}
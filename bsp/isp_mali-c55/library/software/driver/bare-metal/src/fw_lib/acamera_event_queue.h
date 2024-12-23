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

#if !defined( __ACAMERA_EVENT_QUEUE_H__ )
#define __ACAMERA_EVENT_QUEUE_H__

#include "acamera.h"
#include "acamera_loop_buf.h"
#include "system_spinlock.h"

typedef struct acamera_event_queue *acamera_event_queue_ptr_t;
typedef const struct acamera_event_queue *acamera_event_queue_const_ptr_t;

typedef struct acamera_event_queue {
    sys_spinlock lock;
    acamera_loop_buf_t buf;
} acamera_event_queue_t;

static __inline void acamera_event_queue_init( acamera_event_queue_ptr_t p_queue, uint8_t *p_data_buf, int data_buf_size )
{
    acamera_loop_buffer_init( &p_queue->buf, p_data_buf, data_buf_size );
    system_spinlock_init( &p_queue->lock );
}
void acamera_event_queue_push( acamera_event_queue_ptr_t p_queue, int event );
int acamera_event_queue_pop( acamera_event_queue_ptr_t p_queue );
int32_t acamera_event_queue_empty( acamera_event_queue_ptr_t p_queue );


static __inline void acamera_event_queue_deinit( acamera_event_queue_ptr_t p_queue )
{
    system_spinlock_destroy( p_queue->lock );
}

#endif /* __ACAMERA_EVENT_QUEUE_H__ */

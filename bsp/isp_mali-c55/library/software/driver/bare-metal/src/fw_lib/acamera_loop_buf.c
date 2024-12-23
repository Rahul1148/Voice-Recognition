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

#include "acamera_loop_buf.h"

void acamera_loop_buffer_init( acamera_loop_buf_ptr_t p_buf, uint8_t *p_data_buf, int data_buf_size )
{
    p_buf->head = p_buf->tail = 0;
    p_buf->p_data_buf = p_data_buf;
    p_buf->data_buf_size = data_buf_size;
}

uint8_t acamera_loop_buffer_read_u8( acamera_loop_buf_ptr_t p_buf, int pos )
{
    pos += p_buf->tail;
    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }
    return p_buf->p_data_buf[pos];
}

int acamera_loop_buffer_write_u8( acamera_loop_buf_ptr_t p_buf, int pos, uint8_t sample )
{
    pos += p_buf->head;
    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }
    p_buf->p_data_buf[pos++] = sample;
    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }
    return pos;
}

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

#ifndef __SYSTEM_CHARDEV_H__
#define __SYSTEM_CHARDEV_H__

/**
 *   Spawn (misc) character device as the access channel for the Control Software.
 *   Make sense only for the Firmware running in Linux kernel space.
 *   One client at a time supported.
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int system_chardev_init( void );

/**
 *   Nonblocking read from the character device.
 *
 *   @return  number of bytes read on success
 *           -1 is returned after userspace application connected or disconnected
 */
int system_chardev_read( char *data, int size );

/**
 *   Nonblocking write to the character device.
 *
 *   @return  number of bytes written on success
 *           -1 is returned after userspace application connected or disconnected
 */
int system_chardev_write( const char *data, int size );

/**
 *   Deregister character device.
 *
 *   @return  0 - on success
 *           -1 - on error
 */
int system_chardev_destroy( void );

#endif /* __SYSTEM_CHARDEV_H__ */

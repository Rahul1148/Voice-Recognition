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

#ifndef SYSTEM_LOG_H_INCLUDED
#define SYSTEM_LOG_H_INCLUDED

#include "acamera_types.h"
#include "acamera_firmware_config.h"
#include "system_timer.h"  //system_timer_timestamp
#include "system_stdlib.h" //system_memcpy
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

//defines for log level and system maximum value number for levels
#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_NOTICE 2
#define LOG_WARNING 3
#define LOG_ERR 4
#define LOG_CRIT 5
#define LOG_NOTHING 6
#define SYSTEM_LOG_LEVEL_MAX LOG_NOTHING

//system maximum value number of modules
#define SYSTEM_LOG_MODULE_MAX LOG_MODULE_MAX

//initial values for logger log level and log module masks on real time logging, otherwise fixed
#define SYSTEM_LOG_LEVEL FW_LOG_LEVEL
#define SYSTEM_LOG_MASK FW_LOG_MASK


/*define for the logger for real time changing of level and module support
value of 1 means real time logging is enabled otherwise disabled on a compile level*/
#define SYSTEM_LOG_REAL_TIME FW_LOG_REAL_TIME

/*define for the logger to include src information like filenames and line number
value of 1 means filename, function and line number is logged otherwise disabled on a compile level*/
#define SYSTEM_LOG_HAS_SRC FW_LOG_HAS_SRC

/*define for the logger to enable logging from ISR
value of 1 means ISR logging is enabled otherwise disabled on the compile level*/
#define SYSTEM_LOG_FROM_ISR FW_LOG_FROM_ISR

//printf like functions used by the logger to log output
#define SYSTEM_VPRINTF vprintf
#define SYSTEM_PRINTF printf
#define SYSTEM_SNPRINTF snprintf
#define SYSTEM_VSPRINTF vsprintf

/*define for the logger to include time on the output log
value of 1 means timestamp is logged otherwise disabled on the compile level*/
#define SYSTEM_LOG_HAS_TIME FW_LOG_HAS_TIME

//callback for acamera_logger to log the time
#define SYSTEM_TIME_LOG_CB sys_time_log_cb
extern const char *sys_time_log_cb( void );

//debug log names for level and modules
extern const char *const log_level_name[SYSTEM_LOG_LEVEL_MAX];
extern const char *const log_module_name[SYSTEM_LOG_MODULE_MAX];


#endif // LOG_H_INCLUDED

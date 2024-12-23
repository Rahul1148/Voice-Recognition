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
#include "acamera_firmware_config.h"
#include "acamera_logger.h"
#include "acamera_types.h"


uint32_t bus_addr[] = {
0xffe00000, 
#if FIRMWARE_CONTEXT_NUMBER == 2
0xffe01000
#endif // FIRMWARE_CONTEXT_NUMBER == 2
} ;
static uint32_t sensor_counter = 0;
static uint32_t lens_counter = 0;


int32_t get_next_sensor_bus_address( void ) {
    int32_t result = 0;
    if ( sensor_counter < FIRMWARE_CONTEXT_NUMBER ) {
        result = bus_addr[ sensor_counter ];
        sensor_counter++;
    } else {
        result = -1;
        LOG( LOG_ERR, "Attempt to initialize more sensor instances than was configured.");
    }
    return result;
}


void reset_sensor_bus_counter( void ) {
    sensor_counter = 0;
}


int32_t get_next_lens_bus_address(void) {
    int32_t result = 0;
    if ( lens_counter < FIRMWARE_CONTEXT_NUMBER ) {
        result = bus_addr[ lens_counter ];
        lens_counter++;
    } else {
        result = -1;
        LOG( LOG_ERR, "Attempt to initialize more sensor lens instances than was configured.");
    }
    return result;
}


void reset_lens_bus_counter( void ) {
    lens_counter = 0;
}


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

#include "acamera_firmware_config.h"
#include "acamera_lens_api.h"
#include "acamera_types.h"

#include "sensor_bus_config.h"
/*    - Test the driver in this file                            */
/*                                                              */

#if ISP_SENSOR_DRIVER_DONGWOON
#include "dongwoon_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_DW9800
#include "dw9800_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_AD5821
#include "AD5821_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_ROHM
#include "rohm_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_LC898201
#include "LC898201_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_FP5510A
#include "fp5510a_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_BU64748
#include "BU64748_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_BU64295
#include "BU64295_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_AN41908A
#include "an41908a_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_MODEL
#include "model_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_NULL
#include "null_vcm.h"
#endif
#if ISP_SENSOR_DRIVER_V4L2
#include "v4l2_vcm.h"
#endif

#include "acamera_logger.h"

#if ISP_SENSOR_DRIVER_V4L2
int32_t lens_init_v4l2( void **ctx, lens_control_t *ctrl )
{
    uint32_t lens_bus = 0;
#else
int32_t lens_init( void **ctx, lens_control_t *ctrl )
{
    uint32_t lens_bus = get_next_lens_bus_address();
#endif
#if ISP_SENSOR_DRIVER_V4L2
    if ( lens_v4l2_subdev_test( lens_bus ) ) {
        lens_v4l2_subdev_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is V4L2 subdev" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_DONGWOON
    if ( lens_dongwoon_test( lens_bus ) ) {
        lens_dongwoon_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is DONGWOON" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_DW9800
    if ( lens_dw9800_test( lens_bus ) ) {
        lens_dw9800_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is DW9800" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_AD5821
    if ( lens_AD5821_test( lens_bus ) ) {
        lens_AD5821_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is AD5821" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_ROHM
    if ( lens_rohm_test( lens_bus ) ) {
        lens_rohm_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is ROHM" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_LC898201
    if ( lens_LC898201_test( lens_bus ) ) {
        lens_LC898201_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is LC898201" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_FP5510A
    if ( lens_fp5510a_test( lens_bus ) ) {
        lens_fp5510a_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is FP5510A" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_BU64748
    if ( lens_BU64748_test( lens_bus ) ) {
        lens_BU64748_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is BU64748 (ROHM)" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_BU64295
    if ( lens_BU64295_test( lens_bus ) ) {
        lens_BU64295_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is BU64748 (ROHM)" );
        return 0;
    }
#endif    
#if ISP_SENSOR_DRIVER_AN41908A
    if ( lens_an41908a_test( lens_bus ) ) {
        lens_an41908a_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is AN41908A" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_MODEL
    if ( lens_model_test( lens_bus ) ) {
        lens_model_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is Model" );
        return 0;
    }
#endif
#if ISP_SENSOR_DRIVER_NULL
    // Null should always be tested last
    if ( lens_null_test( lens_bus ) ) {
        lens_null_init( ctx, ctrl, lens_bus );
        LOG( LOG_NOTICE, "Lens VCM driver is NULL" );
        return 0;
    }
#endif

    LOG( LOG_WARNING, "NO VALID SENSOR DRIVER FOUND bus:0x%x", lens_bus );
    return -1;
}

#if ISP_SENSOR_DRIVER_V4L2
void lens_deinit_v4l2( void *ctx )
#else
void lens_deinit( void *ctx )
#endif
{
#if ISP_SENSOR_DRIVER_V4L2
    lens_v4l2_subdev_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_BU64748
    lens_BU64748_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_DONGWOON
    lens_dongwoon_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_DW9800
    lens_dw9800_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_AD5821
    lens_AD5821_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_ROHM
    lens_rohm_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_LC898201
    lens_LC898201_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_FP5510A
    lens_fp5510a_deinit( ctx );
#endif
#if ISP_SENSOR_DRIVER_AN41908A
    lens_an41908a_deinit( ctx );
#endif
#if !ISP_SENSOR_DRIVER_V4L2
    reset_lens_bus_counter();
#endif
}

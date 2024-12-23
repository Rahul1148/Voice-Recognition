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

#include "acamera_lens_api.h"
#include "acamera_logger.h"
#include "acamera_sbus_api.h"

typedef struct _lens_context_t {
    acamera_sbus_t p_bus;

    uint16_t pos;
    uint16_t prev_pos;
    uint16_t move_pos;

    uint32_t time;

    lens_param_t param;
} lens_context_t;

uint8_t lens_null_test( uint32_t lens_bus )
{
    return 1;
}

static void vcm_null_drv_move( void *ctx, uint16_t position )
{
    LOG( LOG_WARNING, "Null VCM driver use attempted: no lens movement can be performed with the null driver" );
}

static uint8_t vcm_null_drv_is_moving( void *ctx )
{
    LOG( LOG_WARNING, "Null VCM driver use attempted: no lens movement can be performed with the null driver" );
    return 0;
}

static void vcm_null_write_register( void *ctx, uint32_t address, uint32_t data )
{
}

static uint32_t vcm_null_read_register( void *ctx, uint32_t address )
{
    return 0;
}

static const lens_param_t *lens_get_parameters( void *ctx )
{
    lens_context_t *p_ctx = ctx;
    return (const lens_param_t *)&p_ctx->param;
}

void lens_null_deinit( void *ctx )
{
}

void lens_null_init( void **ctx, lens_control_t *ctrl, uint32_t lens_bus )
{

    static lens_context_t l_ctx;
    *ctx = &l_ctx;

    ctrl->is_moving = vcm_null_drv_is_moving;
    ctrl->move = vcm_null_drv_move;
    ctrl->write_lens_register = vcm_null_write_register;
    ctrl->read_lens_register = vcm_null_read_register;
    ctrl->get_parameters = lens_get_parameters;

    l_ctx.prev_pos = 0;

    memset( &l_ctx.param, 0, sizeof( lens_param_t ) );
    l_ctx.param.min_step = 1 << 6;
    l_ctx.param.lens_type = LENS_VCM_DRIVER_NULL;
}

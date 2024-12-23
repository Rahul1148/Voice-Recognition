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

#include "acamera.h"
#include "acamera_fw.h"
#include "acamera_firmware_config.h"
#include "acamera_logger.h"
#include "system_timer.h"

static ACameraCalibrations *get_current_set( void *p_ctx )
{
    return &( (acamera_context_ptr_t)p_ctx )->acameraCalibrations;
}

LookupTable *_GET_LOOKUP_PTR( void *p_ctx, uint32_t idx )
{
    LookupTable *result = NULL;
    if ( idx < CALIBRATION_TOTAL_SIZE ) {
        result = get_current_set( p_ctx )->calibrations[idx];
    } else {
        result = NULL;
        LOG( LOG_CRIT, "Trying to access an ISP LUT with invalid index %d.", (int)idx );
    }
    return result;
}


const void *_GET_LUT_PTR( void *p_ctx, uint32_t idx )
{
    const void *result = NULL;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->ptr;
    } else {
        while ( 1 ) {
            fsm_param_mon_err_head_t mon_err_head;
            mon_err_head.err_type = MON_TYPE_ERR_CALIBRATION_LUT_NULL;
            mon_err_head.err_param = idx;
            acamera_fsm_mgr_set_param( &( (acamera_context_ptr_t)p_ctx )->fsm_mgr, FSM_PARAM_SET_MON_ERROR_REPORT, &mon_err_head, sizeof( mon_err_head ) );
            LOG( LOG_CRIT, "LUT 0x%x is not initialized. Pointer is NULL. Going to the infinite loop.", (int)idx );

            // sleep 3 second to avoid affect system performance badly.
            system_timer_usleep( 3 * 1000 * 1000 );
        };
    }
    return result;
}

// use fast version of lut access routines
uint8_t *_GET_UCHAR_PTR( void *p_ctx, uint32_t idx )
{
    uint8_t *result = (uint8_t *)_GET_LUT_PTR( p_ctx, idx );
    return result;
}

uint16_t *_GET_USHORT_PTR( void *p_ctx, uint32_t idx )
{
    uint16_t *result = (uint16_t *)_GET_LUT_PTR( p_ctx, idx );
    return result;
}

uint32_t *_GET_UINT_PTR( void *p_ctx, uint32_t idx )
{
    uint32_t *result = (uint32_t *)_GET_LUT_PTR( p_ctx, idx );
    return result;
}

modulation_entry_t *_GET_MOD_ENTRY16_PTR( void *p_ctx, uint32_t idx )
{
    modulation_entry_t *result = (modulation_entry_t *)_GET_LUT_PTR( p_ctx, idx );
    return result;
}

modulation_entry_32_t *_GET_MOD_ENTRY32_PTR( void *p_ctx, uint32_t idx )
{
    modulation_entry_32_t *result = (modulation_entry_32_t *)_GET_LUT_PTR( p_ctx, idx );
    return result;
}

uint32_t _GET_ROWS( void *p_ctx, uint32_t idx )
{
    uint32_t result = 0;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->rows;
    }
    return result;
}

uint32_t _GET_COLS( void *p_ctx, uint32_t idx )
{
    uint32_t result = 0;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->cols;
    }
    return result;
}

uint32_t _GET_LEN( void *p_ctx, uint32_t idx )
{
    uint32_t result = 0;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->cols * lut->rows;
    }
    return result;
}

uint32_t _GET_WIDTH( void *p_ctx, uint32_t idx )
{
    uint32_t result = 0;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->width;
    }
    return result;
}

uint32_t _GET_SIZE( void *p_ctx, uint32_t idx )
{
    uint32_t result = 0;
    LookupTable *lut = _GET_LOOKUP_PTR( p_ctx, idx );
    if ( lut != NULL ) {
        result = lut->cols * lut->rows * lut->width;
    }
    return result;
}

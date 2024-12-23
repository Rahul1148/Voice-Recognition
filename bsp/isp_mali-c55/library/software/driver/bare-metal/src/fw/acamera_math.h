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

#ifndef __ACAMERA_MATH_H__
#define __ACAMERA_MATH_H__

#include "acamera_types.h"
#include "acamera_firmware_config.h"


#if KERNEL_MODULE == 1
#include <asm/div64.h>
#include "linux/math64.h"
#else
#define div64_u64( x, y ) ( ( x ) / ( y ) )
#define div64_s64( x, y ) ( ( x ) / ( y ) )
#endif


#define ACAMERA_ABS( a ) ( {               \
    long ret;                              \
    if ( sizeof( a ) == sizeof( long ) ) { \
        long __a = ( a );                  \
        ret = ( __a < 0 ) ? -__a : __a;    \
    } else {                               \
        int __a = ( a );                   \
        ret = ( __a < 0 ) ? -__a : __a;    \
    }                                      \
    ret;                                   \
} )


#ifndef U16_MAX
#define U16_MAX 0xFFFF
#endif
#define ACAMERA_SIGN( a ) ( ( a ) >= 0 ? ( 1 ) : ( -1 ) )
#define ACAMERA_MIN( a, b ) ( ( a ) >= b ? ( b ) : ( a ) )
#define ACAMERA_MAX( a, b ) ( ( a ) >= b ? ( a ) : ( b ) )
#define ACAMERA_ABSDIFF( a, b ) ( ( a ) > ( b ) ? ( a - b ) : ( b - a ) )
#define LIN_EQUATION_FRACTION_SIZE 5


#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif
#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif


#define array_size( a ) \
    ( sizeof( a ) / sizeof( a[0] ) )


#define round_shift( a, sh ) ( ( ( a ) >> ( sh ) ) + ( ( ( a ) >> ( sh - 1 ) ) & 1 ) )


typedef struct _modulation_entry_t {
    uint16_t x, y;
} modulation_entry_t;


typedef struct _modulation_entry_32_t {
    uint32_t x, y;
} modulation_entry_32_t;


uint32_t acamera_sqrt64( uint64_t arg );
uint16_t acamera_sqrt32( uint32_t arg );
uint32_t acamera_log2_int_to_fixed( const uint32_t val, const uint8_t out_precision, const uint8_t shift_out );
uint32_t acamera_log2_fixed_to_fixed( const uint32_t val, const int in_fix_point, const uint8_t out_fix_point );
int32_t acamera_log2_fixed_to_fixed_64( uint64_t val, int32_t in_fix_point, uint8_t out_fix_point );
uint32_t acamera_math_exp2( uint32_t val, const unsigned char shift_in, const unsigned char shift_out );
uint8_t acamera_sqrt16( uint16_t arg );
uint8_t acamera_log16( uint16_t arg );
uint32_t acamera_math_log2( const uint32_t val, const uint8_t out_precision, const uint8_t shift_out );
uint32_t acamera_multiplication_fixed_to_fixed( uint32_t a, uint32_t b, const int x1, const int x2 );

int32_t acamera_solving_lin_equation_a( int32_t y1, int32_t y2, int32_t x1, int32_t x2, int16_t a_fraction_size );
int32_t acamera_solving_lin_equation_b( int32_t y1, int32_t a, int32_t x1, int16_t a_fraction_size );
int32_t acamera_solving_nth_root_045( int32_t x, const int16_t fraction_size );
uint32_t acamera_div_fixed( uint32_t a, uint32_t b, int16_t a_fraction_size );
uint16_t acamera_sqrt32( uint32_t arg );

uint16_t acamera_line_offset( uint16_t line_len, uint8_t bits_per_pixel );


#define ACAMERA_MODULO( N, D ) ( ( N ) - ( ( ( N ) / ( D ) ) * ( D ) ) )


uint16_t acamera_calc_modulation_u16( uint16_t x, const modulation_entry_t *p_table, int table_len );
uint32_t acamera_calc_modulation_u32( uint32_t x, const modulation_entry_32_t *p_table, int table_len );

uint16_t acamera_calc_scaled_modulation_u16( uint16_t x, uint16_t target_min_y, uint16_t target_max_y, const modulation_entry_t *p_table, int table_len );

uint16_t acamera_calc_equidistant_modulation_u16( uint16_t x, const uint16_t *p_table, uint16_t table_len );
uint32_t acamera_calc_equidistant_modulation_u32( uint32_t x, const uint32_t *p_table, uint32_t table_len );
uint16_t acamera_calc_inv_equidistant_modulation_u16( uint16_t x, const uint16_t *p_table, uint16_t table_len );
uint32_t acamera_calc_inv_equidistant_modulation_u32( uint32_t x, const uint32_t *p_table, uint32_t table_len );


#endif /* __ACAMERA_MATH_H__ */

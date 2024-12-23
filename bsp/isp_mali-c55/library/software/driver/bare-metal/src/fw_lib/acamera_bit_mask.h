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

#if !defined( __ACAMERA_BIT_MASK_H__ )
#define __ACAMERA_BIT_MASK_H__


#define ACAMERA_BITMASK_CELL_TYPE uint32_t
#define ACAMERA_BITMASK_BITS_PER_CELL ( sizeof( ACAMERA_BITMASK_CELL_TYPE ) * 8 )
#define ACAMERA_BITMASK_CELL_COUNT( bits_count ) \
    ( ( bits_count + ACAMERA_BITMASK_BITS_PER_CELL - 1 ) / ACAMERA_BITMASK_BITS_PER_CELL )

static __inline uint8_t acamera_bitmask_get_bit( const ACAMERA_BITMASK_CELL_TYPE *p_bits, int idx )
{
    return ( p_bits[idx / ACAMERA_BITMASK_BITS_PER_CELL] >> ( idx % ACAMERA_BITMASK_BITS_PER_CELL ) ) & 1;
}

static __inline void acamera_bitmask_set_bit( ACAMERA_BITMASK_CELL_TYPE *p_bits, int idx )
{
    p_bits[idx / ACAMERA_BITMASK_BITS_PER_CELL] |= 1 << ( idx % ACAMERA_BITMASK_BITS_PER_CELL );
}

static __inline void acamera_bitmask_clear_bit( ACAMERA_BITMASK_CELL_TYPE *p_bits, int idx )
{
    p_bits[idx / ACAMERA_BITMASK_BITS_PER_CELL] &= ~( 1 << ( idx % ACAMERA_BITMASK_BITS_PER_CELL ) );
}

#endif /* __ACAMERA_BIT_MASK_H__ */

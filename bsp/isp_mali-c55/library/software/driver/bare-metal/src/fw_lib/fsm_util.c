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
#include "acamera_fw.h"

uint32_t acamera_fsm_util_is_irq_event_ignored( fsm_irq_mask_t *p_mask, uint8_t irq_event )
{
    uint32_t ignore_irq = 1;
    uint32_t fsm_mask;
    uint32_t mask = 1 << irq_event;
    fsm_mask = p_mask->irq_mask & mask;
    if ( fsm_mask ) {
        p_mask->irq_mask &= ( ~fsm_mask ) | ( p_mask->repeat_irq_mask );
        ignore_irq = 0;
    }

    return ignore_irq;
}

uint32_t acamera_fsm_util_get_cur_frame_id( fsm_common_t *p_cmn )
{
    uint32_t cur_frame_id = 0;
#if ISP_HW_IS_MALI_C32_C52
    cur_frame_id = acamera_isp_isp_global_dbg_frame_cnt_ctx0_read( p_cmn->isp_base );
#else
    cur_frame_id = acamera_isp_isp_global_dbg_frame_cnt_read( p_cmn->isp_base );
#endif
    return cur_frame_id;
}

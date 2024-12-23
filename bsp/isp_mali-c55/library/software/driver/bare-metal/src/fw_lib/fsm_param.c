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

#include "acamera_fw.h"
#if defined( ISP_HAS_DMA_WRITER_FSM )
#include "dma_writer_fsm.h"
#endif


int acamera_fsm_mgr_set_param( acamera_fsm_mgr_t *p_fsm_mgr, uint32_t param_id, void *input, uint32_t input_size )
{
    int rc = 0;

    if ( param_id >= FSM_PARAM_SET_MAX_ID || param_id <= FSM_PARAM_SET_MIN_ID ) {
        LOG( LOG_ERR, "Invalid param: param_id: %d, min: %d, max: %d.", param_id, FSM_PARAM_SET_MIN_ID, FSM_PARAM_SET_MAX_ID );
        return -1;
    }

    if ( FSM_PARAM_SET_SENSOR_START < param_id && param_id < FSM_PARAM_SET_SENSOR_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "SENSOR FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_CMOS_START < param_id && param_id < FSM_PARAM_SET_CMOS_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "CMOS FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_GENERAL_START < param_id && param_id < FSM_PARAM_SET_GENERAL_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "GENERAL FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_AE_START < param_id && param_id < FSM_PARAM_SET_AE_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AE]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AE]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_AE]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "AE FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_AWB_START < param_id && param_id < FSM_PARAM_SET_AWB_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AWB]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AWB]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_AWB]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "AWB FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_AF_START < param_id && param_id < FSM_PARAM_SET_AF_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AF]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AF]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_AF]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "AF FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_COLOR_MATRIX_START < param_id && param_id < FSM_PARAM_SET_COLOR_MATRIX_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "COLOR_MATRIX FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_PURPLE_FRINGE_START < param_id && param_id < FSM_PARAM_SET_PURPLE_FRINGE_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_PURPLE_FRINGE]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_PURPLE_FRINGE]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_PURPLE_FRINGE]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "PURPLE_FRINGE FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_IRIDIX_START < param_id && param_id < FSM_PARAM_SET_IRIDIX_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "IRIDIX FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_NOISE_REDUCTION_START < param_id && param_id < FSM_PARAM_SET_NOISE_REDUCTION_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "NOISE_REDUCTION FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_CROP_START < param_id && param_id < FSM_PARAM_SET_CROP_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_CROP]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_CROP]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_CROP]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "CROP FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_SHARPENING_START < param_id && param_id < FSM_PARAM_SET_SHARPENING_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "SHARPENING FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_MATRIX_YUV_START < param_id && param_id < FSM_PARAM_SET_MATRIX_YUV_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "MATRIX_YUV FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_GAMMA_ACAMERA_START < param_id && param_id < FSM_PARAM_SET_GAMMA_ACAMERA_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "GAMMA_ACAMERA FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_DMA_WRITER_START < param_id && param_id < FSM_PARAM_SET_DMA_WRITER_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "DMA_WRITER FSM doesn't support set_param()." );
            rc = -1;
        }
    } else if ( FSM_PARAM_SET_MONITOR_START < param_id && param_id < FSM_PARAM_SET_MONITOR_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->ops.set_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->ops.set_param( p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->p_fsm, param_id, input, input_size );
        } else {
            LOG( LOG_ERR, "MONITOR FSM doesn't support set_param()." );
            rc = -1;
        }
    } else {
        LOG( LOG_ERR, "Unsupported param_id: %d.", param_id );
        rc = -1;
    }

    return rc;
}

int acamera_fsm_mgr_get_param( acamera_fsm_mgr_t *p_fsm_mgr, uint32_t param_id, void *input, uint32_t input_size, void *output, uint32_t output_size )
{
    int rc = 0;

    if ( param_id >= FSM_PARAM_GET_MAX_ID || param_id <= FSM_PARAM_GET_MIN_ID ) {
        LOG( LOG_ERR, "Invalid param: param_id: %d, min: %d, max: %d.", param_id, FSM_PARAM_GET_MIN_ID, FSM_PARAM_GET_MAX_ID );
        return -1;
    }

    if( FSM_PARAM_GET_SENSOR_START < param_id && param_id < FSM_PARAM_GET_SENSOR_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_SENSOR]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "SENSOR FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_CMOS_START < param_id && param_id < FSM_PARAM_GET_CMOS_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_CMOS]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "CMOS FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_GENERAL_START < param_id && param_id < FSM_PARAM_GET_GENERAL_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_GENERAL]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "GENERAL FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_AE_START < param_id && param_id < FSM_PARAM_GET_AE_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AE]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AE]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_AE]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "AE FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_AWB_START < param_id && param_id < FSM_PARAM_GET_AWB_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AWB]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AWB]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_AWB]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "AWB FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_AF_START < param_id && param_id < FSM_PARAM_GET_AF_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_AF]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_AF]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_AF]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "AF FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_COLOR_MATRIX_START < param_id && param_id < FSM_PARAM_GET_COLOR_MATRIX_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_COLOR_MATRIX]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "COLOR_MATRIX FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_IRIDIX_START < param_id && param_id < FSM_PARAM_GET_IRIDIX_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_IRIDIX]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "IRIDIX FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_NOISE_REDUCTION_START < param_id && param_id < FSM_PARAM_GET_NOISE_REDUCTION_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_NOISE_REDUCTION]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "NOISE_REDUCTION FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_CROP_START < param_id && param_id < FSM_PARAM_GET_CROP_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_CROP]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_CROP]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_CROP]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "CROP FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_SHARPENING_START < param_id && param_id < FSM_PARAM_GET_SHARPENING_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_SHARPENING]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "SHARPENING FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_MATRIX_YUV_START < param_id && param_id < FSM_PARAM_GET_MATRIX_YUV_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_MATRIX_YUV]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "MATRIX_YUV FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_GAMMA_ACAMERA_START < param_id && param_id < FSM_PARAM_GET_GAMMA_ACAMERA_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_GAMMA_ACAMERA]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "GAMMA_ACAMERA FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_DMA_WRITER_START < param_id && param_id < FSM_PARAM_GET_DMA_WRITER_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "DMA_WRITER FSM doesn't support get_param()." );
            rc = -1;
        }
    } else if( FSM_PARAM_GET_MONITOR_START < param_id && param_id < FSM_PARAM_GET_MONITOR_END ) {
        if ( p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->ops.get_param ) {
            rc = p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->ops.get_param( p_fsm_mgr->fsm_arr[FSM_ID_MONITOR]->p_fsm, param_id, input, input_size, output, output_size );
        } else {
            LOG( LOG_ERR, "MONITOR FSM doesn't support get_param()." );
            rc = -1;
        }
    } else {
        LOG( LOG_ERR, "Unsupported param_id: %d.", param_id );
        rc = -1;
    }

    return rc;
}

void acamera_fsm_mgr_dma_writer_update_address_interrupt( acamera_fsm_mgr_t *p_fsm_mgr, uint8_t irq_event )
{
#if defined( ISP_HAS_DMA_WRITER_FSM )
    dma_writer_update_address_interrupt( p_fsm_mgr->fsm_arr[FSM_ID_DMA_WRITER]->p_fsm, irq_event );
#endif
}

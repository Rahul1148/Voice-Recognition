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

#if !defined( __ACAMERA_FW_H__ )
#define __ACAMERA_FW_H__

#include "acamera_types.h"
#include "acamera_logger.h"
#include "acamera_calibrations.h"
#include "system_interrupts.h"
#include "system_semaphore.h"
#include "acamera_firmware_api.h"
#include "acamera_firmware_config.h"
#include "acamera_isp_config.h"


#define FW_PAUSE 0
#define FW_RUN 1


struct _acamera_fsm_mgr_t;
struct _acamera_context_t;
struct _dma_raw_capture_t;
struct _acamera_firmware_t;
struct _isp_info_t;
typedef struct _acamera_fsm_mgr_t acamera_fsm_mgr_t;
typedef struct _acamera_context_t acamera_context_t;
typedef struct _acamera_context_t *acamera_context_ptr_t;
typedef struct _dma_raw_capture_t dma_raw_capture_t;
typedef struct _acamera_firmware_t acamera_firmware_t;
typedef struct _isp_info_t isp_info_t;

struct _isp_info_t {
    uint8_t state;
};

#include "acamera_fsm_mgr.h"
#include "fsm_util.h"
#include "fsm_param.h"
#include "sensor_init.h"
#include "acamera_isp_config.h"


#if ISP_DMA_RAW_CAPTURE
#include "dma_raw_capture.h"
#endif

#if ( ISP_HAS_FPGA_WRAPPER )
#include "fpga_dma_input.h"
#endif
typedef struct _hw_module_fitted_tab {
    uint8_t pong_config;
    uint8_t wdr;
    uint8_t compression;
    uint8_t temper;
    uint8_t sinter_lite;
    uint8_t sinter;
    uint8_t iridix_ltm;
    uint8_t iridix_gtm;
    uint8_t cnr;
    uint8_t frscaler;
    uint8_t ds_pipe;
} hw_module_fitted_tab;

typedef struct _sytem_tab {
    uint8_t global_freeze_firmware;
    uint8_t global_manual_exposure;
    uint8_t global_manual_exposure_ratio;

    uint8_t global_manual_iridix;
    uint8_t global_manual_sinter;
    uint8_t global_manual_temper;
    uint8_t global_manual_awb;
    uint8_t global_manual_ccm;
    uint8_t global_manual_saturation;
    uint8_t global_manual_auto_level;
    uint8_t global_manual_frame_stitch;
    uint8_t global_manual_raw_frontend;
    uint8_t global_manual_black_level;
    uint8_t global_manual_shading;
    uint8_t global_manual_demosaic;
    uint8_t global_manual_cnr;
    uint8_t global_manual_sharpen;

    uint32_t global_exposure;
    uint32_t global_long_integration_time;
    uint32_t global_short_integration_time;
    uint8_t global_exposure_ratio;


    uint8_t global_iridix_strength_target;
    uint8_t global_maximum_iridix_strength;
    uint8_t global_minimum_iridix_strength;
    uint8_t global_sinter_threshold_target;
    uint8_t global_temper_threshold_target;
    uint16_t global_awb_red_gain;
    uint16_t global_awb_green_even_gain;
    uint16_t global_awb_green_odd_gain;
    uint16_t global_awb_blue_gain;
    int16_t global_ccm_matrix[9];
    uint8_t global_saturation_target;

    uint8_t global_ae_compensation;
    uint8_t global_calibrate_bad_pixels;
    uint32_t global_info_preset_num;
    uint8_t global_dynamic_gamma_enable;
    hw_module_fitted_tab hw_fitted;
} system_tab;

typedef struct _acamera_isp_sw_regs_map {
    volatile uint8_t *isp_sw_config_map;
} acamera_isp_sw_regs_map;


struct _acamera_context_t {
    uint32_t irq_flag;

    // profiling routines
    uint32_t binit_profiler;
    uint32_t breport_profiler;
    uint32_t start_profiling;
    uint32_t stop_profiling;
    uint32_t frame;

    uint8_t system_state;
    uint8_t initialized;
    uint8_t hflip;
    uint8_t vflip;

    acamera_fsm_mgr_t fsm_mgr;
    acamera_firmware_t *p_gfw;

    // current calibration set
    ACameraCalibrations acameraCalibrations;

    // global settings which can be shared through fsms
    system_tab stab;

    uint32_t context_id;
    uint32_t *context_ref;

    // context settings
    acamera_settings settings;

    const acam_reg_t **isp_sequence;

    int32_t isp_sequence_default;

    /* frame counters */
    uint32_t isp_frame_counter_raw; // frame counter for raw callback
    uint32_t isp_frame_counter;     // frame counter for frame / metadata callbacks

    acamera_isp_sw_regs_map sw_reg_map;
};


struct _acamera_firmware_t {
#if ISP_DMA_RAW_CAPTURE
    // dma_capture
    dma_raw_capture_t dma_raw_capture;
#endif

#if ( ISP_HAS_FPGA_WRAPPER )
    dma_input_t dma_input;
#endif

    uint32_t api_context; // the active context for API and to display
    // context instances
    uint32_t context_number;
    acamera_context_t fw_ctx[FIRMWARE_CONTEXT_NUMBER];

    void *dma_chan_isp_config;
    uint32_t dma_flag_isp_config_completed;
    void *dma_chan_isp_metering;
    uint32_t dma_flag_isp_metering_completed;

    uint32_t initialized;

    semaphore_t sem_evt_avail;
};

void acamera_load_isp_sequence( uintptr_t isp_base, const acam_reg_t *sequence[], uint8_t num );
void acamera_load_sw_sequence( uintptr_t isp_base, const acam_reg_t *sequence[], uint8_t num );
void load_sensor_sequence( uint8_t num );
void acamera_load_array_sequence( acamera_sbus_ptr_t p_sbus, uintptr_t isp_offset, char size, const acam_reg_t *sequence[], int group );


static __inline void acamera_fw_interrupts_enable( acamera_context_ptr_t p_ctx )
{
    if ( p_ctx != NULL ) {
        if ( !( p_ctx->irq_flag ) ) {
            system_interrupts_enable();
        }
    }
}

static __inline void acamera_fw_interrupts_disable( acamera_context_ptr_t p_ctx )
{
    if ( p_ctx != NULL ) {
        if ( !( p_ctx->irq_flag ) ) {
            system_interrupts_disable();
        }
    }
}

static __inline void acamera_isp_interrupts_enable( acamera_fsm_mgr_t *p_fsm_mgr )
{
    if ( p_fsm_mgr != NULL ) {
        acamera_fw_interrupts_enable( p_fsm_mgr->p_ctx );
    }
}

static __inline void acamera_isp_interrupts_disable( acamera_fsm_mgr_t *p_fsm_mgr )
{
    if ( p_fsm_mgr != NULL ) {
        acamera_fw_interrupts_disable( p_fsm_mgr->p_ctx );
    }
}

void acamera_fw_raise_event( acamera_context_ptr_t p_ctx, event_id_t event_id );

void acamera_fw_process( acamera_context_t *p_ctx );

void acamera_fw_init( acamera_context_t *p_ctx );
void acamera_fw_deinit( acamera_context_t *p_ctx );
int32_t acamera_init_context( acamera_context_t *p_ctx, acamera_settings *settings, acamera_firmware_t *g_fw );
void acamera_deinit_context( acamera_context_t *p_ctx );
void acamera_general_interrupt_hanlder( acamera_context_ptr_t p_ctx, uint8_t event );

int32_t acamera_init_calibrations( acamera_context_ptr_t p_ctx );
void acamera_change_resolution( acamera_context_ptr_t p_ctx, uint32_t exposure_correction );
void configure_buffers( acamera_context_ptr_t p_ctx, uint32_t start_addr, uint16_t width, uint16_t height );
void acamera_fw_error_routine( acamera_context_t *p_ctx, uint32_t irq_mask );

#define ACAMERA_MGR2CTX_PTR( p_fsm_mgr ) \
    ( ( p_fsm_mgr )->p_ctx )

#define ACAMERA_MGR2FIRMWARE_PTR( p_fsm_mgr ) \
    ( ( p_fsm_mgr )->p_ctx->p_gfw )

#define ACAMERA_FSM2MGR_PTR( p_fsm ) \
    ( ( p_fsm )->p_fsm_mgr )

#define ACAMERA_FSM2CTX_PTR( p_fsm ) \
    ( ( p_fsm )->p_fsm_mgr->p_ctx )

#endif /* __ACAMERA_FW_H__ */

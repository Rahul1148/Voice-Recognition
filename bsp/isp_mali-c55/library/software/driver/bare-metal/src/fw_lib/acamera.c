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
#include "acamera_firmware_api.h"
#include "acamera_firmware_config.h"
#include "acamera_calibrations.h"
#include "acamera.h"
#include "acamera_math.h"
#include "acamera_isp_config.h"
#include "system_stdlib.h"
#include "system_cdma.h"
#include "acamera_metering_stats_mem_config.h"
#include "acamera_aexp_hist_stats_mem_config.h"
#include "acamera_decompander0_mem_config.h"
#include "acamera_ihist_stats_mem_config.h"

#if ISP_HAS_FPGA_WRAPPER
#include "isp_config_seq.h"
#endif

#if ( FIRMWARE_CONTEXT_NUMBER > 1 ) && ( !USER_MODULE )
#define FW_HAS_SW_MCFE 1
#else
#define FW_HAS_SW_MCFE 0
#endif

#if FW_HAS_SW_MCFE
#include "sw_mcfe.h"
#endif

#if FW_HAS_CONTROL_CHANNEL
#include "acamera_ctrl_channel.h"
#endif

#if ISP_DMA_RAW_CAPTURE
#include "dma_raw_capture.h"
#endif

#if ACAMERA_ISP_PROFILING
#include "acamera_profiler.h"
#endif

#if ISP_HAS_FPGA_WRAPPER
#include "acamera_fpga_config.h"
#endif

#if ACAMERA_ISP_PROFILING
#ifndef CHECK_STACK_SIZE_DWORDS
#define CHECK_STACK_SIZE_DWORDS 1024
#endif
#define CHECK_STACK_SIZE_START 512
#endif

#include "acamera_logger.h"
#include "fsm_param.h"

#define ACAMERA_CONTEXT_SIZE ( ACAMERA_ISP1_BASE_ADDR + ACAMERA_ISP1_SIZE )

static acamera_firmware_t g_firmware;

int32_t acamera_set_api_context( uint32_t ctx_num )
{
    int32_t result = 0;
    if ( ctx_num < g_firmware.context_number ) {
        g_firmware.api_context = ctx_num;
        LOG( LOG_INFO, "new api context: %u.", (unsigned int)g_firmware.api_context );
        result = 0;
    } else {
        result = -1;
    }
    return result;
}

uint32_t acamera_get_api_context( void )
{
    uint32_t result = g_firmware.api_context;
    return result;
}

int32_t acamera_get_context_number( void )
{
    int32_t result = g_firmware.context_number;
    return result;
}

void *acamera_get_api_ctx_ptr( void )
{
    return &( g_firmware.fw_ctx[acamera_get_api_context()] );
}

void *acamera_get_ctx_ptr( uint32_t ctx_id )
{
    if ( ctx_id >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_CRIT, "Error: Invalid ctx_id: %d", ctx_id );
        return NULL;
    }

    return &( g_firmware.fw_ctx[ctx_id] );
}

void acamera_notify_evt_data_avail( void )
{
    system_semaphore_raise( g_firmware.sem_evt_avail );
}

static int32_t validate_settings( acamera_settings *settings, uint32_t ctx_num )
{

    int32_t result = 0;
    int32_t idx = 0;
    if ( settings == NULL )
        return -1;
    for ( idx = 0; idx < ctx_num; idx++ ) {
        acamera_settings *ctx_set = &settings[idx];
        if ( ctx_set->sensor_init == NULL ||
             ctx_set->sensor_deinit == NULL ||
             ctx_set->get_calibrations == NULL ) {
            result = -1;
            LOG( LOG_CRIT, "One of the mandatory input parameters in the init settings is null for the context %d", idx );
        }
    }

#if !USER_MODULE && ISP_HAS_DS1 && defined( ISP_HAS_DMA_WRITER_FSM )

#if ISP_HW_IS_MALI_C32_C52
    if ( acamera_isp_isp_global_parameter_status_ds1_pipe_read( 0 ) ) //present on 0
#else
    if ( acamera_isp_isp_global_parameter_status_ds1_pipe_read( 0 ) == 0 ) //present on 1
#endif
    {
        result = -1;
        LOG( LOG_CRIT, "DS Frames are expected while DS block is not present in hardware for the context %d", idx );
    }
#endif

#if !ISP_HW_IS_MALI_C32_C52
    if ( acamera_isp_isp_global_parameter_status_pong_config_fitted_read( 0 ) == 0 && cdma_mode != CDMA_MODE_RTRACK ) {
        LOG( LOG_ERR, "cdma_mode is HWDMA/MCPY, but HW has no pong mem. Switching to RTRACK mode." );
        cdma_mode = CDMA_MODE_RTRACK;
    }

#endif // !USER_MODULE && ISP_HAS_DS1 && defined( ISP_HAS_DMA_WRITER_FSM )
    return result;
}

static int32_t dma_channel_addresses_setup( void *isp_chan, void *metering_chan, void *sw_context_map, uint32_t idx, uint32_t hw_isp_addr )
{
    int32_t result = 0;
    if ( cdma_mode == CDMA_MODE_RTRACK ) { // ping-only
        //PING ISP
        {
            dma_addr_pair_t isp_dma_addr_pair[1] = {
                {hw_isp_addr + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR, ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR + ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_device_setup( isp_chan, ISP_CONFIG_PING, isp_dma_addr_pair, 1, idx ) ) {
                LOG( LOG_CRIT, "ISP device channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            fwmem_addr_pair_t fwmem_add_pair[1] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR ), ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR + ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_fwmem_setup( isp_chan, ISP_CONFIG_PING, fwmem_add_pair, 1, idx ) ) {
                LOG( LOG_CRIT, "ISP memory channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PINGISP 1:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size );
        }
        //PING METERING
        {
            dma_addr_pair_t isp_dma_addr_pair[1] = {
                {hw_isp_addr + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR, ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE + ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_device_setup( metering_chan, ISP_CONFIG_PING, isp_dma_addr_pair, 1, idx ) ) {
                LOG( LOG_CRIT, "Metering device channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }

            fwmem_addr_pair_t fwmem_add_pair[1] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR ), ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE + ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_fwmem_setup( metering_chan, ISP_CONFIG_PING, fwmem_add_pair, 1, idx ) ) {
                LOG( LOG_CRIT, "Metering memory channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PINGMET 1:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size );
        }
    } else {
        //PING ISP
        {
            dma_addr_pair_t isp_dma_addr_pair[2] = {
                {hw_isp_addr + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR, ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR},
                {hw_isp_addr + ACAMERA_ISP1_BASE_ADDR, ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_device_setup( isp_chan, ISP_CONFIG_PING, isp_dma_addr_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "ISP device channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            fwmem_addr_pair_t fwmem_add_pair[2] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR ), ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR},
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_ISP1_BASE_ADDR ), ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_fwmem_setup( isp_chan, ISP_CONFIG_PING, fwmem_add_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "ISP memory channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PINGISP\n1:%08x(%u) <-> %p(%u)\n2:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size, isp_dma_addr_pair[1].address, isp_dma_addr_pair[1].size, fwmem_add_pair[1].address, fwmem_add_pair[1].size );
        }
        //PONG ISP
        {
            dma_addr_pair_t isp_dma_addr_pair[2] = {
                {hw_isp_addr + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR + ISP_CONFIG_PING_SIZE, ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR},
                {hw_isp_addr + ACAMERA_ISP1_BASE_ADDR + ISP_CONFIG_PING_SIZE, ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_device_setup( isp_chan, ISP_CONFIG_PONG, isp_dma_addr_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "ISP device channel address setup for PONG ctx:%d failed", idx );
                result = -1;
            }

            fwmem_addr_pair_t fwmem_add_pair[2] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_DECOMPANDER0_MEM_BASE_ADDR ), ACAMERA_ISP1_BASE_ADDR - ACAMERA_DECOMPANDER0_MEM_BASE_ADDR},
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_ISP1_BASE_ADDR ), ACAMERA_ISP1_SIZE}};
            if ( system_cdma_sg_fwmem_setup( isp_chan, ISP_CONFIG_PONG, fwmem_add_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "ISP memory channel address setup for PONG ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PoNGISP\n1:%08x(%u) <-> %p(%u)\n2:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size, isp_dma_addr_pair[1].address, isp_dma_addr_pair[1].size, fwmem_add_pair[1].address, fwmem_add_pair[1].size );
        }
        //PING METERING
        {
            dma_addr_pair_t isp_dma_addr_pair[2] = {
                {hw_isp_addr + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR, ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE},
                {hw_isp_addr + ACAMERA_METERING_STATS_MEM_BASE_ADDR, ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_device_setup( metering_chan, ISP_CONFIG_PING, isp_dma_addr_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "Metering device channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }

            fwmem_addr_pair_t fwmem_add_pair[2] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR ), ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE},
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_METERING_STATS_MEM_BASE_ADDR ), ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_fwmem_setup( metering_chan, ISP_CONFIG_PING, fwmem_add_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "Metering memory channel address setup for PING ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PINGMET\n1:%08x(%u) <-> %p(%u)\n2:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size, isp_dma_addr_pair[1].address, isp_dma_addr_pair[1].size, fwmem_add_pair[1].address, fwmem_add_pair[1].size );
        }
        //PONG METERING
        {
            dma_addr_pair_t isp_dma_addr_pair[2] = {
                {hw_isp_addr + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR, ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE},
                {hw_isp_addr + ACAMERA_METERING_STATS_MEM_BASE_ADDR + ISP_CONFIG_PING_SIZE, ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_device_setup( metering_chan, ISP_CONFIG_PONG, isp_dma_addr_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "Metering device channel address setup for PONG ctx:%d failed", idx );
                result = -1;
            }

            fwmem_addr_pair_t fwmem_add_pair[2] = {
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_AEXP_HIST_STATS_MEM_BASE_ADDR ), ACAMERA_AEXP_HIST_STATS_MEM_SIZE + ACAMERA_IHIST_STATS_MEM_SIZE},
                {(void *)( (uintptr_t)sw_context_map + ACAMERA_METERING_STATS_MEM_BASE_ADDR ), ACAMERA_METERING_STATS_MEM_SIZE}};
            if ( system_cdma_sg_fwmem_setup( metering_chan, ISP_CONFIG_PONG, fwmem_add_pair, 2, idx ) ) {
                LOG( LOG_CRIT, "Metering memory channel address setup for PONG  ctx:%d failed", idx );
                result = -1;
            }
            LOG( LOG_ERR, "PoNGMET\n1:%08x(%u) <-> %p(%u)\n2:%08x(%u) <-> %p(%u)", isp_dma_addr_pair[0].address, isp_dma_addr_pair[0].size, fwmem_add_pair[0].address, fwmem_add_pair[0].size, isp_dma_addr_pair[1].address, isp_dma_addr_pair[1].size, fwmem_add_pair[1].address, fwmem_add_pair[1].size );
        }
    }
    return result;
}

#if USER_MODULE

int32_t acamera_init( acamera_settings *settings, uint32_t ctx_num )
{
    int32_t result = 0;
    uint32_t idx = 0;

    result = validate_settings( settings, ctx_num );

    if ( result == 0 ) {

#if FW_HAS_CONTROL_CHANNEL
        ctrl_channel_init();
#endif

        g_firmware.api_context = 0;

        system_semaphore_init( &g_firmware.sem_evt_avail );

        if ( ctx_num <= FIRMWARE_CONTEXT_NUMBER ) {

            g_firmware.context_number = ctx_num;

            for ( idx = 0; idx < ctx_num; idx++ ) {
                acamera_context_t *p_ctx = (acamera_context_ptr_t)&g_firmware.fw_ctx[idx];
                LOG( LOG_INFO, "Initialize context %d, context size is %zu bytes.", idx, sizeof( struct _acamera_context_t ) );
                system_memset( (void *)p_ctx, 0x0, sizeof( struct _acamera_context_t ) );
                // each context has unique id
                p_ctx->context_id = idx;

                // init context
                result = acamera_init_context( p_ctx, &settings[idx], &g_firmware );
                if ( result != 0 ) {
                    LOG( LOG_CRIT, "Failed to initialized the context %d", (int)idx );
                    break;
                }
            }

            if ( result == 0 ) {
                g_firmware.initialized = 1;
            } else {
                g_firmware.initialized = 0;
            }

        } else {
            result = -1;
            LOG( LOG_CRIT, "Failed to initialized the firmware context. Not enough memory. " );
        }

    } else {
        LOG( LOG_CRIT, "Input initializations settings are not correct" );
        result = -1;
    }

    return result;
}

void acamera_update_cur_settings_to_isp( uint32_t fw_ctx_id )
{
}

#else /* #if USER_MODULE */
void acamera_update_cur_settings_to_isp( uint32_t fw_ctx_id )
{
    system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PING, SYS_DMA_TO_DEVICE, NULL, fw_ctx_id );
    if ( cdma_mode != CDMA_MODE_RTRACK ) {
        system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PONG, SYS_DMA_TO_DEVICE, NULL, fw_ctx_id );
    }
}

int32_t acamera_init( acamera_settings *settings, uint32_t ctx_num )
{
    int32_t result = 0;
    uint32_t idx;

    result = validate_settings( settings, ctx_num );

    if ( result == 0 ) {

        // disable irq and clear interrupts
        acamera_isp_isp_global_interrupt_mask_vector_write( 0, ISP_IRQ_DISABLE_ALL_IRQ );

#if ACAMERA_ISP_PROFILING && ACAMERA_ISP_PROFILING_INIT
        acamera_profiler_init();
        acamera_profiler_start( 0 );
#endif

#if FW_HAS_CONTROL_CHANNEL
        ctrl_channel_init();
#endif

        if ( result == 0 ) {

            g_firmware.api_context = 0;

            system_semaphore_init( &g_firmware.sem_evt_avail );

            if ( ctx_num <= FIRMWARE_CONTEXT_NUMBER ) {

                g_firmware.context_number = ctx_num;

#if defined( SENSOR_ISP_SEQUENCE_DEFAULT_SETTINGS_FPGA ) && ISP_HAS_FPGA_WRAPPER
                // these settings are loaded only for ARM FPGA demo platform and must be ignored on other systems
                const acam_reg_t **p_sequence = SENSOR_ISP_SEQUENCE_DEFAULT;
                acamera_load_isp_sequence( 0, p_sequence, SENSOR_ISP_SEQUENCE_DEFAULT_SETTINGS_FPGA );
#endif

                void *ping_only_reg_track_mem; // for ping only
                if ( cdma_mode != CDMA_MODE_RTRACK ) {
                    result = system_cdma_init( &g_firmware.dma_chan_isp_config, cdma_mode, NULL );
                    result |= system_cdma_init( &g_firmware.dma_chan_isp_metering, cdma_mode, NULL ); //always hwdma
                } else {
                    if ( ctx_num > 1 ) {
                        LOG( LOG_CRIT, "ERR: register tracking(ping-only) is not possible on multiple contexts." );
                        result = -1;
                    } else {
                        result = system_cdma_init( &g_firmware.dma_chan_isp_config, cdma_mode, &ping_only_reg_track_mem );
#if FW_USE_SYSTEM_DMA
                        result |= system_cdma_init( &g_firmware.dma_chan_isp_metering, CDMA_MODE_HWDMA, NULL ); //always hwdma
#else
                        result |= system_cdma_init( &g_firmware.dma_chan_isp_metering, CDMA_MODE_MEMCPY, NULL ); //always hwdma
#endif
                    }
                }
                if ( result == 0 ) {
                    LOG( LOG_INFO, "DMA Channels allocated %p and %p", g_firmware.dma_chan_isp_config, g_firmware.dma_chan_isp_metering );
                    // allocate memory for dma transfers
                    for ( idx = 0; idx < ctx_num; idx++ ) {
                        acamera_context_t *p_ctx = (acamera_context_ptr_t)&g_firmware.fw_ctx[idx];
                        LOG( LOG_INFO, "Initialize context %d, context size is %zu bytes", idx, sizeof( struct _acamera_context_t ) );
                        system_memset( (void *)p_ctx, 0x0, sizeof( struct _acamera_context_t ) );
                        // each context has unique id
                        p_ctx->context_id = idx;

                        // dump hw default configuration to the current context

                        p_ctx->sw_reg_map.isp_sw_config_map = system_sw_alloc( ACAMERA_CONTEXT_SIZE, cdma_mode == CDMA_MODE_RTRACK ? ping_only_reg_track_mem : NULL );

                        if ( p_ctx->sw_reg_map.isp_sw_config_map ) {
                            result = dma_channel_addresses_setup( g_firmware.dma_chan_isp_config, g_firmware.dma_chan_isp_metering, (void *)p_ctx->sw_reg_map.isp_sw_config_map, idx, settings->hw_isp_addr );
                        } else {
                            LOG( LOG_CRIT, "Software Context %d failed to allocate", idx );
                            result = -1;
                        }

                        if ( result )
                            break;

                        system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PING, SYS_DMA_FROM_DEVICE, 0, idx );
                        // init context
                        result = acamera_init_context( p_ctx, &settings[idx], &g_firmware );
                        if ( result == 0 ) {
                            // initialize ping
                            LOG( LOG_INFO, "DMA config from DDR to ping and pong of size %d", ACAMERA_ISP1_SIZE );
                            // system_cdma_copy current software context to the ping and pong
                            acamera_update_cur_settings_to_isp( idx );
                            if ( result == 0 ) {
#if ISP_SENSOR_DRIVER_MODEL != 1
                                // avoid interrupt status check against the model
                                while ( acamera_isp_isp_global_interrupt_status_vector_read( 0 ) != 0 ) {
                                    // driver is initialized. we can start processing interrupts
                                    // wait until irq mask is cleared and start processing
                                    acamera_isp_isp_global_interrupt_clear_write( 0, 0 );
                                    acamera_isp_isp_global_interrupt_clear_write( 0, 1 );
                                }
#endif // #if ISP_SENSOR_DRIVER_MODEL != 1
                                acamera_isp_isp_global_interrupt_mask_vector_write( 0, ISP_IRQ_MASK_VECTOR );
                                g_firmware.initialized = 1;
                            } else {
                                LOG( LOG_CRIT, "One or more contexts were not initialized properly. " );
                                g_firmware.initialized = 0;
                                break;
                            }
                        } else {
                            LOG( LOG_CRIT, "Failed to initialized the context %d", (int)idx );
                            break;
                        }
                    }
                } else {
                    result = -1;
                    LOG( LOG_CRIT, "Failed to initialize the system DMA engines" );
                }
            } else {
                result = -1;
                LOG( LOG_CRIT, "Failed to initialized the firmware context. Not enough memory. " );
            }
        } else {
            LOG( LOG_CRIT, "Failed to initialized the BSP. Please implement the BSP layer and recompile the firmware" );
            result = -1;
        }

#if ACAMERA_ISP_PROFILING && ACAMERA_ISP_PROFILING_INIT
        acamera_profiler_stop( 0, 1 );
        acamera_profiler_report();
#endif

#if FW_HAS_SW_MCFE
        sw_mcfe_init( &g_firmware );
#endif

    } else {
        LOG( LOG_CRIT, "Input initializations settings are not correct" );
        result = -1;
    }
    acamera_isp_isp_global_mcu_override_config_select_write( 0, 1 ); //put ping pong in slave mode
    if ( ctx_num > 1 ) {
        acamera_isp_isp_global_multi_context_mode_write( 0, 1 );
    }

    g_firmware.dma_flag_isp_config_completed = 1;
    g_firmware.dma_flag_isp_metering_completed = 1;
    return result;
}

#endif /* #if USER_MODULE */

static void acamera_deinit( void )
{
    int idx;
    acamera_context_t *p_ctx;

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_deinit();
#endif

    for ( idx = 0; idx < g_firmware.context_number; idx++ ) {

        p_ctx = (acamera_context_ptr_t)&g_firmware.fw_ctx[idx];

        acamera_deinit_context( p_ctx );

        if ( p_ctx->sw_reg_map.isp_sw_config_map != NULL ) {
            system_sw_free( (void *)p_ctx->sw_reg_map.isp_sw_config_map );
            p_ctx->sw_reg_map.isp_sw_config_map = NULL;
        }
    }

#if FW_HAS_SW_MCFE
    sw_mcfe_deinit();
#endif

    system_cdma_destroy( g_firmware.dma_chan_isp_config );
    system_cdma_destroy( g_firmware.dma_chan_isp_metering );
}

int32_t acamera_terminate()
{
    acamera_logger_empty(); //empty the logger buffer and print remaining logs
    acamera_deinit();
    system_semaphore_destroy( g_firmware.sem_evt_avail );

    return 0;
}


#if USER_MODULE
// single context handler
int32_t acamera_interrupt_handler()
{
    return 0;
}
#else

#if FW_HAS_SW_MCFE

// multiple contexts handler using SW MCFE
int32_t acamera_interrupt_handler()
{
    int32_t result = 0;

    // Call SW MCFE handler for ISP interrupts
    uint32_t irq_mask = acamera_isp_isp_global_interrupt_status_vector_read( 0 );

    //LOG( LOG_ERR, "ISP status IRQ MASK is 0x%x", irq_mask);

    if ( irq_mask > 0 ) {

        // clear irq vector
        acamera_isp_isp_global_interrupt_clear_vector_write( 0, irq_mask );
        acamera_isp_isp_global_interrupt_clear_write( 0, 0 );
        acamera_isp_isp_global_interrupt_clear_write( 0, 1 );

        // We are interested only in FS and FE interrupts
        // FS interrupt
        int32_t irq_bit = ISP_INTERRUPT_EVENT_ISP_START_FRAME_START;
        int32_t irq_is_1 = ( irq_mask & ( 1 << irq_bit ) );

        if ( irq_is_1 ) {
            sw_mcfe_handle_interrupt( irq_bit );
        }

        // FE interrupt
        irq_bit = ISP_INTERRUPT_EVENT_ISP_END_FRAME_END;
        irq_is_1 = ( irq_mask & ( 1 << irq_bit ) );

        if ( irq_is_1 ) {
            sw_mcfe_handle_interrupt( irq_bit );
        }
    }

    return result;
}

#else // FW_HAS_SW_MCFE

static void start_3a_processing_frame( void )
{
    acamera_context_ptr_t p_ctx = (acamera_context_ptr_t)&g_firmware.fw_ctx[0];

    // new_frame event to start reading metering memory and run 3A
    acamera_fw_raise_event( p_ctx, event_id_new_frame );
    acamera_fw_raise_event( p_ctx, event_id_new_stats );
    acamera_fw_raise_event( p_ctx, event_id_end_frame );
}

static void dma_complete_context_func( void *arg, uint32_t ctx_id )
{
    LOG( LOG_INFO, "DMA COMPLETION FOR CONTEXT" );

    g_firmware.dma_flag_isp_config_completed = 1;

    if ( g_firmware.dma_flag_isp_config_completed && g_firmware.dma_flag_isp_metering_completed ) {
        LOG( LOG_INFO, "START PROCESSING FROM CONTEXT CALLBACK" );
        if ( cdma_mode != CDMA_MODE_RTRACK ) {
            start_3a_processing_frame();
        }
    }

    if ( arg ) {
        system_cdma_unmap_sg( arg );
    }
}

static void dma_complete_metering_func( void *arg, uint32_t ctx_id )
{
    LOG( LOG_INFO, "DMA COMPLETION FOR METERING" );

    g_firmware.dma_flag_isp_metering_completed = 1;

    if ( g_firmware.dma_flag_isp_config_completed && g_firmware.dma_flag_isp_metering_completed ) {
        LOG( LOG_INFO, "START PROCESSING FROM METERING CALLBACK" );
        if ( cdma_mode != CDMA_MODE_RTRACK ) {
            start_3a_processing_frame();
        }
    }

    system_cdma_unmap_sg( arg );
    // after we finish transfer context and metering we can start processing the current data
}

// single context handler
int32_t acamera_interrupt_handler()
{
    int32_t result = 0;
    int32_t irq_bit = ISP_INTERRUPT_EVENT_NONES_COUNT - 1;
    LOG( LOG_INFO, "Interrupt handler called" );

    acamera_context_ptr_t p_ctx = (acamera_context_ptr_t)&g_firmware.fw_ctx[0];

    // read the irq vector from isp
    uint32_t irq_mask = acamera_isp_isp_global_interrupt_status_vector_read( 0 );

    LOG( LOG_INFO, "IRQ MASK is %d", irq_mask );

    // clear irq vector
    acamera_isp_isp_global_interrupt_clear_write( 0, 0 );
    acamera_isp_isp_global_interrupt_clear_write( 0, 1 );

    if ( irq_mask > 0 ) {
        /*
#if defined( ISP_INTERRUPT_EVENT_BROKEN_FRAME ) && defined( ISP_INTERRUPT_EVENT_MULTICTX_ERROR ) && defined( ISP_INTERRUPT_EVENT_DMA_ERROR ) && defined( ISP_INTERRUPT_EVENT_WATCHDOG_EXP ) && defined( ISP_INTERRUPT_EVENT_FRAME_COLLISION )
        //check for errors in the interrupt
        if ( ( irq_mask & 1 << ISP_INTERRUPT_EVENT_BROKEN_FRAME ) ||
             ( irq_mask & 1 << ISP_INTERRUPT_EVENT_MULTICTX_ERROR ) ||
             ( irq_mask & 1 << ISP_INTERRUPT_EVENT_DMA_ERROR ) ||
             ( irq_mask & 1 << ISP_INTERRUPT_EVENT_WATCHDOG_EXP ) ||
             ( irq_mask & 1 << ISP_INTERRUPT_EVENT_FRAME_COLLISION ) ) {

            LOG( LOG_ERR, "Found error resetting ISP. MASK is 0x%x", irq_mask );

            acamera_fw_error_routine( p_ctx, irq_mask );
            return -1; //skip other interrupts in case of error
        }
#endif*/

        while ( irq_mask > 0 && irq_bit >= 0 ) {
            int32_t irq_is_1 = ( irq_mask & ( 1 << irq_bit ) );
            irq_mask &= ~( 1 << irq_bit );
            if ( irq_is_1 ) {
                // process interrupts
                if ( irq_bit == ISP_INTERRUPT_EVENT_ISP_START_FRAME_START ) {
                    static uint32_t fs_cnt = 0;
                    if ( fs_cnt < 10 ) {
                        LOG( LOG_CRIT, "[KeyMsg]: FS interrupt: %d", fs_cnt++ );
                    }

#if ISP_DMA_RAW_CAPTURE
                    dma_raw_capture_interrupt( &g_firmware, ACAMERA_IRQ_FRAME_END );
#endif

                    if ( g_firmware.dma_flag_isp_metering_completed == 0 || g_firmware.dma_flag_isp_config_completed == 0 ) {
                        LOG( LOG_ERR, "%s cfg space copy not finished during VBlanking, cfg: %d, meter: %d, skip this frame.", cdma_mode == CDMA_MODE_RTRACK ? "rtrack-pOnly" : "pPong", g_firmware.dma_flag_isp_config_completed, g_firmware.dma_flag_isp_metering_completed );
                        return -2;
                    }

                    // we must finish all previous processing before scheduling new dma
                    if ( acamera_event_queue_empty( &p_ctx->fsm_mgr.event_queue ) ) {
                        // switch to ping/pong contexts for the next frame

                        //if (!acamera_isp_isp_global_mcu_ping_pong_config_select_read(0)) { // cmodel compatibility
                        if ( cdma_mode == CDMA_MODE_RTRACK ) { //Ping only cfg-space copy should be done on frame end(VBlanking)
                            start_3a_processing_frame();
                        } else if ( acamera_isp_isp_global_ping_pong_config_select_read( 0 ) == ISP_CONFIG_PONG ) {
                            g_firmware.dma_flag_isp_config_completed = 0; // used for sync of callbacks
                            g_firmware.dma_flag_isp_metering_completed = 0;
                            LOG( LOG_INFO, "Current config is pong" );
                            //            |^^^^^^^^^|
                            // next --->  |  PING   |
                            //            |_________|

                            // use ping for the next frame
                            acamera_isp_isp_global_mcu_ping_pong_config_select_write( 0, ISP_CONFIG_PING );
                            //
                            //            |^^^^^^^^^|
                            // conf --->  |  PONG   |
                            //            |_________|
                            LOG( LOG_INFO, "DMA metering from pong to DDR of size %d", ACAMERA_METERING_STATS_MEM_SIZE );
                            // dma all stat memory only to the software context
                            system_cdma_copy_sg( g_firmware.dma_chan_isp_metering, ISP_CONFIG_PING, SYS_DMA_FROM_DEVICE, dma_complete_metering_func, 0 );
                            LOG( LOG_INFO, "DMA config from pong to DDR of size %d", ACAMERA_ISP1_SIZE );

                            system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PING, SYS_DMA_TO_DEVICE, dma_complete_context_func, 0 );
                        } else {
                            g_firmware.dma_flag_isp_config_completed = 0; // used for sync of callbacks
                            g_firmware.dma_flag_isp_metering_completed = 0;
                            LOG( LOG_INFO, "Current config is ping" );
                            //            |^^^^^^^^^|
                            // next --->  |  PONG   |
                            //            |_________|

                            // use pong for the next frame
                            acamera_isp_isp_global_mcu_ping_pong_config_select_write( 0, ISP_CONFIG_PONG );

                            //            |^^^^^^^^^|
                            // conf --->  |  PING   |
                            //            |_________|

                            LOG( LOG_INFO, "DMA metering from ping to DDR of size %d", ACAMERA_METERING_STATS_MEM_SIZE );
                            // dma all stat memory only to the software context

                            system_cdma_copy_sg( g_firmware.dma_chan_isp_metering, ISP_CONFIG_PONG, SYS_DMA_FROM_DEVICE, dma_complete_metering_func, 0 );
                            LOG( LOG_INFO, "DMA config from DDR to ping of size %d", ACAMERA_ISP1_SIZE );

                            system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PONG, SYS_DMA_TO_DEVICE, dma_complete_context_func, 0 );
                        }
                    } else {
                        LOG( LOG_ERR, "Attempt to start a new frame before processing is done for the previous one. Skip this frame." );
                    }
                } else if ( irq_bit == ISP_INTERRUPT_EVENT_ISP_END_FRAME_END ) {
                    static uint32_t fe_cnt = 0;
                    if ( fe_cnt < 10 ) {
                        LOG( LOG_ERR, "[KeyMsg]: FE interrupt: %d", fe_cnt++ );
                    }
                    if ( cdma_mode != CDMA_MODE_RTRACK ) {
                        LOG( LOG_DEBUG, "FE ignored, Ppong cfg-space copy inplemented on Frame start" );
                        return 0;
                    }
#if ISP_DMA_RAW_CAPTURE
                    dma_raw_capture_interrupt( &g_firmware, ACAMERA_IRQ_FRAME_END );
#endif

                    if ( g_firmware.dma_flag_isp_metering_completed == 0 || g_firmware.dma_flag_isp_config_completed == 0 ) {
                        LOG( LOG_ERR, "FE: CFG space copy is not finished, cfg: %d, meter: %d, skip this frame.", g_firmware.dma_flag_isp_config_completed, g_firmware.dma_flag_isp_metering_completed );
                        return -2;
                    }

                    // we must finish all previous processing before scheduling new dma
                    if ( acamera_event_queue_empty( &p_ctx->fsm_mgr.event_queue ) ) {
                        // switch to ping/pong contexts for the next frame

                        // these flags are used for sync of callbacks
                        g_firmware.dma_flag_isp_config_completed = 0;
                        g_firmware.dma_flag_isp_metering_completed = 0;
                        LOG( LOG_INFO, "Current config is pong" );
                        //            |^^^^^^^^^|
                        // next --->  |  PING   |
                        //            |_________|

                        // use ping for the next frame
                        acamera_isp_isp_global_mcu_ping_pong_config_select_write( 0, ISP_CONFIG_PING );
                        //
                        //            |^^^^^^^^^|
                        // conf --->  |  PONG   |
                        //            |_________|
                        LOG( LOG_INFO, "DMA metering from ping to DDR of size %d", ACAMERA_METERING_STATS_MEM_SIZE );
                        // dma all stat memory only to the software context
                        system_cdma_copy_sg( g_firmware.dma_chan_isp_metering, ISP_CONFIG_PING, SYS_DMA_FROM_DEVICE, dma_complete_metering_func, 0 );
                        LOG( LOG_INFO, "DMA config from DDR to ping of size %d", ACAMERA_ISP1_SIZE );

                        system_cdma_copy_sg( g_firmware.dma_chan_isp_config, ISP_CONFIG_PING, SYS_DMA_TO_DEVICE, dma_complete_context_func, 0 );
                    } else {
                        LOG( LOG_ERR, "Attempt to start a new frame before processing is done for the previous one. Skip this frame." );
                    }
                } else {
                    // unhandled irq
                    LOG( LOG_INFO, "Unhandled interrupt bit %d", irq_bit );
                }
            }
            irq_bit--;
        }
    }

    return result;
}

#endif // FW_HAS_SW_MCFE

#endif // USER_MODULE


int32_t acamera_process( void )
{
    int32_t result = 0;
    int32_t idx = 0;

    if ( g_firmware.initialized == 1 ) {
        for ( idx = 0; idx < g_firmware.context_number; idx++ ) {
            acamera_context_ptr_t p_ctx = ( acamera_context_ptr_t ) & ( g_firmware.fw_ctx[idx] );
            acamera_fw_process( p_ctx );
        }
    } else {
        result = -1;
        LOG( LOG_CRIT, "Firmware was not initialized properly. Please initialize the firmware before call acamera_process" );
    }

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_process();
#endif

    system_semaphore_wait( g_firmware.sem_evt_avail, FW_EVT_QUEUE_TIMEOUT_MS );

    return result;
}

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
#include "acamera_logger.h"
#include "system_control.h"
#include "system_interrupts.h"
#include "acamera_firmware_config.h"
#include "acamera_firmware_api.h"

#include "acamera_control_config.h"
#include "acamera_command_api.h"
#include "application_command_api.h"

#if ISP_HAS_STREAM_CONNECTION
#include "acamera_connection.h"
#endif

// the settings for each firmware context were pre-generated and
// saved in the header file. They are given as a reference and should be changed
// according to the customer needs.
#include "runtime_initialization_settings.h"

// This example will run the infinite loop to process the firmware events.
// This variable also can be changed outside to stop the processing.
volatile int32_t acamera_main_loop_active = 1;


// The ISP pipeline can have several outputs such as Full Resolution, DownScaler1, DownScaler2 etc
// It is possible to set up the firmware to return the metadata for each output frame from
// the specific channel. This callbacks must be set in acamera_settings structure and passed to the firmware in
// acamera_init api function
// The context id can be used to differentiate contexts

static uint64_t dummy_base = ISP_MBLAZE_DMA_COHERENT_DUMMY_ALLOC_BASE;
static uint64_t dummy_size = 0;
static uint64_t dummy_total = ISP_MBLAZE_DMA_COHERENT_DUMMY_ALLOC_SIZE;
void *callback_dma_alloc_coherent( uint32_t ctx_id, uint64_t size, uint64_t *dma_addr )
{
    void *virt_addr;
    uintptr_t addr;

    if ( dummy_size + size > dummy_total ) {
        LOG( LOG_ERR, "Not enough memory" );
        return NULL;
    }

    addr = dummy_base + dummy_size;
    dummy_size += size;

    *dma_addr = addr;

    /* compute bus address */
    *dma_addr -= ISP_SOC_DMA_BUS_OFFSET;

    /* compute virt address */
    virt_addr = (void *)addr;

    return virt_addr;
}

void callback_dma_free_coherent( uint32_t ctx_id, uint64_t size, void *virt_addr, uint64_t dma_addr )
{
}

int callback_stream_get_frame( uint32_t ctx_id, acamera_stream_type_t type, aframe_t *aframes, uint64_t num_planes )
{
    return -1;
}

int callback_stream_put_frame( uint32_t ctx_id, acamera_stream_type_t type, aframe_t *aframes, uint64_t num_planes )
{
    return -1;
}

// On systems which support pthreads it is more efficient to run
// control channel in a separate thread to let the firmware to communicate
// with ACamera Control Tool (ACT)
// ACT allows to change the firmware behaviour by calling API functions, change ISP registers and
// update calibration LUTs.
// Please read the ACamera Control Tool User Guide for details
#if ISP_HAS_STREAM_CONNECTION && CONNECTION_IN_THREAD
#include <pthread.h>
static void *connection_thread( void *foo )
{
    // acamera_connection_init is used to initialize the
    // communication channel between the firmware application
    // and the firmware. It is used only together with ACT tool
    // and may be omitted on the customer discretion
    // if ACT is not required
    acamera_connection_init();
    for ( ;; ) {
        // the function checks the incoming requests from
        // ACT tool and call the corresponding API command.
        // Please note that acamera_connection_process may be ommitted
        // if ACT tool is not used for the firmware API.
        acamera_connection_process();
    }
}
#endif


// this is a main application IRQ handler to drive the firmware
// The main purpose is to redirect ISP irq event to the firmware core
// Please see the ACamera Porting Guide for details.
static void interrupt_handler( void *ptr, uint32_t mask )
{
    // the lower bits are for ISP interrupts on ACamera FPGA reference platform
    uint32_t isp_mask = mask & 0x0000FFFF;

    // tell the firmware that isp interrupts happened
    if ( isp_mask ) {
        // the first irq pins are connected to ISP
        acamera_interrupt_handler();
    }
}


// The basic usage example for
// ACamera firmware is given below.
int main( void )
{
    int32_t result = 0;
    uint32_t i;
    // The custom platform must be ready to run
    // any system routines from ./platform folder.
    // So bsp_init allows to initialise the system if necessary.
    // This function may be omitted if no initialisation is required
    bsp_init();

// ACamera provides a simple protocol to communicate with firmware
// outside application. Several channels are supported depend on the
// system requirements.
// To start using ACamera Control Tool the connection must be initialised
// before by calling acamera_connection_init
// The connection module parses input commands from ACT and call the required
// api command like acamera_command or acamera_calibrations.
// Please see acamera_command_api.h for details.
#if ISP_HAS_STREAM_CONNECTION
#if !CONNECTION_IN_THREAD
    acamera_connection_init();
#else
    pthread_t control_thread_ptr = 0;
    int res = pthread_create( &control_thread_ptr, NULL, connection_thread, NULL );
#endif
#endif

    for ( i = 0; i < FIRMWARE_CONTEXT_NUMBER; i++ ) {
        settings[i].hw_isp_addr = ISP_SOC_START_ADDR;
    }

    // The firmware supports multicontext.
    // It means that the customer can use the same firmware for controlling
    // several instances of different sensors/isp. To initialise a context
    // the structure acamera_settings must be filled properly.
    // the total number of initialized context must not exceed FIRMWARE_CONTEXT_NUMBER
    // all contexts are numerated from 0 till ctx_number - 1
    result = acamera_init( settings, FIRMWARE_CONTEXT_NUMBER );

    if ( result == 0 ) {
        uint32_t rc = 0;
        uint32_t ctx_num;
        uint32_t prev_ctx_num = 0;

        application_command( TGENERAL, ACTIVE_CONTEXT, 0, COMMAND_GET, &prev_ctx_num );

        // set the interrupt handler. The system must call this interrupt_handler
        // function whenever the ISP interrupt happens.
        // This interrupt handling procedure is only advisable and is used in ACamera demo application.
        // It can be changed by a customer discretion.
        system_interrupt_set_handler( interrupt_handler, NULL );

        // start streaming for sensors
        for ( ctx_num = 0; ctx_num < FIRMWARE_CONTEXT_NUMBER; ctx_num++ ) {
            application_command( TGENERAL, ACTIVE_CONTEXT, ctx_num, COMMAND_SET, &rc );
            application_command( TSENSOR, SENSOR_STREAMING, ON, COMMAND_SET, &rc );
        }

        application_command( TGENERAL, ACTIVE_CONTEXT, prev_ctx_num, COMMAND_SET, &rc );

        // acamera_process function must be called on every incoming interrupt
        // to give the firmware the possibility to apply
        // all internal algorithms and change the ISP state.
        // The external application can be run in the same loop on bare metal systems.
        while ( acamera_main_loop_active ) {
            // acamera_process must be called for each initialised context
            acamera_process();
#if ISP_HAS_STREAM_CONNECTION && !CONNECTION_IN_THREAD
            // acamera_connection_process is used for communication between
            // firmware and ACT through different possible channels like
            // cmd_queue memory in ISP, socket, UART, chardev etc.
            // Different channels can be supported depending on the target
            // platform. The common case when cmd_queue buffer is used
            // ( see acamera_isp_config.h )
            // The channels supported by this routine can be used not only on
            // NIOS2 platform but on the customer system as well.
            acamera_connection_process();
#endif
        }
    } else {
        LOG( LOG_ERR, "Failed to start firmware processing thread. " );
    }

    // this api function will free
    // all resources allocated by the firmware
    acamera_terminate();


    // Additional work may be required after firmware finished
    // this function can be used to free memory regions or
    // for any other purposes.
    bsp_destroy();
    return 0;
}

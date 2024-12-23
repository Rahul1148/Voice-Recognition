#----------------------------------------------------------------------------------
# SPDX-License-Identifier: BSD-3-Clause
#
# Copyright (c) 2024, Arm Limited. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# - Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice, this
#    list of conditions and the following disclaimer in the documentation and/or
#    other materials provided with the distribution.
# - Neither the name of ARM nor the names of its contributors may be used to
#    endorse or promote products derived from this software without specific prior
#    written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#----------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15)

add_library(isp_driver)

target_include_directories(isp_driver
    PUBLIC
        inc/api
        inc/isp
        inc/sys
        src/fw
        src/fw_lib
)

target_sources(isp_driver
    PRIVATE
        src/fw_lib/acamera.c
        src/fw_lib/acamera_calibrations.c
        src/fw_lib/acamera_command_api.c
        src/fw_lib/acamera_command_api_impl.c
        src/fw_lib/acamera_event_queue.c
        src/fw_lib/acamera_fsm_mgr.c
        src/fw_lib/acamera_fw.c
        src/fw_lib/acamera_logger.c
        src/fw_lib/acamera_loop_buf.c
        src/fw_lib/acamera_math.c
        src/fw_lib/acamera_sbus.c
        src/fw_lib/acamera_sbus_i2c.c
        src/fw_lib/acamera_sbus_isp.c
        src/fw_lib/acamera_sbus_isp_sw.c
        src/fw_lib/acamera_sbus_spi.c
        src/fw_lib/ae_acamera_fsm.c
        src/fw_lib/ae_acamera_func.c
        src/fw_lib/ae_acamera_intf.c
        src/fw_lib/af_acamera_fsm.c
        src/fw_lib/af_acamera_func.c
        src/fw_lib/af_acamera_intf.c
        src/fw_lib/awb_acamera_fsm.c
        src/fw_lib/awb_acamera_func.c
        src/fw_lib/awb_acamera_intf.c
        src/fw_lib/cmos_fsm.c
        src/fw_lib/cmos_func.c
        src/fw_lib/cmos_intf.c
        src/fw_lib/color_matrix_fsm.c
        src/fw_lib/color_matrix_func.c
        src/fw_lib/color_matrix_intf.c
        src/fw_lib/crop_fsm.c
        src/fw_lib/crop_func.c
        src/fw_lib/crop_intf.c
        src/fw_lib/dma_writer.c
        src/fw_lib/dma_writer_fsm.c
        src/fw_lib/dma_writer_func.c
        src/fw_lib/dma_writer_intf.c
        src/fw_lib/fsm_param.c
        src/fw_lib/fsm_util.c
        src/fw_lib/gamma_acamera_fsm.c
        src/fw_lib/gamma_acamera_func.c
        src/fw_lib/gamma_acamera_intf.c
        src/fw_lib/general_fsm.c
        src/fw_lib/general_func.c
        src/fw_lib/general_intf.c
        src/fw_lib/iridix_acamera_fsm.c
        src/fw_lib/iridix_acamera_func.c
        src/fw_lib/iridix_acamera_intf.c
        src/fw_lib/matrix_yuv_fsm.c
        src/fw_lib/matrix_yuv_func.c
        src/fw_lib/matrix_yuv_intf.c
        src/fw_lib/monitor_fsm.c
        src/fw_lib/monitor_func.c
        src/fw_lib/monitor_intf.c
        src/fw_lib/noise_reduction_fsm.c
        src/fw_lib/noise_reduction_func.c
        src/fw_lib/noise_reduction_intf.c
        src/fw_lib/purple_fringe_fsm.c
        src/fw_lib/purple_fringe_func.c
        src/fw_lib/purple_fringe_intf.c
        src/fw_lib/sensor_fsm.c
        src/fw_lib/sensor_func.c
        src/fw_lib/sensor_init.c
        src/fw_lib/sensor_intf.c
        src/fw_lib/sharpening_fsm.c
        src/fw_lib/sharpening_func.c
        src/fw_lib/sharpening_intf.c
        src/fw_lib/sw_mcfe.c
        src/fw_lib/sw_mcfe_external_driver.c
        src/fw_lib/sw_mcfe_queue.c
)

add_library(isp_driver_alg_core STATIC IMPORTED)

target_include_directories(isp_driver_alg_core
    INTERFACE
        inc
        inc/api
        inc/isp
        inc/sys
        src/fw
        src/fw_lib
)

if (CMAKE_C_COMPILER_ID STREQUAL "ARMClang")
    set(ALG_CORE_COMPILER "armclang")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(ALG_CORE_COMPILER "gcc")
else ()
    message(FATAL_ERROR "Only ARMClang and GNU compilers are supported!")
endif()
if(ISP_MVE_FP)
    set(ALG_CORE_FLAGS "+mve.fp-float-abi-hard")
else()
    set(ALG_CORE_FLAGS "-float-abi-soft")
endif()
set(ALG_CORE_LIB "libacamera_alg_core-${ALG_CORE_COMPILER}-armv8.1-m.main${ALG_CORE_FLAGS}.a")

set_target_properties(isp_driver_alg_core PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/src/fw_lib/${ALG_CORE_LIB}
)

target_link_libraries(isp_driver
    PUBLIC
        isp_firmware_config
    PRIVATE
        isp_driver_alg_core
)

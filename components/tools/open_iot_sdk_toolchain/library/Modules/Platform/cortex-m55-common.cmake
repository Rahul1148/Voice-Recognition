# Copyright (c) 2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # `-mcpu=cortex-m55` is not supported correctly in GCC 10, see
    # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=97327.
    #
    # Until we bump the minimal required version to 11, use the explicit arch flag
    # (`-march=armv8.1-m.main+fp.dp+mve.fp`) instead.
    set(IOTSDK_TOOLCHAIN_CORTEX_M55_COMMON_FLAGS "-march=armv8.1-m.main+fp.dp+mve.fp -mfloat-abi=hard")
else()
    set(IOTSDK_TOOLCHAIN_CORTEX_M55_COMMON_FLAGS "-mcpu=cortex-m55 -mfloat-abi=hard")
endif()

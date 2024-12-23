# Copyright (c) 2020-2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(${CMAKE_CURRENT_LIST_DIR}/cortex-m55-common.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Generic-ARMClang-cortex-m-common.cmake)

set(CMAKE_CXX_FLAGS_INIT "${IOTSDK_TOOLCHAIN_CORTEX_M55_COMMON_FLAGS} ${CMAKE_CXX_FLAGS_INIT}")

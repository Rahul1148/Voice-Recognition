# Copyright (c) 2020-2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(${CMAKE_CURRENT_LIST_DIR}/cortex-m33-common.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Generic-GNU-cortex-m-common.cmake)

set(CMAKE_C_FLAGS_INIT "${IOTSDK_TOOLCHAIN_CORTEX_M33_COMMON_FLAGS} ${CMAKE_C_FLAGS_INIT}")
# Copyright (c) 2020-2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(${CMAKE_CURRENT_LIST_DIR}/Generic-cortex-m-common.cmake)

set(CMAKE_ASM_FLAGS_INIT "${CMAKE_ASM_FLAGS_INIT} -g3")
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -ffunction-sections -funsigned-char -fomit-frame-pointer -g3")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -ffunction-sections -funsigned-char -fomit-frame-pointer -g3")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -specs=nosys.specs")

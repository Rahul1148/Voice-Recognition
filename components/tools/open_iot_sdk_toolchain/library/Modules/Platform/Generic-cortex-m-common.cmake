# Copyright (c) 2020-2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set(CMAKE_ASM_FLAGS_INIT "-mthumb")
set(CMAKE_C_FLAGS_INIT "-mthumb -fdata-sections")
set(CMAKE_CXX_FLAGS_INIT "-mthumb -fdata-sections -fno-exceptions -fno-rtti")

# Clear toolchain options for all languages as IOTSDK uses different
# initialization options (such as for optimization and debug symbols)
set(CMAKE_ASM_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
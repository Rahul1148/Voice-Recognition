/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2024 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "fff.h"
#include "portmacro.h"

typedef int SemaphoreHandle_t;

DECLARE_FAKE_VALUE_FUNC( BaseType_t,
                         xSemaphoreTake,
                         SemaphoreHandle_t,
                         TickType_t );
DECLARE_FAKE_VALUE_FUNC( BaseType_t,
                         xSemaphoreGive,
                         SemaphoreHandle_t );
DECLARE_FAKE_VALUE_FUNC( SemaphoreHandle_t,
                         xSemaphoreCreateMutex );
DECLARE_FAKE_VOID_FUNC( vSemaphoreDelete,
                        SemaphoreHandle_t );

#endif /* SEMAPHORE_H */
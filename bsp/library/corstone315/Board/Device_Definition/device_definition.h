/*
 * Copyright (c) 2019-2024 Arm Limited. All rights reserved.
 *
 * Licensed under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * \file device_definition.h
 * \brief The structure definitions in this file are exported based on the
 * peripheral definitions from device_cfg.h.
 * This file is meant to be used as a helper for baremetal
 * applications and/or as an example of how to configure the generic
 * driver structures.
 */

#ifndef __DEVICE_DEFINITION_H__
#define __DEVICE_DEFINITION_H__

#include "device_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ======= Defines peripheral configuration structures ======= */
/* UART CMSDK driver structures */
#ifdef UART0_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART0_CMSDK_DEV_S;
#endif
#ifdef UART0_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART0_CMSDK_DEV_NS;
#endif

#ifdef UART1_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART1_CMSDK_DEV_S;
#endif
#ifdef UART1_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART1_CMSDK_DEV_NS;
#endif

#ifdef UART2_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART2_CMSDK_DEV_S;
#endif
#ifdef UART2_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART2_CMSDK_DEV_NS;
#endif

#ifdef UART3_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART3_CMSDK_DEV_S;
#endif
#ifdef UART3_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART3_CMSDK_DEV_NS;
#endif

#ifdef UART4_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART4_CMSDK_DEV_S;
#endif
#ifdef UART4_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART4_CMSDK_DEV_NS;
#endif

#ifdef UART5_CMSDK_S
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART5_CMSDK_DEV_S;
#endif
#ifdef UART5_CMSDK_NS
#include "uart_cmsdk_drv.h"
extern struct uart_cmsdk_dev_t UART5_CMSDK_DEV_NS;
#endif

/* ARM PPC driver structures */
#ifdef PPC_CORSTONE315_MAIN0_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_MAIN0_DEV_S;
#endif

#ifdef PPC_CORSTONE315_MAIN_EXP0_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_MAIN_EXP0_DEV_S;
#endif

#ifdef PPC_CORSTONE315_MAIN_EXP1_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_MAIN_EXP1_DEV_S;
#endif

#ifdef PPC_CORSTONE315_MAIN_EXP2_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_MAIN_EXP2_DEV_S;
#endif

#ifdef PPC_CORSTONE315_MAIN_EXP3_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_MAIN_EXP3_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH0_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH0_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH1_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH1_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH_EXP0_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH_EXP0_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH_EXP1_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH_EXP1_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH_EXP2_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH_EXP2_DEV_S;
#endif

#ifdef PPC_CORSTONE315_PERIPH_EXP3_S
#include "ppc_corstone315_drv.h"
extern struct ppc_corstone315_dev_t PPC_CORSTONE315_PERIPH_EXP3_DEV_S;
#endif

/* System counters */
#ifdef SYSCOUNTER_CNTRL_ARMV8_M_S
#include "syscounter_armv8-m_cntrl_drv.h"
extern struct syscounter_armv8_m_cntrl_dev_t SYSCOUNTER_CNTRL_ARMV8_M_DEV_S;
#endif

#ifdef SYSCOUNTER_READ_ARMV8_M_S
#include "syscounter_armv8-m_read_drv.h"
extern struct syscounter_armv8_m_read_dev_t SYSCOUNTER_READ_ARMV8_M_DEV_S;
#endif
#ifdef SYSCOUNTER_READ_ARMV8_M_NS
#include "syscounter_armv8-m_read_drv.h"
extern struct syscounter_armv8_m_read_dev_t SYSCOUNTER_READ_ARMV8_M_DEV_NS;
#endif

/* System timers */
#ifdef SYSTIMER0_ARMV8_M_S
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER0_ARMV8_M_DEV_S;
#endif
#ifdef SYSTIMER0_ARMV8_M_NS
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER0_ARMV8_M_DEV_NS;
#endif

#ifdef SYSTIMER1_ARMV8_M_S
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER1_ARMV8_M_DEV_S;
#endif
#ifdef SYSTIMER1_ARMV8_M_NS
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER1_ARMV8_M_DEV_NS;
#endif

#ifdef SYSTIMER2_ARMV8_M_S
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER2_ARMV8_M_DEV_S;
#endif
#ifdef SYSTIMER2_ARMV8_M_NS
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER2_ARMV8_M_DEV_NS;
#endif

#ifdef SYSTIMER3_ARMV8_M_S
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER3_ARMV8_M_DEV_S;
#endif
#ifdef SYSTIMER3_ARMV8_M_NS
#include "systimer_armv8-m_drv.h"
extern struct systimer_armv8_m_dev_t SYSTIMER3_ARMV8_M_DEV_NS;
#endif

/* System Watchdogs */
#ifdef SYSWDOG_ARMV8_M_S
#include "syswdog_armv8-m_drv.h"
extern struct syswdog_armv8_m_dev_t SYSWDOG_ARMV8_M_DEV_S;
#endif
#ifdef SYSWDOG_ARMV8_M_NS
#include "syswdog_armv8-m_drv.h"
extern struct syswdog_armv8_m_dev_t SYSWDOG_ARMV8_M_DEV_NS;
#endif

/* ARM MPC SIE 300 driver structures */
#ifdef MPC_SRAM_S
#include "mpc_sie_drv.h"
extern struct mpc_sie_dev_t MPC_SRAM_DEV_S;
#endif

#ifdef MPC_QSPI_S
#include "mpc_sie_drv.h"
extern struct mpc_sie_dev_t MPC_QSPI_DEV_S;
#endif

#ifdef MPC_DDR4_S
#include "mpc_sie_drv.h"
extern struct mpc_sie_dev_t MPC_DDR4_DEV_S;
#endif

#ifdef MPC_ISRAM0_S
#include "mpc_sie_drv.h"
extern struct mpc_sie_dev_t MPC_ISRAM0_DEV_S;
#endif

#ifdef MPC_ISRAM1_S
#include "mpc_sie_drv.h"
extern struct mpc_sie_dev_t MPC_ISRAM1_DEV_S;
#endif

#ifdef MPS3_IO_S
#include "arm_mps3_io_drv.h"
extern struct arm_mps3_io_dev_t MPS3_IO_DEV_S;
#endif

#ifdef MPS3_IO_NS
#include "arm_mps3_io_drv.h"
extern struct arm_mps3_io_dev_t MPS3_IO_DEV_NS;
#endif

/* DMA350 driver structures */
#ifdef DMA350_DMA0_S
#include "dma350_ch_drv.h"
#include "dma350_drv.h"
extern struct dma350_dev_t DMA350_DMA0_DEV_S;

#ifdef DMA350_DMA0_CH0_S
extern struct dma350_ch_dev_t DMA350_DMA0_CH0_DEV_S;
#endif

#ifdef DMA350_DMA0_CH1_S
extern struct dma350_ch_dev_t DMA350_DMA0_CH1_DEV_S;
#endif

#ifdef DMA350_DMA0_CH0_NS
extern struct dma350_ch_dev_t DMA350_DMA0_CH0_DEV_NS;
#endif

#ifdef DMA350_DMA0_CH1_NS
extern struct dma350_ch_dev_t DMA350_DMA0_CH1_DEV_NS;
#endif

#endif /* DMA350_DMA0_S */

#if defined(DMA350_DMA0_S)
#include "dma350_lib.h"
extern const struct dma350_remap_list_t dma350_address_remap;
#endif

/* TGU driver structure */
#ifdef TGU_ARMV8_M_ITCM_S
#include "tgu_armv8_m_drv.h"
extern struct tgu_armv8_m_dev_t TGU_ARMV8_M_ITCM_DEV_S;
#endif

#ifdef TGU_ARMV8_M_DTCM_S
#include "tgu_armv8_m_drv.h"
extern struct tgu_armv8_m_dev_t TGU_ARMV8_M_DTCM_DEV_S;
#endif

#ifdef KMU_S
#include "kmu_drv.h"
extern struct kmu_dev_t KMU_DEV_S;
#endif

#ifdef LCM_S
#include "lcm_drv.h"
extern struct lcm_dev_t LCM_DEV_S;
#endif

#ifdef SAM_S
#include "sam_drv.h"
extern struct sam_dev_t SAM_DEV_S;
#endif

#ifdef HDLCD_NS
#include "hdlcd_drv.h"
extern struct hdlcd_dev_t HDLCD_DEV_NS;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_DEFINITION_H__ */

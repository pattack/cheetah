//
// Created by pouyan on 10/11/25.
//

#pragma once

#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    [[noreturn]] void NMI_Handler();
    [[noreturn]] void HardFault_Handler();
    [[noreturn]] void MemManage_Handler();
    [[noreturn]] void BusFault_Handler();
    [[noreturn]] void UsageFault_Handler();
    void SVC_Handler();
    void DebugMon_Handler();
    void PendSV_Handler();
    void SysTick_Handler();

#ifdef __cplusplus
}
#endif

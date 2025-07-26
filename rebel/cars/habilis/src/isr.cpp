//
// Created by pouyan on 7/25/25.
//

#include <stm32f1xx_hal.h>

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
}

extern "C" void  HardFault_Handler(void)
{
    while (1);
}

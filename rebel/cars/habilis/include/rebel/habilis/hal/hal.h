//
// Created by pouyan on 10/11/25.
//

#pragma once

#include <stm32f4xx_hal.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct {
    UART_HandleTypeDef *huart;

    I2C_HandleTypeDef *hi2c;
} Peripherals;

void SetPeripherals(Peripherals *peripherals);
Peripherals* GetPeripherals();

#ifdef __cplusplus
 }
#endif

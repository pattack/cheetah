//
// Created by pouyan on 3/29/26.
//

#pragma once

#include <rebel/habilis/hal/hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    void I2C1_EV_IRQHandler();
    void I2C1_ER_IRQHandler();
    void I2C2_EV_IRQHandler();
    void I2C2_ER_IRQHandler();

#ifdef __cplusplus
}
#endif
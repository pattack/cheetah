//
// Created by pouyan on 7/21/25.
//

#include <memory>

#include <rebel/car/car_factory.hpp>
#include <rebel/habilis/hal.h>
#include <rebel/habilis/car/i2c_bus.hpp>
#include <rebel/habilis/car/habilis.hpp>
#include <rebel/habilis/toolkit/store.hpp>
#include <rebel/habilis/toolkit/usart_logger.hpp>

namespace Rebel::Car {
    void BoardInitOnce() {
        static bool done = false;
        if (done) {
            return;
        }

        HAL_Init();
        HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE2);

        RCC_OscInitTypeDef iosc = {};
        iosc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        iosc.HSIState = RCC_HSI_ON;
        iosc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        iosc.PLL.PLLState = RCC_PLL_NONE;
        HAL_RCC_OscConfig(&iosc);

        RCC_ClkInitTypeDef iclk = {};
        iclk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                         | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        iclk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
        iclk.AHBCLKDivider = RCC_SYSCLK_DIV1;
        iclk.APB1CLKDivider = RCC_HCLK_DIV1;
        iclk.APB2CLKDivider = RCC_HCLK_DIV1;
        HAL_RCC_ClockConfig(&iclk, FLASH_LATENCY_0);

        HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
        SystemCoreClockUpdate();

        done = true;
    }

    Car *CarFactory::Build() {
        BoardInitOnce();

        static Rebel::Habilis::Toolkit::UsartLogger logger{USART1, 115200};
        static Rebel::Habilis::Toolkit::Store store{logger};

        static Rebel::Habilis::Car::I2CBus i2c1{I2C1};
        static Rebel::Habilis::Car::Habilis car{store, i2c1};

        return &car;
    }
}

//
// Created by pouyan on 7/21/25.
//

#include <memory>

#include <rebellion/factory.hpp>

#include <rebel/habilis/hal/hal.h>
#include <rebel/habilis/device/i2c_bus.hpp>
#include <rebel/habilis/car.hpp>
#include <rebel/habilis/store.hpp>
#include <rebel/habilis/module/logger.hpp>

namespace Rebellion {
    void initBoardOnce(const bool internalOsc) {
        static bool done = false;
        if (done) {
            return;
        }

        RCC_OscInitTypeDef iosc = {};
        RCC_ClkInitTypeDef iclk = {};
        uint32_t mco1Source = RCC_MCO1SOURCE_HSE;

        iosc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        iosc.HSIState = RCC_HSE_ON;
        iosc.PLL.PLLState = RCC_PLL_NONE;

        iclk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                         | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        iclk.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
        iclk.AHBCLKDivider = RCC_SYSCLK_DIV1;
        iclk.APB1CLKDivider = RCC_HCLK_DIV1;
        iclk.APB2CLKDivider = RCC_HCLK_DIV1;

        if (internalOsc) {
            iosc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
            iosc.HSIState = RCC_HSI_ON;
            iosc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
            iclk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
            mco1Source = RCC_MCO1SOURCE_HSI;
        }

        HAL_Init();
        HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE2);
        HAL_RCC_OscConfig(&iosc);
        HAL_RCC_ClockConfig(&iclk, FLASH_LATENCY_0);
        HAL_RCC_MCOConfig(RCC_MCO1, mco1Source, RCC_MCODIV_1);
        SystemCoreClockUpdate();

        done = true;
    }

    Car *Factory::BuildCar() {
        initBoardOnce(true);

        static Rebel::Habilis::Device::USART usart1{USART1, 115200};
        static Rebel::Habilis::Device::I2CBus i2c1{I2C1};

        static Rebel::Habilis::Component::STDIO stdio{usart1};

        static Rebel::Habilis::Module::Logger logger{stdio};

        static Rebel::Habilis::Store store{logger};
        static Rebel::Habilis::Car car{store, i2c1};

        return &car;
    }
}

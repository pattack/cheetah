//
// Created by pouyan on 7/23/25.
//

#include <rebel/habilis/hal/hal.h>

#include <rebel/habilis/kit.hpp>

namespace Rebel::Habilis {
    Kit &Kit::Default() {
        static Kit instance{};

        return instance;
    }

    Kit::Kit() {
        this->setup(true);

        this->Devices = {
            .usart1 = new Device::USART(USART1, 115200),
            .usart2 = new Device::USART(USART2, 115200),
        };

        this->Components = {
            .stdio = new Component::STDIO(this->Devices.usart1),
        };

        this->Modules = {
            .logger = new Module::Logger(this->Components.stdio),
        };
    }

    bool Kit::setup(const bool internalOsc) {
        static auto done = false;
        if (done) {
            return done;
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

        return done;
    }
};

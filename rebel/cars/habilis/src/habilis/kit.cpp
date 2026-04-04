//
// Created by pouyan on 7/23/25.
//

#include <habilis/hal/hal.h>
#include <habilis/kit.hpp>

namespace Habilis {
    Kit &Kit::Default() {
        static Kit instance{};

        return instance;
    }

    Kit::Kit() {
        this->setup();

        this->Devices = {
            .usart1{new USART{USART1, 115200}},
            .usart2{new USART{USART2, 115200}},

            .i2c1{new I2C{I2C1}},
            .i2c2{new I2C{I2C2}},
        };

        this->Components = {
            .usart_printer{new USART_Printer{this->Devices.usart1}},
        };

        const std::shared_ptr<GPIO_TypeDef> gpiob {GPIOB};

        this->Modules = {
            .logger{new Logger{this->Components.usart_printer}},
            .indicator{
                new Indicator{
                    LED(GPIO(gpiob, GPIO_PIN_0)),
                    LED(GPIO(gpiob, GPIO_PIN_1))
                }
            }
        };

        this->Modules.logger->log(Rebel::Logger::Log_Level::Info, "[Habilis/Kit] created\r\n");
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
}

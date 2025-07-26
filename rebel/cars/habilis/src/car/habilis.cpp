//
// Created by pouyan on 7/15/25.
//

#include <cstdio>

#include <stm32f1xx_hal.h>

#include <rebel/habilis/car/habilis.hpp>
#include <rebel/habilis/toolkit/store.hpp>

namespace Rebel::Habilis::Car
{
    Habilis::Habilis(): engine(0x40)
    {
        this->configure();

        this->store = {};
        this->engine = I2CBus(I2C1, 0x40);
    }

    void Habilis::Run()
    {
        this->store.GetLogger()->Log("Car is running\r\n");

        constexpr uint8_t cmd[] = {0x00, 0x00};
        const uint8_t err = this->engine.publish(cmd, sizeof(cmd));

        char log[32];
        sprintf(log, "i2c send status: %d\r\n", err);
        this->store.GetLogger()->Log(log);

        for (;;)
        {
            this->PushThrottle(0.2);
            HAL_Delay(250);
            this->PushThrottle(0.7);
            HAL_Delay(250);
            this->PushThrottle(0.3);
            HAL_Delay(250);
            this->PushThrottle(0.0);
            HAL_Delay(250);
            this->PushThrottle(1.0);
        }
    }

    Rebel::Toolkit::Store* Habilis::GetStore()
    {
        return &this->store;
    }

    void Habilis::SubscribeThrottle(std::function<void(float pressure)> handler)
    {
    }

    void Habilis::SubscribeSteer(std::function<void(float angle)> handler)
    {
    }

    void Habilis::SubscribeBrake(std::function<void(float pressure)> handler)
    {
    }

    void Habilis::PushThrottle(float pressure)
    {
        char log[64];
        sprintf(log, "Pushing throttle: %d%%\r\n", static_cast<int>(pressure * 100));
        this->store.GetLogger()->Log(log);

        // todo: return this->engine->AdjustRPM(pressure);
        constexpr uint8_t channel = 0;
        constexpr uint16_t on = 0;
        const uint16_t off = static_cast<uint16_t>(pressure * 4096);

        uint8_t cmd[5];
        cmd[0] = 0x06 + 4 * channel;
        cmd[1] = on & 0xFF;
        cmd[2] = on >> 8;
        cmd[3] = off & 0xFF;
        cmd[4] = off >> 8;

        const uint8_t err = this->engine.publish(cmd, sizeof(cmd));

        sprintf(log, "i2c send status: %d\r\n", err);
        this->store.GetLogger()->Log(log);
    }

    void Habilis::ReleaseThrottle()
    {
        // return this->engine->AdjustRPM(static_cast<float>(RPM::Stopped));
    }

    void Habilis::SetSteeringAngle(float angle)
    {
    }

    void Habilis::SetGear(int gear)
    {
    }

    void Habilis::PressBrakes(float pressure)
    {
    }

    void Habilis::ReleaseBrakes()
    {
    }

    float Habilis::GetSpeed() const
    {
        // constexpr float tireRadius = 1;
        // constexpr float tireCircumference = 2 * std::numbers::pi * tireRadius;
        // constexpr float gearRatio = 1;
        // constexpr float finalDriveRatio = 1;
        //
        // return (this->engine->RPM() * static_cast<int>(tireCircumference * 60)) / static_cast<int>(gearRatio *
        //     finalDriveRatio * 1000);

        return 0;
    }

    float Habilis::GetSteeringAngle() const
    {
        return 0;
    }

    float Habilis::GetGear() const
    {
        return 0;
    }

    float Habilis::GetThrottlePosition() const
    {
        return 0;
    }

    float Habilis::GetBrakePosition() const
    {
        return 0;
    }

    void Habilis::configure()
    {
        HAL_Init();

        RCC_OscInitTypeDef iosc = {};
        iosc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        iosc.HSEState = RCC_HSE_ON;
        iosc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
        iosc.PLL.PLLState = RCC_PLL_ON;
        iosc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        iosc.PLL.PLLMUL = RCC_PLL_MUL9;
        HAL_RCC_OscConfig(&iosc);

        RCC_ClkInitTypeDef iclk = {};
        iclk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        iclk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        iclk.AHBCLKDivider = RCC_SYSCLK_DIV1;
        iclk.APB1CLKDivider = RCC_HCLK_DIV2;
        iclk.APB2CLKDivider = RCC_HCLK_DIV1;
        HAL_RCC_ClockConfig(&iclk, FLASH_LATENCY_2);

        SystemCoreClockUpdate();
    }
}

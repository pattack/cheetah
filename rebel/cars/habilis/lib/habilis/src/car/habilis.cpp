//
// Created by pouyan on 7/15/25.
//

#include <cstdio>

#include <stm32f1xx_hal.h>
#include <rebel/habilis/car/habilis.hpp>

#include <rebel/habilis/toolkit/store.hpp>

namespace Rebel::Habilis::Car
{
    Habilis::Habilis()
    {
        this->configure();

        this->store = {};
    }

    void Habilis::Run()
    {
        this->store.GetLogger()->Log("Car is running...\r\n");
        this->PushThrottle(0.0);

        char log[64];
        for (;;)
        {
            sprintf(log, "Still running %lu...\r\n", HAL_GetTick());
            this->store.GetLogger()->Log(log);

            HAL_Delay(250);
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
        this->store.GetLogger()->Log("Pushing throttle...\r\n");
        // return this->engine->AdjustRPM(pressure);
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

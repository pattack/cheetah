//
// Created by pouyan on 7/15/25.
//

#include <cstddef>

#include <stm32f1xx_hal.h>

#include <rebel/habilis/car/habilis.hpp>

namespace Rebel::Habilis::Car
{
    void Habilis::Run()
    {
        this->PushThrottle(0.0);
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
}

UART_HandleTypeDef huart1;

void configureUart1()
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&huart1);
}

void uartPrint(const char* msg)
{
    HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(const_cast<char*>(msg)), 18, HAL_MAX_DELAY);
}

//
// Created by pouyan on 7/15/25.
//

#include <memory>

#include <stm32f1xx_hal.h>
#include <rebel/habilis/car/habilis.hpp>

#include <rebel/habilis/toolkit/store.hpp>

namespace Rebel::Habilis::Car
{
    Habilis::Habilis()
    {
    }

    void Habilis::Run()
    {
        this->PushThrottle(0.0);
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
}

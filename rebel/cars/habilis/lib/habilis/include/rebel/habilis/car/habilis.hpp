//
// Created by pouyan on 7/21/25.
//

#pragma once

#include <rebel/car/car.hpp>

namespace Rebel::Habilis::Car
{
    class Habilis : public Rebel::Car::Car
    {
    public:
        void Run() override;

        void SubscribeThrottle(std::function<void(float pressure)> handler) override;
        void SubscribeSteer(std::function<void(float angle)> handler) override;
        void SubscribeBrake(std::function<void(float pressure)> handler) override;

        void PushThrottle(float pressure) override;
        void ReleaseThrottle() override;
        void SetSteeringAngle(float angle) override;
        void SetGear(int gear) override;
        void PressBrakes(float pressure) override;
        void ReleaseBrakes() override;

        float GetSpeed() const override;
        float GetSteeringAngle() const override;
        float GetGear() const override;
        float GetThrottlePosition() const override;
        float GetBrakePosition() const override;
    };
}

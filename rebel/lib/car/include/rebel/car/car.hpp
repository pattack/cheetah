//
// Created by pouyan on 1/3/25.
//

#pragma once

#include <functional>

namespace Rebel::Car
{
    class Car
    {
    public:
        /**
         * @brief main loop, blocks forever
         */
        virtual void Run() = 0;

        // Event Listeners

        virtual void SubscribeThrottle(std::function<void(float pressure)> handler) = 0;

        virtual void SubscribeSteer(std::function<void(float angle)> handler) = 0;

        virtual void SubscribeBrake(std::function<void(float pressure)> handler) = 0;

        // Control commands

        /**
         * @brief Speeds up/down the car.
         * @param pressure A value between 0 and 1.
         */
        virtual void PushThrottle(float pressure) = 0;

        /**
         * @brief Stops controlling the speed.
         */
        virtual void ReleaseThrottle() = 0;

        virtual void SetSteeringAngle(float angle) = 0;

        virtual void SetGear(int gear) = 0;

        virtual void PressBrakes(float pressure) = 0;

        virtual void ReleaseBrakes() = 0;

        // Feedback

        /**
         * @brief Returns car speed in km/h.
         */
        virtual float GetSpeed() const = 0;

        virtual float GetSteeringAngle() const = 0;

        virtual float GetGear() const = 0;

        virtual float GetThrottlePosition() const = 0;

        virtual float GetBrakePosition() const = 0;
    };
}

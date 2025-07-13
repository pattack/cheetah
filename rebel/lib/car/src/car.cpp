//
// Created by pouyan on 1/3/25.
//

#include <numbers>

#include <rebel/car/engine.hpp>
#include <rebel/car/car.hpp>

namespace Rebel::Car
{
    Car::Car(Engine* engine): engine(engine)
    {
    }

    int Car::Speed() const
    {
        constexpr float tireRadius = 1;
        constexpr float tireCircumference = 2 * std::numbers::pi * tireRadius;
        constexpr float gearRatio = 1;
        constexpr float finalDriveRatio = 1;

        return (this->engine->RPM() * static_cast<int>(tireCircumference * 60)) / static_cast<int>(gearRatio *
            finalDriveRatio * 1000);
    }

    int Car::PushThrottle(float pressure) const
    {
        return this->engine->AdjustRPM(pressure);
    }

    int Car::ReleaseThrottle() const
    {
        return this->engine->AdjustRPM(static_cast<float>(RPM::Stopped));
    }
}

//
// Created by pouyan on 1/11/25.
//

#include <rebel/car/engine.hpp>
#include <rebel/car/engine_loopback.hpp>
#include <rebel/car/engine_loopless.hpp>

namespace Rebel::Car
{
    Engine::Engine(int maxRPM): maxRPM(maxRPM)
    {
        auto* lb = new EngineLoopback();

        this->Install(lb);
        this->Calibrate(lb);
    }

    Engine::Engine(int maxRPM, EngineDriver* driver): maxRPM(maxRPM)
    {
        auto* ll = new EngineLoopless(driver);

        this->Install(ll);
        this->Calibrate(ll);
    }

    Engine::Engine(int maxRPM, EngineDriver* driver, EngineSensor* sensor): maxRPM(maxRPM)
    {
        this->Install(driver);
        this->Calibrate(sensor);
    }

    void Engine::Install(EngineDriver* driver)
    {
        this->driver = driver;
    }

    void Engine::Calibrate(EngineSensor* sensor)
    {
        this->sensor = sensor;
    }

    int Engine::AdjustRPM(float ratio) const
    {
        if (ratio < 0 || ratio > 1)
        {
            return 1;
        }

        const int rpm = int(ratio * float(this->maxRPM));
        this->driver->WriteRPM(rpm);

        return 0;
    }

    int Engine::RPM() const
    {
        return this->sensor->ReadRPM();
    }

    int Engine::ChangeDirection(RotationDirection direction) const
    {
        return 1; // todo: write it using driver
    }

    RotationDirection Engine::Direction() const
    {
        return RotationDirection::CW; // todo: read it from sensor
    }
}

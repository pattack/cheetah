//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <rebel/car/habilis/engine_driver.hpp>
#include <rebel/car/habilis/engine_loopback.hpp>
#include <rebel/car/habilis/engine_sensor.hpp>

namespace Rebel::Car
{
    class EngineLoopless : public EngineDriver, public EngineSensor
    {
    public:
        EngineLoopless(EngineDriver* driver);

        void WriteRPM(int rpm) override;

        int ReadRPM() const override;

    private:
        EngineDriver* driver;
        EngineLoopback* lb;
    };
}

//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <rebel/car/habilis/engine_driver.hpp>
#include <rebel/car/habilis/engine_sensor.hpp>

namespace Rebel::Car
{
    class EngineLoopback : public EngineDriver, public EngineSensor
    {
    public:
        void WriteRPM(int rpm) override;

        int ReadRPM() const override;

    private:
        int rpm = 0;
    };
}

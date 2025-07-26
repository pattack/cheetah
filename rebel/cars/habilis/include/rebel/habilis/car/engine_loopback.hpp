//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <rebel/habilis/car/engine_driver.hpp>
#include <rebel/habilis/car/engine_sensor.hpp>

namespace Rebel::Habilis::Car
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

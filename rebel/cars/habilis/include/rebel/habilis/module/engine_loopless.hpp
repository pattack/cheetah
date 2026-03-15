//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <rebel/habilis/module/engine_driver.hpp>
#include <rebel/habilis/module/engine_loopback.hpp>
#include <rebel/habilis/module/engine_sensor.hpp>

namespace Rebel::Habilis::Module
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

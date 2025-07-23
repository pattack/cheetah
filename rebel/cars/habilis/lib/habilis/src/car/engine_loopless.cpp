//
// Created by pouyan on 1/11/25.
//

#include <rebel/habilis/car/engine_loopless.hpp>

namespace Rebel::Habilis::Car
{
    EngineLoopless::EngineLoopless(EngineDriver* driver): driver(driver)
    {
        this->lb = new EngineLoopback();
    }

    void EngineLoopless::WriteRPM(int rpm)
    {
        this->lb->WriteRPM(rpm);
        this->driver->WriteRPM(rpm);
    }

    int EngineLoopless::ReadRPM() const
    {
        return this->lb->ReadRPM();
    }
}

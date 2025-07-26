//
// Created by pouyan on 1/11/25.
//

#include <rebel/habilis/car/engine_loopback.hpp>

namespace Rebel::Habilis::Car
{
    void EngineLoopback::WriteRPM(int rpm)
    {
        this->rpm = rpm;
    }

    int EngineLoopback::ReadRPM() const
    {
        return this->rpm;
    }
}

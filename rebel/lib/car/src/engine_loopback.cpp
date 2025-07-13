//
// Created by pouyan on 1/11/25.
//

#include <rebel/car/engine_loopback.hpp>

namespace Rebel::Car
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

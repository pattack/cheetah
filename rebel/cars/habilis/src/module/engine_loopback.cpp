//
// Created by pouyan on 1/11/25.
//

#include <rebel/habilis/module/engine_loopback.hpp>

namespace Rebel::Habilis::Module {
    void EngineLoopback::WriteRPM(int rpm) {
        this->rpm = rpm;
    }

    int EngineLoopback::ReadRPM() const {
        return this->rpm;
    }
}

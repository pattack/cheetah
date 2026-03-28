//
// Created by pouyan on 3/28/26.
//

#include <rebel/habilis/module/accelerator.hpp>

namespace Rebel::Habilis::Module {
    Accelerator::Accelerator(const Rebel::Habilis::Component::ADS1110 &sensor) : sensor(sensor) {
    }

    std::pair<float, bool> Accelerator::status() {
        auto [value, ok] = this->sensor.read();
        if (!ok) {
            return {this->lastPressure, false};
        }

        auto changed = this->lastPressure != value;
        this->lastPressure = value;

        return {value, changed};
    }
}

//
// Created by pouyan on 3/28/26.
//

#include <habilis/module/accelerator.hpp>

namespace Habilis {
    Accelerator::Accelerator(std::unique_ptr<ADS1110> sensor) : sensor(std::move(sensor)) {
    }

    std::pair<float, bool> Accelerator::status() {
        auto [value, ok] = this->sensor->read();
        if (!ok) {
            return {this->lastPressure, false};
        }

        auto changed = this->lastPressure != value;
        this->lastPressure = value;

        return {value, changed};
    }
}

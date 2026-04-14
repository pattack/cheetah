//
// Created by pouyan on 3/28/26.
//

#include <habilis/io/mod/accelerator.hpp>

namespace Habilis {
    Accelerator::Accelerator(std::unique_ptr<Rebel::Reader<float>> sensor) : sensor(std::move(sensor)) {
    }

    std::pair<float, bool> Accelerator::read() {
        const auto value = this->sensor->read();

        const auto changed = std::abs(this->lastPressure - value) > 1e-2;
        if (changed) {
            this->lastPressure = value;
        }

        return {this->lastPressure, changed};
    }
}

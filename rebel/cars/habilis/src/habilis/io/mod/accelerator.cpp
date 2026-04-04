//
// Created by pouyan on 3/28/26.
//

#include <habilis/io/mod/accelerator.hpp>

namespace Habilis {
    Accelerator::Accelerator(std::unique_ptr<Rebel::Reader<float>> sensor) : sensor(std::move(sensor)) {
    }

    std::pair<float, bool> Accelerator::read() {
        auto value = this->sensor->read();

        auto changed = this->lastPressure != value;
        this->lastPressure = value;

        return {value, changed};
    }
}

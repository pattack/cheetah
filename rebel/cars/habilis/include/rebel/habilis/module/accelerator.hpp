//
// Created by pouyan on 3/28/26.
//

#pragma once

#include <utility>

#include <rebel/habilis/component/ads1110.hpp>

namespace Rebel::Habilis::Module {
    class Accelerator {
    public:
        explicit Accelerator(const Rebel::Habilis::Component::ADS1110 &sensor);

        /**
         * @brief reads accelerator value from sensor and returns the value and changed indicator
         *
         * @return float pressure, bool changed:
         *   pressure value from 0 to 1
         *   changed indicates if value differs from last read
         */
        std::pair<float, bool> status();

    private:
        Rebel::Habilis::Component::ADS1110 sensor;

        float lastPressure = 0;
    };
};

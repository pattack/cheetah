//
// Created by pouyan on 3/28/26.
//

#pragma once

#include <utility>

#include <habilis/component/ads1110.hpp>

namespace Habilis {
    class Accelerator {
    public:
        explicit Accelerator(std::unique_ptr<ADS1110> sensor);

        /**
         * @brief reads accelerator value from sensor and returns the value and changed indicator
         *
         * @return pair{pressure, changed}:
         *   pressure value from 0 to 1
         *   changed indicates if value differs from last read
         */
        std::pair<float, bool> status();

    private:
        std::unique_ptr<ADS1110> sensor;

        float lastPressure = 0;
    };
}

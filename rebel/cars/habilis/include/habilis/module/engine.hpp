//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <habilis/component/pca9685.hpp>

namespace Habilis {
    class Engine {
    public:
        explicit Engine(const PCA9685 &driver);

        /**
         * @brief Perform actions in order to reach the desired speed
         *
         * @param speed desired speed from stopped=0 to max-speed=1
         * @return whether if operation was successful
         */
        [[nodiscard]] bool reach(float speed) const;

    private:
        PCA9685 driver;

        const int maxRPM = 1000;
    };
}

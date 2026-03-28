//
// Created by pouyan on 1/11/25.
//

#pragma once

#include <rebel/habilis/component/pca9685.hpp>

namespace Rebel::Habilis::Module {
    class Engine {
    public:
        explicit Engine(const Rebel::Habilis::Component::PCA9685 &driver);

        /**
         * @brief Perform actions in order to reach the desired speed
         *
         * @param speed desired speed from stopped=0 to max-speed=1
         * @return whether if operation was successful
         */
        [[nodiscard]] bool reach(float speed) const;

    private:
        Rebel::Habilis::Component::PCA9685 driver;

        const int maxRPM = 1000;
    };
}

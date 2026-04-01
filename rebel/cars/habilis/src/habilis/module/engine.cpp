//
// Created by pouyan on 1/11/25.
//

#include <habilis/module/engine.hpp>

namespace Habilis {
    Engine::Engine(const PCA9685 &driver) : driver(driver) {
    }

    bool Engine::reach(const float speed) const {
        return this->driver.write(0, speed);
    }
}

//
// Created by pouyan on 1/11/25.
//

#include <habilis/module/engine.hpp>

namespace Habilis {
    Engine::Engine(std::unique_ptr<PCA9685> driver) : driver(std::move(driver)) {
    }

    bool Engine::reach(const float speed) const {
        return this->driver->write(0, speed);
    }
}

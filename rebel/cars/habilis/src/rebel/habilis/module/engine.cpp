//
// Created by pouyan on 1/11/25.
//

#include <rebel/habilis/module/engine.hpp>

namespace Rebel::Habilis::Module {
    Engine::Engine(const Rebel::Habilis::Component::PCA9685 &driver) : driver(driver) {
    }

    bool Engine::reach(const float speed) const {
        return this->driver.write(0, speed);
    }
}

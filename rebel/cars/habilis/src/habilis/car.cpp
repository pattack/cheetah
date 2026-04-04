//
// Created by pouyan on 4/4/26.
//

#include <habilis/car.hpp>

namespace Habilis {
    void Car::move(const float speed) const {
        this->m_engine->revolve(speed, false);
    }
}

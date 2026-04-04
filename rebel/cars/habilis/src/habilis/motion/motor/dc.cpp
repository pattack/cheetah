//
// Created by pouyan on 4/4/26.
//

#include <habilis/motion/motor/dc.hpp>

namespace Habilis {
    DC_Motor::DC_Motor(std::unique_ptr<Rebel::Writer<float>> controller) : m_controller(std::move(controller)) {
    }

    void DC_Motor::revolve(const float rate, const bool cw) {
        this->m_controller->write(cw ? rate : -rate);
    }

    int DC_Motor::rpm() {
        return 0;
    }
}

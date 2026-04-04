//
// Created by pouyan on 4/4/26.
//

#include <habilis/car.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    void Car::move(const float speed) const {
        this->m_engine->revolve(speed, false);
    }

    void Car::reset_devices() {
        if (Kit::Default().Devices.i2c1->slot(0x00)->write({0x06})) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Info,
                                               "[Habilis/Svc/Car] general call performed successfully\r\n");
        } else {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Svc/Car] general call failed\r\n");
        }
    }
}

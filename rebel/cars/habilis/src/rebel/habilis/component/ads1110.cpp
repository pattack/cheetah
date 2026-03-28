//
// Created by pouyan on 3/28/26.
//

#include <rebel/habilis/component/ads1110.hpp>
#include <rebel/habilis/kit.hpp>

namespace Rebel::Habilis::Component {
    ADS1110::ADS1110(const Rebel::Habilis::Device::I2CDevice device) : device(device) {
        if (!this->configure()) {
            Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Error,
                                                               "[Habilis/Component/ADS1110] configuration failed \r\n");
        }
    }

    std::pair<float, bool> ADS1110::read() const {
        uint8_t pressure[2] = {};
        if (const auto ok = this->device.receive(pressure, 2); !ok) {
            return {0, false};
        }

        const auto value = (pressure[0] << 8) | pressure[1];

        return {this->normalize(this->diffVoltage(value)), true};
    }

    bool ADS1110::configure() const {
        constexpr uint8_t cmd[] = {0x8C};

        return this->device.send(cmd, 1);
    }

    float ADS1110::diffVoltage(const int value) const {
        return (static_cast<float>(value) * this->refVoltage) / (-this->minCode * this->pga);
    }

    float ADS1110::normalize(const float value) const {
        return value / this->maxVoltage;
    }
}

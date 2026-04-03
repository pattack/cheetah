//
// Created by pouyan on 3/28/26.
//

#include <habilis/component/ads1110.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    ADS1110::ADS1110(std::unique_ptr<I2C_Slot> device) : device(std::move(device)) {
        if (!this->configure()) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1110] configuration failed \r\n");
        }
    }

    std::pair<float, bool> ADS1110::read() const {
        const auto raw = this->device->receive();
        if (raw.empty()) {
            return {0, false};
        }

        const auto value = (raw[0] << 8) | raw[1];

        return {this->normalize(this->diffVoltage(value)), true};
    }

    bool ADS1110::configure() const {
        const std::vector<uint8_t> cmd{0x8C};

        return this->device->send(cmd);
    }

    float ADS1110::diffVoltage(const int value) const {
        return (static_cast<float>(value) * this->refVoltage) / (-this->minCode * this->pga);
    }

    float ADS1110::normalize(const float value) const {
        return value / this->maxVoltage;
    }
}

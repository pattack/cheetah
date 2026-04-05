//
// Created by pouyan on 3/28/26.
//

#include <habilis/io/com/ads1110.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    ADS1110::ADS1110(std::unique_ptr<I2C_Slot> device) : m_device(std::move(device)) {
        if (this->configure()) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1110] configured successfully\r\n");
        } else {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1110] configuration failed\r\n");
        }
    }

    float ADS1110::read() {
        const auto raw = this->m_device->read(2);
        if (raw.empty()) {
            return 0;
        }

        const auto value = (raw[0] << 8) | raw[1];

        return this->normalize(this->diffVoltage(value));
    }

    bool ADS1110::configure() const {
        const std::vector<uint8_t> cmd{0x80};

        return this->m_device->write(cmd);
    }

    float ADS1110::diffVoltage(const int value) const {
        return (static_cast<float>(value) * this->refVoltage) / (-this->minCode * this->pga);
    }

    float ADS1110::normalize(const float value) const {
        return value / this->maxVoltage;
    }
}

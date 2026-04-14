//
// Created by pouyan on 3/28/26.
//

#include <habilis/io/com/ads1115.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    ADS1115::ADS1115(std::unique_ptr<I2C_Slot> device, short int channel) : m_device(std::move(device)),
                                                                            m_channel(channel) {
        if (this->configure()) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1115] configured successfully\r\n");
        } else {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1115] configuration failed\r\n");
        }
    }

    float ADS1115::read() {
        // read cfg & select operation mode and input

        const std::vector<uint8_t> cmd{0x00};
        if (const auto ok = this->m_device->write(cmd); !ok) {
            return 0;
        }

        const auto raw = this->m_device->read(2);
        if (raw.empty()) {
            return 0;
        }

        const auto value = (raw[0] << 8) | raw[1];

        return this->normalize(this->diffVoltage(value));
    }

    bool ADS1115::configure() const {
        const std::vector<uint8_t> cmd{0x01, 0x44, 0xE3};

        return this->m_device->write(cmd);
    }

    float ADS1115::diffVoltage(const int value) const {
        return (static_cast<float>(value) * this->refVoltage) / (-this->minCode * this->pga);
    }

    float ADS1115::normalize(const float value) const {
        return value / this->maxVoltage;
    }
}

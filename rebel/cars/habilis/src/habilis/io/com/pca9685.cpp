//
// Created by pouyan on 3/15/26.
//

#include <memory>

#include <habilis/io/com/pca9685.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    PCA9685::PCA9685(std::unique_ptr<I2C_Slot> slot, const short int channel) : m_device(std::move(slot)),
        m_channel(channel) {
        if (this->configure()) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/PCA9685] configured successfully\r\n");
        } else {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/PCA9685] configuration failed\r\n");
        }
    }

    void PCA9685::write(const float value) {
        // todo: handle negative value
        constexpr uint8_t on = 0;
        const auto off = static_cast<uint16_t>(value * 4096);

        const std::vector cmd{
            static_cast<uint8_t>(0x06 + 4 * this->m_channel),
            static_cast<uint8_t>(on & 0xFF),
            static_cast<uint8_t>(on >> 8),
            static_cast<uint8_t>(off & 0xFF),
            static_cast<uint8_t>(off >> 8),
        };

        const auto ok = this->m_device->write(cmd);
    }

    bool PCA9685::configure() const {
        const std::vector<uint8_t> cmd{0x00, 0x20};

        return this->m_device->write(cmd);
    }
};

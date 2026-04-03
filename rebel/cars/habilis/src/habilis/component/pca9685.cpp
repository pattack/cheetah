//
// Created by pouyan on 3/15/26.
//

#include <memory>

#include <habilis/component/pca9685.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    PCA9685::PCA9685(std::unique_ptr<I2C_Slot> slot) : slot(std::move(slot)) {
        if (!this->configure()) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/PCA9685] configuration failed\r\n");
        }
    }

    bool PCA9685::write(const uint8_t channel, const float ratio) const {
        constexpr uint8_t on = 0;
        const auto off = static_cast<uint16_t>(ratio * 4096);

        const std::vector cmd {
            static_cast<uint8_t>(0x06 + 4 * channel),
            static_cast<uint8_t>(on & 0xFF),
            static_cast<uint8_t>(on >> 8),
            static_cast<uint8_t>(off & 0xFF),
            static_cast<uint8_t>(off >> 8),
        };

        const auto ok = this->slot->send(cmd);

        return ok;
    }

    bool PCA9685::configure() const {
        const std::vector<uint8_t> cmd{0x00, 0x20};
        const auto ok = this->slot->send(cmd);

        return ok;
    }
};

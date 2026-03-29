//
// Created by pouyan on 3/15/26.
//

#include <rebel/habilis/component/pca9685.hpp>
#include <rebel/habilis/kit.hpp>

namespace Rebel::Habilis::Component {
    PCA9685::PCA9685(const Rebel::Habilis::Device::I2CSlot slot) : slot(slot) {
        if (!this->configure()) {
            Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Error,
                                                               "[Habilis/Component/PCA9685] configuration failed \r\n");
        }
    }

    bool PCA9685::write(const uint8_t channel, const float ratio) const {
        constexpr uint16_t on = 0;
        const auto off = static_cast<uint16_t>(ratio * 4096);

        uint8_t cmd[5];
        cmd[0] = 0x06 + 4 * channel;
        cmd[1] = on & 0xFF;
        cmd[2] = on >> 8;
        cmd[3] = off & 0xFF;
        cmd[4] = off >> 8;

        const auto [ok, err] = this->slot.send(cmd, 5);

        return ok;
    }

    bool PCA9685::configure() const {
        constexpr uint8_t cmd[] = {0x00, 0x20};

        const auto [ok, err] = this->slot.send(cmd, 2);

        return ok;
    }
};

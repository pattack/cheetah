//
// Created by pouyan on 3/28/26.
//

#include <habilis/io/com/ads1115.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    const float ADS1115::FSR[] = {6.144, 4.096, 2.048, 1.024, 0.512, 0.256};

    ADS1115::ADS1115(std::unique_ptr<I2C_Slot> device, const short int channel) : m_device(std::move(device)),
        m_channel(channel) {
        if (this->configure(CFG_MUX_A0_GND | CFG_PGA_4_096 | CFG_MODE_CC | CFG_DR_32 | CFG_COMP_QUE_DISABLE)) {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1115] configured successfully\r\n");
        } else {
            Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Error,
                                               "[Habilis/Component/ADS1115] configuration failed\r\n");
        }
    }

    float ADS1115::read() {
        const std::vector<uint8_t> cmd{ADDR_CONVERSION};
        if (const auto ok = this->m_device->write(cmd); !ok) {
            return 0;
        }

        const auto raw = this->m_device->read(2);
        if (raw.empty()) {
            return 0;
        }

        const auto value = (raw[0] << 8) | raw[1];

        return this->normalize(this->toVoltage(value));
    }

    bool ADS1115::configure(const int cfg) {
        this->m_abs_fsr = FSR[(cfg >> CFG_PGA_POS) & 0b111];
        const std::vector<uint8_t> cmd{ADDR_CONFIG, static_cast<uint8_t>(cfg >> 8), static_cast<uint8_t>(cfg & 0xFF)};

        return this->m_device->write(cmd);
    }

    float ADS1115::toVoltage(const int value) const {
        return (static_cast<float>(value) * this->m_abs_fsr) / MIN_CODE;
    }

    float ADS1115::normalize(const float value) const {
        return value / this->m_max_voltage;
    }
}

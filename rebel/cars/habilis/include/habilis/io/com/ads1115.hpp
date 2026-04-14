//
// Created by pouyan on 4/14/26.
//

#pragma once

#include <memory>

#include <rebel/io/reader.hpp>

#include <habilis/io/dev/i2c.hpp>

namespace Habilis {
    class ADS1115 : public Rebel::Reader<float> {
    public:
        explicit ADS1115(std::unique_ptr<I2C_Slot> device, short int channel);

        float read() override;

    private:
        std::unique_ptr<I2C_Slot> m_device;
        short int m_channel;

        const float pga = 1; // Gain = 1
        const float minCode = -(1 << 15); // Data Rate = 15SPS (16 bits)
        const float refVoltage = 2.048;
        const float maxVoltage = 3.3;

        [[nodiscard]] bool configure() const;
        [[nodiscard]] float diffVoltage(int value) const;
        [[nodiscard]] float normalize(float value) const;
    };
}
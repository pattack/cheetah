//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <utility>

#include <rebel/habilis/device/i2c.hpp>

namespace Rebel::Habilis::Component {
    class ADS1110 {
    public:
        explicit ADS1110(Rebel::Habilis::Device::I2CDevice device);

        [[nodiscard]] std::pair<float, bool> read() const;

    private:
        Rebel::Habilis::Device::I2CDevice device;

        const float pga = 1; // Gain = 1
        const float minCode = -(1 << 15); // Data Rate = 15SPS (16 bits)
        const float refVoltage = 2.048;
        const float maxVoltage = 5.0;

        [[nodiscard]] float diffVoltage(int value) const;
        [[nodiscard]] float normalize(float value) const;
    };
};

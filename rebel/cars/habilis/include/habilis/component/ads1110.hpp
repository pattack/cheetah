//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>
#include <utility>

#include <habilis/io/i2c.hpp>

namespace Habilis {
    class ADS1110 {
    public:
        explicit ADS1110(std::unique_ptr<I2C_Slot> device);

        [[nodiscard]] std::pair<float, bool> read() const;

    private:
        std::unique_ptr<I2C_Slot> device;

        const float pga = 1; // Gain = 1
        const float minCode = -(1 << 15); // Data Rate = 15SPS (16 bits)
        const float refVoltage = 2.048;
        const float maxVoltage = 5.0;

        [[nodiscard]] bool configure() const;
        [[nodiscard]] float diffVoltage(int value) const;
        [[nodiscard]] float normalize(float value) const;
    };
}

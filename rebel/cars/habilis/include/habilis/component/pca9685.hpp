//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <habilis/device/i2c.hpp>

namespace Habilis {
    class PCA9685 {
    public:
        explicit PCA9685(I2CSlot slot);

        [[nodiscard]] bool write(uint8_t channel, float ratio) const;

    private:
        I2CSlot slot;

        [[nodiscard]] bool configure() const;
    };
}
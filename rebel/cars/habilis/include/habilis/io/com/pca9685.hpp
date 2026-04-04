//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>

#include <habilis/io/dev/i2c.hpp>

namespace Habilis {
    class PCA9685 {
    public:
        explicit PCA9685(std::unique_ptr<I2C_Slot> slot);

        [[nodiscard]] bool write(uint8_t channel, float ratio) const;

    private:
        std::unique_ptr<I2C_Slot> slot;

        [[nodiscard]] bool configure() const;
    };
}
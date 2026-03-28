//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <rebel/habilis/device/i2c.hpp>

namespace Rebel::Habilis::Component {
    class PCA9685 {
    public:
        explicit PCA9685(Rebel::Habilis::Device::I2CDevice device);

        [[nodiscard]] bool write(uint8_t channel, float ratio) const;

    private:
        Rebel::Habilis::Device::I2CDevice device;

        [[nodiscard]] bool configure() const;
    };
};
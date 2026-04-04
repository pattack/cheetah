//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>

#include <rebel/io/writer.hpp>

#include <habilis/io/dev/i2c.hpp>

namespace Habilis {
    class PCA9685 : public Rebel::Writer<float> {
    public:
        explicit PCA9685(std::unique_ptr<I2C_Slot> slot, short int channel);

        void write(float value) override;

    private:
        std::unique_ptr<I2C_Slot> m_device;
        short int m_channel;

        [[nodiscard]] bool configure() const;
    };
}

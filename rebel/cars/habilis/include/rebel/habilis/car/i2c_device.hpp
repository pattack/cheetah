//
// Created by pouyan on 3/6/26.
//

#pragma once

#include <rebel/habilis/car/i2c_bus.hpp>

namespace Rebel::Habilis::Car
{
    class I2CBus;

    class I2CDevice
    {
    public:
        explicit I2CDevice(I2CBus* bus, uint8_t address);

        [[nodiscard]] bool isReady();
        bool send(const uint8_t* data, size_t length);
        bool receive(uint8_t* data, size_t length);

    private:
        I2CBus* bus;
        uint8_t address;
    };
};

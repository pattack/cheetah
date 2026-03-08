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
        explicit I2CDevice(I2CBus* bus, uint16_t address);

        [[nodiscard]] HAL_StatusTypeDef isReady() const;
        HAL_StatusTypeDef send(const uint8_t* data, size_t length) const;
        HAL_StatusTypeDef receive(uint8_t* data, size_t length) const;

    private:
        I2CBus* bus;
        uint16_t address;
    };
};

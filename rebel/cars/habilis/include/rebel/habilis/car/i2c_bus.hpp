//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <rebel/habilis/hal/hal.h>
#include <rebel/habilis/car/i2c_device.hpp>

namespace Rebel::Habilis::Car
{
    class I2CDevice;

    class I2CBus
    {
        friend class I2CDevice;

    public:
        explicit I2CBus(I2C_TypeDef* instance);

        I2CBus(const I2CBus&) = delete;
        I2CBus& operator=(const I2CBus&) = delete;
        I2CBus(I2CBus&&) = delete;
        I2CBus& operator=(I2CBus&&) = delete;

        I2CDevice device(uint16_t address);
        uint32_t error();

    private:
        I2C_HandleTypeDef hi2c;

        HAL_StatusTypeDef isDeviceReady(uint16_t address);
        HAL_StatusTypeDef write(uint16_t address, const uint8_t* data, size_t length);
        HAL_StatusTypeDef read(uint16_t address, uint8_t* data, size_t length);

    protected:
        void configure(I2C_TypeDef *instance);

        void waitForReadiness();
        void recover();
        static uint16_t addressOnWire(uint16_t address);
    };
};

//
// Created by pouyan on 7/13/25.
//

#include <cmath>

#include <rebel/habilis/car/i2c_bus.hpp>

namespace Rebel::Habilis::Car
{
    I2CBus::I2CBus(I2C_TypeDef* instance) : hi2c{}
    {
        this->configure(instance);
    }

    I2CDevice I2CBus::device(const uint8_t address)
    {
        return I2CDevice(this, address);
    }

    HAL_StatusTypeDef I2CBus::isDeviceReady(const uint8_t address)
    {
        this->waitForReadiness();

        return HAL_I2C_IsDeviceReady(&this->hi2c, address << 1, 1, 100);
    }

    HAL_StatusTypeDef I2CBus::write(const uint8_t address, const uint8_t* data, const size_t length)
    {
        this->waitForReadiness();

        return HAL_I2C_Master_Transmit(&this->hi2c, address << 1, const_cast<uint8_t*>(data), length, 100);
    }

    HAL_StatusTypeDef I2CBus::read(const uint8_t address, uint8_t* data, const size_t length)
    {
        this->waitForReadiness();

        return HAL_I2C_Master_Receive(&this->hi2c, address << 1, data, length, 100);
    }

    uint32_t I2CBus::error()
    {
        return HAL_I2C_GetError(&this->hi2c);
    }

    void I2CBus::configure(I2C_TypeDef* instance)
    {
        this->hi2c.Instance = instance;
        this->hi2c.Init.ClockSpeed = 100000;
        this->hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
        this->hi2c.Init.OwnAddress1 = 0;
        this->hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        this->hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        this->hi2c.Init.OwnAddress2 = 0;
        this->hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        this->hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
        if (HAL_I2C_Init(&this->hi2c) != HAL_OK)
        {
            // todo: log error
        }
    }

    void I2CBus::waitForReadiness()
    {
        while (HAL_I2C_GetState(&this->hi2c) != HAL_I2C_STATE_READY) {}
    }
}

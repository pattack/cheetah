//
// Created by pouyan on 7/13/25.
//

#include <rebel/habilis/car/i2c.hpp>

namespace Rebel::Habilis::Car
{
    I2CBus::I2CBus(const uint8_t address) : address_(address)
    {
    }

    I2CBus::I2CBus(I2C_TypeDef* instance, const uint8_t address) : I2CBus(address)
    {
        this->configure(instance);
    }

    uint32_t I2CBus::publish(const uint8_t* data, const size_t length)
    {
        if (HAL_I2C_GetState(&this->hi2c) == HAL_I2C_STATE_READY)
        {
            HAL_I2C_Master_Transmit(&this->hi2c, this->address_ << 1, const_cast<uint8_t*>(data), length, 100);
        }

        return HAL_I2C_GetError(&this->hi2c);
    }

    // void I2CBus::subscribe(const ReceiveCallback cb)
    // {
    //     subscribers_.push_back(cb);
    // }

    // void I2CBus::on_data_received(const uint8_t* data, const size_t length) const
    // {
    //     for (auto& cb : subscribers_)
    //     {
    //         cb(data, length);
    //     }
    // }

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

        auto peripherals = GetPeripherals();
        peripherals->hi2c = &this->hi2c;
        SetPeripherals(peripherals);
    }
}

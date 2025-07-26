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
        HAL_I2C_Master_Transmit(&this->hi2c, this->address_ << 1, const_cast<uint8_t*>(data), length,
                                100);

        return this->hi2c.ErrorCode;
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
        // __HAL_AFIO_REMAP_I2C1_DISABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_I2C1_CLK_ENABLE();

        GPIO_InitTypeDef igpio = {};
        igpio.Pin = GPIO_PIN_6 | GPIO_PIN_7; // PB6=SCL, PB7=SDA
        igpio.Mode = GPIO_MODE_AF_OD;
        igpio.Speed = GPIO_SPEED_FREQ_HIGH;
        igpio.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOB, &igpio);

        this->hi2c.Instance = instance;
        this->hi2c.Init.ClockSpeed = 100000;
        this->hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
        this->hi2c.Init.OwnAddress1 = 0;
        this->hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        this->hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        this->hi2c.Init.OwnAddress2 = 0;
        this->hi2c.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
        this->hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

        // __HAL_RCC_I2C1_FORCE_RESET();
        // __HAL_RCC_I2C1_RELEASE_RESET();
        //
        // HAL_I2C_DeInit(&this->hi2c);
        HAL_I2C_Init(&this->hi2c);
    }
}


//
// Created by pouyan on 7/13/25.
//

#include <stm32f1xx_hal.h>

#include <rebel/car/habilis/i2c_bus.hpp>

namespace Rebel::Car::Habilis
{
    I2CBus::I2CBus(const uint8_t address)
        : address_(address)
    {
    }

    bool I2CBus::publish(const uint8_t* data, size_t length)
    {
        // Board-specific I2C send implementation
        return true;
    }

    void I2CBus::subscribe(const ReceiveCallback cb)
    {
        subscribers_.push_back(cb);
    }

    void I2CBus::on_data_received(const uint8_t* data, const size_t length) const
    {
        for (auto& cb : subscribers_)
        {
            cb(data, length);
        }
    }
}

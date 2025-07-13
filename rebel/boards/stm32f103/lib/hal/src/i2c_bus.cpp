//
// Created by pouyan on 7/13/25.
//

#include <rebel/hal/stm32f103/i2c_bus.hpp>

namespace Rebel
{
    namespace HAL
    {
        I2CBus::I2CBus(uint8_t address)
            : address_(address)
        {
        }

        bool I2CBus::publish(const uint8_t* data, size_t length)
        {
            // Board-specific I2C send implementation
            return true;
        }

        void I2CBus::subscribe(ReceiveCallback cb)
        {
            subscribers_.push_back(cb);
        }

        void I2CBus::on_data_received(const uint8_t* data, size_t length)
        {
            for (auto& cb : subscribers_)
            {
                cb(data, length);
            }
        }
    }
}

//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <stm32f1xx_hal.h>

#include <rebel/habilis/car/bus.hpp>

namespace Rebel::Habilis::Car
{
    class I2CBus
    {
    public:
        explicit I2CBus(uint8_t address);

        I2CBus(I2C_TypeDef* instance, uint8_t address);

        uint32_t publish(const uint8_t* data, const size_t length) /* override */;

        // void subscribe(ReceiveCallback cb) override;

        // This would be called from the ISR or polling loop when data is received
        // void on_data_received(const uint8_t* data) const;
    private:
        uint8_t address_;

        I2C_HandleTypeDef hi2c{};

        void configure(I2C_TypeDef *instance);
    };
};

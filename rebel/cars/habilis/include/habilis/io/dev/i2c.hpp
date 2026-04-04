//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <habilis/hal/hal.h>

namespace Habilis {
    class I2C_Slot;

    class I2C {
    public:
        explicit I2C(I2C_TypeDef *instance);

        [[nodiscard]] std::unique_ptr<I2C_Slot> slot(uint16_t address) const;

        void handle_event_irq();

        void handle_error_irq();

    protected:
        std::pair<HAL_StatusTypeDef, uint32_t> is_device_ready(uint16_t address);

        std::pair<HAL_StatusTypeDef, uint32_t> transmit(uint16_t address, const uint8_t *data, size_t length);

        std::pair<HAL_StatusTypeDef, uint32_t> receive(uint16_t address, uint8_t *data, size_t length);

    private:
        I2C_HandleTypeDef m_hi2c;

        void configure(I2C_TypeDef *instance);

        void wait_for_readiness();

        void recover(uint32_t err);

        static uint16_t addressOnWire(uint16_t address);
    };

    class I2C_Slot : I2C {
    public:
        explicit I2C_Slot(const I2C &bus, uint16_t address);

        [[nodiscard]] bool probe();

        [[nodiscard]] bool write(const std::vector<uint8_t> &data);

        [[nodiscard]] std::vector<uint8_t> read();

    private:
        uint16_t m_address;
    };
}

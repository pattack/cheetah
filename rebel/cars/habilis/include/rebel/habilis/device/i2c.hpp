//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <utility>

#include <rebel/habilis/hal/hal.h>

namespace Rebel::Habilis::Device {
    class I2CSlot;

    class I2C {
        friend class I2CSlot;

    public:
        explicit I2C(I2C_TypeDef *instance);

        I2C(const I2C &) = delete;

        I2C &operator=(const I2C &) = delete;

        I2C(I2C &&) = delete;

        I2C &operator=(I2C &&) = delete;

        I2CSlot slot(uint16_t address);

        void handleEventIRQ();
        void handleErrorIRQ();

    private:
        I2C_HandleTypeDef hi2c;

        std::pair<HAL_StatusTypeDef, uint32_t> isDeviceReady(uint16_t address);

        std::pair<HAL_StatusTypeDef, uint32_t> write(uint16_t address, const uint8_t *data, size_t length);

        std::pair<HAL_StatusTypeDef, uint32_t> read(uint16_t address, uint8_t *data, size_t length);

    protected:
        void configure(I2C_TypeDef *instance);

        void waitForReadiness();

        void recover(uint32_t err);

        static uint16_t addressOnWire(uint16_t address);
    };

    class I2CSlot {
    public:
        explicit I2CSlot(I2C *bus, uint16_t address);

        [[nodiscard]] std::pair<bool, uint32_t> isReady() const;

        std::pair<bool, uint32_t> send(const uint8_t *data, size_t length) const;

        std::pair<bool, uint32_t> receive(uint8_t *data, size_t length) const;

    private:
        I2C *bus;
        uint16_t address;
    };
};

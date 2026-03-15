//
// Created by pouyan on 7/13/25.
//

#include <cmath>

#include <rebel/habilis/device/i2c_bus.hpp>

namespace Rebel::Habilis::Device {
    I2CBus::I2CBus(I2C_TypeDef *instance) : hi2c{} {
        this->configure(instance);
    }

    I2CDevice I2CBus::device(const uint16_t address) {
        return I2CDevice(this, address);
    }

    HAL_StatusTypeDef I2CBus::isDeviceReady(const uint16_t address) {
        this->waitForReadiness();

        return HAL_I2C_IsDeviceReady(&this->hi2c, I2CBus::addressOnWire(address), 1, 1);
    }

    HAL_StatusTypeDef I2CBus::write(const uint16_t address, const uint8_t *data, const size_t length) {
        this->waitForReadiness();

        const auto status = HAL_I2C_Master_Transmit(&this->hi2c, I2CBus::addressOnWire(address),
                                                    const_cast<uint8_t *>(data),
                                                    length, 100);
        if (status != HAL_OK) {
            this->recover();
        }

        return status;
    }

    HAL_StatusTypeDef I2CBus::read(const uint16_t address, uint8_t *data, const size_t length) {
        this->waitForReadiness();

        const auto status = HAL_I2C_Master_Receive(&this->hi2c, I2CBus::addressOnWire(address), data, length, 100);
        if (status != HAL_OK) {
            this->recover();
        }

        return status;
    }

    uint32_t I2CBus::error() {
        return HAL_I2C_GetError(&this->hi2c);
    }

    void I2CBus::configure(I2C_TypeDef *instance) {
        this->hi2c.Instance = instance;
        this->hi2c.Init.ClockSpeed = 100000;
        this->hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
        this->hi2c.Init.OwnAddress1 = 0x00;
        this->hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        this->hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        this->hi2c.Init.OwnAddress2 = 0x00;
        this->hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        this->hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
        if (HAL_I2C_Init(&this->hi2c) != HAL_OK) {
            // todo: log error
        }

        auto peripherals = GetPeripherals();
        peripherals->hi2c = &this->hi2c;
        SetPeripherals(peripherals);
    }

    void I2CBus::waitForReadiness() {
        while (HAL_I2C_GetState(&this->hi2c) != HAL_I2C_STATE_READY) {
        }
    }

    void I2CBus::recover() {
        // HAL_I2C_DeInit(&this->hi2c);
        // this->configure(this->hi2c.Instance);
    }

    uint16_t I2CBus::addressOnWire(const uint16_t address) {
        return address << 1;
    }
}

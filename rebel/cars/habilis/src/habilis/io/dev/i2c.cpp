//
// Created by pouyan on 7/13/25.
//

#include <habilis/io/dev/i2c.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    I2C::I2C(I2C_TypeDef *instance) : m_hi2c() {
        this->configure(instance);
    }

    std::unique_ptr<I2C_Slot> I2C::slot(const uint16_t address) const {
        return std::make_unique<I2C_Slot>(std::as_const(*this), address);
    }

    void I2C::handle_event_irq() {
        HAL_I2C_EV_IRQHandler(&this->m_hi2c);
    }

    void I2C::handle_error_irq() {
        HAL_I2C_ER_IRQHandler(&this->m_hi2c);
    }

    std::pair<HAL_StatusTypeDef, uint32_t> I2C::is_device_ready(const uint16_t address) {
        this->wait_for_readiness();

        const auto status = HAL_I2C_IsDeviceReady(&this->m_hi2c, I2C::addressOnWire(address), 1, 1);
        const auto err = HAL_I2C_GetError(&this->m_hi2c);

        return {status, err};
    }

    std::pair<HAL_StatusTypeDef, uint32_t>
    I2C::transmit(const uint16_t address, const uint8_t *data, const size_t length) {
        this->wait_for_readiness();

        const auto status = HAL_I2C_Master_Transmit(&this->m_hi2c, I2C::addressOnWire(address),
                                                       const_cast<uint8_t *>(data), length, 100);
        const auto err = HAL_I2C_GetError(&this->m_hi2c);
        if (status != HAL_OK) {
            this->recover(err);
        }

        return {status, err};
    }

    std::pair<HAL_StatusTypeDef, uint32_t> I2C::receive(const uint16_t address, uint8_t *data, const size_t length) {
        this->wait_for_readiness();

        const auto status = HAL_I2C_Master_Receive(&this->m_hi2c, I2C::addressOnWire(address), data, length, 100);
        const auto err = HAL_I2C_GetError(&this->m_hi2c);
        if (status != HAL_OK) {
            this->recover(err);
        }

        return {status, err};
    }

    void I2C::configure(I2C_TypeDef *instance) {
        this->m_hi2c.Instance = instance;
        this->m_hi2c.Init.ClockSpeed = 400000;
        this->m_hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
        this->m_hi2c.Init.OwnAddress1 = 0x00;
        this->m_hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        this->m_hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        this->m_hi2c.Init.OwnAddress2 = 0x00;
        this->m_hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        this->m_hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
        if (HAL_I2C_Init(&this->m_hi2c) != HAL_OK) {
            // todo: indicate failure
        }
    }

    void I2C::wait_for_readiness() {
        while (HAL_I2C_GetState(&this->m_hi2c) != HAL_I2C_STATE_READY) {
        }
    }

    void I2C::recover(const uint32_t err) {
        if (err != HAL_I2C_ERROR_AF) {
            Kit::Default().Modules.indicator->showError();
        }

        // HAL_I2C_DeInit(&this->hi2c);
        // this->configure(this->hi2c.Instance);
    }

    uint16_t I2C::addressOnWire(const uint16_t address) {
        return address << 1;
    }

    I2C_Slot::I2C_Slot(const I2C &bus, const uint16_t address) : I2C(bus), m_address(address) {
    }

    bool I2C_Slot::probe() {
        if (auto [status, err] = this->is_device_ready(this->m_address); status == HAL_OK) {
            return true;
        }

        // todo: handle error

        return false;
    }

    bool I2C_Slot::write(const std::vector<uint8_t> &data) {
        if (auto [status, err] = this->transmit(this->m_address, data.data(), data.size()); status == HAL_OK) {
            return true;
        }

        // todo: handle error

        return false;
    }

    std::vector<uint8_t> I2C_Slot::read() {
        std::vector<uint8_t> buffer{};

        const auto rx = new uint8_t();
        for (;;) {
            if (auto [status, err] = this->receive(this->m_address, rx, 1); status == HAL_OK) {
                if (*rx == '\n') {
                    break;
                }

                buffer.push_back(*rx);
            } else {
                // todo: handle error

                break;
            }
        }

        return buffer;
    }
}

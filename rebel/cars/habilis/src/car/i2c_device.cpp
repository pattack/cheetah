//
// Created by pouyan on 3/6/26.
//

#include <rebel/habilis/car/i2c_device.hpp>

namespace Rebel::Habilis::Car {
    I2CDevice::I2CDevice(I2CBus* bus, const uint8_t address) : bus(bus), address(address)
    {
    }

    HAL_StatusTypeDef I2CDevice::isReady() const
    {
        return this->bus->isDeviceReady(this->address);
    }

    HAL_StatusTypeDef I2CDevice::send(const uint8_t* data, const size_t length) const
    {
        return this->bus->write(this->address, data, length);
    }

    HAL_StatusTypeDef I2CDevice::receive(uint8_t* data, const size_t length) const
    {
        return this->bus->read(this->address, data, length);
    }
}
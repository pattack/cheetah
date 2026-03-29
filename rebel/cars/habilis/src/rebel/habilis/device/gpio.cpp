//
// Created by pouyan on 3/15/26.
//

#include <rebel/habilis/device/gpio.hpp>

namespace Rebel::Habilis::Device {
    GPIO::GPIO(GPIO_TypeDef *instance, const uint16_t pins) : gpio(instance), igpio(), pins(pins) {
        this->configure();
    }

    void GPIO::write(const bool on) const {
        HAL_GPIO_WritePin(this->gpio, this->pins, on ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

    bool GPIO::read() const {
        return HAL_GPIO_ReadPin(this->gpio, this->pins) == GPIO_PIN_RESET;
    }

    void GPIO::configure() {
        this->igpio.Pin = this->pins;
        this->igpio.Mode = GPIO_MODE_OUTPUT_OD;
        this->igpio.Pull = GPIO_PULLUP;

        HAL_GPIO_Init(this->gpio, &this->igpio);

        this->write(false);
    }
}

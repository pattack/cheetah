//
// Created by pouyan on 3/29/26.
//

#include <utility>

#include <habilis/io/mod/indicator.hpp>

namespace Habilis {
    Indicator::Indicator(LED led) : led(std::move(led)) {
    }

    void Indicator::showTransient() const {
        this->led.turnOff(); // todo: blink
    }

    void Indicator::showSteady() const {
        this->led.turnOff();
    }

    void Indicator::showError() const {
        this->led.turnOn();
    }
}

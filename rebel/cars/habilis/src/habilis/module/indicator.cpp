//
// Created by pouyan on 3/29/26.
//

#include <habilis/module/indicator.hpp>

namespace Habilis {
    Indicator::Indicator(const LED &ledStatus, const LED &ledError) : ledStatus(ledStatus), ledError(ledError) {
    }

    void Indicator::showTransient() const {
        this->ledError.turnOff();
        this->ledStatus.turnOn(); // todo: blink
    }

    void Indicator::showSteady() const {
        this->ledError.turnOff();
        this->ledStatus.turnOn();
    }

    void Indicator::showError() const {
        this->ledStatus.turnOff();
        this->ledError.turnOn();
    }
}

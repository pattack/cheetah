//
// Created by pouyan on 3/29/26.
//

#include <utility>

#include <habilis/io/mod/indicator.hpp>

namespace Habilis {
    Indicator::Indicator(LED ledStatus, LED ledError) : ledStatus(std::move(ledStatus)), ledError(std::move(ledError)) {
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

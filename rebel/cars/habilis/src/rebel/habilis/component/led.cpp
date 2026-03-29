//
// Created by pouyan on 3/29/26.
//

#include <rebel/habilis/component/led.hpp>

namespace Rebel::Habilis::Component {
    LED::LED(const Rebel::Habilis::Device::GPIO &slot) : slot(slot) {
    }

    void LED::turnOn() const {
        this->slot.write(true);
    }

    void LED::turnOff() const {
        this->slot.write(false);
    }
}

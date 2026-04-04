//
// Created by pouyan on 3/29/26.
//

#include <habilis/io/com/led.hpp>

namespace Habilis {
    LED::LED(const GPIO &slot) : slot(slot) {
    }

    void LED::turnOn() const {
        this->slot.write(true);
    }

    void LED::turnOff() const {
        this->slot.write(false);
    }
}

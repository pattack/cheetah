//
// Created by pouyan on 3/29/26.
//

#pragma once

#include <habilis/io/dev/gpio.hpp>

namespace Habilis {
    class LED {
    public:
        explicit LED(const GPIO &slot);

        void turnOn() const;

        void turnOff() const;

        // todo: void blink(float speed) const;

    private:
        GPIO slot;
    };
}

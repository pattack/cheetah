//
// Created by pouyan on 3/29/26.
//

#pragma once

#include <rebel/habilis/device/gpio.hpp>

namespace Rebel::Habilis::Component {
    class LED {
    public:
        explicit LED(const Rebel::Habilis::Device::GPIO &slot);

        void turnOn() const;

        void turnOff() const;

        // todo: void blink(float speed) const;

    private:
        Rebel::Habilis::Device::GPIO slot;
    };
};

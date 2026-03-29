//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <utility>

#include <rebel/habilis/hal/hal.h>

namespace Rebel::Habilis::Device {
    class GPIO {
    public:
        explicit GPIO(GPIO_TypeDef *instance, uint16_t pins);

        void write(bool on) const;

        [[nodiscard]] bool read() const;

    private:
        GPIO_TypeDef *gpio;
        GPIO_InitTypeDef igpio;
        uint16_t pins;

    protected:
        void configure();
    };
};

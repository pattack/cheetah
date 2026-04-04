//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>

#include <habilis/hal/hal.h>

namespace Habilis {
    class GPIO {
    public:
        explicit GPIO(std::shared_ptr<GPIO_TypeDef> instance, uint16_t pins);

        void write(bool on) const;

        [[nodiscard]] bool read() const;

    private:
        std::shared_ptr<GPIO_TypeDef> gpio;
        GPIO_InitTypeDef igpio;
        uint16_t pins;

    protected:
        void configure();
    };
};

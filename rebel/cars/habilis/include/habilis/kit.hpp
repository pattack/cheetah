//
// Created by pouyan on 3/24/26.
//

#pragma once

#include <habilis/component/stdio.hpp>
#include <habilis/device/i2c.hpp>
#include <habilis/device/usart.hpp>
#include <habilis/io/text/logger.hpp>
#include <habilis/module/indicator.hpp>

namespace Habilis {
    class Kit {
    public:
        struct {
            USART *usart1, *usart2;
            I2C *i2c1, *i2c2;
        } Devices{};

        struct {
            STDIO *stdio;
        } Components{};

        struct {
            Logger *logger;
            Indicator *indicator;
        } Modules{};

        static Kit &Default();

    private:
        Kit();

        bool setup(bool internalOsc);
    };
}

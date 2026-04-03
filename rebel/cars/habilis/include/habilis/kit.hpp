//
// Created by pouyan on 3/24/26.
//

#pragma once

#include <memory>

#include <habilis/io/i2c.hpp>
#include <habilis/io/usart.hpp>
#include <habilis/io/text/usart_printer.hpp>
#include <habilis/io/text/logger.hpp>
#include <habilis/module/indicator.hpp>

namespace Habilis {
    class Kit {
    public:
        struct {
            std::shared_ptr<USART> usart1, usart2;
            std::shared_ptr<I2C> i2c1, i2c2;
        } Devices{};

        struct {
            std::shared_ptr<USART_Printer> usart_printer;
        } Components{};

        struct {
            std::shared_ptr<Logger> logger;
            std::shared_ptr<Indicator> indicator;
        } Modules{};

        static Kit &Default();

    private:
        Kit();

        bool setup(bool internalOsc = true);
    };
}

//
// Created by pouyan on 3/24/26.
//

#pragma once

#include <rebel/habilis/component/stdio.hpp>
#include <rebel/habilis/device/usart.hpp>
#include <rebel/habilis/module/logger.hpp>

namespace Rebel::Habilis {
    class Kit {
    public:
        struct {
            Device::USART *usart1, *usart2;
        } Devices{};

        struct {
            Component::STDIO *stdio;
        } Components{};

        struct {
            Module::Logger *logger;
        } Modules{};

        static Kit &Default();

    private:
        Kit();

        bool setup(bool internalOsc);
    };
};

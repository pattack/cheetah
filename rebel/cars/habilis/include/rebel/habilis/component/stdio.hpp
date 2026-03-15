//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <rebel/habilis/device/usart.hpp>

namespace Rebel::Habilis::Component {
    class STDIO {
    public:
        STDIO(Rebel::Habilis::Device::USART &usart);

        void print(const char *message);

    private:
        Rebel::Habilis::Device::USART &usart;
    };
};

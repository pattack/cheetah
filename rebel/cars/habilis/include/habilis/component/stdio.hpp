//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <habilis/device/usart.hpp>

namespace Habilis {
    class STDIO {
    public:
        explicit STDIO(USART *usart);

        void print(const char *message) const;

    private:
        USART *usart;
    };
}

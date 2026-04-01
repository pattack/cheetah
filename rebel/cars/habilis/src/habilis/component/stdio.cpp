//
// Created by pouyan on 3/15/26.
//

#include <habilis/component/stdio.hpp>

namespace Habilis {
    STDIO::STDIO(USART *usart) : usart(usart) {
    }

    void STDIO::print(const char *message) const {
        this->usart->write(message);
    }
};

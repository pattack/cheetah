//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <habilis/hal/hal.h>

namespace Habilis {
    class USART {
    public:
        USART(USART_TypeDef *instance, uint32_t baudRate);

        bool write(const char *message);

        void handleIRQ();

    private:
        USART_HandleTypeDef husart;

    protected:
        void configure(USART_TypeDef *instance, uint32_t baudRate);
    };
}

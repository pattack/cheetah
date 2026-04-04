//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <string>
#include <string_view>

#include <habilis/hal/hal.h>

namespace Habilis {
    class USART {
    public:
        USART(USART_TypeDef *instance, uint32_t baudRate);

        bool write(std::string_view message);
        const std::string &read();

        void handle_irq();

    private:
        USART_HandleTypeDef husart;

    protected:
        void configure(USART_TypeDef *instance, uint32_t baudRate);

        void wait_for_readiness();
    };
}

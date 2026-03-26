//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <rebel/habilis/hal/hal.h>

namespace Rebel::Habilis::Device {
    class USART {
    public:
        USART(USART_TypeDef *instance, uint32_t baudrate);

        bool write(const char *message);

    private:
        UART_HandleTypeDef huart;

    protected:
        void configure(USART_TypeDef *instance, uint32_t baudrate);
    };
};

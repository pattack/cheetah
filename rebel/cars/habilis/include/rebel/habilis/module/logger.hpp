//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebellion/logger.hpp>

#include <rebel/habilis/hal/hal.h>

namespace Rebel::Habilis::Module
{
    class UsartLogger final : public Rebellion::Logger
    {
    public:
        explicit UsartLogger(USART_TypeDef* instance, uint32_t baudrate);

        void Log(const char* message) override;

    private:
        UART_HandleTypeDef huart;

    protected:
        void configure(USART_TypeDef* instance, uint32_t baudrate);
    };
}

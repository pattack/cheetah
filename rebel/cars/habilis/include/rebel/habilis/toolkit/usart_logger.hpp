//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/habilis/hal/hal.h>
#include <rebel/toolkit/logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    class UsartLogger final : public Rebel::Toolkit::Logger
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

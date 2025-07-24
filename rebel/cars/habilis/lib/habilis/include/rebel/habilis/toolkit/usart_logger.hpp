//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <stm32f1xx_hal.h>

#include <rebel/toolkit/logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    class UsartLogger final : public Rebel::Toolkit::Logger
    {
    public:
        explicit UsartLogger(USART_TypeDef* Instance);

        void Log(const char* message) override;

    private:
        UART_HandleTypeDef huart{};

        void initHuart(USART_TypeDef* Instance);
    };
}

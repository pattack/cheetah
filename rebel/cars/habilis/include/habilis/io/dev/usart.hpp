//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>
#include <string>
#include <string_view>

#include <habilis/hal/hal.h>

namespace Habilis {
    class USART {
    public:
        USART(USART_TypeDef *instance, uint32_t baudRate);

        [[nodiscard]] bool write(std::string_view message) const;
        [[nodiscard]] const std::string &read() const;

        void handle_irq() const;

    private:
        std::shared_ptr<USART_HandleTypeDef> m_husart;

    protected:
        void configure(USART_TypeDef *instance, uint32_t baudRate);

        void wait_for_readiness() const;
    };
}

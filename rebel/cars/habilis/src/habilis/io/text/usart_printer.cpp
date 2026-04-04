//
// Created by pouyan on 3/15/26.
//

#include <habilis/io/text/usart_printer.hpp>

namespace Habilis {
    USART_Printer::USART_Printer(std::shared_ptr<USART> usart) : m_usart(std::move(usart)) {
    }

    void USART_Printer::write(const std::string_view message) {
        this->m_usart->write(message);
    }
};

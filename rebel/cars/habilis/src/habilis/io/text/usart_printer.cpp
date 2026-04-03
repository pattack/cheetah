//
// Created by pouyan on 3/15/26.
//

#include <habilis/io/text/usart_printer.hpp>

namespace Habilis {
    USART_Printer::USART_Printer(std::shared_ptr<USART> usart) : usart(std::move(usart)) {
    }

    void USART_Printer::print(const std::string_view message) {
        this->usart->write(message);
    }
};

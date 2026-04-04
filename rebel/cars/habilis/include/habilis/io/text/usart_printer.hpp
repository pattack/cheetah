//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>

#include <rebel/io/text/printer.hpp>

#include <habilis/io/dev/usart.hpp>

namespace Habilis {
    class USART_Printer : public Rebel::Printer {
    public:
        explicit USART_Printer(std::shared_ptr<USART> usart);

        void write(std::string_view message) override;

    private:
        std::shared_ptr<USART> m_usart;
    };
}

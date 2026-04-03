//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <memory>

#include <rebel/io/text/printer.hpp>

#include <habilis/io/usart.hpp>

namespace Habilis {
    class USART_Printer : public Rebel::Printer {
    public:
        explicit USART_Printer(std::shared_ptr<USART> usart);

        void print(std::string_view message) override;

    private:
        std::shared_ptr<USART> usart;
    };
}

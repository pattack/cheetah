//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <rebel/io/text/scanner.hpp>

#include <habilis/io/usart.hpp>

namespace Habilis {
    class USART_Scanner : public Rebel::Scanner {
    public:
        explicit USART_Scanner(USART &usart);

        const std::string &scan() override;

    private:
        USART &usart;
    };
}
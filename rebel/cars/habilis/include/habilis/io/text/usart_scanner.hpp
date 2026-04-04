//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <memory>

#include <rebel/io/text/scanner.hpp>

#include <habilis/io/dev/usart.hpp>

namespace Habilis {
    class USART_Scanner : public Rebel::Scanner {
    public:
        explicit USART_Scanner(std::shared_ptr<USART> usart);

        const std::string &read() override;

    private:
        std::shared_ptr<USART> m_usart;
    };
}
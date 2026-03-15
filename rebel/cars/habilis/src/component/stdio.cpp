//
// Created by pouyan on 3/15/26.
//

#include <rebel/habilis/component/stdio.hpp>

namespace Rebel::Habilis::Component {
    STDIO::STDIO(Rebel::Habilis::Device::USART &usart) : usart(usart) {
    }

    void STDIO::print(const char *message) {
        this->usart.Write(message);
    }
};

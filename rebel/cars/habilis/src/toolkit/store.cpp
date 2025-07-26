//
// Created by pouyan on 7/23/25.
//

#include <rebel/habilis/toolkit/store.hpp>
#include <rebel/habilis/toolkit/usart_logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    Store::Store() : logger(USART1, 115200)
    {
    }

    Rebel::Toolkit::Logger* Store::GetLogger()
    {
        return &this->logger;
    }
}

//
// Created by pouyan on 7/23/25.
//

#include <rebel/habilis/toolkit/store.hpp>

namespace Rebel::Habilis::Toolkit
{
    Store::Store(Rebel::Toolkit::Logger& logger) : logger(logger)
    {
    }

    Rebel::Toolkit::Logger* Store::GetLogger()
    {
        return &this->logger;
    }
}

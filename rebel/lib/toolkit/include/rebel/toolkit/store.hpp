//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/toolkit/logger.hpp>

namespace Rebel::Toolkit
{
    class Store
    {
    public:
        virtual Logger* GetLogger() = 0;
    };
}

//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebellion/logger.hpp>

namespace Rebellion
{
    class Store
    {
    public:
        virtual ~Store() = default;

        virtual Logger* GetLogger() = 0;
    };
};

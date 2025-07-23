//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/toolkit/logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    class Logger final : public Rebel::Toolkit::Logger
    {
    public:
        void Log(const char* message) override;
    };
}

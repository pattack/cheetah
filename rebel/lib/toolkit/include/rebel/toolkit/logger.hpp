//
// Created by pouyan on 7/23/25.
//

#pragma once

namespace Rebel::Toolkit
{
    class Logger
    {
    public:
        virtual void Log(const char* message) = 0;
    };
}

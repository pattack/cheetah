//
// Created by pouyan on 3/6/26.
//

#pragma once

namespace Rebel::Toolkit
{
    class Stdout
    {
    public:
        virtual ~Stdout() = default;

        virtual void putc(char c) = 0;
    };
};
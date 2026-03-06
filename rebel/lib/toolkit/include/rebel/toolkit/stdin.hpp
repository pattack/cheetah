//
// Created by pouyan on 3/6/26.
//

#pragma once

namespace Rebel::Toolkit
{
    class Stdin
    {
    public:
        virtual ~Stdin() = default;

        virtual char getc() = 0;
    };
};
//
// Created by pouyan on 3/6/26.
//

#pragma once

#include <cstddef>

namespace Rebel::Toolkit
{
    template <typename Addr, typename Word, typename Status>
    class Bus
    {
    public:
        virtual ~Bus() = default;

        virtual Status probe(Addr address) = 0;
        virtual Status write(Addr address, const Word* data, size_t length) = 0;
        virtual Status read(Addr address, Word* data, size_t length) = 0;
    };
};
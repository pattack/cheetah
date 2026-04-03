//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <string_view>

namespace Rebel {
    class Printer {
    public:
        virtual ~Printer() = default;

        virtual void print(std::string_view message) = 0;
    };
}

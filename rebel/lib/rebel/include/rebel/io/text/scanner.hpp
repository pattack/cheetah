//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <string>

namespace Rebel {
    class Scanner {
    public:
        virtual ~Scanner() = default;

        virtual const std::string &scan() = 0;
    };
}

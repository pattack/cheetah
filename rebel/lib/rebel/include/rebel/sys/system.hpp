//
// Created by pouyan on 3/25/26.
//

#pragma once

#include <vector>

#include <rebel/sys/process.hpp>

namespace Rebel {
    class System {
    public:
        [[noreturn]] static void Boot();

    private:
        static std::vector<Process*> applications();
        static std::vector<Process*> services();
    };
};

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
        static std::vector<std::shared_ptr<Process>> applications();
        static std::vector<std::shared_ptr<Process>> services();
    };
};

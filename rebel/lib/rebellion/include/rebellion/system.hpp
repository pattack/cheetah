//
// Created by pouyan on 3/25/26.
//

#pragma once

#include <vector>

#include <rebellion/agent.hpp>

namespace Rebellion {
    class System {
    public:
        [[noreturn]] static void Boot();

    private:
        static std::vector<Agent*> applications();
    };
};

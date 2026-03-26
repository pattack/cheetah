//
// Created by pouyan on 3/26/26.
//

#include <starter/application/movement.hpp>

#include <rebellion/system.hpp>

namespace Rebellion {
    std::vector<Agent*> System::applications() {
        static std::vector<Agent*> apps {
            new Starter::Movement(),
        };

        return apps;
    }
};
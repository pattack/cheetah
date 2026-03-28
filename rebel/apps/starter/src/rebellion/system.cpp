//
// Created by pouyan on 3/26/26.
//

#include <starter/application/movement.hpp>

#include <rebellion/system.hpp>

namespace Rebellion {
    std::vector<Process*> System::applications() {
        static std::vector<Process*> procs {
            new Starter::Movement(),
        };

        return procs;
    }
};
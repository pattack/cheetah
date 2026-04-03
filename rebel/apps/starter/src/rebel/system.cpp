//
// Created by pouyan on 3/26/26.
//

#include <starter/application/movement.hpp>

#include <rebel/sys/system.hpp>

namespace Rebel {
    std::vector<std::shared_ptr<Process>> System::applications() {
        static std::vector<std::shared_ptr<Process>> procs {
            std::make_shared<Starter::Movement>(),
        };

        return procs;
    }
};
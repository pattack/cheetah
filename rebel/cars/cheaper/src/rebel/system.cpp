//
// Created by pouyan on 4/6/26.
//

#include <rebel/sys/bus.hpp>
#include <rebel/sys/system.hpp>

#include <cheaper/driver.hpp>

namespace Rebel {
    std::vector<std::shared_ptr<Process>> System::services() {
        static std::vector<std::shared_ptr<Process>> procs {
            std::make_shared<Cheaper::Driver>(),
        };

        return procs;
    }
}
//
// Created by pouyan on 3/25/26.
//

#include <rebel/sys/bus.hpp>
#include <rebel/sys/system.hpp>

#include <habilis/car.hpp>

namespace Rebel {
    std::vector<std::shared_ptr<Process>> System::services() {
        static std::vector<std::shared_ptr<Process>> procs {
            std::make_shared<Habilis::CarService>(),
        };

        return procs;
    }
}

//
// Created by pouyan on 3/25/26.
//

#include <rebel/sys/bus.hpp>
#include <rebel/sys/system.hpp>

#include <habilis/car.hpp>

namespace Rebel {
    std::vector<Process*> System::services() {
        static std::vector<Process*> procs {
            new Habilis::CarService(),
        };

        return procs;
    }
}

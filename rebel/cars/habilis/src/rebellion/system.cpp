//
// Created by pouyan on 3/25/26.
//

#include <rebellion/bus.hpp>
#include <rebellion/system.hpp>

#include <rebel/habilis/service/car.hpp>

namespace Rebellion {
    std::vector<Agent*> System::services() {
        static std::vector<Agent*> svcs {
            new Rebel::Habilis::Service::Car(),
        };

        return svcs;
    }
};

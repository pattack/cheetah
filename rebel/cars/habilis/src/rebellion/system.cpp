//
// Created by pouyan on 3/25/26.
//

#include <rebellion/bus.hpp>
#include <rebellion/system.hpp>

#include <rebel/habilis/service/car.hpp>

namespace Rebellion {
    void System::Boot() {
        const auto eventBus = new Bus();
        const auto commandBus = new Bus();

        // attach controllers to the event bus, command bus
        for (const auto app : System::applications()) {
            app->Connect(eventBus, commandBus);
        }

        // attach services to the command bus, event bus
        Rebel::Habilis::Service::Car{}.Connect(commandBus, eventBus);

        for (;;) {
        }
    }
};

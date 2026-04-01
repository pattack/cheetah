//
// Created by pouyan on 3/27/26.
//

#include <rebel/sys/bus.hpp>
#include <rebel/sys/system.hpp>

namespace Rebel {
    void System::Boot() {
        const auto eventBus = new Bus();
        const auto commandBus = new Bus();

        // attach controllers to the event bus, command bus
        for (const auto proc : System::applications()) {
            proc->Attach(eventBus, commandBus);
        }

        // attach services to the command bus, event bus
        for (const auto proc : System::services()) {
            proc->Attach(commandBus, eventBus);
        }

        for (;;) {
            for (const auto proc : System::services()) {
                proc->Proceed();
            }

            for (const auto proc : System::applications()) {
                proc->Proceed();
            }
        }
    }
};
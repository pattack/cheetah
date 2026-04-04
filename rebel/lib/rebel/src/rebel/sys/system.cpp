//
// Created by pouyan on 3/27/26.
//

#include <rebel/sys/bus.hpp>
#include <rebel/sys/system.hpp>

namespace Rebel {
    void System::Boot() {
        const auto b_events = std::make_shared<Bus>();
        const auto b_commands = std::make_shared<Bus>();

        // attach controllers to the event bus, command bus
        for (const auto &proc: System::applications()) {
            proc->attach(b_events, b_commands);
        }

        // attach services to the command bus, event bus
        for (const auto &proc: System::services()) {
            proc->attach(b_commands, b_events);
        }

        for (;;) {
            for (const auto &proc: System::services()) {
                proc->proceed();
            }

            for (const auto &proc: System::applications()) {
                proc->proceed();
            }
        }
    }
}

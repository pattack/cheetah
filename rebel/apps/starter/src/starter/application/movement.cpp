//
// Created by pouyan on 7/21/25.
//

#include <rebellion/module/logger.hpp>

#include <starter/application/movement.hpp>

namespace Starter {
    void Movement::Connect(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) {
        // Register event listeners
        Rebellion::Module::Logger::Log(Rebellion::Module::Logger::LogLevel::Info, "Registering listeners\r\n");

        ibus->On("event/throttle", [this](Rebellion::EventPayload payload) {
                // this->OnThrottle(pressure);
            }
        );
    }

    void Movement::OnThrottle(float pressure) {
        // Decide what to do with throttle input
        // e.g., car->PushThrottle(pressure);
    }

    void Movement::OnSteer(float angle) {
        // Decide what to do with steer input
        // e.g., car->SetSteeringAngle(angle);
    }

    void Movement::OnBrake(float pressure) {
        // Decide what to do with brake input
        // e.g., car->PressBrakes(pressure);
    }
}

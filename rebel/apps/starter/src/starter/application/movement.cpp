//
// Created by pouyan on 7/21/25.
//

#include <rebel/io/text/logger.hpp>

#include <starter/application/movement.hpp>

namespace Starter {
    void Movement::Attach(Rebel::ReceiveBus *ibus, Rebel::SendBus *obus) {
        Rebel::Logger::Log(Rebel::Logger::LogLevel::Info, "[Starter/App/Movement] Attach\r\n");

        this->commands = obus;
        ibus->On("event/accelerator_pressed", [this](const Rebel::EventPayload &payload) {
            this->onAcceleratorPressed(std::any_cast<float>(payload));
        });
    }

    void Movement::Proceed() {
        Rebel::Logger::Log(Rebel::Logger::LogLevel::Debug, "[Starter/App/Movement] Proceed\r\n");
    }

    void Movement::onAcceleratorPressed(float pressure) const {
        Rebel::Logger::Log(Rebel::Logger::LogLevel::Debug, "[Starter/App/Movement] OnAcceleratorPressed\r\n");

        this->commands->Raise("action/move", pressure);
    }
}

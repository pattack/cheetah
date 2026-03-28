//
// Created by pouyan on 7/21/25.
//

#include <rebellion/module/logger.hpp>

#include <starter/application/movement.hpp>

namespace Starter {
    void Movement::Attach(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) {
        Rebellion::Module::Logger::Log(Rebellion::Module::Logger::LogLevel::Info, "[Starter/App/Movement] Attach\r\n");

        this->commands = obus;
        ibus->On("event/accelerator_pressed", [this](const Rebellion::EventPayload &payload) {
            this->onAcceleratorPressed(std::any_cast<float>(payload));
        });
    }

    void Movement::Proceed() {
        Rebellion::Module::Logger::Log(Rebellion::Module::Logger::LogLevel::Debug, "[Starter/App/Movement] Proceed\r\n");
    }

    void Movement::onAcceleratorPressed(float pressure) const {
        Rebellion::Module::Logger::Log(Rebellion::Module::Logger::LogLevel::Debug, "[Starter/App/Movement] OnAcceleratorPressed\r\n");

        this->commands->Raise("action/move", pressure);
    }
}

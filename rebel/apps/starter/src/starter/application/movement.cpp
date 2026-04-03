//
// Created by pouyan on 7/21/25.
//

#include <rebel/io/text/logger.hpp>

#include <starter/application/movement.hpp>

namespace Starter {
    void Movement::Attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) {
        Rebel::Logger::Log(Rebel::Logger::Log_Level::Info, "[Starter/App/Movement] Attach\r\n");

        this->events = std::move(b_receive);
        this->commands = std::move(b_send);

        this->events->On("event/accelerator_pressed", [this](const Rebel::Event_Payload &payload) {
            this->on_accelerator_pressed(std::any_cast<float>(payload));
        });
    }

    void Movement::Proceed() {
        Rebel::Logger::Log(Rebel::Logger::Log_Level::Debug, "[Starter/App/Movement] Proceed\r\n");
    }

    void Movement::on_accelerator_pressed(float pressure) const {
        // todo: resolve swprintf in __strftime to be able to use std::format
        Rebel::Logger::Log(Rebel::Logger::Log_Level::Debug, "[Starter/App/Movement] on_accelerator_pressed {}\r\n");

        this->commands->Raise("action/move", pressure);
    }
}

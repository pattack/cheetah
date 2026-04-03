//
// Created by pouyan on 3/31/26.
//

#include <habilis/car.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    CarService::CarService() {

    }

    void CarService::Attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) {
        Kit::Default().Modules.indicator->showTransient();
        Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Info,
                                                           "[Habilis/Svc/Car] Attach\r\n");

        this->commands = std::move(b_receive);
        this->events = std::move(b_send);

        this->commands->On("action/move", [this](const Rebel::Event_Payload &payload) {
            // this->move(std::any_cast<float>(payload));
        });
    }

    void CarService::Proceed() {
        Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Debug,
                                                           "[Habilis/Svc/Car] Proceed\r\n");

        // if (const auto [pressure, changed] = this->accelerator->status(); changed) {
        //     if (pressure > 0) {
        //         this->events->Raise("event/accelerator_pressed", pressure);
        //     } else {
        //         this->events->Raise("event/accelerator_released", pressure);
        //     }
        // }
    }
}

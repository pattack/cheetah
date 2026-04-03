//
// Created by pouyan on 3/31/26.
//

#include <habilis/car.hpp>
#include <habilis/kit.hpp>

namespace Habilis {
    CarService::CarService() {

    }

    void CarService::Attach(Rebel::Receive_Bus *ibus, Rebel::Send_Bus *obus) {
        Kit::Default().Modules.indicator->showTransient();
        Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Info,
                                                           "[Habilis/Svc/Car] Attach\r\n");

        this->events = obus;
        ibus->On("action/move", [this](const Rebel::Event_Payload &payload) {
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

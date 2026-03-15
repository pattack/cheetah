//
// Created by pouyan on 7/21/25.
//

#include <rebellion/application.hpp>
#include <rebellion/car.hpp>
#include <rebellion/factory.hpp>

namespace Rebellion {
    void Application::Run() {
        const auto car = Rebellion::Factory::BuildCar();

        // Register event listeners
        car->GetStore()->GetLogger()->Log("Registering listeners\r\n");
        car->SubscribeThrottle([this](const float pressure) {
                this->OnThrottle(pressure);
            }
        );
        car->SubscribeSteer([this](const float angle) {
                this->OnSteer(angle);
            }
        );
        car->SubscribeBrake([this](const float pressure) {
                this->OnBrake(pressure);
            }
        );

        car->Run();
    }

    void Application::OnThrottle(float pressure) {
        // Decide what to do with throttle input
        // e.g., car->PushThrottle(pressure);
    }

    void Application::OnSteer(float angle) {
        // Decide what to do with steer input
        // e.g., car->SetSteeringAngle(angle);
    }

    void Application::OnBrake(float pressure) {
        // Decide what to do with brake input
        // e.g., car->PressBrakes(pressure);
    }
}

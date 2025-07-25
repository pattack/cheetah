//
// Created by pouyan on 7/21/25.
//

#include <rebel/app/main.hpp>
#include <rebel/car/car.hpp>
#include <rebel/car/car_factory.hpp>

namespace Rebel::App
{
    void Main::Run()
    {
        auto car = Rebel::Car::CarFactory::Build();

        // Register event listeners
        car->GetStore()->GetLogger()->Log("Registering listeners\r\n");
        car->SubscribeThrottle([this](const float pressure)
            {
                this->OnThrottle(pressure);
            }
        );
        car->SubscribeSteer([this](const float angle)
            {
                this->OnSteer(angle);
            }
        );
        car->SubscribeBrake([this](const float pressure)
            {
                this->OnBrake(pressure);
            }
        );

        car->GetStore()->GetLogger()->Log("Running the car\r\n");
        car->Run();
    }

    void Main::OnThrottle(float pressure)
    {
        // Decide what to do with throttle input
        // e.g., car->PushThrottle(pressure);
    }

    void Main::OnSteer(float angle)
    {
        // Decide what to do with steer input
        // e.g., car->SetSteeringAngle(angle);
    }

    void Main::OnBrake(float pressure)
    {
        // Decide what to do with brake input
        // e.g., car->PressBrakes(pressure);
    }
}

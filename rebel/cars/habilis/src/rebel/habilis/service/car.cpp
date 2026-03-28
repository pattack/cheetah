//
// Created by pouyan on 7/15/25.
//

#include <rebel/habilis/kit.hpp>
#include <rebel/habilis/service/car.hpp>

namespace Rebel::Habilis::Service {
    Car::Car() {
        this->accelerator = new Rebel::Habilis::Module::Accelerator(
            Rebel::Habilis::Component::ADS1110(Rebel::Habilis::Kit::Default().Devices.i2c1->device(0x48))
        );

        this->engine = new Rebel::Habilis::Module::Engine(
            Rebel::Habilis::Component::PCA9685(Rebel::Habilis::Kit::Default().Devices.i2c1->device(0x41))
        );
    }

    void Car::Attach(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) {
        Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Info,
                                                           "[Habilis/Svc/Car] Attach\r\n");

        this->events = obus;
        ibus->On("action/move", [this](const Rebellion::EventPayload &payload) {
            this->move(std::any_cast<float>(payload));
        });
    }

    void Car::Proceed() {
        Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Debug,
                                                           "[Habilis/Svc/Car] Proceed\r\n");

        if (const auto [pressure, changed] = this->accelerator->status(); changed) {
            if (pressure > 0) {
                this->events->Raise("event/accelerator_pressed", pressure);
            } else {
                this->events->Raise("event/accelerator_released", pressure);
            }
        }
    }

    void Car::move(const float speed) const {
        Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Debug,
                                                           "[Habilis/Svc/Car] Move\r\n");

        if (!this->engine->reach(speed)) {
            Rebel::Habilis::Kit::Default().Modules.logger->log(Rebellion::Module::Logger::LogLevel::Error,
                                                               "[Habilis/Svc/Car] Engine reach failed\r\n");
        }
    }

    // float Car::GetSpeed() const {
    // constexpr float tireRadius = 1;
    // constexpr float tireCircumference = 2 * std::numbers::pi * tireRadius;
    // constexpr float gearRatio = 1;
    // constexpr float finalDriveRatio = 1;
    //
    // return (this->engine->RPM() * static_cast<int>(tireCircumference * 60)) / static_cast<int>(gearRatio *
    //     finalDriveRatio * 1000);

    // return 0;
    // }

    void Car::scanDevices() const {
        // char log[64];
        //
        // sprintf(log, "Scanning for connected devices\r\n");
        // Store::GetLogger()->Log(log);
        // for (uint8_t addr = 0x08; addr < 0x78; addr++) {
        //     if (this->i2c.device(addr).isReady() == HAL_OK) {
        //         sprintf(log, "Found device at 0x%02X\r\n", addr);
        //         Store::GetLogger()->Log(log);
        //     }
        // }
    }
};

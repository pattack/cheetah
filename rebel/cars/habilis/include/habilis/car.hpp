//
// Created by pouyan on 3/31/26.
//

#pragma once

#include <rebel/io/analog/sensor.hpp>
#include <rebel/motion/brake.hpp>
#include <rebel/motion/motor.hpp>
#include <rebel/motion/servo.hpp>
#include <rebel/sys/process.hpp>

namespace Habilis {
    class CarService : public Rebel::Process {
    public:
        CarService();

        void Attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) override;

        void Proceed() override;

    private:
        std::shared_ptr<Rebel::Receive_Bus> commands;
        std::shared_ptr<Rebel::Send_Bus> events;

        std::unique_ptr<Rebel::Sensor<float>> accelerator;
        std::unique_ptr<Rebel::Motor> engine;
        std::unique_ptr<Rebel::Brake> brake;
        std::unique_ptr<Rebel::Servo> steering;
    };
}

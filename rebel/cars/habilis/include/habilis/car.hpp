//
// Created by pouyan on 3/31/26.
//

#pragma once

#include <rebel/motion/brake.hpp>
#include <rebel/motion/motor.hpp>
#include <rebel/motion/servo.hpp>
#include <rebel/sys/process.hpp>
#include <rebel/io/reader.hpp>

namespace Habilis {
    class CarService : public Rebel::Process {
    public:
        CarService();

        void Attach(Rebel::Receive_Bus *ibus, Rebel::Send_Bus *obus) override;

        void Proceed() override;

    private:
        Rebel::Send_Bus *events = nullptr;

        Rebel::Reader<float> *accelerator;
        Rebel::Motor *engine;
        Rebel::Brake *brake;
        Rebel::Servo *steering;
    };
}

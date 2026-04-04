//
// Created by pouyan on 3/31/26.
//

#pragma once

#include <rebel/io/reader.hpp>
#include <rebel/sys/process.hpp>

#include <habilis/motion/brake.hpp>
#include <habilis/motion/motor.hpp>
#include <habilis/motion/servo.hpp>

namespace Habilis {
    class CarService : public Rebel::Process {
    public:
        CarService();

        void Attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) override;

        void Proceed() override;

    private:
        std::shared_ptr<Rebel::Receive_Bus> m_commands;
        std::shared_ptr<Rebel::Send_Bus> m_events;

        std::unique_ptr<Motor> m_engine;
        std::unique_ptr<Servo> m_steering;
        std::unique_ptr<Brake> m_brake;

        std::unique_ptr<Rebel::Reader<float>> m_accelerator;
        std::unique_ptr<Rebel::Reader<float>> m_gyroscope;
    };
}

//
// Created by pouyan on 4/4/26.
//

#pragma once

#include <memory>

#include <rebel/io/reader.hpp>

#include <habilis/motion/brake.hpp>
#include <habilis/motion/motor.hpp>
#include <habilis/motion/servo.hpp>

namespace Habilis {
    class Car {
    public:
        Car() = default;

        void move(float speed) const;

    protected:
        std::unique_ptr<Motor> m_engine;
        std::unique_ptr<Servo> m_steering;
        std::unique_ptr<Brake> m_brake;

        std::unique_ptr<Rebel::Reader<float>> m_gyroscope;

        void reset_devices();
    };
}

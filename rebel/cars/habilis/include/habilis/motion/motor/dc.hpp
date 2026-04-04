//
// Created by pouyan on 4/4/26.
//

#pragma once

#include <memory>

#include <rebel/io/writer.hpp>
#include <rebel/io/reader.hpp>

#include <habilis/motion/motor.hpp>

namespace Habilis {
    class DC_Motor : public Motor {
    public:
        explicit DC_Motor(std::unique_ptr<Rebel::Writer<float>> controller);

        void revolve(float rate, bool cw) override;

        int rpm() override;

    private:
        std::unique_ptr<Rebel::Writer<float>> m_controller;

        std::unique_ptr<Rebel::Reader<float>> m_tachometer;
        std::unique_ptr<Rebel::Reader<float>> m_thermometer;
    };
}

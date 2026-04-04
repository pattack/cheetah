//
// Created by pouyan on 3/31/26.
//

#pragma once

#include <rebel/sys/process.hpp>

#include <habilis/car.hpp>
#include <habilis/io/mod/accelerator.hpp>

namespace Habilis {
    class Driver : public Rebel::Process, public Car {
    public:
        Driver();

        void attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) override;

        void proceed() override;

    private:
        std::shared_ptr<Rebel::Receive_Bus> m_commands;
        std::shared_ptr<Rebel::Send_Bus> m_events;

        std::unique_ptr<Accelerator> m_accelerator;

        void on_move(const Rebel::Event_Payload &payload) const;
    };
}

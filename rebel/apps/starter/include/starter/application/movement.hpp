//
// Created by pouyan on 3/26/26.
//

#pragma once

#include <rebel/sys/process.hpp>

namespace Starter {
    class Movement : public Rebel::Process {
    public:
        void Attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) override;

        void Proceed() override;

    private:
        void on_accelerator_pressed(float pressure) const;

    protected:
        std::shared_ptr<Rebel::Receive_Bus> events;
        std::shared_ptr<Rebel::Send_Bus> commands;
    };
};

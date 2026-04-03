//
// Created by pouyan on 3/26/26.
//

#pragma once

#include <rebel/sys/process.hpp>

namespace Starter {
    class Movement : public Rebel::Process {
    public:
        void Attach(Rebel::Receive_Bus *b_receive, Rebel::Send_Bus *b_send) override;

        void Proceed() override;

    private:
        void on_accelerator_pressed(float pressure) const;

    protected:
        Rebel::Send_Bus *commands = nullptr;
    };
};

//
// Created by pouyan on 4/6/26.
//

#pragma once

#include <rebel/sys/process.hpp>

namespace Cheaper {
    class Driver : public Rebel::Process {
    public:
        void attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) override;

        void proceed() override;
    };
}

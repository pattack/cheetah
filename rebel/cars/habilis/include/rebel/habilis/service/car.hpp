//
// Created by pouyan on 7/21/25.
//

#pragma once

#include <rebellion/agent.hpp>

namespace Rebel::Habilis::Service {
    class Car : public Rebellion::Agent {
    public:
        void Connect(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) override;

    protected:
        void boot() const;

        void scanDevices() const;
    };
}

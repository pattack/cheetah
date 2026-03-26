//
// Created by pouyan on 3/26/26.
//

#pragma once

#include <rebellion/agent.hpp>

namespace Starter {
    class Movement : public Rebellion::Agent {
    public:
        void Connect(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) override;

    private:
        void OnThrottle(float pressure);

        void OnSteer(float angle);

        void OnBrake(float pressure);
    };
};

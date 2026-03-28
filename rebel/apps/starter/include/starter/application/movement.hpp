//
// Created by pouyan on 3/26/26.
//

#pragma once

#include <rebellion/process.hpp>

namespace Starter {
    class Movement : public Rebellion::Process {
    public:
        void Attach(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) override;

        void Proceed() override;

    private:
        void onAcceleratorPressed(float pressure) const;

    protected:
        Rebellion::SendBus *commands = nullptr;
    };
};

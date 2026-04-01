//
// Created by pouyan on 3/26/26.
//

#pragma once

#include <rebel/sys/process.hpp>

namespace Starter {
    class Movement : public Rebel::Process {
    public:
        void Attach(Rebel::ReceiveBus *ibus, Rebel::SendBus *obus) override;

        void Proceed() override;

    private:
        void onAcceleratorPressed(float pressure) const;

    protected:
        Rebel::SendBus *commands = nullptr;
    };
};

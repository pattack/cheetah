//
// Created by pouyan on 7/21/25.
//

#pragma once

#include <rebellion/process.hpp>

#include <rebel/habilis/module/accelerator.hpp>
#include <rebel/habilis/module/engine.hpp>

namespace Rebel::Habilis::Service {
    class Car : public Rebellion::Process {
    public:
        Car();

        void Attach(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) override;

        void Proceed() override;

    private:
        Rebellion::SendBus *events = nullptr;

        Rebel::Habilis::Module::Accelerator *accelerator;
        Rebel::Habilis::Module::Engine *engine;

        void move(float speed) const;

        void scanDevices() const;
    };
}

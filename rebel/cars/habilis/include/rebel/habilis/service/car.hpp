//
// Created by pouyan on 7/21/25.
//

#pragma once

#include <rebellion/process.hpp>

#include <rebel/habilis/module/accelerator.hpp>

namespace Rebel::Habilis::Service {
    class Car : public Rebellion::Process {
    public:
        Car();

        void Attach(Rebellion::ReceiveBus *ibus, Rebellion::SendBus *obus) override;

        void Proceed() override;

    private:
        Rebellion::SendBus *events = nullptr;

        Rebel::Habilis::Module::Accelerator *accelerator;

        void move(float speed);

        void boot() const;

        void scanDevices() const;
    };
}

//
// Created by pouyan on 1/3/25.
//

#pragma once

#include <rebel/sys/bus.hpp>

namespace Rebel {
    class Process {
    public:
        virtual ~Process() = default;

        /**
         * @brief activates the process on input and output buses
         */
        virtual void Attach(ReceiveBus *ibus, SendBus *obus) = 0;

        virtual void Proceed() = 0;
    };
};

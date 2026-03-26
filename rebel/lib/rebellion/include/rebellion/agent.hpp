//
// Created by pouyan on 1/3/25.
//

#pragma once

#include <rebellion/bus.hpp>

namespace Rebellion {
    class Agent {
    public:
        virtual ~Agent() = default;

        /**
         * @brief activates the mediator on input and output buses
         */
        virtual void Connect(ReceiveBus *ibus, SendBus *obus) = 0;
    };
};

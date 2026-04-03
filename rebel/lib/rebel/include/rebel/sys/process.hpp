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
        virtual void Attach(Receive_Bus *b_receive, Send_Bus *b_send) = 0;

        virtual void Proceed() = 0;
    };
};

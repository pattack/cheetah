//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>
#include <vector>

namespace Rebel::HAL
{
    class Bus
    {
    public:
        using ReceiveCallback = std::function<void(const uint8_t * data, size_t length)>;

        virtual ~Bus() = default;

        // Send data to the peripheral
        virtual bool publish(const uint8_t* data, size_t length) = 0;

        // Register a callback for received data (subscriber)
        virtual void subscribe(ReceiveCallback cb) = 0;

    protected:
        // Optionally, store subscribers in the base class if you want to manage multiple
        std::vector<ReceiveCallback> subscribers_;
    };
}

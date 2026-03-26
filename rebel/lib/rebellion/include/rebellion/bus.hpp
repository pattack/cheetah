//
// Created by pouyan on 3/25/26.
//

#pragma once

#include <functional>
#include <map>
#include <string>

namespace Rebellion {
    class ReceiveBus {
    public:
        virtual ~ReceiveBus() = default;

        virtual void On(std::string topic, std::function<void(const void *payload)> handler) = 0;
    };

    class SendBus {
    public:
        virtual ~SendBus() = default;

        virtual void Raise(std::string topic, void *payload) = 0;
    };

    class Bus : public ReceiveBus, public SendBus {
    public:
        void On(std::string topic, std::function<void(const void *payload)> handler) override;

        void Raise(std::string topic, void *payload) override;

    private:
        std::map<std::string, std::vector<std::function<void(const void *payload)>>> handlers;
    };
};

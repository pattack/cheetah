//
// Created by pouyan on 3/25/26.
//

#pragma once

#include <any>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace Rebel {
    typedef std::string EventTopic;
    typedef std::any EventPayload;
    typedef std::function<void(EventPayload payload)> EventHandler;

    class ReceiveBus {
    public:
        virtual ~ReceiveBus() = default;

        virtual void On(EventTopic topic, EventHandler handler) = 0;
    };

    class SendBus {
    public:
        virtual ~SendBus() = default;

        virtual void Raise(EventTopic topic, EventPayload payload) = 0;
    };

    class Bus : public ReceiveBus, public SendBus {
    public:
        void On(EventTopic topic, EventHandler handler) override;

        void Raise(EventTopic topic, EventPayload payload) override;

    private:
        std::unordered_map<EventTopic, std::vector<EventHandler>> handlers;
    };
};

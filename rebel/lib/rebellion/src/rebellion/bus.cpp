//
// Created by pouyan on 3/26/26.
//

#include <rebellion/bus.hpp>

namespace Rebellion {
    void Bus::On(const EventTopic topic, const EventHandler handler) {
        if (!this->handlers.contains(topic)) {
            this->handlers[topic] = std::vector<EventHandler>();
        }

        this->handlers[topic].push_back(handler);
    }

    void Bus::Raise(const EventTopic topic, const std::any payload) {
        if (!this->handlers.contains(topic)) {
            return;
        }

        for (const auto& handler : this->handlers[topic]) {
            handler(payload);
        }
    }
}
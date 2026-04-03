//
// Created by pouyan on 3/26/26.
//

#include <rebel/sys/bus.hpp>

namespace Rebel {
    void Bus::On(const Event_Topic topic, const Event_Handler handler) {
        if (!this->handlers.contains(topic)) {
            this->handlers[topic] = std::vector<Event_Handler>();
        }

        this->handlers[topic].push_back(handler);
    }

    void Bus::Raise(const Event_Topic topic, const std::any payload) {
        if (!this->handlers.contains(topic)) {
            return;
        }

        for (const auto& handler : this->handlers[topic]) {
            handler(payload);
        }
    }
}
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
    typedef std::string Event_Topic;
    typedef std::any Event_Payload;
    typedef std::function<void(Event_Payload payload)> Event_Handler;

    class Receive_Bus {
    public:
        virtual ~Receive_Bus() = default;

        virtual void On(Event_Topic topic, Event_Handler handler) = 0;
    };

    class Send_Bus {
    public:
        virtual ~Send_Bus() = default;

        virtual void Raise(Event_Topic topic, Event_Payload payload) = 0;
    };

    class Bus : public Receive_Bus, public Send_Bus {
    public:
        void On(Event_Topic topic, Event_Handler handler) override;

        void Raise(Event_Topic topic, Event_Payload payload) override;

    private:
        std::unordered_map<Event_Topic, std::vector<Event_Handler>> handlers;
    };
};

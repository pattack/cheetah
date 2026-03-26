//
// Created by pouyan on 3/26/26.
//

#include <rebellion/bus.hpp>

namespace Rebellion {
    void Bus::On(std::string topic, std::function<void(const void *payload)> handler) {
        // todo: insert handler
    }

    void Bus::Raise(std::string topic, void *payload) {
        // todo: invoke handlers
    }
}
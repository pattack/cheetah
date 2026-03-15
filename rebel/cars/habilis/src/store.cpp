//
// Created by pouyan on 7/23/25.
//

#include <rebel/habilis/store.hpp>

namespace Rebel::Habilis {
    Store::Store(Rebellion::Logger &logger) : logger(logger) {
    }

    Rebellion::Logger *Store::GetLogger() {
        return &this->logger;
    }
}

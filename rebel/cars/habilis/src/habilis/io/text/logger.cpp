
//
// Created by pouyan on 7/23/25.
//

#include <habilis/io/text/logger.hpp>

namespace Habilis {
    Logger::Logger(STDIO *stdio) : stdio(stdio) {
    }

    void Logger::log(Rebel::Logger::LogLevel level, const char *message) const {
        // todo: filter with minimum level and add it to the message
        this->stdio->print(message);
    }
};

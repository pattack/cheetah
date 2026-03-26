//
// Created by pouyan on 7/23/25.
//

#include <rebel/habilis/module/logger.hpp>

namespace Rebel::Habilis::Module {
    Logger::Logger(Rebel::Habilis::Component::STDIO *stdio) : stdio(stdio) {
    }

    void Logger::log(Rebellion::Module::Logger::LogLevel level, const char *message) const {
        this->stdio->print(message);
    }
};

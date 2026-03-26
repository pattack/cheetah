//
// Created by pouyan on 3/23/26.
//

#include <rebel/habilis/module/logger.hpp>
#include <rebel/habilis/kit.hpp>

#include <rebellion/module/logger.hpp>

namespace Rebellion::Module {
    void Logger::Log(const LogLevel level, const char *message) {
        Rebel::Habilis::Kit::Default().Modules.logger->log(level, message);
    }
}

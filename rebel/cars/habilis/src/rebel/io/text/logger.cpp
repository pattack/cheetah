//
// Created by pouyan on 3/23/26.
//

#include <habilis/kit.hpp>

#include <rebel/io/text/logger.hpp>

namespace Rebel {
    void Logger::Log(const LogLevel level, const char *message) {
        Habilis::Kit::Default().Modules.logger->log(level, message);
    }
}

//
// Created by pouyan on 3/23/26.
//

#include <habilis/kit.hpp>

#include <rebel/io/mod/logger.hpp>

namespace Rebel {
    void Logger::Log(const Log_Level level, const std::string_view message) {
        Habilis::Kit::Default().Modules.logger->log(level, message);
    }
}

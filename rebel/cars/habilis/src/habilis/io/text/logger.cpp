
//
// Created by pouyan on 7/23/25.
//

#include <habilis/io/text/logger.hpp>

namespace Habilis {
    Logger::Logger(std::shared_ptr<Rebel::Printer> printer) : printer(std::move(printer)) {
    }

    void Logger::log(Rebel::Logger::Log_Level level, const std::string_view message) const {
        // todo: filter with minimum level and add it to the message
        this->printer->print(message);
    }
};

//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <memory>

#include <rebel/io/mod/logger.hpp>
#include <rebel/io/text/printer.hpp>

namespace Habilis {
    class Logger {
    public:
        explicit Logger(std::shared_ptr<Rebel::Printer> printer);

        void log(Rebel::Logger::Log_Level level, std::string_view message) const;

    private:
        std::shared_ptr<Rebel::Printer> printer;
    };
}

//
// Created by pouyan on 3/23/26.
//

#pragma once

#include <string_view>

namespace Rebel {
    class Logger {
    public:
        Logger() = delete;
        ~Logger() = delete;

        enum class Log_Level {
            Error,
            Info,
            Debug
        };

        static void Log(Log_Level level, std::string_view message);

        // Prevent copy/move construction.
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;

        // Prevent copy/move assignment operations.
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;
    };
};
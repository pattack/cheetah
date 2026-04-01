//
// Created by pouyan on 3/23/26.
//

#pragma once

namespace Rebel {
    class Logger {
    public:
        Logger() = delete;
        ~Logger() = delete;

        enum class LogLevel {
            Error,
            Info,
            Debug
        };

        static void Log(LogLevel level, const char *message);

        // Prevent copy/move construction.
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;

        // Prevent copy/move assignment operations.
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;
    };
};
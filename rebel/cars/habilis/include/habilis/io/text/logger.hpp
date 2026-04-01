//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/io/text/logger.hpp>

#include <habilis/component/stdio.hpp>

namespace Habilis {
    class Logger {
    public:
        explicit Logger(STDIO *stdio);

        void log(Rebel::Logger::LogLevel level, const char *message) const;

    private:
        // todo: depend on Stream interface which STDIO is one implementation
        STDIO *stdio;
    };
}

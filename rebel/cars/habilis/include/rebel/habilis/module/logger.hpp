//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebellion/module/logger.hpp>

#include <rebel/habilis/component/stdio.hpp>

namespace Rebel::Habilis::Module {
    class Logger {
    public:
        explicit Logger(Rebel::Habilis::Component::STDIO *stdio);

        void log(Rebellion::Module::Logger::LogLevel level, const char *message) const;

    private:
        // note: can depend on Stream interface which STDIO is one implementation
        Rebel::Habilis::Component::STDIO *stdio;
    };
}

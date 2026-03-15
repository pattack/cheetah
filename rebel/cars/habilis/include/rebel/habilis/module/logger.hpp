//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebellion/logger.hpp>

#include <rebel/habilis/component/stdio.hpp>

namespace Rebel::Habilis::Module {
    class Logger final : public Rebellion::Logger {
    public:
        explicit Logger(Rebel::Habilis::Component::STDIO &stdio);

        void Log(const char *message) override;

    private:
        // note: can depend on Stream interface which STDIO is one implementation
        Rebel::Habilis::Component::STDIO &stdio;
    };
}

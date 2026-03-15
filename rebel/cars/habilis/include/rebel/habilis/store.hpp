//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebellion/store.hpp>

namespace Rebel::Habilis {
    class Store final : public Rebellion::Store {
    public:
        explicit Store(Rebellion::Logger &logger);

        Rebellion::Logger *GetLogger() override;

    private:
        Rebellion::Logger &logger;
    };
};

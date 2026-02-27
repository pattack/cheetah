//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/toolkit/store.hpp>

namespace Rebel::Habilis::Toolkit
{
    class Store final : public Rebel::Toolkit::Store
    {
    public:
        explicit Store(Rebel::Toolkit::Logger& logger);

        Rebel::Toolkit::Logger* GetLogger() override;

    private:
        Rebel::Toolkit::Logger& logger;
    };
}

//
// Created by pouyan on 7/23/25.
//

#pragma once

#include <rebel/toolkit/store.hpp>

#include <rebel/habilis/toolkit/usart_logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    class Store final : public Rebel::Toolkit::Store
    {
    public:
        Store();

        Rebel::Toolkit::Logger* GetLogger() override;

    private:
        UsartLogger logger;
    };
}

//
// Created by pouyan on 1/11/25.
//

#pragma once

namespace Rebel::Car
{
    class EngineDriver
    {
    public:
        virtual ~EngineDriver() = default;

        /**
         * @brief Writes rpm on wire
         */
        virtual void WriteRPM(int rpm) = 0;
    };
}

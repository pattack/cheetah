//
// Created by pouyan on 1/11/25.
//

#pragma once

namespace Rebel::Car
{
    class EngineSensor
    {
    public:
        virtual ~EngineSensor() = default;

        /**
         * @brief Reads rpm from wire
         */
        virtual int ReadRPM() const = 0;
    };
}

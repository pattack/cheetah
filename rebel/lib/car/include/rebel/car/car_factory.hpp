//
// Created by pouyan on 7/14/25.
//

#pragma once

#include <rebel/car/car.hpp>

namespace Rebel::Car
{
    class CarFactory
    {
    public:
        // Create the car
        static Car* Build();
    };
}

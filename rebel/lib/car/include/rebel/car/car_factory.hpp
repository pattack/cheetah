//
// Created by pouyan on 7/14/25.
//

#pragma once

#include <memory>

#include <rebel/car/car.hpp>

namespace Rebel::Car
{
    class CarFactory
    {
    public:
        // Create the car
        static std::unique_ptr<Car> Build();
    };
}

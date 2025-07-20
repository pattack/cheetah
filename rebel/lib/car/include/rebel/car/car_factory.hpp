//
// Created by pouyan on 7/14/25.
//

#pragma once

namespace Rebel::Car
{
    class Car;

    class CarFactory
    {
    public:
        // Create the car
        static Car* Build();
    };
}

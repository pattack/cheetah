//
// Created by pouyan on 7/14/25.
//

#pragma once

#include <rebellion/car.hpp>

namespace Rebellion {
    class Factory {
    public:
        // Create the car
        static Car *BuildCar();
    };
}

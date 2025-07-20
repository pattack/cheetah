//
// Created by pouyan on 7/15/25.
//

#include <rebel/car/car_factory.hpp>

namespace Rebel::Car
{
    __attribute__((weak)) std::unique_ptr<Car> CarFactory::Build()
    {
        return std::unique_ptr<Car>{};
    }
}

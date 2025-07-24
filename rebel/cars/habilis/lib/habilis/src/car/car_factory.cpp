//
// Created by pouyan on 7/21/25.
//

#include <memory>

#include <rebel/car/car_factory.hpp>
#include <rebel/habilis/car/habilis.hpp>

namespace Rebel::Car
{
    Car* CarFactory::Build()
    {
        static Rebel::Habilis::Car::Habilis car{};

        return &car;
    }
}

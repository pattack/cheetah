//
// Created by pouyan on 7/21/25.
//

#include <memory>

#include <rebel/car/car_factory.hpp>
#include <rebel/habilis/car/habilis.hpp>

namespace Rebel::Car
{
    std::unique_ptr<Car> CarFactory::Build()
    {
        return std::make_unique<Rebel::Habilis::Car::Habilis>();
    }
}

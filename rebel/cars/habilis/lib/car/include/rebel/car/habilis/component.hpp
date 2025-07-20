//
// Created by pouyan on 7/14/25.
//

#pragma once

namespace Rebel::Car::Habilis
{
    class Component
    {
    public:
        virtual ~Component() = default;

        // Initialize static hardware settings, setup memory, internal state, configure pins.
        // Safe to call without hardware power-on.
        virtual void Configure() = 0;

        // Activate the component and start its tasks
        virtual void Start() = 0;

        // Deactivate safely: power down if needed.
        virtual void Stop() = 0;

        // Undo Configure. Release resources, reset configuration.
        virtual void Deconfigure() = 0;
    };
}

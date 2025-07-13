//
// Created by pouyan on 1/3/25.
//

#pragma once

namespace Rebel
{
    class Engine;

    class Car
    {
    public:
        Car(Engine* engine);

        /**
         * @brief Returns car speed in km/h.
         */
        int Speed() const;

        /**
         * @brief Speeds up/down the car.
         * @param pressure A value between 0 and 1.
         */
        int PushThrottle(float pressure) const;

        /**
         * @brief Stops controlling the speed.
         */
        int ReleaseThrottle() const;

    private:
        Engine* engine;
    };
}

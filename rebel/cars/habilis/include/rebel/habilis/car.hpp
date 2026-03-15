//
// Created by pouyan on 7/21/25.
//

#pragma once

#include <rebellion/car.hpp>
#include <rebellion/store.hpp>

#include <rebel/habilis/device/i2c_bus.hpp>
#include <rebel/habilis/store.hpp>

namespace Rebel::Habilis {
    class Car : public Rebellion::Car {
    public:
        Car(Store &store, Device::I2CBus &i2c);

        void Run() override;

        Rebellion::Store *GetStore() override;

        void SubscribeThrottle(std::function<void(float pressure)> handler) override;

        void SubscribeSteer(std::function<void(float angle)> handler) override;

        void SubscribeBrake(std::function<void(float pressure)> handler) override;

        void PushThrottle(float pressure) override;

        void ReleaseThrottle() override;

        void SetSteeringAngle(float angle) override;

        void SetGear(int gear) override;

        void PressBrakes(float pressure) override;

        void ReleaseBrakes() override;

        float GetSpeed() const override;

        float GetSteeringAngle() const override;

        float GetGear() const override;

        float GetThrottlePosition() const override;

        float GetBrakePosition() const override;

    private:
        Store &store;
        Device::I2CBus &i2c;

    protected:
        void boot() const;

        void scanDevices() const;
    };
}

//
// Created by pouyan on 7/15/25.
//

#include <cstdio>

#include <rebel/habilis/hal/hal.h>
#include <rebel/habilis/car.hpp>
#include <rebel/habilis/store.hpp>

namespace Rebel::Habilis {
    Car::Car(Store &store, Device::I2CBus &i2c) : store(store), i2c(i2c) {
    }

    void Car::Run() {
        char log[64] = {};
        uint8_t cmd[10] = {};

        this->boot();

        uint8_t pressure[3] = {};
        const auto iPressure = this->i2c.device(0x48);

        auto status = iPressure.isReady();
        sprintf(log, "Probe sensor: status=%d, err=%lu\r\n", status, this->i2c.error());
        this->store.GetLogger()->Log(log);
        HAL_Delay(400);

        cmd[0] = 0x8C;
        status = iPressure.send(cmd, 1);
        sprintf(log, "Configure sensor: status=%d, err=%lu\r\n", status, this->i2c.error());
        this->store.GetLogger()->Log(log);
        HAL_Delay(400);

        float throttle = 0.1;
        this->PushThrottle(throttle);

        for (;;) {
            status = iPressure.receive(pressure, 3);
            sprintf(log, "Read sensor: value=%d, status=%d, err=%lu\r\n", (pressure[0] << 8) | pressure[1], status,
                    this->i2c.error());
            this->store.GetLogger()->Log(log);

            throttle += 0.1;
            if (throttle > 1.0) {
                throttle = 0;
            }

            HAL_Delay(300);
            this->PushThrottle(throttle);
        }
    }

    Rebellion::Store *Car::GetStore() {
        return &this->store;
    }

    void Car::SubscribeThrottle(std::function<void(float pressure)> handler) {
    }

    void Car::SubscribeSteer(std::function<void(float angle)> handler) {
    }

    void Car::SubscribeBrake(std::function<void(float pressure)> handler) {
    }

    void Car::PushThrottle(const float pressure) {
        char log[64];
        sprintf(log, "Pushing throttle: %d%%\r\n", static_cast<int>(pressure * 100));
        this->store.GetLogger()->Log(log);

        // todo: return this->engine->AdjustRPM(pressure);
        constexpr uint8_t channel = 0;
        constexpr uint16_t on = 0;
        const auto off = static_cast<uint16_t>(pressure * 4096);

        const auto engine = this->i2c.device(0x41);
        uint8_t cmd[5];
        cmd[0] = 0x06 + 4 * channel;
        cmd[1] = on & 0xFF;
        cmd[2] = on >> 8;
        cmd[3] = off & 0xFF;
        cmd[4] = off >> 8;
        auto status = engine.send(cmd, 5);
        sprintf(log, "Write pwm: status=%d, err=%lu\r\n", status, this->i2c.error());
        this->store.GetLogger()->Log(log);
    }

    void Car::ReleaseThrottle() {
        // return this->engine->AdjustRPM(static_cast<float>(RPM::Stopped));
    }

    void Car::SetSteeringAngle(float angle) {
    }

    void Car::SetGear(int gear) {
    }

    void Car::PressBrakes(float pressure) {
    }

    void Car::ReleaseBrakes() {
    }

    float Car::GetSpeed() const {
        // constexpr float tireRadius = 1;
        // constexpr float tireCircumference = 2 * std::numbers::pi * tireRadius;
        // constexpr float gearRatio = 1;
        // constexpr float finalDriveRatio = 1;
        //
        // return (this->engine->RPM() * static_cast<int>(tireCircumference * 60)) / static_cast<int>(gearRatio *
        //     finalDriveRatio * 1000);

        return 0;
    }

    float Car::GetSteeringAngle() const {
        return 0;
    }

    float Car::GetGear() const {
        return 0;
    }

    float Car::GetThrottlePosition() const {
        return 0;
    }

    float Car::GetBrakePosition() const {
        return 0;
    }

    void Car::boot() const {
        uint8_t cmd[10] = {};

        this->store.GetLogger()->Log("Warming up the engine\r\n");
        HAL_Delay(500);

        // this->scanDevices();
        // this->i2c.device(0x01).isReady();

        const auto engine = this->i2c.device(0x41);
        cmd[0] = 0x00;
        cmd[1] = 0x20;
        engine.send(cmd, 2);
    }

    void Car::scanDevices() const {
        char log[64];

        sprintf(log, "Scanning for connected devices\r\n");
        this->store.GetLogger()->Log(log);
        for (uint8_t addr = 0x08; addr < 0x78; addr++) {
            if (this->i2c.device(addr).isReady() == HAL_OK) {
                sprintf(log, "Found device at 0x%02X\r\n", addr);
                this->store.GetLogger()->Log(log);
            }
        }
    }
};

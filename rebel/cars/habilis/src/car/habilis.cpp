//
// Created by pouyan on 7/15/25.
//

#include <cstdio>

#include <rebel/habilis/hal.h>
#include <rebel/habilis/car/habilis.hpp>
#include <rebel/habilis/toolkit/store.hpp>

namespace Rebel::Habilis::Car
{
    Habilis::Habilis(Rebel::Habilis::Toolkit::Store& store, I2CBus& i2c) : store(store), i2c(i2c) {}

    void Habilis::Run()
    {
        char log[64];
        uint8_t cmd[10];

        sprintf(log, "Warming up the engine\r\n");
        this->store.GetLogger()->Log(log);
        HAL_Delay(100);

        for (uint8_t addr = 0x08; addr < 0x78; addr++)
        {
            volatile auto ok = this->i2c.device(addr).isReady();
            sprintf(log, "addr %02X status=%u\r\n", addr, ok);
            this->store.GetLogger()->Log(log);

            if (ok)
            {
                sprintf(log, "Found device at 0x%02X\r\n", addr);
                this->store.GetLogger()->Log(log);
            }
            HAL_Delay(10);
        }

        auto engine = this->i2c.device(0x41);
        cmd[0] = 0x00;
        cmd[1] = 0x20;
        engine.send(cmd, 2);
        HAL_Delay(100);

        this->store.GetLogger()->Log("Touching the throttle pedal\r\n");
        HAL_Delay(100);

        auto iPressure = this->i2c.device(0x48);
        // cmd[0] = 0x01;
        // cmd[1] = 0xC5;
        // cmd[2] = 0x83;
        // iPressure->send(cmd, 3);
        // HAL_Delay(100);

        uint8_t pressure[2];
        float throttle = 0.1;
        for (;;)
        {
            // cmd[0] = 0x00;
            // iPressure->send(cmd, 1);
            // HAL_Delay(100);
            const auto err = iPressure.receive(pressure, 2);
            // const auto err = HAL_I2C_Master_Receive(&iPressure.hi2c, 0x48 << 1, pressure, 2, 100);
            sprintf(log, "Read pressure (%d): %d\r\n", err, (pressure[0] << 8) | pressure[1]);
            this->store.GetLogger()->Log(log);
            HAL_Delay(1000);

            throttle += 0.1;
            if (throttle > 1.0) {
                throttle = 0;
            }
        }
    }

    Rebel::Toolkit::Store* Habilis::GetStore()
    {
        return &this->store;
    }

    void Habilis::SubscribeThrottle(std::function<void(float pressure)> handler)
    {
    }

    void Habilis::SubscribeSteer(std::function<void(float angle)> handler)
    {
    }

    void Habilis::SubscribeBrake(std::function<void(float pressure)> handler)
    {
    }

    void Habilis::PushThrottle(float pressure)
    {
        char log[64];
        sprintf(log, "Pushing throttle: %d%%\r\n", static_cast<int>(pressure * 100));
        this->store.GetLogger()->Log(log);

        // todo: return this->engine->AdjustRPM(pressure);
        constexpr uint8_t channel = 0;
        constexpr uint16_t on = 0;
        const auto off = static_cast<uint16_t>(pressure * 4096);

        auto engine = this->i2c.device(0x41);
        uint8_t cmd[5];
        cmd[0] = 0x06 + 4 * channel;
        cmd[1] = on & 0xFF;
        cmd[2] = on >> 8;
        cmd[3] = off & 0xFF;
        cmd[4] = off >> 8;
        engine.send(cmd, sizeof(cmd));
    }

    void Habilis::ReleaseThrottle()
    {
        // return this->engine->AdjustRPM(static_cast<float>(RPM::Stopped));
    }

    void Habilis::SetSteeringAngle(float angle)
    {
    }

    void Habilis::SetGear(int gear)
    {
    }

    void Habilis::PressBrakes(float pressure)
    {
    }

    void Habilis::ReleaseBrakes()
    {
    }

    float Habilis::GetSpeed() const
    {
        // constexpr float tireRadius = 1;
        // constexpr float tireCircumference = 2 * std::numbers::pi * tireRadius;
        // constexpr float gearRatio = 1;
        // constexpr float finalDriveRatio = 1;
        //
        // return (this->engine->RPM() * static_cast<int>(tireCircumference * 60)) / static_cast<int>(gearRatio *
        //     finalDriveRatio * 1000);

        return 0;
    }

    float Habilis::GetSteeringAngle() const
    {
        return 0;
    }

    float Habilis::GetGear() const
    {
        return 0;
    }

    float Habilis::GetThrottlePosition() const
    {
        return 0;
    }

    float Habilis::GetBrakePosition() const
    {
        return 0;
    }

}

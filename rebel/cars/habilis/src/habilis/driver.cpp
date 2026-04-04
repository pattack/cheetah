//
// Created by pouyan on 3/31/26.
//

#include <habilis/driver.hpp>
#include <habilis/kit.hpp>

#include <habilis/io/com/ads1110.hpp>
#include <habilis/io/com/pca9685.hpp>
#include <habilis/motion/motor/dc.hpp>

namespace Habilis {
    Driver::Driver() {
        this->reset_devices();

        this->m_accelerator = std::make_unique<Accelerator>(
            std::make_unique<ADS1110>(Kit::Default().Devices.i2c1->slot(0x48))
        );

        this->m_engine = std::make_unique<DC_Motor>(
            std::make_unique<PCA9685>(Kit::Default().Devices.i2c1->slot(0x41), 0)
        );

        Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Info, "[Habilis/Svc/Driver] created\r\n");
    }

    void Driver::attach(std::shared_ptr<Rebel::Receive_Bus> b_receive, std::shared_ptr<Rebel::Send_Bus> b_send) {
        Kit::Default().Modules.indicator->showTransient();

        this->m_commands = std::move(b_receive);
        this->m_events = std::move(b_send);

        this->m_commands->On("action/move", [this](const Rebel::Event_Payload &payload) {
            this->on_move(payload);
        });

        Kit::Default().Modules.logger->log(Rebel::Logger::Log_Level::Info, "[Habilis/Svc/Driver] attached\r\n");
    }

    void Driver::proceed() {
        if (const auto [pressure, changed] = this->m_accelerator->read(); changed) {
            if (pressure > 0) {
                this->m_events->Raise("event/accelerator_pressed", pressure);
            } else {
                this->m_events->Raise("event/accelerator_released", pressure);
            }
        }
    }

    void Driver::on_move(const Rebel::Event_Payload &payload) const {
        this->move(std::any_cast<float>(payload));
    }
}

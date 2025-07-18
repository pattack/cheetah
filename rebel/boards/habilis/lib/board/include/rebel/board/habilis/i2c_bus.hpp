//
// Created by pouyan on 7/13/25.
//

#pragma once

#include <rebel/board/bus.hpp>

namespace Rebel::Board::Habilis
{
    class I2CBus final : public Rebel::Board::Bus
    {
    public:
        explicit I2CBus(uint8_t address);

        bool publish(const uint8_t* data, size_t length) override;

        void subscribe(ReceiveCallback cb) override;

        // This would be called from the ISR or polling loop when data is received
        void on_data_received(const uint8_t* data, size_t length) const;

    private:
        uint8_t address_;
    };
};

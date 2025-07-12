//
// Created by pouyan on 1/13/25.
//

#ifndef PWM_ON_BUS_H
#define PWM_ON_BUS_H

#include <stdint.h>

#include <engine_driver.h>
#include <bus.h>

namespace Rebel {
  class PWMOnBus: public EngineDriver {
    public:
      PWMOnBus(Bus* bus, uint8_t address);

      void WriteRPM(int rpm) override;

    private:
      uint8_t address;
  };
}

#endif //PWM_ON_BUS_H

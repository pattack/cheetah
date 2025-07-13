//
// Created by pouyan on 1/11/25.
//

#pragma once

#include "engine_driver.h"
#include "engine_sensor.h"

namespace Rebel {
  class EngineLoopback: public EngineDriver, public EngineSensor {
    public:
      void WriteRPM(int rpm) override;

      int ReadRPM() const override;

    private:
      int rpm = 0;
  };
}

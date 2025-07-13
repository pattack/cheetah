//
// Created by pouyan on 1/11/25.
//

#pragma once

#include "engine_driver.h"
#include "engine_loopback.h"
#include "engine_sensor.h"

namespace Rebel {
  class EngineLoopless: public EngineDriver, public EngineSensor {
    public:
      EngineLoopless(EngineDriver* driver);

      void WriteRPM(int rpm) override;

      int ReadRPM() const override;

    private:
      EngineDriver* driver;
      EngineLoopback* lb;
  };
}

//
// Created by pouyan on 1/11/25.
//

#ifndef ENGINE_LOOPLESS_H
#define ENGINE_LOOPLESS_H

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

#endif //ENGINE_LOOPLESS_H

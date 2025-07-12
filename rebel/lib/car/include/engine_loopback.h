//
// Created by pouyan on 1/11/25.
//

#ifndef ENGINE_LOOPBACK_H
#define ENGINE_LOOPBACK_H

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

#endif //ENGINE_LOOPBACK_H

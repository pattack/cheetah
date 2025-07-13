//
// Created by pouyan on 1/11/25.
//

#include <rebel/car/engine_loopback.h>

namespace Rebel {
  void EngineLoopback::WriteRPM(int rpm) {
    this->rpm = rpm;
  }

  int EngineLoopback::ReadRPM() const {
    return this->rpm;
  }
}

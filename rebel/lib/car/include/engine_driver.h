//
// Created by pouyan on 1/11/25.
//

#ifndef ENGINE_DRIVER_H
#define ENGINE_DRIVER_H

namespace Rebel {
  class EngineDriver {
    public:
      virtual ~EngineDriver() = default;

      /**
       * @brief Writes rpm on wire
       */
      virtual void WriteRPM(int rpm) = 0;
  };
}

#endif //ENGINE_DRIVER_H

//
// Created by pouyan on 1/11/25.
//

#ifndef ENGINE_SENSOR_H
#define ENGINE_SENSOR_H

namespace Rebel {
  class EngineSensor {
    public:
      virtual ~EngineSensor() = default;

      /**
       * @brief Reads rpm from wire
       */
      virtual int ReadRPM() const = 0;
  };
}

#endif //ENGINE_SENSOR_H

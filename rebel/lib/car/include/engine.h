//
// Created by pouyan on 1/11/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "engine_driver.h"
#include "engine_sensor.h"
#include "rotation_direction.h"

namespace Rebel {
  enum class RPM {
    Stopped,
    MaxSpeed,
  };

  class Engine {
    public:
      Engine(int maxRPM);

      Engine(int maxRPM, EngineDriver* driver);

      Engine(int maxRPM, EngineDriver* driver, EngineSensor* sensor);

      /**
       * @brief Sets target rpm using driver.
       */
      void Install(EngineDriver* driver);

      /**
       * @brief Read engine's actual rpm from sensor.
       */
      void Calibrate(EngineSensor* sensor);

      /**
       * @brief Attempt to reach to target rpm.
       * @param ratio A value between 0 (= stopped) and 1 (= running at max rpm).
       */
      int AdjustRPM(float ratio) const;

      /**
       * @brief Returns actual engine's speed in rpm.
       */
      int RPM() const;

      /**
       * @brief Changes rotaions direction of the engine.
       */
      int ChangeDirection(RotationDirection direction) const;

      /**
       * @brief Returns actual engine's rotation direction.
       */
      RotationDirection Direction() const;

    private:
      const int maxRPM;

      EngineDriver* driver;
      EngineSensor* sensor;
  };
}

#endif //ENGINE_H

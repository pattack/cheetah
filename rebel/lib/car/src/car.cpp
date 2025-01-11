//
// Created by pouyan on 1/3/25.
//

#include <math.h>

#include <engine.h>
#include <car.h>

namespace Rebel {
  Car::Car(Engine* engine): engine(engine) {}

  int Car::Speed() const {
    const float tireRadius = 1;
    const float tireCircumference = 2 * M_PI * tireRadius;
    const float gearRatio = 1;
    const float finalDriveRatio = 1;

    return (this->engine->RPM() * int(tireCircumference * 60)) / int(gearRatio * finalDriveRatio * 1000);
  }

  int Car::PushThrottle(float pressure) const {
    return this->engine->AdjustRPM(pressure);
  }

  int Car::ReleaseThrottle() const {
    return this->engine->AdjustRPM(static_cast<float>(RPM::Stopped));
  }
}

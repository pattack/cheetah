//
// Created by pouyan on 1/3/25.
//

#ifndef REBEL_CAR_H
#define REBEL_CAR_H

class Car {
  private:
    int engineRPM;

  public:
    /**
     * @brief Returns actual car engine's speed in rpm.
     */
    int EngineRPM() const;

    /**
     * @brief Speeds up the car.
     * @param throttle A value between 0 and 1.
     * @throw std::invalid_argument if throttle is negative
     */
    void Accelerate(float throttle);
};

#endif //REBEL_CAR_H
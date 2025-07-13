//
// Created by pouyan on 1/3/25.
//

#include <stdio.h>
#include <unity.h>

#include <rebel/car/engine.hpp>
#include <rebel/car/car.hpp>

void setUp(void) {}

void tearDown(void) {}

void test_car_accelerate(void) {
  Rebel::Car::Engine* engine = new Rebel::Car::Engine(1000);
  const Rebel::Car::Car car(engine);

  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.Speed(), __LINE__, "expected car to be stopped");
  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.PushThrottle(0.1), __LINE__, "expected no error while pushing throttle");
  UNITY_TEST_ASSERT_EQUAL_UINT(37, car.Speed(), __LINE__, "expected car to be running at 37 km/h");
  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.ReleaseThrottle(), __LINE__, "expected no error while releasing throttle");
  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.Speed(), __LINE__, "expected car to be stopped");
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_car_accelerate);

  return UNITY_END();
}

int main(void) {
  return runUnityTests();
}

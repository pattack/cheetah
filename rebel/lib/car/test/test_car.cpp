//
// Created by pouyan on 1/3/25.
//

#include <stdio.h>
#include <unity.h>

#include <engine.h>
#include <car.h>

void setUp(void) {
  printf("Setting up car tests\n");
}

void tearDown(void) {
}

void test_car_accelerate(void) {
  Rebel::Engine* engine = new Rebel::Engine(1000);
  Rebel::Car car(engine);

  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.Speed(), __LINE__, "expected car to be stopped");
  car.PushThrottle(0.1);

  UNITY_TEST_ASSERT_EQUAL_UINT(37, car.Speed(), __LINE__, "expected car to be running at 37 km/h");
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_car_accelerate);

  return UNITY_END();
}

int main(void) {
  return runUnityTests();
}

//
// Created by pouyan on 1/3/25.
//

#include <stdio.h>
#include <unity.h>

#include "car.h"

void setUp(void) {
  printf("Setting up car tests\n");
}

void tearDown(void) {
}

void test_car_accelerate(void) {
  Car car;

  UNITY_TEST_ASSERT_EQUAL_UINT(0, car.EngineRPM(), __LINE__, "expected car to be stopped");
  car.Accelerate(0.1);

  UNITY_TEST_ASSERT_GREATER_THAN_UINT(0, car.EngineRPM(), __LINE__, "expected car to be running");
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_car_accelerate);

  return UNITY_END();
}

void setup(void) {
  runUnityTests();
}

void loop(void) {}
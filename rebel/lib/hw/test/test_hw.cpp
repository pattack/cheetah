//
// Created by pouyan on 1/13/25.
//

#include <stdio.h>
#include <unity.h>

#include <pwm_on_bus.h>

void setUp(void) {}

void tearDown(void) {}

void test_hw_foo(void) {
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_hw_foo);

  return UNITY_END();
}

int main(void) {
  return runUnityTests();
}

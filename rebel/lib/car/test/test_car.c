//
// Created by pouyan on 1/3/25.
//

#include <unity.h>

void setUp(void) {
}

void tearDown(void) {
}

void test_car_ingnition(void) {
  UNITY_TEST_ASSERT_EQUAL_UINT(1, 2, 14, "Intentionally failing test to sanity check the test setup");
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_car_ingnition);

  return UNITY_END();
}

int main(void) {
  return runUnityTests();
}

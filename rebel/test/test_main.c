//
// Created by pouyan on 1/3/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unity.h>
#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>
#include <simavr/sim_io.h>
#include <simavr/sim_interrupts.h>
#include <simavr/avr_ioport.h>

#include "test_main.h"

struct {
  const char* name;
  uint32_t freq;
  const char* fwPath;
} dut = {
  .name = "atmega328p",
  .freq = 8e+6L, // 8MHz
  .fwPath = FIRMWARE_PATH,
};

avr_t *mcu;

void setUp(void) {
  printf("Making MCU '%s'...\n", dut.name);

  mcu = avr_make_mcu_by_name(dut.name);
  if (!mcu) {
    fprintf(stderr, "MCU '%s' not known\n", dut.name);

    exit(EXIT_FAILURE);
  }

  mcu->frequency = dut.freq;
  printf("Initializing MCU...\n");
  avr_init(mcu);
  elf_firmware_t f;
  memset(&f, 0, sizeof(f));
  printf("Reading firmware from %s...\n", dut.fwPath);

  if (elf_read_firmware(dut.fwPath, &f) < 0) {
    fprintf(stderr, "Failed to read firmware\n");

    exit(EXIT_FAILURE);
  }
  printf("Loading firmware...\n");
  avr_load_firmware(mcu, &f);
  printf("Firmware loaded successfully.\n");

  // todo: load vcd

  printf("AVR simulator setup completed.\n");
}

void tearDown(void) {
}

void test_foo(void) {
  UNITY_TEST_ASSERT_EQUAL_UINT(1, 2, 1, "Intentionally failing test to sanity check the test setup");
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_foo);

  return UNITY_END();
}

int main(void) {
  return runUnityTests();
}
#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

#define SPEED_CTRL_ADDR 0x40
#define MOTOR_L_ADDR 0x06
#define MOTOR_R_ADDR 0x0A

void wakeUpPwmDriver();
void lockOnSpeed(uint8_t motor, float ratio);

struct pwm {
	uint16_t on;
	uint16_t off;

  void writeOnWire() {
    Wire.write(on & 0xFF); // Low Byte of ON
    Wire.write((on >> 8) & 0xFF); // High Byte of ON
    Wire.write(off & 0xFF); // Low Byte of OFF
    Wire.write((off >> 8) & 0xFF); // High Byte of OFF
  }
};

pwm speed(float ratio);

void setup() {
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);

  wakeUpPwmDriver();
}

void loop() {
  lockOnSpeed(MOTOR_L_ADDR, 0.75);
  lockOnSpeed(MOTOR_R_ADDR, 0.25);
  delay(20000);

  lockOnSpeed(MOTOR_L_ADDR, 0.1);
  delay(5000);

  lockOnSpeed(MOTOR_L_ADDR, 0);
  lockOnSpeed(MOTOR_R_ADDR, 0);
  delay(10000);
}

void wakeUpPwmDriver() {
  Wire.beginTransmission(SPEED_CTRL_ADDR);
  Wire.write(0x00); // Mode1
  Wire.write(0x20); // Mode2
  Wire.endTransmission(true);
}

void lockOnSpeed(uint8_t motor, float ratio) {
  Wire.beginTransmission(SPEED_CTRL_ADDR);
  Wire.write(motor); // Which motor
  speed(ratio).writeOnWire(); // Wire PWM details
  Wire.endTransmission(true);
}

pwm speed(float ratio) {
	pwm res = {0, (uint16_t)(ratio * 4096)};

	return res;
}

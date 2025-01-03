#include <stdint.h>
#include <util/delay.h>

#include <avr/io.h>

#include <i2c.h>

typedef struct {
	uint16_t on;
	uint16_t off;
} pwm;

pwm speed(float ratio);

#define USI_SEND 0

#define SPEED_CTRL_ADDR 0x40
#define MOTOR_L_ADDR 0x06
#define MOTOR_R_ADDR 0x0A

int main(void) {
	I2C_Master_Initialize();

	uint8_t buff[10];

  // MODE1 = 0x20
	buff[0] = (SPEED_CTRL_ADDR << TWI_ADR_BITS) | USI_SEND;
	buff[1] = 0x00;
	buff[2] = 0x20;
	I2C_Start_Read_Write(buff, 3);
	I2C_Master_Stop();

	pwm s;

  s = speed(0.75);
	buff[0] = (SPEED_CTRL_ADDR << TWI_ADR_BITS) | USI_SEND;
	buff[1] = MOTOR_L_ADDR;
	buff[2] = (uint8_t)(s.on & 0xFF);
	buff[3] = (uint8_t)((s.on >> 8) & 0xFF);
	buff[4] = (uint8_t)(s.off & 0xFF);
	buff[5] = (uint8_t)((s.off >> 8) & 0xFF);
	I2C_Start_Read_Write(buff, 6);
	I2C_Master_Stop();

	s = speed(0.25);
	buff[0] = (SPEED_CTRL_ADDR << TWI_ADR_BITS) | USI_SEND;
	buff[1] = MOTOR_R_ADDR;
	buff[2] = (uint8_t)(s.on & 0xFF);
	buff[3] = (uint8_t)((s.on >> 8) & 0xFF);
	buff[4] = (uint8_t)(s.off & 0xFF);
	buff[5] = (uint8_t)((s.off >> 8) & 0xFF);
	I2C_Start_Read_Write(buff, 6);
	I2C_Master_Stop();

	_delay_ms(20000);

	s = speed(0.1);
	buff[0] = (SPEED_CTRL_ADDR << TWI_ADR_BITS) | USI_SEND;
	buff[1] = MOTOR_L_ADDR;
	buff[2] = (uint8_t)(s.on & 0xFF);
	buff[3] = (uint8_t)((s.on >> 8) & 0xFF);
	buff[4] = (uint8_t)(s.off & 0xFF);
	buff[5] = (uint8_t)((s.off >> 8) & 0xFF);
	I2C_Start_Read_Write(buff, 6);
	I2C_Master_Stop();

	for (;;) {
		_delay_ms(500);
	}

	return 0;
}

pwm speed(float ratio) {
	pwm res = {0, (uint16_t)(ratio * 4096)};

	return res;
}

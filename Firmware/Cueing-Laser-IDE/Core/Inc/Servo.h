#ifndef __SERVO_H__
#define __SERVO_H__
#include <stm32f446xx.h>
#include <stm32f4xx_hal.h>

void Servo1_setAngle(uint8_t angle);
void Servo2_setAngle(uint8_t angle);
void Servo3_setAngle(uint8_t angle);
void Servo4_setAngle(uint8_t angle);
#endif
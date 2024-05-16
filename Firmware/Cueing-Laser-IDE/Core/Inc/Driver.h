/*
*
* Driver.h 
* Created on: April/15/2024
* Author: trietmt9 
*
*/

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stm32f446xx.h>
#include <stm32f4xx_hal.h>


void LED1_Brightness(uint8_t brightness);
void LED2_Brightness(uint8_t brightness);
void LED3_Brightness(uint8_t brightness);
void Vibrator_Control(uint8_t pwm);
#endif
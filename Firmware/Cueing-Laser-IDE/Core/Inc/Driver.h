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

typedef enum
{
    MIN = 20,
    LOW_BEAM = 30,
    MID_BEAM = 40,
    HIGH_BEAM = 80,
    MAX_BEAM = 100
}PWM_signal;

void LED1_Control(PWM_signal brightness);
void LED2_Control(PWM_signal brightness);
void LED3_Control(PWM_signal brightness);
void Vibrator_Control(PWM_signal pwm);
#endif
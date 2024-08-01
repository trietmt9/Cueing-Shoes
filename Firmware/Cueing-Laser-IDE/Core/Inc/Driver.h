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
}Brightness;

typedef enum
{
    FOG_NOT_DETECTED = 0,
    WEAK = 70,
    MEDIUM = 80, 
    STRONG = 100
}Vibrate_percentage;

void Laser_Brightness(Brightness brightness);
void Vibrator_Control(Vibrate_percentage pwm);
#endif
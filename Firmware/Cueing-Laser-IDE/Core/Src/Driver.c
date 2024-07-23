/**
 * @file
 * @brief Driver file for controlling LEDs and Vibrator using PWM.
 */

/**
 * @defgroup Driver_Module Driver Module
 * @ingroup STM32F4xx_HAL_Driver
 * @brief This file contains functions that allow you to control LEDs and Vibrator using PWM.
*/
#include "Driver.h"
extern TIM_TypeDef htim3;

/**
 * @brief Controls the brightness of LED1.
 *
 * @param[in] brightness The brightness level of LED1.
 */
void Vibrator_Control(PWM_signal pwm)
{
    TIM3->CCR1 = pwm;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

/**
 * @brief Controls the brightness of LED2.
 *
 * @param[in] brightness The brightness level of LED2.
 */
void LED_Brightness(PWM_signal brightness)
{
    TIM3->CCR2 = brightness;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}


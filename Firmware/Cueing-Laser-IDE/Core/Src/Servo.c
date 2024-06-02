/**
 * @file servo_control.c
 * @brief Servo control functions
 *
 * This file contains functions to control the servos using PWM signals.
 *
 * @author Your Name
 * @date 2022-01-01
 */

#include<Servo.h>
extern TIM_TypeDef htim4;

/**
 * @brief Sets the angle for Servo 1.
 *
 * This function sets the angle for Servo 1 by calculating the corresponding PWM value and writing it to the TIM4 CCR1 register.
 *
 * @param angle The desired angle for Servo 1 in degrees.
 */
void Servo1_setAngle(angle_t angle) {
    uint8_t pwm;
    pwm = ((angle*10)/90)+5;
    TIM4->CCR1 = pwm;
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

/**
 * @brief Sets the angle for Servo 2.
 *
 * This function sets the angle for Servo 2 by calculating the corresponding PWM value and writing it to the TIM4 CCR2 register.
 *
 * @param angle The desired angle for Servo 2 in degrees.
 */
void Servo2_setAngle(angle_t angle) {
    uint8_t pwm;
    pwm = ((angle*10)/90)+5;
    TIM4->CCR2 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
}

/**
 * @brief Sets the angle for Servo 3.
 *
 * This function sets the angle for Servo 3 by calculating the corresponding PWM value and writing it to the TIM4 CCR3 register.
 *
 * @param angle The desired angle for Servo 3 in degrees.
 */
void Servo3_setAngle(angle_t angle) {
    uint8_t pwm;
    
    pwm = ((angle*10)/90)+5;
    TIM4->CCR3 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
}

/**
 * @brief Sets the angle for Servo 4.
 *
 * This function sets the angle for Servo 4 by calculating the corresponding PWM value and writing it to the TIM4 CCR4 register.
 *
 * @param angle The desired angle for Servo 4 in degrees.
 */
void Servo4_setAngle(angle_t angle) {
    uint8_t pwm;
    pwm = ((angle*10)/90)+5;
    TIM4->CCR4 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
}

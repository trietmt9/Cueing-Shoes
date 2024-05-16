#include<Servo.h>
extern TIM_TypeDef htim4;

void Servo1_setAngle(uint8_t angle)
{
    uint8_t pwm;
    pwm = (angle*10)/180;
    TIM4->CCR1 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
}

void Servo2_setAngle(uint8_t angle)
{
    uint8_t pwm;
    pwm = (angle*10)/180;
    TIM4->CCR2 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
}

void Servo3_setAngle(uint8_t angle)
{
    uint8_t pwm;
    pwm = (angle*10)/180;
    TIM4->CCR3 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
}

void Servo4_setAngle(uint8_t angle)
{
    uint8_t pwm;
    pwm = (angle*10)/180;
    TIM4->CCR4 = pwm;
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
}
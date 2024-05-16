#include <Driver.h>
extern TIM_TypeDef htim3;
void LED1_Brightness(uint8_t brightness)
{
    TIM3->CCR1 = brightness;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void LED2_Brightness(uint8_t brightness)
{
    TIM3->CCR2 = brightness;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void LED3_Brightness(uint8_t brightness)
{
    TIM3->CCR3 = brightness;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void Vibrator_Control(uint8_t pwm)
{
    TIM3->CCR4 = pwm;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}
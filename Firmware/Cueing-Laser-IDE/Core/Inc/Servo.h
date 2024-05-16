#ifndef __SERVO_H__
#define __SERVO_H__
#include <stm32f446xx.h>
#include <stm32f4xx_hal.h>

typedef enum 
{
    _0_DEGREE,
    _1_DEGREE,
    _2_DEGREE,
    _3_DEGREE,
    _4_DEGREE,
    _5_DEGREE,
    _6_DEGREE,
    _7_DEGREE,
    _8_DEGREE,
    _9_DEGREE,
    _10_DEGREE,
    _11_DEGREE,
    _12_DEGREE,
    _13_DEGREE,
    _14_DEGREE,
    _15_DEGREE,
    _16_DEGREE,
    _17_DEGREE,
    _18_DEGREE,
    _19_DEGREE,
    _20_DEGREE,
    _21_DEGREE,
    _22_DEGREE,
    _23_DEGREE,
    _24_DEGREE,
    _25_DEGREE,
    _26_DEGREE,
    _27_DEGREE,
    _28_DEGREE,
    _29_DEGREE,
    _30_DEGREE,
    _31_DEGREE,
    _32_DEGREE,
    _33_DEGREE,
    _34_DEGREE,
    _35_DEGREE,
    _36_DEGREE,
    _37_DEGREE,
    _38_DEGREE,
    _39_DEGREE,
    _40_DEGREE,
    _41_DEGREE,
    _42_DEGREE,
    _43_DEGREE,
    _44_DEGREE,
    _45_DEGREE,
    _46_DEGREE,
    _47_DEGREE,
    _48_DEGREE,
    _49_DEGREE,
    _50_DEGREE,
    _51_DEGREE,
    _52_DEGREE,
    _53_DEGREE,
    _54_DEGREE,
    _55_DEGREE,
    _56_DEGREE,
    _57_DEGREE,
    _58_DEGREE,
    _59_DEGREE,
    _60_DEGREE,
    _61_DEGREE,
    _62_DEGREE,
    _63_DEGREE,
    _64_DEGREE,
    _65_DEGREE,
    _66_DEGREE,
    _67_DEGREE,
    _68_DEGREE,
    _69_DEGREE,
    _70_DEGREE,
    _71_DEGREE,
    _72_DEGREE,
    _73_DEGREE,
    _74_DEGREE,
    _75_DEGREE,
    _76_DEGREE,
    _77_DEGREE,
    _78_DEGREE,
    _79_DEGREE,
    _80_DEGREE,
    _81_DEGREE,
    _82_DEGREE,
    _83_DEGREE,
    _84_DEGREE,
    _85_DEGREE,
    _86_DEGREE,
    _87_DEGREE,
    _88_DEGREE,
    _89_DEGREE,
    _90_DEGREE,
    _91_DEGREE,
    _92_DEGREE,
    _93_DEGREE,
    _94_DEGREE,
    _95_DEGREE,
    _96_DEGREE,
    _97_DEGREE,
    _98_DEGREE,
    _99_DEGREE,
    _100_DEGREE,
    _101_DEGREE,
    _102_DEGREE,
    _103_DEGREE,
    _104_DEGREE,
    _105_DEGREE,
    _106_DEGREE,
    _107_DEGREE,
    _108_DEGREE,
    _109_DEGREE,
    _110_DEGREE,
    _111_DEGREE,
    _112_DEGREE,
    _113_DEGREE,
    _114_DEGREE,
    _115_DEGREE,
    _116_DEGREE,
    _117_DEGREE,
    _118_DEGREE,
    _119_DEGREE,
    _120_DEGREE,
    _121_DEGREE,
    _122_DEGREE,
    _123_DEGREE,
    _124_DEGREE,
    _125_DEGREE,
    _126_DEGREE,
    _127_DEGREE,
    _128_DEGREE,
    _129_DEGREE,
    _130_DEGREE,
    _131_DEGREE,
    _132_DEGREE,
    _133_DEGREE,
    _134_DEGREE,
    _135_DEGREE,
    _136_DEGREE,
    _137_DEGREE,
    _138_DEGREE,
    _139_DEGREE,
    _140_DEGREE,
    _141_DEGREE,
    _142_DEGREE,
    _143_DEGREE,
    _144_DEGREE,
    _145_DEGREE,
    _146_DEGREE,
    _147_DEGREE,
    _148_DEGREE,
    _149_DEGREE,
    _150_DEGREE,
    _151_DEGREE,
    _152_DEGREE,
    _153_DEGREE,
    _154_DEGREE,
    _155_DEGREE,
    _156_DEGREE,
    _157_DEGREE,
    _158_DEGREE,
    _159_DEGREE,
    _160_DEGREE,
    _161_DEGREE,
    _162_DEGREE,
    _163_DEGREE,
    _164_DEGREE,
    _165_DEGREE,
    _166_DEGREE,
    _167_DEGREE,
    _168_DEGREE,
    _169_DEGREE,
    _170_DEGREE,
    _171_DEGREE,
    _172_DEGREE,
    _173_DEGREE,
    _174_DEGREE,
    _175_DEGREE,
    _176_DEGREE,
    _177_DEGREE,
    _178_DEGREE,
    _179_DEGREE,
    _180_DEGREE
}angle_t;
void Servo1_setAngle(uint8_t angle);
void Servo2_setAngle(uint8_t angle);
void Servo3_setAngle(uint8_t angle);
void Servo4_setAngle(uint8_t angle);
#endif
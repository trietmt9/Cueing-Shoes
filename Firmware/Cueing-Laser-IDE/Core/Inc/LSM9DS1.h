/*
*
* LSM9DS1.h 
* Created on: June/20/2024
* Author: trietmt9 
*
*/
#ifndef INC_LSM9DS_H_
#define INC_LSM9DS_H_
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#define SPI_TIMEOUT                 1000
/****** define Accelerometer and gyroscope register address value ******/
#define ACT_THS                     0x04U
#define ACT_DUR                     0x05U
#define INT_GEN_CFG_XL              0x06U
#define INT_GEN_THS_X_XL            0x07U
#define INT_GEN_THS_Y_XL            0x08U
#define INT_GEN_THS_Z_XL            0x09U
#define INT_GEN_DUR_XL              0x0AU
#define REFERENCE_G                 0x0BU
#define INT1_CTRL                   0x0CU
#define INT2_CTRL                   0x0DU
#define WHO_AM_I                    0x0FU  
#define CTRL_REG1_G                 0x10U
#define CTRL_REG2_G                 0x11U
#define CTRL_REG3_G                 0x12U
#define ORIENT_CFG_G                0x13U
#define INT_GEN_SRC_G               0x14U
#define OUT_TEMP_L                  0x15U
#define OUT_TEMP_H                  0x16U
#define STATUS_REG_1                0x17U
#define OUT_X_L_G                   0x18U
#define OUT_X_H_G                   0x19U
#define OUT_Y_L_G                   0x1AU
#define OUT_Y_H_G                   0x1BU
#define OUT_Z_L_G                   0x1CU
#define OUT_Z_H_G                   0x1DU
#define CTRL_REG4                   0x1EU
#define CTRL_REG5_XL                0x1FU
#define CTRL_REG6_XL                0x20U
#define CTRL_REG7_XL                0x21U
#define CTRL_REG8                   0x22U
#define CTRL_REG9                   0x23U
#define CTRL_REG10                  0x24U
#define INT_GEN_SRC_XL              0x26U
#define STATUS_REG_2                0x27U
#define OUT_X_L_XL                  0x28U
#define OUT_X_H_XL                  0x29U
#define OUT_Y_L_XL                  0x2AU
#define OUT_Y_H_XL                  0x2BU
#define OUT_Z_L_XL                  0x2CU
#define OUT_Z_H_XL                  0x2DU
#define FIFO_CTRL                   0x2EU
#define FIFO_SRC                    0x2FU
#define INT_GEN_CFG_G               0x30U
#define INT_GEN_THS_XH_G            0x31U
#define INT_GEN_THS_XL_G            0x32U
#define INT_GEN_THS_YH_G            0x33U
#define INT_GEN_THS_YL_G            0x34U
#define INT_GEN_THS_ZH_G            0x35U
#define INT_GEN_THS_ZL_G            0x36U
#define INT_GEN_DUR_G               0x37U

    
/****** define Magnetic sensor register address value ******/

#define OFFSET_X_REG_L_M            0x05U
#define OFFSET_X_REG_H_M            0x06U
#define OFFSET_Y_REG_L_M            0x07U
#define OFFSET_Y_REG_H_M            0x08U
#define OFFSET_Z_REG_L_M            0x09U
#define OFFSET_Z_REG_H_M            0x0AU
#define WHO_AM_I_M                  0x0FU
#define CTRL_REG1_M                 0x20U
#define CTRL_REG2_M                 0x21U
#define CTRL_REG3_M                 0x22U
#define CTRL_REG4_M                 0x23U
#define CTRL_REG5_M                 0x24U
#define STATUS_REG_M                0x27U
#define OUT_X_L_M                   0x28U
#define OUT_X_H_M                   0x29U
#define OUT_Y_L_M                   0x2AU
#define OUT_Y_H_M                   0x2BU
#define OUT_Z_L_M                   0x2CU
#define OUT_Z_H_M                   0x2DU
#define INT_CFG_M                   0x30U
#define INT_SRC_M                   0x31U
#define INT_THS_L_M                 0x32U
#define INT_THS_H_M                 0x33U

/****** Create structure data type for the Sensor ******/
typedef struct
{
    struct 
    {
        int16_t Gx_RAW;
        int16_t Gy_RAW;
        int16_t Gz_RAW;
        int16_t Ax_RAW;
        int16_t Ay_RAW;
        int16_t Az_RAW;
        int16_t Mx_RAW;
        int16_t My_RAW;
        int16_t Mz_RAW;
    }RawData_t;

    struct 
    {
        int16_t Gx;
        int16_t Gy;
        int16_t Gz;
        int16_t Ax;
        int16_t Ay;
        int16_t Az;
        int16_t Mx;
        int16_t My;
        int16_t Mz;
    }Data_t;

}data_t;
/* Gyro Output data rate selection */
typedef enum 
{
    ODR_G_PD,      // Power down 
    ODR_G_14_9_Hz, // 14.9 Hz
    ODR_G_59_5_Hz, // 59.5 Hz
    ODR_G_119_Hz,  // 119 Hz 
    ODR_G_238_Hz,  // 238 Hz
    ODR_G_476_Hz,  // 476 Hz
    ODR_G_952_Hz  // 952 Hz
}Gyro_OP_DataRate_t;



/* Gyroscope full-scale selection*/
typedef enum 
{
    FS_G_245, // 250 dps: 00
    FS_G_500, // 500 dps: 01 
    FS_G_NOT_AVAILABLE, // Not available : 10
    FS_G_2000 // 2000 dps: 11
} Gyro_Scale_t;

/* Output data rate and power mode selection */
typedef enum 
{   
    ODR_XL_PD, // Power Down
    ODR_XL_10_Hz, // 10 Hz
    ODR_XL_50_Hz, // 50 Hz
    ODR_XL_119Hz, // 119Hz 
    ODR_XL_238Hz, // 238Hz
    ODR_XL_476Hz, // 476Hz
    ODR_XL_952Hz  // 952Hz
}Accel_OP_DataRate_t;

/* Low pass cutoff frequency in high resolution mode */
typedef enum
{
    DCF_DIV_50_Hz,      // ODR divide for 50
    DCF_DIV_100,        // ODR divide for 100
    DCF_DIV_9,          // ODR divide for 9
    DCF_DIV_400,        // ODR divide for 400
}LPF_CutOff_Freq;

typedef enum 
{
	A_ABW_408, // 408 Hz (0x0)
	A_ABW_211, // 211 Hz (0x1)
	A_ABW_105, // 105 Hz (0x2)
	A_ABW_50,  //  50 Hz (0x3)
}Accel_abw;
/* I2C bus enable */
typedef enum
{
    I2C_EN,
    I2C_DIS
}I2C_DISABLE;

/* Magnometer Scale*/
typedef enum 
{
	FS_M__4GS,  // 00:  4Gs
	FS_M__8GS,  // 01:  8Gs
	FS_M__12GS, // 10:  12Gs
	FS_M__16GS, // 11:  16Gs
}mag_scale;

typedef struct 
{   
    uint8_t enabled; 
    uint16_t scale; 
    uint8_t sampleRate; 
    uint8_t bandwidth;
}Gyro_settings;

typedef struct
{
    uint8_t enabled;
    uint16_t scale;
    uint8_t sampleRate;
    uint8_t bandwidth;
}XL_settings;

typedef struct
{
    uint8_t enabled; 
    uint16_t scale;
    uint8_t sampleRate;
}Mag_settings;

void LSM9DS1_Init(SPI_HandleTypeDef* SPI_x);
void IsWhoAmI(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i);
void LSM9DS1_Read(SPI_HandleTypeDef *SPIx, data_t *pData);
float LSMD9S_Read_Mag();
#endif

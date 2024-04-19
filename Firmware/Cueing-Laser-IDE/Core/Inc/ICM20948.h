#ifndef __ICM20948__H
#define __ICM20948__H
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "stdio.h"

/*********************** GENERAL MACROS ***********************/
#define SPI_TIMEOUT                             100
/*********************** GYROSCOPE, ACCELEROMETER AND TEMPERATURE REGISTERS MACROS ***********************/
        /************* USER BANK 0 REGISTERS MAP *************/
#define WHO_AM_I                                0x00U 
#define USER_CTRL                               0x03U
#define LP_CONFIG                               0x05U
#define PWR_MGMT_1                              0x06U
#define PWR_MGMT_2                              0x07U
#define INT_PIN_CFG                             0x0FU
#define INT_ENABLE                              0x10U
#define INT_ENABLE_1                            0x11U
#define INT_ENABLE_2                            0x12U
#define INT_ENABLE_3                            0x13U
#define I2C_MST_STATUS                          0x17U
#define INT_STATUS                              0x19U   
#define INT_STATUS_1                            0x1AU
#define INT_STATUS_2                            0x1BU
#define INT_STATUS_3                            0x1CU
#define DELAY_TIMEH                             0x28U
#define DELAY_TIMEL                             0x29U
#define ACCEL_XOUT_H                            0x2DU
#define ACCEL_XOUT_L                            0x2EU
#define ACCEL_YOUT_H                            0x2FU
#define ACCEL_YOUT_L                            0x30U
#define ACCEL_ZOUT_H                            0x31U
#define ACCEL_ZOUT_L                            0x32U
#define GYRO_XOUT_H                             0x33U
#define GYRO_XOUT_L                             0x34U
#define GYRO_YOUT_H                             0x35U
#define GYRO_YOUT_L                             0x36U
#define GYRO_ZOUT_H                             0x37U
#define GYRO_ZOUT_L                             0x38U
#define TEMP_OUT_H                              0x39U
#define TEMP_OUT_L                              0x3AU
#define EXTI_SLV_SENS_DATA_00                   0x3BU
#define EXTI_SLV_SENS_DATA_01                   0x3CU
#define EXTI_SLV_SENS_DATA_02                   0x3DU
#define EXTI_SLV_SENS_DATA_03                   0x3EU
#define EXTI_SLV_SENS_DATA_04                   0x3FU
#define EXTI_SLV_SENS_DATA_05                   0x40U
#define EXTI_SLV_SENS_DATA_06                   0x41U
#define EXTI_SLV_SENS_DATA_07                   0x42U
#define EXTI_SLV_SENS_DATA_08                   0x43U
#define EXTI_SLV_SENS_DATA_09                   0x44U
#define EXTI_SLV_SENS_DATA_10                   0x45U
#define EXTI_SLV_SENS_DATA_11                   0x46U
#define EXTI_SLV_SENS_DATA_12                   0x47U
#define EXTI_SLV_SENS_DATA_13                   0x48U
#define EXTI_SLV_SENS_DATA_14                   0x49U
#define EXTI_SLV_SENS_DATA_15                   0x4AU
#define EXTI_SLV_SENS_DATA_16                   0x4BU
#define EXTI_SLV_SENS_DATA_17                   0x4CU
#define EXTI_SLV_SENS_DATA_18                   0x4DU
#define EXTI_SLV_SENS_DATA_19                   0x4EU
#define EXTI_SLV_SENS_DATA_20                   0x4FU
#define EXTI_SLV_SENS_DATA_21                   0x50U
#define EXTI_SLV_SENS_DATA_22                   0x51U
#define EXTI_SLV_SENS_DATA_23                   0x52U
#define FIFO_EN_1                               0x66U
#define FIFO_EN_2                               0x67U
#define FIFO_RST                                0x68U
#define FIFO_MODE                               0x69U
#define FIFO_COUNTH                             0x70U
#define FIFO_COUNTL                             0x71U
#define FIFO_R_W                                0x72U
#define DATA_RDY_STATUS                         0x74U
#define FIFO_CFG                                0x76U
#define REG_BANK_SEL                            0x7FU

/************* USER BANK 1 REGISTERS MAP *************/
#define SELF_TEST_X_GYRO                        0x02U
#define SELF_TEST_Y_GYRO                        0x03U
#define SELF_TEST_Z_GYRO                        0x04U
#define SELF_TEST_X_ACCEL                       0x0EU
#define SELF_TEST_Y_ACCEL                       0x0FU
#define SELF_TEST_Z_ACCEL                       0x10U
#define XA_OFFS_H                               0x14U
#define XA_OFFS_L                               0x15U
#define YA_OFFS_H                               0x17U
#define YA_OFFS_L                               0x18U
#define ZA_OFFS_H                               0x1AU
#define ZA_OFFS_L                               0x1BU 
#define TIMEBASE_CORRECTION_PLL                 0x28U

/************* USER BANK 2 REGISTERS MAP *************/

#define GYRO_SMPLRT_DIV                         0x00U
#define GYRO_CONFIG_1                           0x01U
#define GYRO_CONFIG_2                           0x02U
#define XG_OFFS_USRH                            0x03U
#define XG_OFFS_USRL                            0x04U
#define YG_OFFS_USRH                            0x05U
#define YG_OFFS_USRL                            0x06U
#define ZG_OFFS_USRH                            0x07U
#define ZG_OFFS_USRL                            0x08U   
#define ODR_ALIGN_EN                            0x09U
#define ACCEL_SMPLRT_DIV_1                      0x10U
#define ACCEL_SMPLRT_DIV_2                      0x11U
#define ACC_INTEL_CTRL                          0x12U
#define ACC_WOM_THR                             0x13U
#define ACCEL_CONFIG_1                          0x14U
#define ACCEL_CONFIG_2                          0x15U
#define FSYNC_CONFIG                            0x52U
#define TEMP_CONFIG                             0x53U
#define MOD_CTRL_USR                            0x54U

/************* USER BANK 3 REGISTERS MAP *************/
#define I2C_MST_ODR_CONFIG                      0x00U
#define I2C_MST_CTRL                            0x01U
#define I2C_MST_DELAY_CTRL                      0x02U
#define I2C_SLV0_ADDR                           0x03U
#define I2C_SLV0_REG                            0x04U
#define I2C_SLV0_CTRL                           0x05U
#define I2C_SLV0_DO                             0x06U
#define I2C_SLV1_ADDR                           0x07U
#define I2C_SLV1_REG                            0x08U
#define I2C_SLV1_CTRL                           0x09U
#define I2C_SLV1_DO                             0x0AU
#define I2C_SLV2_ADDR                           0x0BU
#define I2C_SLV2_REG                            0x0CU
#define I2C_SLV2_CTRL                           0x0DU
#define I2C_SLV2_DO                             0x0EU
#define I2C_SLV3_ADDR                           0x0FU
#define I2C_SLV3_REG                            0x10U
#define I2C_SLV3_CTRL                           0x11U
#define I2C_SLV3_DO                             0x12U
#define I2C_SLV4_ADDR                           0x13U
#define I2C_SLV4_REG                            0x14U
#define I2C_SLV4_CTRL                           0x15U
#define I2C_SLV4_DO                             0x16U
#define I2C_SLV4_DI                             0x17U 


/*============== USER BANK 0 DESCRIPTIONS MACROS ==============*/
#define ICM20948_AVAILABLE                      0xEAU

            /*====== USER CONTROL REGISTER ======*/
#define I2C_MST_RST                             0x01U                                                         
#define SRAM_RST                                0x02U 
#define DMP_RST                                 0x03U 
#define I2C_IF_DIS                              0x04U
#define I2C_MST_EN                              0x05U
#define FIFO_EN                                 0x06U
#define DMP_EN                                  0x07U

            /*====== LOW POWER CONFIGURATION REGISTER ======*/

#define GYRO_CYCLE                              0x01U
#define ACCEL_CYCLE                             0x02U
#define I2C_MST_CYCLE                           0x03U

            /*====== POWER MANAGEMENT 1 REGISTER ======*/
#define CLKSEL                                  0x00U
#define TEMP_DIS                                0x03U
#define LP_EN                                   0x05U
#define SLEEP                                   0x06U
#define DEVICE_RESET                            0x07U

            /*====== POWER MANAGEMENT 2 REGISTER ======*/
#define DISABLE_ACCEL                           0x00U
#define DISABLE_GYRO                            0x03U

            /*====== INTERRUPTS PIN CONFIG REGISTER ======*/
#define BYPASS_EN                               0x01U
#define FSYNC_INT_MODE_EN                       0x02U
#define ACTL_FSYNC                              0x03U
#define INT_ANYRD_2CLEAR                        0x04U
#define INT1_LATCH_EN                           0x05U
#define INT1_OPEN                               0x06U
#define INT1_ACTL                               0x07U

            /*====== INTERRUPTS ENABLE REGISTER ======*/
#define I2C_MST_INT_EN                          0x00U
#define DMP_INT1_EN                             0x01U
#define PLL_RDY_EN                              0x02U
#define WOM_INT_EN                              0x03U
#define REG_WOF_EN                              0x07U   

            /*====== INTERRUPTS ENABLE 1 REGISTER ======*/
#define RAW_DATA_0_RDY_EN                       0x00U

            /*====== INTERRUPTS ENABLE 2 REGISTER ======*/
#define FIFO_OVERFLOW_EN                        0x00U

            /*====== INTERRUPTS ENABLE 3 REGISTER ======*/
#define FIFO_WM_EN                              0x00U

            /*====== I2C MASTER STATUS REGISTER ======*/
#define I2C_SLV0_NACK                           0x00U
#define I2C_SLV1_NACK                           0x01U
#define I2C_SLV2_NACK                           0x02U
#define I2C_SLV3_NACK                           0x03U
#define I2C_SLV4_NACK                           0x04U
#define I2C_LOST_ARB                            0x05U
#define I2C_SLV4_DONE                           0x06U
#define PASS_THROUGH                            0x07U

            /*====== INTERRUPTS STATUS REGISTER ======*/
#define I2C_MST_INT                             0x00U
#define DMP_INT1                                0x01U
#define PLL_RDY_INT                             0x02U
#define WOM_INT                                 0x03U

            /*====== INTERRUPTS STATUS 1 REGISTER ======*/
#define RAW_DATA_0_RDY                          0x00U

            /*====== INTERRUPTS STATUS 2 REGISTER ======*/
#define FIFO_OVERFLOW                           0x00U

            /*====== INTERRUPTS STATUS 3 REGISTER ======*/
#define FIFO_WM_INT                             0x00U

            /*====== DELAY TIME HIGH REGISTER ======*/
#define DELAY_TIME_H                            0x00U

            /*====== DELAY TIME LOW REGISTER ======*/
#define DELAY_TIME_L                            0x00U

            /*====== FIRST IN FIRST OUT ENABLE 1 REGISTER ======*/
#define SLV_1_FIFO_EN                           0x00U
#define SLV_2_FIFO_EN                           0x01U
#define SLV_3_FIFO_EN                           0x02U
#define SLV_4_FIDO_EN                           0x03U

            /*====== FIRST IN FIRST OUT ENABLE 2 REGISTER ======*/
#define TEMP_FIFO_EN                            0x00U
#define GYRO_X_FIFO_EN                          0x01U
#define GYRO_Y_FIFO_EN                          0x02U
#define GYRO_Z_FIFO_EN                          0x03U
#define ACCEL_FIFO_EN                           0x04U

            /*====== FIRST IN FIRST OUT RESET REGISTER ======*/
#define FIFO_RESET                              0x00U

            /*====== FIRST IN FIRST OUT MODE REGISTER ======*/
#define FIFO_MODE_REG                           0x00U

            /*====== FIRST IN FIRST OUT COUNT HIGH REGISTER ======*/
#define FIFO_CNT_H                              0x00U

            /*====== FIRST IN FIRST OUT COUNT LOW REGISTER ======*/
#define FIFO_CNT_L                              0x00U

            /*====== FIRST IN FIRST OUT READ WRITE REGISTER ======*/
#define FIFO_R_W_REG                            0x00U

            /*====== INTERRUPT SOURCE REGISTER ======*/
#define INT_SOURCE                              0x00U

            /*====== DATA READY STATUS REGISTER ======*/
#define RAW_DATA_RDY                            0x00U   

            /*====== FIRST IN FIRST OUT CONFIG REGISTER ======*/
#define FIFO_CFG_REG                            0x00U

            /*====== USER BANK SELECT REGISTER ======*/
#define USER_BANK                               0x04U   

/*============== USER BANK 1 R/W DESCRIPTIONS MACROS ==============*/
            /*====== SELF TEST X AXIS GYROSCOPE REGISTER ======*/
#define XG_ST_DATA                              0x00U

            /*====== SELF TEST Y AXIS GYROSCOPE REGISTER ======*/
#define YG_ST_DATA                              0x00U

            /*====== SELF TEST Z AXIS GYROSCOPE REGISTER ======*/
#define ZG_ST_DATA                              0x00U

            /*====== SELF TEST X AXIS ACCELEROMETER REGISTER ======*/
#define XA_ST_DATA                              0x00U

            /*====== SELF TEST Y AXIS ACCELEROMETER REGISTER ======*/
#define YA_ST_DATA                              0x00U

            /*====== SELF TEST Z AXIS ACCELEROMETER REGISTER ======*/
#define ZA_ST_DATA                              0x00U

            /*====== ACCELEROMETER X AXIS OFFSET REGISTER ======*/
#define XA_OFFS_H_REG                           0x00U

            /*====== ACCELEROMETER X AXIS OFFSET REGISTER ======*/
#define XA_OFFS_L_REG                           0x01U

            /*====== ACCELEROMETER Y AXIS OFFSET REGISTER ======*/
#define YA_OFFS_H_REG                           0x00U

            /*====== ACCELEROMETER Y AXIS OFFSET REGISTER ======*/
#define YA_OFFS_L_REG                           0x01U

            /*====== ACCELEROMETER Z AXIS OFFSET REGISTER ======*/
#define ZA_OFFS_H_REG                           0x00U

            /*====== ACCELEROMETER Z AXIS OFFSET REGISTER ======*/
#define ZA_OFFS_L_REG                           0x01U

            /*====== TIME BASE CORRECTION PLL CONTROL REGISTER ======*/
#define TBC_PLL                                 0x00U

/*============== USER BANK 2 R/W DESCRIPTIONS MACROS ==============*/
            /*====== GYROSCOPE SAMPLE RATE DIVIDE REGISTER ======*/
#define GYRO_SMPLRT_DIV_REG                      0x00U

            /*====== GYROSCOPE CONFIGURATIONS 1 REGISTER ======*/           
#define GYRO_FCHOICE                            0x00U
#define GYRO_FS_SEL                             0x01U
#define GYRO_DLPFCFG                            0x03U

            /*====== GYROSCOPE CONFIGURATIONS 2 REGISTER ======*/
#define GYRO_AVGCFG                             0x00U
#define ZGYRO_CTEN                              0x03U
#define YGYRO_CTEN                              0x04U
#define XGYRO_CTEN                              0x05U

            /*====== GYROSCOPE X AXIS OFFSET USER HIGH REGISTER ======*/
#define XG_OFFS_USER_H                          0x00U

            /*====== GYROSCOPE X AXIS OFFSET USER LOW REGISTER ======*/
#define XG_OFFS_USER_L                          0x00U

            /*====== GYROSCOPE Y AXIS OFFSET USER HIGH REGISTER ======*/
#define YG_OFFS_USER_H                          0x00U

            /*====== GYROSCOPE Y AXIS OFFSET USER LOW REGISTER ======*/
#define YG_OFFS_USER_L                          0x00U

            /*====== GYROSCOPE Z AXIS OFFSET USER HIGH REGISTER ======*/
#define ZG_OFFS_USER_H                          0x00U

            /*====== GYROSCOPE Z AXIS OFFSET USER LOW REGISTER ======*/
#define ZG_OFFS_USER_L                          0x00U

            /*====== OUTPUT DATA RATE TIME ALIGNMENT ENABLE REGISTER ======*/
#define ODR_ALIGN_EN_REG                        0x00U

            /*====== ACCELEROMETER SAMPLE RATE DIVIDE 1 REGISTER ======*/
#define ACCEL_SMPLRT_DIV_1_REG                  0x00U

            /*====== ACCELEROMETER SAMPLE RATE DIVIDE 2 REGISTER ======*/
#define ACCEL_SMPLRT_DIV_2_REG                  0x00U

            /*====== ACCELEROMETER INTEL CONTROL REGISTER ======*/
#define ACCEL_INTEL_MODE_INT                    0x00U
#define ACCEL_INTEL_EN                          0x01U

            /*====== ACCELEROMETER WAKEUP OF MOTION THRESHOLD REGISTER ======*/
#define WOM_THRESHOLD                           0x00U

            /*====== ACCELEROMETER CONFIGURATIONS 1 REGISTER ======*/
#define ACCEL_FCHOICE                           0x00U
#define ACCEL_FS_SEL                            0x01U  
#define ACCEL_DLPFCFG                           0x03U

            /*====== ACCELEROMETER CONFIGURATIONS 2 REGISTER ======*/
#define DEC3_CFG                                0x00U
#define AZ_ST_EN_REG                            0x02U
#define AY_ST_EN_REG                            0x03U
#define AX_ST_EN_REG                            0x04U

            /*====== FREQUENCY SYNCHRONOUS CONFIGURATION REGISTER ======*/
#define EXT_SYNC_SET                            0x00U
#define WOF_EDGE_INT                            0x04U
#define WOF_DEGLITCH_EN                         0x05U
#define DELAY_TIME_EN                           0x07U

            /*====== TEMPERATURE CONFIGURATION REGISTER ======*/
#define TEMP_DLPFCFG                            0x00U

            /*====== USER CONTROL MODE REGISTER ======*/
#define REG_LP_DMP_EN                           0x00U

/*============== USER BANK 3 R/W DESCRIPTIONS MACROS ==============*/
            /*====== I2C MASTER OUTPUT DATA RATE CONFIGURATION REGISTER ======*/
#define I2C_MST_ODR_CONFIG_REG                   0x00U

            /*====== I2C MASTER CONTROL REGISTER ======*/
#define I2C_MST_CLK                             0x00U
#define I2C_MST_P_NSR                           0x04U
#define MULTI_MST_EN                            0x07U

            /*====== I2C MASTER DELAY CONTROL REGISTER ======*/
#define I2C_SLV0_DELAY_EN                       0x00U
#define I2C_SLV1_DELAY_EN                       0x01U
#define I2C_SLV2_DELAY_EN                       0x02U
#define I2C_SLV3_DELAY_EN                       0x03U
#define I2C_SLV4_DELAY_EN                       0x04U
#define DELAY_ES_SHADOW                         0x07U

            /*====== I2C SLAVE 0 ADDRESS REGISTER ======*/
#define I2C_ID_0                                0x00U
#define I2C_SLV0_RNW                            0x07U

            /*====== I2C SLAVE 0 REGISTER READ AND WRITE REGISTER ======*/
#define I2C_SLV0_REG_REG                        0x00U

            /*====== I2C SLAVE 0 CONTROL REGISTER ======*/
#define I2C_SLV0_LENG                           0x00U
#define I2C_SLV0_GRP                            0x04U
#define I2C_SLV0_REG_DIS                        0x05U
#define I2C_SLV0_BYTE_SW                        0x06U
#define I2C_SLV0_EN                             0x07U

            /*====== I2C SLAVE 0 DIGITAL OUTPUT REGISTER ======*/
#define I2C_SLV0_DO_REG                          0x00U

            /*====== I2C SLAVE 1 ADDRESS REGISTER ======*/
#define I2C_ID_1                                0x00U
#define I2C_SLV1_RNW                            0x07U

            /*====== I2C SLAVE 1 REGISTER READ AND WRITE REGISTER ======*/
#define I2C_SLV1_REG_REG                        0x00U

            /*====== I2C SLAVE 1 CONTROL REGISTER ======*/
#define I2C_SLV1_LENG                           0x00U
#define I2C_SLV1_GRP                            0x04U
#define I2C_SLV1_REG_DIS                        0x05U
#define I2C_SLV1_BYTE_SW                        0x06U
#define I2C_SLV1_EN                             0x07U

            /*====== I2C SLAVE 1 DIGITAL OUTPUT REGISTER ======*/
#define I2C_SLV1_DO_REG                          0x00U

            /*====== I2C SLAVE 2 ADDRESS REGISTER ======*/
#define I2C_ID_2                                0x00U
#define I2C_SLV2_RNW                            0x07U

            /*====== I2C SLAVE 2 REGISTER READ AND WRITE REGISTER ======*/
#define I2C_SLV2_REG_REG                        0x00U

            /*====== I2C SLAVE 2 CONTROL REGISTER ======*/
#define I2C_SLV2_LENG                           0x00U
#define I2C_SLV2_GRP                            0x04U
#define I2C_SLV2_REG_DIS                        0x05U
#define I2C_SLV2_BYTE_SW                        0x06U
#define I2C_SLV2_EN                             0x07U

            /*====== I2C SLAVE 2 DIGITAL OUTPUT REGISTER ======*/
#define I2C_SLV2_DO_REG                          0x00U

            /*====== I2C SLAVE 3 ADDRESS REGISTER ======*/
#define I2C_ID_3                                0x00U
#define I2C_SLV3_RNW                            0x07U

            /*====== I2C SLAVE 3 REGISTER READ AND WRITE REGISTER ======*/
#define I2C_SLV3_REG_REG                        0x00U

            /*====== I2C SLAVE 3 CONTROL REGISTER ======*/
#define I2C_SLV3_LENG                           0x00U
#define I2C_SLV3_GRP                            0x04U
#define I2C_SLV3_REG_DIS                        0x05U
#define I2C_SLV3_BYTE_SW                        0x06U
#define I2C_SLV3_EN                             0x07U

            /*====== I2C SLAVE 3 DIGITAL OUTPUT REGISTER ======*/
#define I2C_SLV3_DO_REG                          0x00U

            /*====== I2C SLAVE 4 ADDRESS REGISTER ======*/
#define I2C_ID_4                                0x00U
#define I2C_SLV4_RNW                            0x07U

            /*====== I2C SLAVE 4 REGISTER READ AND WRITE REGISTER ======*/
#define I2C_SLV4_REG_REG                        0x00U

            /*====== I2C SLAVE 4 CONTROL REGISTER ======*/
#define I2C_SLV4_DLY                            0x00U
#define I2C_SLV4_REG_DIS                        0x05U
#define I2C_SLV4_INT_EN                         0x06U
#define I2C_SLV4_EN                             0x07U

            /*====== I2C SLAVE 4 DIGITAL OUTPUT REGISTER ======*/
#define I2C_SLV4_DO_REG                         0x00U

            /*====== I2C SLAVE 4 DIGITAL INPUT REGISTER ======*/
#define I2C_SLV4_DI_REG                         0x00U

/*********************** MAGNETOMETER REGISTERS MACROS ***********************/
#define WIA                                     0x01U
#define ST1                                     0x10U 
#define HXL                                     0x11U
#define HXH                                     0x12U
#define HYL                                     0x13U
#define HYH                                     0x14U
#define HZL                                     0x15U
#define HZH                                     0x16U
#define ST2                                     0x18U
#define CNTL2                                   0x31U
#define CNTL3                                   0x32U
#define TS1                                     0x33U
#define TS2                                     0x34U

/*============== DETAILS R/W DESCRIPTIONS MACROS FOR MAGNETOMETER ==============*/
#define DEVICE_MAGNETOMETER_ID                  0x09U

            /*====== CONTROL 2 REGISTER ======*/  
#define MODE_0                                  0x00U
#define MODE_1                                  0x01U
#define MODE_2                                  0x02U
#define MODE_3                                  0x03U
#define MPDE_4                                  0x04U

            /*====== CONTROL 3 REGISTER ======*/
#define SRST                                    0x00U     

/********************* Enum for controlling IMU *********************/
typedef enum
{
        BANK_0,
        BANK_1,
        BANK_2,
        BANK_3
}usrbank_sel;

typedef enum
{
        INTERNAL_20MHz_Osc,
        BEST_CLK_SRC,
        STOP_CLK = 7
}clk_sel;

typedef enum
{
        SLEEP_DIS,
        SLEEP_EN
}sleep_mode;

typedef enum
{
        DEVICE_SET,
        DEVICE_RST
}device_reset;

typedef enum
{
        DLPF_DISABLED,
        DLPF_ENABLED
}FCHOICE;

typedef enum
{
        GYRO_FS_250DPS,
        GYRO_FS_500DPS,
        GYRO_FS_1000DPS,
        GYRO_FS_2000DPS
}GYRO_FULL_SCALE;
typedef enum
{
        GYRO_196_6Hz_229_8Hz,
        GYRO_151_8Hz_187_6Hz,
        GYRO_119_5Hz_154_3Hz,
        GYRO_51_2Hz_73_3Hz,   
        GYRO_23_9Hz_35_5Hz,
        GYRO_11_6Hz_17_8Hz,
        GYRO_5_7Hz_8_9Hz,
        GYRO_361_4Hz_376_5Hz,    
} Gyro_LowPassFilter_Bandwidth;
typedef enum
{
        GYRO_SMPLRT_DIV_0,
        GYRO_SMPLRT_DIV_1,
        GYRO_SMPLRT_DIV_2,
        GYRO_SMPLRT_DIV_3,
        GYRO_SMPLRT_DIV_4,
        GYRO_SMPLRT_DIV_5,
        GYRO_SMPLRT_DIV_6,
        GYRO_SMPLRT_DIV_7,
        GYRO_SMPLRT_DIV_8,
        GYRO_SMPLRT_DIV_9,
        GYRO_SMPLRT_DIV_10,
        GYRO_SMPLRT_DIV_11,
        GYRO_SMPLRT_DIV_12,
        GYRO_SMPLRT_DIV_13,
        GYRO_SMPLRT_DIV_14,
        GYRO_SMPLRT_DIV_15,
        GYRO_SMPLRT_DIV_16,
        GYRO_SMPLRT_DIV_17,
        GYRO_SMPLRT_DIV_18,
        GYRO_SMPLRT_DIV_19,
        GYRO_SMPLRT_DIV_20,
        GYRO_SMPLRT_DIV_21,
        GYRO_SMPLRT_DIV_22,
        GYRO_SMPLRT_DIV_23,
        GYRO_SMPLRT_DIV_24,
        GYRO_SMPLRT_DIV_25,
        GYRO_SMPLRT_DIV_26,
        GYRO_SMPLRT_DIV_27,
        GYRO_SMPLRT_DIV_28,
        GYRO_SMPLRT_DIV_29,
        GYRO_SMPLRT_DIV_30,
        GYRO_SMPLRT_DIV_31,
        GYRO_SMPLRT_DIV_32,
        GYRO_SMPLRT_DIV_33,
        GYRO_SMPLRT_DIV_34,
        GYRO_SMPLRT_DIV_35,     
        GYRO_SMPLRT_DIV_36,
        GYRO_SMPLRT_DIV_37,
        GYRO_SMPLRT_DIV_38,
        GYRO_SMPLRT_DIV_39,
        GYRO_SMPLRT_DIV_40,
        GYRO_SMPLRT_DIV_41,
        GYRO_SMPLRT_DIV_42,
        GYRO_SMPLRT_DIV_43,
        GYRO_SMPLRT_DIV_44,
        GYRO_SMPLRT_DIV_45,
        GYRO_SMPLRT_DIV_46,
        GYRO_SMPLRT_DIV_47,
        GYRO_SMPLRT_DIV_48,
        GYRO_SMPLRT_DIV_49,
        GYRO_SMPLRT_DIV_50,
        GYRO_SMPLRT_DIV_51,
        GYRO_SMPLRT_DIV_52,
        GYRO_SMPLRT_DIV_53,
        GYRO_SMPLRT_DIV_54,
        GYRO_SMPLRT_DIV_55,
        GYRO_SMPLRT_DIV_56,
        GYRO_SMPLRT_DIV_57,
        GYRO_SMPLRT_DIV_58,
        GYRO_SMPLRT_DIV_59,
        GYRO_SMPLRT_DIV_60,
        GYRO_SMPLRT_DIV_61,
        GYRO_SMPLRT_DIV_62,
        GYRO_SMPLRT_DIV_63,
        GYRO_SMPLRT_DIV_64,
        GYRO_SMPLRT_DIV_65,
        GYRO_SMPLRT_DIV_66,
        GYRO_SMPLRT_DIV_67,
        GYRO_SMPLRT_DIV_68,
        GYRO_SMPLRT_DIV_69,
        GYRO_SMPLRT_DIV_70,
        GYRO_SMPLRT_DIV_71,
        GYRO_SMPLRT_DIV_72,
        GYRO_SMPLRT_DIV_73,
        GYRO_SMPLRT_DIV_74,
        GYRO_SMPLRT_DIV_75,
        GYRO_SMPLRT_DIV_76,
        GYRO_SMPLRT_DIV_77,
        GYRO_SMPLRT_DIV_78,
        GYRO_SMPLRT_DIV_79,
        GYRO_SMPLRT_DIV_80,
        GYRO_SMPLRT_DIV_81,
        GYRO_SMPLRT_DIV_82,
        GYRO_SMPLRT_DIV_83,
        GYRO_SMPLRT_DIV_84,
        GYRO_SMPLRT_DIV_85,
        GYRO_SMPLRT_DIV_86,
        GYRO_SMPLRT_DIV_87,
        GYRO_SMPLRT_DIV_88,
        GYRO_SMPLRT_DIV_89,
        GYRO_SMPLRT_DIV_90,
        GYRO_SMPLRT_DIV_91,
        GYRO_SMPLRT_DIV_92,
        GYRO_SMPLRT_DIV_93,
        GYRO_SMPLRT_DIV_94,
        GYRO_SMPLRT_DIV_95,
        GYRO_SMPLRT_DIV_96,
        GYRO_SMPLRT_DIV_97,
        GYRO_SMPLRT_DIV_98,
        GYRO_SMPLRT_DIV_99,
        GYRO_SMPLRT_DIV_100,
        GYRO_SMPLRT_DIV_101,
        GYRO_SMPLRT_DIV_102,
        GYRO_SMPLRT_DIV_103,
        GYRO_SMPLRT_DIV_104,
        GYRO_SMPLRT_DIV_105,
        GYRO_SMPLRT_DIV_106,
        GYRO_SMPLRT_DIV_107,
        GYRO_SMPLRT_DIV_108,
        GYRO_SMPLRT_DIV_109,
        GYRO_SMPLRT_DIV_110,
        GYRO_SMPLRT_DIV_111,
        GYRO_SMPLRT_DIV_112,
        GYRO_SMPLRT_DIV_113,
        GYRO_SMPLRT_DIV_114,
        GYRO_SMPLRT_DIV_115,
        GYRO_SMPLRT_DIV_116,
        GYRO_SMPLRT_DIV_117,
        GYRO_SMPLRT_DIV_118,
        GYRO_SMPLRT_DIV_119,
        GYRO_SMPLRT_DIV_120,
        GYRO_SMPLRT_DIV_121,
        GYRO_SMPLRT_DIV_122,
        GYRO_SMPLRT_DIV_123,
        GYRO_SMPLRT_DIV_124,
        GYRO_SMPLRT_DIV_125,
        GYRO_SMPLRT_DIV_126,
        GYRO_SMPLRT_DIV_127,
        GYRO_SMPLRT_DIV_128,
        GYRO_SMPLRT_DIV_129,
        GYRO_SMPLRT_DIV_130,
        GYRO_SMPLRT_DIV_131,
        GYRO_SMPLRT_DIV_132,
        GYRO_SMPLRT_DIV_133,
        GYRO_SMPLRT_DIV_134,
        GYRO_SMPLRT_DIV_135,
        GYRO_SMPLRT_DIV_136,
        GYRO_SMPLRT_DIV_137,
        GYRO_SMPLRT_DIV_138,
        GYRO_SMPLRT_DIV_139,
        GYRO_SMPLRT_DIV_140,
        GYRO_SMPLRT_DIV_141,
        GYRO_SMPLRT_DIV_142,
        GYRO_SMPLRT_DIV_143,
        GYRO_SMPLRT_DIV_144,
        GYRO_SMPLRT_DIV_145,
        GYRO_SMPLRT_DIV_146,
        GYRO_SMPLRT_DIV_147,
        GYRO_SMPLRT_DIV_148,
        GYRO_SMPLRT_DIV_149,
        GYRO_SMPLRT_DIV_150,
        GYRO_SMPLRT_DIV_151,
        GYRO_SMPLRT_DIV_152,
        GYRO_SMPLRT_DIV_153,
        GYRO_SMPLRT_DIV_154,
        GYRO_SMPLRT_DIV_155,
        GYRO_SMPLRT_DIV_156,
        GYRO_SMPLRT_DIV_157,
        GYRO_SMPLRT_DIV_158,
        GYRO_SMPLRT_DIV_159,
        GYRO_SMPLRT_DIV_160,
        GYRO_SMPLRT_DIV_161,
        GYRO_SMPLRT_DIV_162,
        GYRO_SMPLRT_DIV_163,
        GYRO_SMPLRT_DIV_164,
        GYRO_SMPLRT_DIV_165,
        GYRO_SMPLRT_DIV_166,
        GYRO_SMPLRT_DIV_167,
        GYRO_SMPLRT_DIV_168,
        GYRO_SMPLRT_DIV_169,
        GYRO_SMPLRT_DIV_170,
        GYRO_SMPLRT_DIV_171,
        GYRO_SMPLRT_DIV_172,
        GYRO_SMPLRT_DIV_173,
        GYRO_SMPLRT_DIV_174,
        GYRO_SMPLRT_DIV_175,
        GYRO_SMPLRT_DIV_176,
        GYRO_SMPLRT_DIV_177,
        GYRO_SMPLRT_DIV_178,
        GYRO_SMPLRT_DIV_179,
        GYRO_SMPLRT_DIV_180,
        GYRO_SMPLRT_DIV_181,
        GYRO_SMPLRT_DIV_182,
        GYRO_SMPLRT_DIV_183,
        GYRO_SMPLRT_DIV_184,
        GYRO_SMPLRT_DIV_185,
        GYRO_SMPLRT_DIV_186,
        GYRO_SMPLRT_DIV_187,
        GYRO_SMPLRT_DIV_188,
        GYRO_SMPLRT_DIV_189,
        GYRO_SMPLRT_DIV_190,
        GYRO_SMPLRT_DIV_191,
        GYRO_SMPLRT_DIV_192,
        GYRO_SMPLRT_DIV_193,
        GYRO_SMPLRT_DIV_194,
        GYRO_SMPLRT_DIV_195,
        GYRO_SMPLRT_DIV_196,
        GYRO_SMPLRT_DIV_197,
        GYRO_SMPLRT_DIV_198,
        GYRO_SMPLRT_DIV_199,
        GYRO_SMPLRT_DIV_200,
        GYRO_SMPLRT_DIV_201,
        GYRO_SMPLRT_DIV_202,
        GYRO_SMPLRT_DIV_203,
        GYRO_SMPLRT_DIV_204,
        GYRO_SMPLRT_DIV_205,
        GYRO_SMPLRT_DIV_206,
        GYRO_SMPLRT_DIV_207,
        GYRO_SMPLRT_DIV_208,
        GYRO_SMPLRT_DIV_209,
        GYRO_SMPLRT_DIV_210,
        GYRO_SMPLRT_DIV_211,
        GYRO_SMPLRT_DIV_212,
        GYRO_SMPLRT_DIV_213,
        GYRO_SMPLRT_DIV_214,
        GYRO_SMPLRT_DIV_215,
        GYRO_SMPLRT_DIV_216,
        GYRO_SMPLRT_DIV_217,
        GYRO_SMPLRT_DIV_218,
        GYRO_SMPLRT_DIV_219,
        GYRO_SMPLRT_DIV_220,
        GYRO_SMPLRT_DIV_221,
        GYRO_SMPLRT_DIV_222,
        GYRO_SMPLRT_DIV_223,
        GYRO_SMPLRT_DIV_224,
        GYRO_SMPLRT_DIV_225,
        GYRO_SMPLRT_DIV_226,
        GYRO_SMPLRT_DIV_227,
        GYRO_SMPLRT_DIV_228,
        GYRO_SMPLRT_DIV_229,
        GYRO_SMPLRT_DIV_230,
        GYRO_SMPLRT_DIV_231,
        GYRO_SMPLRT_DIV_232,
        GYRO_SMPLRT_DIV_233,
        GYRO_SMPLRT_DIV_234,
        GYRO_SMPLRT_DIV_235,
        GYRO_SMPLRT_DIV_236,
        GYRO_SMPLRT_DIV_237,
        GYRO_SMPLRT_DIV_238,
        GYRO_SMPLRT_DIV_239,
        GYRO_SMPLRT_DIV_240,
        GYRO_SMPLRT_DIV_241,
        GYRO_SMPLRT_DIV_242,
        GYRO_SMPLRT_DIV_243,
        GYRO_SMPLRT_DIV_244,
        GYRO_SMPLRT_DIV_245,
        GYRO_SMPLRT_DIV_246,
        GYRO_SMPLRT_DIV_247,
        GYRO_SMPLRT_DIV_248,
        GYRO_SMPLRT_DIV_249,
        GYRO_SMPLRT_DIV_250,
        GYRO_SMPLRT_DIV_251,
        GYRO_SMPLRT_DIV_252,
        GYRO_SMPLRT_DIV_253,
        GYRO_SMPLRT_DIV_254,
        GYRO_SMPLRT_DIV_255
}gyro_smplrate_div;

typedef enum
{
        ACCEL_246Hz_265Hz_0,
        ACCEL_246Hz_265Hz_1,
        ACCEL_111_4Hz_136Hz,
        ACCEL_50_4Hz_68_8Hz,   
        ACCEL_23_9Hz_34_4Hz,
        ACCEL_11_5Hz_17Hz,
        ACCEL_5_7Hz_8_3Hz,
        ACCEL_473Hz_499Hz,    
} Accel_LowPassFilter_Bandwidth;

typedef enum
{
       ACCEL_FS_2G,
       ACCEL_FS_4G,
       ACCEL_FS_8G,
       ACCEL_FS_16
}ACCEL_FULL_SCALE;
typedef enum
{
        ODR_ALGIN_OFF,
        ODR_ALGIN_ON
}outputdatarate;

typedef enum
{
        I2C_ENABLE,
        I2C_DISABLE
}i2c_dis_reg;
/********************* Gyroscope and Accelerometer control functions *********************/
void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i);
void ICM20948_Init(SPI_HandleTypeDef *SPIx);
float ICM20948_Read();

#endif

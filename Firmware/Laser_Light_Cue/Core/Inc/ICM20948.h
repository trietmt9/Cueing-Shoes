#ifndef __ICM20948__H
#define __ICM20948__H
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"

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
#define ACC_SMPLRT_DIV_1                        0x10U
#define ACC_SMPLRT_DIV_2                        0x11U
#define ACC_INTEL_CTRL                          0x12U
#define ACC_WOM_THR                             0x13U
#define ACC_CONFIG_1                            0x14U
#define ACC_CONFIG_2                            0x15U
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
#define REG_BANK_SEL_REG                        0x00U   

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
#define ACCEL_SMPLRT_DIV_1                      0x00U

            /*====== ACCELEROMETER SAMPLE RATE DIVIDE 2 REGISTER ======*/
#define ACCEL_SMPLRT_DIV_2                      0x00U

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

#endif
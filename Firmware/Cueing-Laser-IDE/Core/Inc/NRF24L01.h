#ifndef __NRF24L01__H
#define __NRF24L01__H
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"

/*********************** GENERAL MACROS ***********************/
#define SPI_TIMEOUT                                     100
/*********************** NRF24l01 commands ***********************/

#define NRF24L01_CMD_READ_REGISTER                      0x00U
#define NRF24L01_CMD_WRITE_REGISTER                     0x20U
#define NRF24L01_CMD_R_RX_PAYLOAD                       0x61U
#define NRF24L01_CMD_W_TX_PAYLOAD                       0xA0U
#define NRF24L01_CMD_FLUSH_TX                           0xE1U
#define NRF24L01_CMD_FLUSH_RX                           0xE2U
#define NRF24L01_CMD_REUSE_TX_PL                        0xE3U
#define NRF24L01_CMD_R_RX_PL_WID                        0x60u
#define NRF24L01_CMD_W_ACK_PAYLOAD                      0xA8U
#define NRF24L01_CMD_W_TX_PAYLOAD_NOACK                 0xB0U
#define NRF24L01_CMD_NOP                                0xFFU

/*********************** NRF24l01 REGISTER MAP ***********************/

#define NRF24L01_REG_CONFIG                             0x00U
#define NRF24L01_REG_EN_AA                              0x01U
#define NRF24L01_REG_EN_RXADDR                          0x02U
#define NRF24L01_REG_SETUP_AW                           0x03U
#define NRF24L01_REG_SETUP_RETR                         0x04U
#define NRF24L01_REG_RF_CH                              0x05U
#define NRF24L01_REG_RF_SETUP                           0x06U
#define NRF24L01_REG_STATUS                             0x07U
#define NRF24L01_REG_OBSERVE_TX                         0x08U
#define NRF24L01_REG_RPD                                0x09U
#define NRF24L01_REG_RX_ADDR_P0                         0x0AU
#define NRF24L01_REG_RX_ADDR_P1                         0x0BU
#define NRF24L01_REG_RX_ADDR_P2                         0x0CU
#define NRF24L01_REG_RX_ADDR_P3                         0x0DU
#define NRF24L01_REG_RX_ADDR_P4                         0x0EU
#define NRF24L01_REG_RX_ADDR_P5                         0x0FU
#define NRF24L01_REG_TX_ADDR                            0x10U
#define NRF24L01_REG_RX_PW_P0                           0x11U
#define NRF24L01_REG_RX_PW_P1                           0x12U
#define NRF24L01_REG_RX_PW_P2                           0x13U
#define NRF24L01_REG_RX_PW_P3                           0x14U
#define NRF24L01_REG_RX_PW_P4                           0x15U
#define NRF24L01_REG_RX_PW_P5                           0x16U
#define NRF24L01_REG_FIFO_STATUS                        0x17U
#define NRF24L01_REG_DYNPD                              0x1CU
#define NRF24L01_REG_FEATURE                            0x1DU

/*********************** REGISTER MAP BIT CONTROL ***********************/
/*============ CONFIG REGISTER MAP ============*/

#define PRIM_RX                                         0x00U
#define PWR_UP                                          0x01U
#define CRCO                                            0x02U
#define EN_CRC                                          0x03U
#define MASK_MAX_RT                                     0x04U
#define MASK_TX_DS                                      0x05U
#define MASK_RX_DR                                      0x06U

/*============ ENABLE AUTO-ACKNOWLEDGEMENT REGISTER MAP ============*/

#define ENAA_P0                                         0x00U
#define ENAA_P1                                         0x01U
#define ENAA_P2                                         0x02U
#define ENAA_P3                                         0x03U
#define ENAA_P4                                         0x04U
#define ENAA_P5                                         0x05U

/*============ ENABLE RECEIVE ADDRESSES REGISTER MAP ============*/

#define ERX_P0                                          0x00U
#define ERX_P1                                          0x01U
#define ERX_P2                                          0x02U
#define ERX_P3                                          0x03U
#define ERX_P4                                          0x04U
#define ERX_P5                                          0x05U

/*============ SETUP ADDRESS WIDTHS REGISTER MAP ============*/

#define AW                                              0x00U

/*============ SETUP AUTO-RETRANSMISSION REGISTER MAP ============*/

#define ARC                                             0x00U // [3:0] BITS
#define ARD                                             0x04U // [7:4] BITS 

/*============ RADIO FREQUENCY CHANNEL REGISTER MAP ============*/

#define RF_CH                                           0x00U

/*============ RADIO FREQUENCY SETUP REGISTER MAP ============*/

#define RF_PWR                                          0x01U // [2:1] BITS
#define RF_DR_HIGH                                      0x03U
#define PLL_LOCK                                        0x04U
#define RF_DR_LOW                                       0x05U
#define CONT_WAVE                                       0x07U

/*============ STATUS REGISTER MAP ============*/

#define TX_FULL                                         0x00U
#define RX_P_NO                                         0x01U // [3:1] BITS
#define MAX_RT                                          0x04U
#define TX_DS                                           0x05U 
#define RX_DR                                           0x06U

/*============ OBSERVE TX REGISTER MAP ============*/

#define ARC_CNT                                         0x00U // [3:0] BITS
#define PLOS_CNT                                        0x04U // [7:4] BITS

/*============ RECEIVED POWER DETECTOR REGISTER MAP ============*/

#define RPD                                             0x00U //* READ ONLY REGISTER

/*============ RECEIVE PAYLOAD WIDTHS PIPE 0 REGISTER MAP ============*/

#define RX_PW_P0                                        0x00U // [5:0] BITS

/*============ RECEIVE PAYLOAD WIDTHS PIPE 1 REGISTER MAP ============*/

#define RX_PW_P1                                        0x00U // [5:0] BITS

/*============ RECEIVE PAYLOAD WIDTHS PIPE 2 REGISTER MAP ============*/

#define RX_PW_P2                                        0x00U // [5:0] BITS

/*============ RECEIVE PAYLOAD WIDTHS PIPE 3 REGISTER MAP ============*/

#define RX_PW_P3                                        0x00U // [5:0] BITS

/*============ RECEIVE PAYLOAD WIDTHS PIPE 4 REGISTER MAP ============*/

#define RX_PW_P4                                        0x00U // [5:0] BITS

/*============ RECEIVE PAYLOAD WIDTHS PIPE 5 REGISTER MAP ============*/

#define RX_PW_P5                                        0x00U // [5:0] BITS

/*============ FIFO STATUS REGISTER MAP ============*/

#define RX_EMPTY                                        0x00U
#define RX_FULL                                         0x01U
#define TX_EMPTY                                        0x04U
#define TX_FULL                                         0x05U
#define TX_REUSE                                        0x06U

/*============ DYNAMIC PAYLOAD LENGTH REGISTER MAP ============*/

#define DPL_P0                                          0x00U
#define DPL_P1                                          0x01U
#define DPL_P2                                          0x02U
#define DPL_P3                                          0x03U
#define DPL_P4                                          0x04U
#define DPL_P5                                          0x05U

/*============ FEATURE REGISTER MAP ============*/

#define EN_DYN_ACK                                      0x00U
#define EN_ACK_PAY                                      0x01U
#define EN_DPL                                          0x02U

/*********************** NRF24L01 CONTROL ENUMS ***********************/
enum
{
    TRANSMIT,
    RECEIVE
};

enum
{
    POWER_DOWN,
    POWER_UP,
};

enum
{
    DISABLE_CRC,
    ENABLE_CRC
};

enum
{
    TX_FIFO_NOT_EMPTY,
    TX_FIFO_EMPTY
};

enum 
{
    PIPE_0,
    PIPE_1,
    PIPE_2,
    PIPE_3,
    PIPE_4,
    PIPE_5
};

enum
{
    PAYLOAD_PIPE_NOT_USE,
    PAYLOAD_PIPE_1_BYTE,
    PAYLOAD_PIPE_2_BYTE,
    PAYLOAD_PIPE_3_BYTE,
    PAYLOAD_PIPE_4_BYTE,
    PAYLOAD_PIPE_5_BYTE,
    PAYLOAD_PIPE_6_BYTE,
    PAYLOAD_PIPE_7_BYTE,
    PAYLOAD_PIPE_8_BYTE,
    PAYLOAD_PIPE_9_BYTE,
    PAYLOAD_PIPE_10_BYTE,
    PAYLOAD_PIPE_11_BYTE,
    PAYLOAD_PIPE_12_BYTE,
    PAYLOAD_PIPE_13_BYTE,
    PAYLOAD_PIPE_14_BYTE,
    PAYLOAD_PIPE_15_BYTE,
    PAYLOAD_PIPE_16_BYTE,
    PAYLOAD_PIPE_17_BYTE,
    PAYLOAD_PIPE_18_BYTE,
    PAYLOAD_PIPE_19_BYTE,
    PAYLOAD_PIPE_20_BYTE,
    PAYLOAD_PIPE_21_BYTE,
    PAYLOAD_PIPE_22_BYTE,
    PAYLOAD_PIPE_23_BYTE,
    PAYLOAD_PIPE_24_BYTE,
    PAYLOAD_PIPE_25_BYTE,
    PAYLOAD_PIPE_26_BYTE,
    PAYLOAD_PIPE_27_BYTE,
    PAYLOAD_PIPE_28_BYTE,
    PAYLOAD_PIPE_29_BYTE,
    PAYLOAD_PIPE_30_BYTE,
    PAYLOAD_PIPE_31_BYTE,
    PAYLOAD_PIPE_32_BYTE,
};

enum 
{
    RF_PWR_MIN,
    RF_PWR_LOW,
    RF_PWR_HIGH,
    RF_PWR_MAX,
};
/*********************** NRF24L01 CONTROL FUNCTIONS ***********************/
void NRF24_Init(SPI_HandleTypeDef* SPIx, uint16_t MHz);
void NRF24_SET_PA(SPI_HandleTypeDef* SPIx, uint8_t PA_Level);
void NRF24_CHECK_DATA_AVAILABLE(SPI_HandleTypeDef *SPIx,uint8_t pipe);
void NRF24_Tx_Mode(SPI_HandleTypeDef *SPIx, uint8_t *Address);
void NRF24_Rx_Mode(SPI_HandleTypeDef* SPIx, uint8_t *Address, uint8_t pipe);
void NRF24_Select_Channel(SPI_HandleTypeDef* SPIx, uint8_t channel);
void NRF24_Transmit(SPI_HandleTypeDef *SPIx, uint8_t *pData);
void NRF24_Receive();

#endif
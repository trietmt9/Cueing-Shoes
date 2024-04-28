/*
*
* FIR_Filter.c 
* Created on: April/26/2024
* Author: trietmt9 
*
*/

#include "NRF24L01.h"

/*********************** SPI ABSTRACTS LAYER FUNCTIONS ***********************/
inline static void NRF24_SELECT(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

inline static void NRF24_UNSELECT(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
}

inline static void NRF24_ENABLE(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

inline static void NRF24_DISABLE(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void SPI_Write_Byte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t Data)
{
    uint8_t temp_reg[2];
    temp_reg[0] = (reg | NRF24L01_CMD_WRITE_REGISTER);
    temp_reg[1] = Data;
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, &temp_reg, 2, SPI_TIMEOUT);
    NRF24_UNSELECT();
}

void SPI_Write_MultiByte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t *pData, uint8_t Data_length)
{
    uint8_t temp_reg = 0;
    temp_reg = (reg | NRF24L01_CMD_WRITE_REGISTER);
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, &temp_reg, 1, SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, pData, Data_length, SPI_TIMEOUT);
    NRF24_UNSELECT();
}

uint8_t SPI_Read_Byte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t* pData)
{
    uint8_t temp_reg;
    temp_reg = (reg | NRF24L01_CMD_READ_REGISTER);
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, &temp_reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, 1, SPI_TIMEOUT);
    NRF24_UNSELECT();
    return pData;
}

void SPI_Read_MultiByte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t* pData, uint16_t data_length)
{
    uint8_t temp_reg;
    temp_reg = (reg | NRF24L01_CMD_READ_REGISTER);
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, &temp_reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, data_length, SPI_TIMEOUT);
    NRF24_UNSELECT();
}

void NRF24L01_SEND_CMD(SPI_HandleTypeDef *SPI, uint8_t* CMD)
{
    NRF24_SELECT();
    HAL_SPI_Transmit(SPI, CMD, 1, SPI_TIMEOUT);
    NRF24_UNSELECT();
}

void NRF24_FLUSH_RX(SPI_HandleTypeDef* SPIx)
{   
    uint8_t flush_rx = NRF24L01_CMD_FLUSH_RX;
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, flush_rx, 1, SPI_TIMEOUT);
    NRF24_UNSELECT();
}

void NRF24_FLUSH_TX(SPI_HandleTypeDef* SPIx)
{
    uint8_t flush_tx = NRF24L01_CMD_FLUSH_TX;
    NRF24_SELECT();
    HAL_SPI_Transmit(SPIx, flush_tx, 1, SPI_TIMEOUT);
    NRF24_UNSELECT();
}
static void NRF24_Reset(SPI_HandleTypeDef *SPIx)
{
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG,       0x08);
    SPI_Write_Byte(SPIx, NRF24L01_REG_EN_AA,        0x3F);
    SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR,    0x03);
    SPI_Write_Byte(SPIx, NRF24L01_REG_SETUP_AW,     0x03);
    SPI_Write_Byte(SPIx, NRF24L01_REG_SETUP_RETR,   0x03);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_CH,        0x02);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_SETUP,     0x0E);
    SPI_Write_Byte(SPIx, NRF24L01_REG_STATUS,       0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P0,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P1,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P2,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P3,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P4,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P5,     0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_DYNPD,        0x00);
    SPI_Write_Byte(SPIx, NRF24L01_REG_FEATURE,      0x00); 
}

void NRF24_Init(SPI_HandleTypeDef* SPIx, uint16_t MHz)
{
    uint8_t temp_data = 0;
    NRF24_DISABLE();
    NRF24_SELECT();
    // Reset the NRF24L01 before setup
    NRF24_Reset(SPIx);

    // Select Channel 
    NRF24_Select_Channel(SPIx, MHz);
    // Disable CE pin before configuration
    NRF24_UNSELECT(); 
    NRF24_ENABLE();
}
void NRF24_Rx_setting(SPI_HandleTypeDef* SPIx, uint8_t pipe, uint8_t* Address)
{
    // Select pipe number 
    switch(pipe)
    {
        case PIPE_0:
            SPI_Write_MultiByte(SPIx, NRF24L01_REG_RX_ADDR_P0, Address, 5);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P0, PAYLOAD_PIPE_32_BYTE);
            break;
        case PIPE_1:
            SPI_Write_MultiByte(SPIx, NRF24L01_REG_RX_ADDR_P1, Address, 5);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P1, PAYLOAD_PIPE_32_BYTE);
            break;
        case PIPE_2:
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P2, Address);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P2, PAYLOAD_PIPE_32_BYTE);
            break;
        case PIPE_3:
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P3, Address);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P3, PAYLOAD_PIPE_32_BYTE);
            break; 
        case PIPE_4:
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P4, Address);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P4, PAYLOAD_PIPE_32_BYTE);
            break;
        case PIPE_5:
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P5, Address);
            SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P5, PAYLOAD_PIPE_32_BYTE);
            break;
    }
}
void NRF24_Select_Channel(SPI_HandleTypeDef* SPIx, uint8_t channel)
{  // Select channel
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_CH, channel);
}

void NRF24_Rx_Mode(SPI_HandleTypeDef* SPIx, uint8_t *Address, uint8_t pipe)
{
    uint8_t temp_data = 0;
    temp_data |= (RECEIVE << PRIM_RX);
    NRF24_DISABLE();
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG, temp_data);
    NRF24_ENABLE();
}
void NRF24_Tx_Mode(SPI_HandleTypeDef *SPIx, uint8_t *Address)
{
    uint8_t temp_data = 0;
    // Disable CE pin
    NRF24_DISABLE();
    // Write 5 Bytes to address
    SPI_Write_MultiByte(SPIx, NRF24L01_REG_TX_ADDR, Address, 5);

    // Set transmit mode and power up the module
    temp_data |= (POWER_UP << PWR_UP)|(TRANSMIT << PRIM_RX);
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG, temp_data);

    // Enable CE pin
    NRF24_ENABLE();
}

void NRF24_CHECK_DATA_AVAILABLE(SPI_HandleTypeDef *SPIx,uint8_t pipe)
{
    uint8_t status;
    SPI_Read_Byte(SPIx, NRF24L01_REG_STATUS, &status);
    if((status & (1 << RX_DR)) && (status & (pipe << 1)))
    {
        SPI_Write_Byte(SPIx, NRF24L01_REG_STATUS,(1 << RX_DR));
    }
}

void NRF24_Transmit(SPI_HandleTypeDef *SPIx, uint8_t *pData)
{
    uint8_t cmd = 0;
    cmd = NRF24L01_CMD_W_TX_PAYLOAD;
        // Send payload command 
    NRF24L01_SEND_CMD(SPIx, &cmd);

    NRF24_SELECT();
    // Send payload 
    HAL_SPI_Transmit(SPIx, pData, 32, SPI_TIMEOUT);

    NRF24_UNSELECT();
    HAL_Delay(1);

    // check FIFO status 
    uint8_t fifo_status;
    SPI_Read_Byte(SPIx, NRF24L01_REG_FIFO_STATUS, &fifo_status);
    
    if((fifo_status & (TX_FIFO_EMPTY << TX_EMPTY)) && (!(fifo_status & (1 << 3))))  
    {
        cmd = NRF24L01_CMD_FLUSH_TX;   
        NRF24L01_SEND_CMD(SPIx, &cmd); 
    }
}

void NRF24_Receive(SPI_HandleTypeDef *SPIx, uint8_t *pData)
{
    uint8_t cmd = 0; 
    
    // Send Received command
    cmd = NRF24L01_CMD_R_RX_PAYLOAD;
    NRF24L01_SEND_CMD(SPIx, &cmd);

    // Received data from pipe 
    NRF24_SELECT();
    HAL_SPI_Receive(SPIx, pData, 32, SPI_TIMEOUT);
    NRF24_UNSELECT();
    HAL_Delay(1);

    cmd = NRF24L01_CMD_FLUSH_RX; 
    NRF24L01_SEND_CMD(SPIx, &cmd);

}
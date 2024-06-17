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
    HAL_GPIO_WritePin(NRF24_CS_GPIO_Port, NRF24_CS_Pin, GPIO_PIN_RESET);
}

inline static void NRF24_UNSELECT(void)
{
    HAL_GPIO_WritePin(NRF24_CS_GPIO_Port, NRF24_CS_Pin, GPIO_PIN_SET);
}

inline static void NRF24_ENABLE(void)
{
    HAL_GPIO_WritePin(NRF24_CE_GPIO_Port, NRF24_CE_Pin, GPIO_PIN_SET);
}

inline static void NRF24_DISABLE(void)
{
    HAL_GPIO_WritePin(NRF24_CE_GPIO_Port, NRF24_CE_Pin, GPIO_PIN_RESET);
}

void SPI_Write_Byte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t* Data)
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

/**
 * @brief  NRF24L01 FLUSH_RX function
 * @param[in]  SPIx: SPI handle
 * @return  None
 * @details  This function flushes the RX FIFO of the NRF24L01 module.
 *  It sends the specified command to the NRF24L01 module and then flushes the RX FIFO.
 *  @note  The NRF24L01 module must be initialized and configured before using this function.
 */
void NRF24_FLUSH_RX(SPI_HandleTypeDef* SPIx)
{
    uint8_t flush_rx = NRF24L01_CMD_FLUSH_RX;
    NRF24L01_SEND_CMD(SPIx, flush_rx);
}

/**
 * @brief  NRF24L01 FLUSH_TX function
 * @param[in]  SPIx: SPI handle
 * @return  None
 * @details  This function flushes the TX FIFO of the NRF24L01 module.
 *  It sends the specified command to the NRF24L01 module and then flushes the TX FIFO.
 *  @note  The NRF24L01 module must be initialized and configured before using this function.
 */
void NRF24_FLUSH_TX(SPI_HandleTypeDef* SPIx)
{
    uint8_t flush_tx = NRF24L01_CMD_FLUSH_TX;
    NRF24L01_SEND_CMD(SPIx, flush_tx);
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

/**
 * @brief  NRF24L01 Set channel function
 * @param[in]  SPIx: SPI handle
 * @param[in]  channel: Select channel from 0 - 127
 * @return  None
 * @details  This function sets the working channel of the NRF24L01 
 */
void NRF24_Select_Channel(SPI_HandleTypeDef* SPIx, uint8_t channel)
{  // Select channel
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_CH, channel);
}

/**
 * @brief  NRF24L01 Set Transmit Mode function
 * @param[in]  SPIx: SPI handle
 * @param[in]  Address: Pointer to the buffer containing the transmit address
 * @param[in] pip: NRF24L01 pipeline number
 * @return  None
 * @details This function sets the receive mode and powers up the NRF24L01 module.
 *  It writes the specified receive address to the RX_ADDR register of the NRF24L01 module.
 *  After setting the receive mode, the function enables the CE pin to activate the module.
 */
void NRF24_Rx_Mode(SPI_HandleTypeDef* SPIx, uint8_t *Address, uint8_t pipe)
{
    uint8_t temp_data = 0;
    uint8_t pipe_select = 0;
    // Select Rx mode 
    temp_data |= (RECEIVE << PRIM_RX);
    NRF24_DISABLE();
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG, &temp_data);

    // Setup Address width 
    temp_data = 0;
    temp_data |= (sizeof(Address) << AW);
    SPI_Write_Byte(SPIx, NRF24L01_REG_SETUP_AW, &temp_data);

    // Select pipe number and maximum pipe width 
    switch(pipe)
    {
        case PIPE_0:
            // Enable Pipe 0 
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P0);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 0 address
            SPI_Write_MultiByte(SPIx, NRF24L01_REG_RX_ADDR_P0, Address, 5);
            break;
        case PIPE_1:
            // Enable Pipe 1
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P1);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 1 address
            SPI_Write_MultiByte(SPIx, NRF24L01_REG_RX_ADDR_P1, Address, 5);
            break;
        case PIPE_2:
            // Enable Pipe 2
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P2);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 2 address
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P2, Address);
            break;
        case PIPE_3:
            // Enable Pipe 3
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P3);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 3 address
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P3, Address);
            break; 
        case PIPE_4:
            // Enable Pipe 4
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P4);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 4 address
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P4, Address);
            break;
        case PIPE_5:
            // Enable Pipe 5
            pipe_select = 0;
            pipe_select |= ( 1 << ERX_P5);
            SPI_Write_Byte(SPIx, NRF24L01_REG_EN_RXADDR, &pipe_select);
            // Set Pipe 5 address
            SPI_Write_Byte(SPIx,NRF24L01_REG_RX_ADDR_P5, Address);
            
            
            break;
    }

    NRF24_ENABLE();
}

/**
 * @brief  NRF24L01 Set Transmit Mode function
 * @param[in]  SPIx: SPI handle
 * @param[in]  Address: Pointer to the buffer containing the transmit address
 * @return  None
 * @details  This function sets the transmit mode and powers up the NRF24L01 module.
 *  It writes the specified transmit address to the TX_ADDR register of the NRF24L01 module.
 *  After setting the transmit mode, the function enables the CE pin to activate the module.
 */
void NRF24_Tx_Mode(SPI_HandleTypeDef *SPIx, uint8_t *Address)
{
    uint8_t temp_data = 0;

    /*
     * @brief  Disable CE pin
     */
    NRF24_DISABLE();

    /*
     * @brief  Write 5 Bytes to address
     */
    SPI_Write_MultiByte(SPIx, NRF24L01_REG_TX_ADDR, Address, 5);

    /*
     * @brief  Set transmit mode and power up the module
     */
    temp_data &=~ (RECEIVE << PRIM_RX);
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG, temp_data);

    /*
     * @brief  Enable CE pin
     */
    NRF24_ENABLE();
}

/**
 * @brief  NRF24L01 Check Data Available function
 * @param[in]  SPIx: SPI handle
 * @param[in]  pipe: Pipe number
 * @return  None
 * @details  This function checks if there is data available in the specified pipe of the NRF24L01 module.
 *  If data is available, it clears the RX_DR flag in the STATUS register.
 */
void NRF24_CHECK_DATA_AVAILABLE(SPI_HandleTypeDef *SPIx,uint8_t pipe)
{
    uint8_t status;
    /*
     * @brief  Reads the status register of the NRF24L01 module
     */
    SPI_Read_Byte(SPIx, NRF24L01_REG_STATUS, &status);
    /*
     * @brief  Checks if there is data available in the specified pipe
     */
    if((status & (1 << RX_DR)) && (status & (pipe << 1))){
        SPI_Write_Byte(SPIx, NRF24L01_REG_STATUS,(1 << RX_DR));
    }
}

/**
 * @brief  NRF24L01 Set Power Amplifier Level function
 * @param[in]  SPIx: SPI handle
 * @param[in]  PA_Level: Power Amplifier level
 * @return  None
 * @details  This function sets the Power Amplifier level of the NRF24L01 module.
 *  The PA_Level parameter is a bitmask that specifies the desired power amplifier level.
 *  The function writes the specified PA_Level to the RF_SETUP register of the NRF24L01 module.
 */
void NRF24_SET_PA(SPI_HandleTypeDef* SPIx, PA_LEVEL PA_Level)
{
    uint8_t temp_data = 0;
    temp_data = (PA_Level << RF_PWR);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_SETUP, &temp_data);
}

void NRF24_DataRate(SPI_HandleTypeDef* SPIx, uint8_t data_rate)
{
    uint8_t temp_data = 0;
    if(data_rate == _1Mbps) temp_data &=~ ((1<<RF_DR_LOW)|(1<<RF_DR_HIGH));
    else if(data_rate == _2Mbps) temp_data |= (1<<RF_DR_HIGH);
    else if(data_rate == _250Kbps) temp_data |= (1<<RF_DR_LOW);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RF_SETUP, &temp_data);
}
void NRF24_Retries(SPI_HandleTypeDef *SPIx, retries_time_t retries_times, retransmit_delay_t retransmit_delay)
{
    uint8_t temp_data = 0;
    temp_data |= (retries_times << ARC)|(retransmit_delay << ARD);
    SPI_Write_Byte(SPIx, NRF24L01_REG_SETUP_RETR, &temp_data);
}

void NRF24_PAYLOADSIZE(SPI_HandleTypeDef *SPIx, payload_size_t* size)
{ 
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P0, size);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P1, size);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P2, size); 
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P3, size);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P4, size);
    SPI_Write_Byte(SPIx, NRF24L01_REG_RX_PW_P5, size);
}
void NRF24_Init(SPI_HandleTypeDef* SPIx, uint16_t MHz, PA_LEVEL PA_level)
{
    uint8_t temp_data = 0;
    NRF24_DISABLE();
    NRF24_SELECT();

    // Reset the NRF24L01 before setup
    NRF24_Reset(SPIx);

    // FLush Rx Packet 
    NRF24_FLUSH_RX(SPIx);

    // FLush Tx Packet
    NRF24_FLUSH_TX(SPIx);

    // Set retry connection times and retry delay 
    NRF24_Retries(SPIx,_5_times, _250uS);
    
    // Set data rate 
    NRF24_DataRate(SPIx, _1Mbps);
    // Disable Dynamic payload 
    temp_data = 0x00u;
    SPI_Write_Byte(SPIx, NRF24L01_REG_DYNPD, &temp_data);

    // Enable auto acknoledge of all pipes 
    temp_data = 0;
    temp_data = 0x3Fu;
    SPI_Write_Byte(SPIx, NRF24L01_REG_EN_AA, &temp_data); 
    
    //Set payload length at maximum 32 bytes
    NRF24_PAYLOADSIZE(SPIx, PAYLOAD_PIPE_32_BYTE);


    // Start setting configuration 
    temp_data = 0;
    temp_data |= (POWER_UP << PWR_UP);
    SPI_Write_Byte(SPIx, NRF24L01_REG_CONFIG, &temp_data);

    // Set Power Amplifier level
    NRF24_SET_PA(SPIx, PA_level);

    // Select Channel 
    NRF24_Select_Channel(SPIx, MHz);

    // Reset Status Register
    temp_data = 0;
    temp_data |= (1 << RX_DR)|(1 << TX_DS)|(1 << MAX_RT);
    SPI_Write_Byte(SPIx, NRF24L01_REG_STATUS, &temp_data);
    // Enable CE pin after configuration
    NRF24_UNSELECT(); 
    NRF24_ENABLE();
}
/**
 * @brief  NRF24L01 Transmit function
 * @param[in]  SPIx: SPI handle
 * @param[in,out]  pData: Pointer to the buffer to store transmitted data
 * @return  None
 * @details  This function sends the payload command to the NRF24L01 module and transmits data from the specified buffer.
 *  After transmitting the data, it checks the FIFO status and flushes the TX FIFO if necessary.
 *  @note  The NRF24L01 module must be initialized and configured before using this function.
 */
void NRF24_Transmit(SPI_HandleTypeDef *SPIx, uint8_t *pData)
{
    uint8_t cmd = 0;

    // Send payload command
    cmd = NRF24L01_CMD_W_TX_PAYLOAD;
    NRF24L01_SEND_CMD(SPIx, &cmd);

    NRF24_SELECT();

    // Send payload
    HAL_SPI_Transmit(SPIx, pData, PAYLOAD_PIPE_32_BYTE, SPI_TIMEOUT);

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

/**
 * @brief  NRF24L01 Receive function
 * @param[in]  SPIx: SPI handle
 * @param[in,out]  pData: Pointer to the buffer to store received data
 * @return  None
 * @details  This function sends the received command to the NRF24L01 module and receives data from the specified pipe.
 *  After receiving the data, it flushes the RX FIFO.
 *  @note  The NRF24L01 module must be initialized and configured before using this function.
 */
void NRF24_Receive(SPI_HandleTypeDef *SPIx, uint8_t *pData)
{
    uint8_t cmd = 0;

    // Send Received command
    cmd = NRF24L01_CMD_R_RX_PAYLOAD;
    NRF24L01_SEND_CMD(SPIx, &cmd);

    // Received data from pipe
    NRF24_SELECT();
    HAL_SPI_Receive(SPIx, pData, PAYLOAD_PIPE_32_BYTE, SPI_TIMEOUT);
    NRF24_UNSELECT();
    HAL_Delay(1);

    cmd = NRF24L01_CMD_FLUSH_RX;
    NRF24L01_SEND_CMD(SPIx, &cmd);
}

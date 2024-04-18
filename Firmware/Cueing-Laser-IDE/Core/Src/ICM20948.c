#include "ICM20948.h"
/********************* NCS pin control functions *********************/
inline static void CS_ACTIVATE()
{
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}
inline static void CS_DEACTIVATE()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

/********************* USER BANK SELECTION functions *********************/


/********************* Read/Write registers functions *********************/
void SPI_WriteRegisters(SPI_HandleTypeDef *SPIx, uint8_t Register, uint8_t* Data, uint8_t Data_length)
{
    CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, Data, Data_length, SPI_TIMEOUT);
    CS_DEACTIVATE();
}

void USER_BANK_SELECTION(SPI_HandleTypeDef *SPIx, uint8_t USER_BANK_SELECT)
{   
    // uint8_t user_bank_options = 0; 
    // user_bank_options = (USER_BANK_SELECT << USER_BANK); // select the user bank 
    CS_ACTIVATE();
    SPI_WriteRegisters(SPIx, REG_BANK_SEL, &USER_BANK_SELECT, 1);
    CS_DEACTIVATE();
}
void SPI_ReadRegisters( SPI_HandleTypeDef *SPIx,uint8_t reg, uint8_t* pData) 
{
	reg = reg | 0x80;
	CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, 1, SPI_TIMEOUT);
	CS_DEACTIVATE();
}

void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
    USER_BANK_SELECTION(SPIx, 0);
    SPI_ReadRegisters(SPIx, WHO_AM_I, who_am_i);
}

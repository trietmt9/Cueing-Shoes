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
void SPI_WriteByte(SPI_HandleTypeDef *SPIx, uint8_t Register, uint8_t* Data, uint8_t Data_length)
{
    CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, Data, Data_length, SPI_TIMEOUT);
    CS_DEACTIVATE();
}

void SPI_ReadByte(SPI_HandleTypeDef *SPIx,uint8_t reg, uint8_t* pData) 
{
	reg = reg | 0x80;
	CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, 1, SPI_TIMEOUT);
	CS_DEACTIVATE();
}

void SPI_WriteRegisters(usrbank_sel user_bank, SPI_HandleTypeDef *SPIx, uint8_t Register, uint8_t* Data, uint8_t Data_length)
{
    USER_BANK_SELECTION(SPIx, user_bank);
    CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, Data, Data_length, SPI_TIMEOUT);
    CS_DEACTIVATE();
}

void SPI_ReadRegisters(usrbank_sel user_bank, SPI_HandleTypeDef *SPIx,uint8_t reg, uint8_t* pData) 
{
	reg = reg | 0x80;
    USER_BANK_SELECTION(SPIx, user_bank);
	CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, 1, SPI_TIMEOUT);
	CS_DEACTIVATE();
}
void USER_BANK_SELECTION(SPI_HandleTypeDef *SPIx, uint8_t USER_BANK_SELECT)
{   
    uint8_t user_bank_options = 0; 
    user_bank_options = (USER_BANK_SELECT << USER_BANK); // select the user bank 
    CS_ACTIVATE();
    SPI_WriteByte(SPIx, REG_BANK_SEL, &user_bank_options, 1);
    CS_DEACTIVATE();
}
void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
    SPI_ReadRegisters(BANK_0, SPIx, WHO_AM_I, who_am_i);
}

void ICM20948_Init(SPI_HandleTypeDef *SPIx)
{
    uint8_t temp_data = 0;
    temp_data |= (1 << CLKSEL)|( 1 << SLEEP)|(1 << DEVICE_RESET);
    SPI_WriteRegisters(BANK_0, SPIx, PWR_MGMT_1, &temp_data, sizeof(temp_data));

    temp_data |= (1 << GYRO_FCHOICE)|(1 << GYRO_FS_SEL)|(1 << GYRO_DLPFCFG);
    SPI_WriteRegisters(BANK_2, SPIx, GYRO_CONFIG_1, &temp_data, sizeof(temp_data));
}

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

void USER_BANK_SELECTION(SPI_HandleTypeDef *SPIx, uint8_t USER_BANK_SELECT)
{   
    uint8_t user_bank_options = 0; 
    user_bank_options = (USER_BANK_SELECT << USER_BANK); // select the user bank 
    CS_ACTIVATE();
    SPI_WriteByte(SPIx, REG_BANK_SEL, &user_bank_options, 1);
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

void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
    SPI_ReadRegisters(BANK_0, SPIx, WHO_AM_I, who_am_i);
}

void ICM20948_Init(SPI_HandleTypeDef *SPIx)
{
    uint8_t temp_data = 0;
    uint8_t who_am_i = 0;
    WHO_AM_I_CHECK(SPIx, &who_am_i);
    if(who_am_i == ICM20948_AVAILABLE)
    {
        // disable I2C slave module
        temp_data = (I2C_DISABLE<< I2C_IF_DIS);
        SPI_WriteRegisters(BANK_0, SPIx, USER_CTRL, &temp_data, sizeof(temp_data));

        // reset the IMU, in this configuration temp will equal to 0xC1u 
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL)|( SLEEP_EN << SLEEP)|(DEVICE_RST << DEVICE_RESET);
        SPI_WriteRegisters(BANK_0, SPIx, PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // exit sleep mode
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL);
        SPI_WriteRegisters(BANK_0, SPIx, PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // choose sample rate divider at 100, temp = 0x64u
        temp_data = 0;
        temp_data |= (GYRO_SMPLRT_DIV_100 << GYRO_SMPLRT_DIV_REG);
        SPI_WriteRegisters(BANK_2, SPIx, GYRO_SMPLRT_DIV, &temp_data, sizeof(temp_data));

        // enable low-pass filter  
        // choose full scale rate at 500 dps with 3 decibels bandwith is 51.2Hz and Noise bandwith is 73.3Hz
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << GYRO_FCHOICE)|(GYRO_FS_500DPS << GYRO_FS_SEL)|(GYRO_51_2Hz_73_3Hz << GYRO_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, GYRO_CONFIG_1, &temp_data, sizeof(temp_data));

        // enable output data rate alignment 
        temp_data = 0;
        temp_data |= (ODR_ALGIN_ON << ODR_ALIGN_EN_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ODR_ALIGN_EN, &temp_data, sizeof(temp_data));

        // select sample rate divider for Accelerometer 
        temp_data = 0;
        temp_data |= (0<<ACCEL_SMPLRT_DIV_1_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_SMPLRT_DIV_1, &temp_data, sizeof(temp_data));

        temp_data = 0;
        temp_data |= (0<<ACCEL_SMPLRT_DIV_2_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_SMPLRT_DIV_2, &temp_data, sizeof(temp_data));

        // select accelerometer at 4g 
        // enable low-pass filter 
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << ACCEL_FCHOICE)|(ACCEL_FS_4G << ACCEL_FS_SEL)|(ACCEL_111_4Hz_136Hz << ACCEL_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_CONFIG_1, &temp_data, sizeof(temp_data));


    }
}

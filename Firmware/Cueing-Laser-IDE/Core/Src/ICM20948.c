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

void SPI_ReadRegisters(usrbank_sel user_bank, SPI_HandleTypeDef *SPIx,uint8_t reg, uint8_t* pData, uint8_t Data_length) 
{
	reg = reg | 0x80;
    USER_BANK_SELECTION(SPIx, user_bank);
	CS_ACTIVATE();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, Data_length, SPI_TIMEOUT);
	CS_DEACTIVATE();
}

void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
    SPI_ReadRegisters(BANK_0, SPIx, WHO_AM_I, who_am_i, 1);
}



void ICM20948_Read(SPI_HandleTypeDef* SPIx, gyro_accel_data_t* data)
{
    // Read accelerometer data
    uint8_t accel_data[6];
    SPI_ReadRegisters(BANK_0, SPIx, ACCEL_XOUT_H, accel_data, 6);
    data->RAW_Ax = (int16_t)(accel_data[0]<<8|accel_data[1]);
    data->RAW_Ay = (int16_t)(accel_data[2]<<8|accel_data[3]);
    data->RAW_Az = (int16_t)(accel_data[4]<<8|accel_data[5]);

    // Convert accelerometer raw data to true accelerometer data 
    data->Ax = (double)data->RAW_Ax / 8;
    data->Ay = (double)data->RAW_Ay / 8;
    data->Az = (double)data->RAW_Az / 8;

    // Read gyroscope data
    uint8_t gyro_data[6];
    SPI_ReadRegisters(BANK_0, SPIx, GYRO_XOUT_H, gyro_data, 6);
    data->RAW_Gx = (int16_t)(gyro_data[0]<<8|gyro_data[1]);
    data->RAW_Gy = (int16_t)(gyro_data[2]<<8|gyro_data[3]);
    data->RAW_Gz = (int16_t)(gyro_data[4]<<8|gyro_data[5]);

    // Convert gyroscope raw data to true gyroscope data
    data->Gx = (double)data->RAW_Gx / 250;
    data->Gy = (double)data->RAW_Gy / 250;
    data->Gz = (double)data->RAW_Gz / 250;

}
// void GYRO_BIAS_CANCELLATION(SPI_HandleTypeDef *SPIx)
// {
//     int16_t Gx_bias, Gy_bias, Gz_bias;
//     gyro_accel_data_t data; 
//     int32_t x_bias, y_bias, z_bias = 0;
//     for(int sample; sample < SAMPLE_RATE; sample++)
//     {
//         ICM20948_Read(SPIx, &data);
//         x_bias += (int32_t)data.Gx;
//         y_bias += (int32_t)data.Gy;
//         z_bias += (int32_t)data.Gz;
//         HAL_Delay(2);
//     }
//     Gx_bias = -(int16_t)(x_bias / 4000);
//     Gy_bias = -(int16_t)(y_bias / 4000);
//     Gz_bias = -(int16_t)(z_bias / 4000);
//     HAL_Delay(20);
//     SPI_WriteRegisters(BANK_2, SPIx, XG_OFFS_USER_H, (uint8_t*)(Gx_bias<<8), 1);
//     SPI_WriteRegisters(BANK_2, SPIx, XG_OFFS_USER_L, (uint8_t*) Gx_bias, 1);
//     SPI_WriteRegisters(BANK_2, SPIx, YG_OFFS_USER_H, (uint8_t*)(Gy_bias<<8), 1);
//     SPI_WriteRegisters(BANK_2, SPIx, YG_OFFS_USER_L, (uint8_t*) Gy_bias, 1);
//     SPI_WriteRegisters(BANK_2, SPIx, ZG_OFFS_USER_H, (uint8_t*)(Gz_bias<<8), 1);
//     SPI_WriteRegisters(BANK_2, SPIx, ZG_OFFS_USER_L, (uint8_t*) Gz_bias, 1);

// }

void ICM20948_Init(SPI_HandleTypeDef *SPIx)
{
    uint8_t temp_data = 0;
    uint8_t who_am_i = 0;
    WHO_AM_I_CHECK(SPIx, &who_am_i);
    if(who_am_i == ICM20948_AVAILABLE)
    {
        // Disable I2C slave module
        temp_data = (I2C_DISABLE<< I2C_IF_DIS);
        SPI_WriteRegisters(BANK_0, SPIx, USER_CTRL, &temp_data, sizeof(temp_data));

        // Reset the IMU, in this configuration temp will equal to 0xC1u 
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL)|( SLEEP_EN << SLEEP)|(DEVICE_RST << DEVICE_RESET);
        SPI_WriteRegisters(BANK_0, SPIx, PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // Exit sleep mode
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL);
        SPI_WriteRegisters(BANK_0, SPIx, PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // Bias cancellation

        // GYRO_BIAS_CANCELLATION(SPIx);
        // Choose sample rate divider at 100, temp = 0x64u
        temp_data = 0;
        temp_data |= (GYRO_SMPLRT_DIV_100 << GYRO_SMPLRT_DIV_REG);
        SPI_WriteRegisters(BANK_2, SPIx, GYRO_SMPLRT_DIV, &temp_data, sizeof(temp_data));

        // Enable low-pass filter  
        // Choose full scale rate at 500 dps with 3 decibels band-with is 51.2Hz and Noise band-with is 73.3Hz
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << GYRO_FCHOICE)|(GYRO_FS_500DPS << GYRO_FS_SEL)|(GYRO_11_6Hz_17_8Hz << GYRO_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, GYRO_CONFIG_1, &temp_data, sizeof(temp_data));

        // Enable output data rate alignment 
        temp_data = 0;
        temp_data |= (ODR_ALGIN_ON << ODR_ALIGN_EN_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ODR_ALIGN_EN, &temp_data, sizeof(temp_data));

        // Select sample rate divider for Accelerometer 
        temp_data = 0;
        temp_data |= (0<<ACCEL_SMPLRT_DIV_1_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_SMPLRT_DIV_1, &temp_data, sizeof(temp_data));

        temp_data = 0;
        temp_data |= (0x0A<<ACCEL_SMPLRT_DIV_2_REG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_SMPLRT_DIV_2, &temp_data, sizeof(temp_data));

        // Select accelerometer at 4g 
        // Enable low-pass filter 
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << ACCEL_FCHOICE)|(ACCEL_FS_8G << ACCEL_FS_SEL)|(ACCEL_111_4Hz_136Hz << ACCEL_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, ACCEL_CONFIG_1, &temp_data, sizeof(temp_data));

    }
}
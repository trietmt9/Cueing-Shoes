/*
*
* ICM20948.c 
* Created on: April/15/2024
* Author: trietmt9 
*
*/
#include "ICM20948.h"

/********************* Serial Peripheral Interface (SPI) abstract functions *********************/

/********************* NCS pin control functions *********************/
/**
 * @brief Activates the chip select pin.
 *
 * This function Activates the chip select pin (GPIOA4) by setting it to GPIO_PIN_RESET.
 */
inline static void CS_SELECT()
{
    HAL_Delay(100);
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Deactivates the chip select pin.
 *
 * This function deactivates the chip select pin (GPIOA4) by setting it to GPIO_PIN_SET.
 */
inline static void CS_UNSELECT(void)
{
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);
}

/********************* Read/Write single byte functions *********************/
/**
 * @brief Writes a single byte of data to a register in the ICM20948.
 *
 * @param[in] SPIx The SPI handle to use for communication.
 * @param[in] Register The register address to write to.
 * @param[out] pData The pointer to the byte of data to be written.
 * @param[in] Data_length The length of the data to write.
 *
 * This function writes a single byte of data to the specified register in the ICM20948.
 * It first writes the register address with the most significant bit set to 1,
 * then writes the data from the provided pointer.
 *
 * @note The SPI handle must be initialized and configured before calling this function.
 */
void SPI_WriteByte(SPI_HandleTypeDef *SPIx, uint8_t Register, uint8_t* pData, uint8_t Data_length)
{
    CS_SELECT();
    HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, pData, Data_length, SPI_TIMEOUT);
    CS_UNSELECT();
}

/**
 * @brief Reads a single byte of data from a register in the ICM20948.
 *
 * @param[in] SPIx The SPI handle to use for communication.
 * @param[in] reg The register address to read from.
 * @param[out] pData The pointer to the byte of data to be read.
 *
 * This function reads a single byte of data from the specified register in the ICM20948.
 * It first writes the register address with the most significant bit set to 1,
 * then reads the data from the ICM20948.
 *
 * @note The SPI handle must be initialized and configured before calling this function.
 */
void SPI_ReadByte(SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t* pData)
{
    reg |= 0x80;
    CS_SELECT();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, 1, SPI_TIMEOUT);
    CS_UNSELECT();
}


/********************* USER BANK SELECTION functions *********************/
/**
 * @brief Selects the user bank for the ICM20948.
 * 
 * @param user_bank The user bank to select.
 * @param SPIx The SPI handle.
 */
void USER_BANK_SELECTION(SPI_HandleTypeDef *SPIx, uint8_t USER_BANK_SELECT)
{
    uint8_t user_bank_options = 0; 
    user_bank_options = (USER_BANK_SELECT << USER_BANK); // select the user bank 
    CS_SELECT();
    SPI_WriteByte(SPIx, ICM20948_REG_BANK_SEL, &user_bank_options, 1);
    CS_UNSELECT();
}

/********************* Read/Write registers functions *********************/
/**
 * @brief Writes a sequence of data to a register in the ICM20948.
 * 
 * @param user_bank The user bank to write to.
 * @param SPIx The SPI handle.
 * @param Register The register to write to.
 * @param Data The data to write.
 * @param Data_length The length of the data to write.
 */
void SPI_WriteRegisters(usrbank_sel user_bank, SPI_HandleTypeDef *SPIx, uint8_t Register, uint8_t* Data, uint8_t Data_length)
{
    USER_BANK_SELECTION(SPIx, user_bank);
    CS_SELECT();
    HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
    HAL_SPI_Transmit(SPIx, Data, Data_length, SPI_TIMEOUT);
    CS_UNSELECT();
}

/**
 * @brief Reads a sequence of data from a register in the ICM20948.
 *
 * @param user_bank The user bank to read from.
 * @param SPIx The SPI handle.
 * @param Register The register to read from.
 * @param pData The data to read into.
 * @param Data_length The length of the data to read.
 */
void SPI_ReadRegisters(usrbank_sel user_bank, SPI_HandleTypeDef *SPIx, uint8_t reg, uint8_t* pData, uint8_t Data_length) 
{
    reg |= 0x80;
    USER_BANK_SELECTION(SPIx, user_bank);
    CS_SELECT();
    HAL_SPI_Transmit(SPIx, &reg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPIx, pData, Data_length, SPI_TIMEOUT);
    CS_UNSELECT();
}

/**
 * @brief Reads the WHO_AM_I register of the ICM20948.
 *
 * @param[in] SPIx The SPI handle to use for communication.
 * @param[out] who_am_i The pointer to the byte of data to be read.
 */
void WHO_AM_I_CHECK(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
    SPI_ReadRegisters(BANK_0, SPIx, ICM20948_REG_WHO_AM_I, who_am_i, 1);
}


/**
 * @brief Reads the accelerometer and gyroscope data from the ICM20948 sensor.
 *
 * @param[in] SPIx The SPI handle to use for communication.
 * @param[out] data A pointer to a struct containing the accelerometer and gyroscope data.
 */
void ICM20948_Read(SPI_HandleTypeDef* SPIx, gyro_accel_data_t* data)
{
    // Read accelerometer data
    uint8_t accel_data[6];
    SPI_ReadRegisters(BANK_0, SPIx, ICM20948_REG_ACCEL_XOUT_H, accel_data, 6);
    data->RAW_Ax = (int16_t)(accel_data[0]<<8|accel_data[1]);
    data->RAW_Ay = (int16_t)(accel_data[2]<<8|accel_data[3]);
    data->RAW_Az = (int16_t)(accel_data[4]<<8|accel_data[5]);

    // Convert accelerometer raw data to true accelerometer data
    data->Ax = (double)data->RAW_Ax / 8;
    data->Ay = (double)data->RAW_Ay / 8;
    data->Az = (double)data->RAW_Az / 8;

    // Read gyroscope data
    uint8_t gyro_data[6];
    SPI_ReadRegisters(BANK_0, SPIx, ICM20948_REG_GYRO_XOUT_H, gyro_data, 6);
    data->RAW_Gx = (int16_t)(gyro_data[0]<<8|gyro_data[1]);
    data->RAW_Gy = (int16_t)(gyro_data[2]<<8|gyro_data[3]);
    data->RAW_Gz = (int16_t)(gyro_data[4]<<8|gyro_data[5]);

    // Convert gyroscope raw data to true gyroscope data
    data->Gx = (double)data->RAW_Gx / 500;
    data->Gy = (double)data->RAW_Gy / 500;
    data->Gz = (double)data->RAW_Gz / 500;

    // compute Roll Pitch angle
    data->Roll = atan2(data->Ay, sqrt((data->Ax*data->Ax) + (data->Az*data->Az))) * 180 / M_PI;
    data->Pitch = atan2(-data->Ax, sqrt((data->Ay*data->Ay) + (data->Az*data->Az))) * 180 / M_PI;

}

/**
 * @brief Initial setting for the accelerometer and gyroscope data of the ICM20948 sensor.
 *
 * @param[in] SPIx The SPI handle to use for communication.
 */
void ICM20948_Init(SPI_HandleTypeDef *SPIx)
{
    uint8_t temp_data = 0;
    uint8_t who_am_i = 0;
    WHO_AM_I_CHECK(SPIx, &who_am_i);
    if(who_am_i == ICM20948_AVAILABLE)
    {
        // Disable I2C slave module
        temp_data = (I2C_DISABLE<< I2C_IF_DIS);
        SPI_WriteRegisters(BANK_0, SPIx, ICM20948_REG_USER_CTRL, &temp_data, sizeof(temp_data));

        // Reset the IMU, in this configuration temp will equal to 0xC1u 
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL)|( SLEEP_EN << SLEEP)|(DEVICE_RST << DEVICE_RESET);
        SPI_WriteRegisters(BANK_0, SPIx, ICM20948_REG_PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // Exit sleep mode
        temp_data = 0; 
        temp_data |= (BEST_CLK_SRC << CLKSEL);
        SPI_WriteRegisters(BANK_0, SPIx, ICM20948_REG_PWR_MGMT_1, &temp_data, sizeof(temp_data));

        // Bias cancellation

        // GYRO_BIAS_CANCELLATION(SPIx);
        // Choose sample rate divider at 100, temp = 0x64u
        temp_data = 0;
        temp_data |= (GYRO_SMPLRT_DIV_100 << GYRO_SMPLRT_DIV);
        SPI_WriteRegisters(BANK_2, SPIx, GYRO_SMPLRT_DIV, &temp_data, sizeof(temp_data));

        // Enable low-pass filter  
        // Choose full scale rate at 500 dps with 3 decibels band-with is 51.2Hz and Noise band-with is 73.3Hz
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << GYRO_FCHOICE)|(GYRO_FS_500DPS << GYRO_FS_SEL)|(GYRO_11_6Hz_17_8Hz << GYRO_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, ICM20948_REG_GYRO_CONFIG_1, &temp_data, sizeof(temp_data));

        // Enable output data rate alignment 
        temp_data = 0;
        temp_data |= (ODR_ALGIN_ON << ODR_ALIGN_EN);
        SPI_WriteRegisters(BANK_2, SPIx, ODR_ALIGN_EN, &temp_data, sizeof(temp_data));

        // Select sample rate divider for Accelerometer 
        temp_data = 0;
        temp_data |= (ACCEL_SMPLRT_DIV_1000<<ACCEL_SMPLRT_DIV_2);
        SPI_WriteRegisters(BANK_2, SPIx, ICM20948_REG_ACCEL_SMPLRT_DIV_2, &temp_data, sizeof(temp_data));

        // Select accelerometer at 8g 
        // Enable low-pass filter 
        temp_data = 0;
        temp_data |= (DLPF_ENABLED << ACCEL_FCHOICE)|(ACCEL_FS_8G << ACCEL_FS_SEL)|(ACCEL_111_4Hz_136Hz << ACCEL_DLPFCFG);
        SPI_WriteRegisters(BANK_2, SPIx, ICM20948_REG_ACCEL_CONFIG_1, &temp_data, sizeof(temp_data));

    }
}

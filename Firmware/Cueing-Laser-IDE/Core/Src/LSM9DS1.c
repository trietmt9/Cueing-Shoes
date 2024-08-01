/*
*
* LSM9DS1.c
* Created on: June/20/2024
* Author: trietmt9
*
*/
#include "LSM9DS1.h"
#include "main.h"

/**
 * @brief This function writes data to a specified register of the LSM9DS1 sensor using SPI communication.
 *
 * @param SPIx Pointer to the SPI handle structure that contains the configuration information for the SPI module.
 * @param csPin The GPIO pin connected to the LSM9DS1 sensor's chip select (CS) pin.
 * @param Register The address of the register to write data to.
 * @param pData Pointer to the data buffer that contains the data to be written.
 * @param Data_length The number of bytes of data to be written.
 *
 * @return None.
 *
 */
void SPI_WriteRegisters(SPI_HandleTypeDef *SPIx, uint8_t csPin, uint8_t Register, uint8_t* pData, uint8_t Data_length)
{
  HAL_GPIO_WritePin(GPIOA, csPin, RESET);
  HAL_SPI_Transmit(SPIx, &Register, sizeof(Register), SPI_TIMEOUT);
  HAL_SPI_Transmit(SPIx, pData, Data_length, SPI_TIMEOUT);
  HAL_GPIO_WritePin(GPIOA, csPin, SET);
}

/**
 * @brief This function reads data from a specified register of the LSM9DS1 sensor using SPI communication.
 *
 * @param[in] SPIx Pointer to the SPI handle structure that contains the configuration information for the SPI module.
 * @param[in] csPin The GPIO pin connected to the LSM9DS1 sensor's chip select (CS) pin.
 * @param[in] reg The address of the register to read data from.
 * @param[out] pData Pointer to the data buffer that will contain the read data.
 * @param[in] Data_length The number of bytes of data to be read.
 *
 * @return None.
 *
 */
void SPI_ReadRegisters(SPI_HandleTypeDef *SPIx, uint8_t csPin, uint8_t reg, uint8_t* pData, uint8_t Data_length)
{
  reg = 0x80 | (reg & 0x3F);
  HAL_GPIO_WritePin(GPIOA, csPin, RESET);
	HAL_SPI_Transmit(SPIx, &reg, sizeof(reg), SPI_TIMEOUT);
  HAL_SPI_Receive(SPIx, pData, Data_length , SPI_TIMEOUT);
  HAL_GPIO_WritePin(GPIOA, csPin, SET);
}

/**
 * @brief This function reads the "Who Am I" register of the LSM9DS1 sensor using SPI communication.
 *
 * @param[in] SPIx Pointer to the SPI handle structure that contains the configuration information for the SPI module.
 * @param[out] who_am_i Pointer to the data buffer that will contain the read "Who Am I" register value.
 *
 * @return None.
 *
 */
void IsWhoAmI(SPI_HandleTypeDef *SPIx, uint8_t* who_am_i)
{
  SPI_ReadRegisters(SPIx, IMU_AG_CS_Pin, WHO_AM_I, who_am_i, sizeof(who_am_i));
}


/**
 * @brief This function reads data from the LSM9DS1 sensor using SPI communication.
 *
 * @param[in] SPIx Pointer to the SPI handle structure that contains the configuration information for the SPI module.
 * @param[in] pData Pointer to the data buffer that will contain the read data.
 *
 * @return None.
 *
 * @note This function assumes that the GPIO and SPI peripherals have been properly initialized and configured.
 * @note The function sets the CS pin to low before initiating the SPI communication, reads the register data,
 * and then sets the CS pin back to high to complete the read operation.
 */
void LSM9DS1_Read(SPI_HandleTypeDef *SPIx, data_t *pData)
{
  uint8_t gData[6];
  SPI_ReadRegisters(SPIx, IMU_AG_CS_Pin, OUT_X_H_G, gData, 6);
  pData->RawData_t.Gx_RAW  = (int16_t)((gData[0] << 8) | gData[1]);
  pData->RawData_t.Gy_RAW  = (int16_t)((gData[2] << 8) | gData[3]);
  pData->RawData_t.Gy_RAW  = (int16_t)((gData[4] << 8) | gData[5]);
  
  pData->Data_t.Gx = pData->RawData_t.Gx_RAW/2000;
  pData->Data_t.Gy = pData->RawData_t.Gy_RAW/2000;
  pData->Data_t.Gz = pData->RawData_t.Gz_RAW/2000;
  
  uint8_t xlData[6];
  SPI_ReadRegisters(SPIx, IMU_AG_CS_Pin, OUT_X_H_XL, xlData, 6);
  pData->RawData_t.Ax_RAW  = (int16_t)((xlData[0] << 8) | xlData[1]);
  pData->RawData_t.Ay_RAW  = (int16_t)((xlData[2] << 8) | xlData[3]);
  pData->RawData_t.Az_RAW  = (int16_t)((xlData[4] << 8) | xlData[5]);
  
  pData->Data_t.Ax = pData->RawData_t.Ax_RAW/4;
  pData->Data_t.Ay = pData->RawData_t.Ay_RAW/4;
  pData->Data_t.Az = pData->RawData_t.Az_RAW/4;
}

/**
 * @brief This function initializes the LSM9DS1 sensor using SPI communication.
 *
 * @param[in] SPIx Pointer to the SPI handle structure that contains the configuration information for the SPI module.
 * 
 */
void LSM9DS1_Init(SPI_HandleTypeDef* SPIx)
{
  uint8_t who_am_i, temp;
  IsWhoAmI(SPIx,&who_am_i);
  // Setup bandwidth and DPS of IMU's gyroscope 
  temp = 0;
  temp = 0x78;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG1_G, &temp, sizeof(temp));
  // Configure output and interrupts selection 
  temp = 0;
  temp = 0x00;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG2_G, &temp, sizeof(temp));
  // HIGH PASS FILTER
  temp = 0;
  temp = 0x48u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG3_G, &temp, sizeof(temp));
  // ORIENT
  temp = 0;
  temp = 0x00u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, ORIENT_CFG_G, &temp, sizeof(temp));
  // interrupts
  temp = 0;
  temp = 0x00u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, INT_GEN_SRC_G, &temp, sizeof(temp));
  //Gyro Output enable
  temp = 0;
  temp = 0x38u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG4, &temp, sizeof(temp));
  // Accelerometer output enable
  temp = 0;
  temp = 0x78u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG5_XL, &temp, sizeof(temp));
  // BW and ODR
  temp = 0;
  temp = 0x16u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG6_XL, &temp, sizeof(temp));
  // cut off frequency = 16Hz and Output data rate = 59.5Hz
  temp = 0;
  temp = 0x02u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG7_XL, &temp, sizeof(temp));
  //
  temp = 0;
  temp = 0x40u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG8, &temp, sizeof(temp));
  //
  temp = 0;
  temp = 0x07u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, CTRL_REG9, &temp, sizeof(temp));
  //
  temp = 0;
  temp = 0x00u;
  SPI_WriteRegisters(SPIx, IMU_AG_CS_Pin, FIFO_CTRL, &temp, sizeof(temp));

}

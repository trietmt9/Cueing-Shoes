#include "LSM9DS.h"
Gyro_settings *Gyro;
XL_settings *Accel;
void CS_Enable()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
}
void CS_Disable()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
}
void writeByte(SPI_TypeDef *SPI_x ,uint8_t reg, uint8_t data)
{   
	CS_Enable();
    HAL_SPI_Transmit(SPI_x, &reg, 1, SPI_TIMEOUT); 
    HAL_SPI_Transmit(SPI_x, &data, 1, SPI_TIMEOUT);
    CS_Disable();
}

uint8_t readByte(SPI_TypeDef*SPI_x ,uint8_t reg, uint8_t* data)
{
    uint8_t tempReg = (reg|0x80);
    CS_Enable();
    HAL_SPI_Transmit(SPI_x, &tempReg, 1, SPI_TIMEOUT);
    HAL_SPI_Receive(SPI_x, &data, 1, SPI_TIMEOUT);
    CS_Disable();
    return data;
}

void Gyro_Init(SPI_TypeDef* SPI_x)
{
    uint8_t tempReg; 
    Gyro->enabled = 1;
    Gyro->scale = FS_G_500;
    Gyro->sampleRate = ODR_G_119_Hz;
    tempReg |= (1 << 3);
    tempReg |= (3 << 5);
    writeByte(SPI_x, CTRL_REG1_G, &tempReg);
}

void XL_Init(SPI_TypeDef* SPI_x)
{
    uint8_t tempReg; 
    Accel->enabled = 1;
    Accel->scale = ODR_XL_50_Hz;
    Accel->sampleRate = A_ABW_408;
    tempReg |= (2 << 3);
    tempReg |= (3 << 5);
    writeByte(SPI_x, CTRL_REG6_XL, &tempReg);
}

uint8_t LSM9DS_Init(SPI_TypeDef* SPI_x)
{
    uint8_t who_am_i;
    uint8_t tempReg;
    // tempReg |= (1 << 2);
    // writeByte(SPI_x, CTRL_REG9, tempReg);
    readByte(SPI_x, WHO_AM_I,&who_am_i);
    Gyro_Init(SPI_x);
    XL_Init(SPI_x);
    return who_am_i;

}

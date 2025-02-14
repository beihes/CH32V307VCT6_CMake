/*
 * i2cx.c
 *
 *  Created on: 2025年2月10日
 *      Author: 26448
 */

#include "i2cx.h"

/*********************************************************************
 * @fn      I2C1_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void I2C1_Init(uint32_t bound, uint16_t address)
{
}

/*********************************************************************
 * @fn      I2C2_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void I2C2_Init(uint32_t bound, uint16_t address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2C_InitTypeDef I2C_InitTSturcture = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2C_InitTSturcture);

    I2C_Cmd(I2C2, ENABLE);
}

void I2CX_ReadOneByte_Start(I2C_TypeDef *I2CX, DriverAddr driverAddr)
{
    while (I2C_GetFlagStatus(I2CX, I2C_FLAG_BUSY) != RESET)
        ;
    I2C_GenerateSTART(I2CX, ENABLE);

    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, driverAddr, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
}

void I2CX_ReadOneByte_8Bit(I2C_TypeDef *I2CX, uint16_t ReadAddr)
{
    I2C_SendData(I2CX, (uint8_t)(ReadAddr & 0x00FF));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
}

void I2CX_ReadOneByte_16Bit(I2C_TypeDef *I2CX, uint16_t ReadAddr)
{
    I2C_SendData(I2CX, (uint8_t)(ReadAddr >> 8));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_SendData(I2CX, (uint8_t)(ReadAddr & 0x00FF));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
}

uint8_t I2CX_ReadOneByte_End(I2C_TypeDef *I2CX, DriverAddr driverAddr)
{
    uint8_t temp = 0;
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, driverAddr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    while (I2C_GetFlagStatus(I2CX, I2C_FLAG_RXNE) == RESET)
        I2C_AcknowledgeConfig(I2CX, DISABLE);
    temp = I2C_ReceiveData(I2CX);
    I2C_GenerateSTOP(I2CX, ENABLE);
    return temp;
}

void I2CX_WriteOneByte_Start(I2C_TypeDef *I2CX, DriverAddr driverAddr)
{
    while (I2C_GetFlagStatus(I2CX, I2C_FLAG_BUSY) != RESET)
        ;
    I2C_GenerateSTART(I2CX, ENABLE);

    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, driverAddr, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
}

void I2CX_WriteOneByte_8Bit(I2C_TypeDef *I2CX, uint16_t writeAddr)
{
    I2C_SendData(I2CX, (uint8_t)(writeAddr & 0x00FF));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
}

void I2CX_WriteOneByte_16Bit(I2C_TypeDef *I2CX, uint16_t writeAddr)
{
    I2C_SendData(I2CX, (uint8_t)(writeAddr >> 8));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_SendData(I2CX, (uint8_t)(writeAddr & 0x00FF));
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
}

void I2CX_WriteOneByte_End(I2C_TypeDef *I2CX, uint8_t dataToWrite)
{
    if (I2C_GetFlagStatus(I2CX, I2C_FLAG_TXE) != RESET)
    {
        I2C_SendData(I2CX, dataToWrite);
    }

    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTOP(I2CX, ENABLE);
}
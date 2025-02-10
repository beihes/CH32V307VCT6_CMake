/*
 * spi1.c
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#include "spi1.h"

/*******************************************************************************
 * Function Name  : SPI1_Init
 * Description    : SPI1操作相关引脚和硬件初始化
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    /* CS# */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_2);

    /* SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* MISO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1, &SPI_InitStructure);
    // SPI1->HSCR |= 0x01;                                                         // Enable High Speed Read
    SPI_Cmd(SPI1, ENABLE);
}

/*********************************************************************
 * @fn      SPI1_ReadWrite_Byte
 *
 * @brief   SPI1 发送并接收一个字节（轮询方式）。
 *
 * @param   TxData - 需要发送的 1 字节数据。
 *
 * @return  接收到的 1 字节数据；如果超时，返回 0。
 */
uint8_t SPI1_ReadWrite_Byte(uint8_t TxData)
{
    uint8_t i = 0;
    // 1. 等待 TXE（发送缓冲区空标志位）为 1，表示可以发送数据
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
    {
        i++;
        if (i > 200) // 超过 200 次循环未准备好，返回 0，防止死循环
            return 0;
    }
    // 2. 发送 1 字节数据
    SPI_I2S_SendData(SPI1, TxData);
    i = 0; // 重置计数器
    // 3. 等待 RXNE（接收缓冲区非空标志位）为 1，表示接收完成
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
    {
        i++;
        if (i > 200) // 超时判断，避免 SPI 设备未响应导致死循环
            return 0;
    }
    // 4. 读取 SPI 接收到的数据并返回
    return SPI_I2S_ReceiveData(SPI1);
}

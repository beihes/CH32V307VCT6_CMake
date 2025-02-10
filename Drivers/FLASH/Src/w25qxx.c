/********************************** (C) COPYRIGHT *******************************
 * File Name          : SPI_FLAH.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : SPI FLASH芯片操作相关文件
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include <w25qxx.h>
// #include <SW_UDISK.h>
#include "spi1.h"

/******************************************************************************/
/* 常、变量定义 */
volatile uint8_t w25xxxType = 0x00;         /* FLASH芯片类型: 0: W25XXX系列 */
volatile uint32_t w25xxxID = 0x00;          /* FLASH芯片ID号 */
volatile uint32_t w25xxxSectorCount = 0x00; /* FLASH芯片扇区数 */
volatile uint16_t w25xxxSectorSize = 0x00;  /* FLASH芯片扇区大小 */

/*******************************************************************************
 * Function Name  : W25XXX_Init
 * Description    : FLASH芯片操作相关引脚和硬件初始化
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint8_t W25XXX_Init(void)
{
    SPI1_Init();
    return ENABLE;
}

/*******************************************************************************
 * Function Name  : W25XXX_SPI_SendByte
 * Description    : SPI发送一个字节数据
 * Input          : byte: 要发送的字节
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint8_t W25XXX_SPI_SendByte(uint8_t byte)
{
    return SPI1_ReadWrite_Byte(byte);
}

/*******************************************************************************
 * Function Name  : W25XXX_SPI_ReadByte
 * Description    : SPI接收一个字节数据
 * Input          : None
 * Output         : None
 * Return         : 返回接收的字节数据
 *******************************************************************************/
uint8_t W25XXX_SPI_ReadByte(void)
{
    return SPI1_ReadWrite_Byte(0xFF);
}

/*******************************************************************************
 * Function Name  : W25XXX_ReadID
 * Description    : 读取FLASH芯片ID
 * Input          : None
 * Output         : None
 * Return         : 返回4个字节,最高字节为0x00,
 *                  次高字节为Manufacturer ID(0xEF),
 *                  次低字节为Memory Type ID
 *                  最低字节为Capacity ID
 *                  W25X40BL返回: 0xEF、0x30、0x13
 *                  W25X10BL返回: 0xEF、0x30、0x11
 *******************************************************************************/
uint32_t W25XXX_ReadID(void)
{
    uint32_t dat;
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_JEDEC_ID);
    dat = (uint32_t)W25XXX_SPI_SendByte(DEF_DUMMY_BYTE) << 16;
    dat |= (uint32_t)W25XXX_SPI_SendByte(DEF_DUMMY_BYTE) << 8;
    dat |= W25XXX_SPI_SendByte(DEF_DUMMY_BYTE);
    W25XXX_PIN_CS_HIGH();
    return (dat);
}

/*******************************************************************************
 * Function Name  : W25XXX_WriteEnable
 * Description    : FLASH芯片允许写操作
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_WriteEnable(void)
{
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_WREN);
    W25XXX_PIN_CS_HIGH();
}

/*******************************************************************************
 * Function Name  : W25XXX_WriteDisable
 * Description    : FLASH芯片禁止写操作
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_WriteDisable(void)
{
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_WRDI);
    W25XXX_PIN_CS_HIGH();
}

/*******************************************************************************
 * Function Name  : W25XXX_ReadStatusReg
 * Description    : FLASH芯片读取状态寄存器
 * Input          : None
 * Output         : None
 * Return         : 返回寄存器值
 *******************************************************************************/
uint8_t W25XXX_ReadStatusReg(void)
{
    uint8_t status;

    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_RDSR);
    status = W25XXX_SPI_ReadByte();
    W25XXX_PIN_CS_HIGH();
    return (status);
}

/*******************************************************************************
 * Function Name  : W25XXX_IC_Check
 * Description    : FLASH芯片检测
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_IC_Check(void)
{
    uint32_t count;
    /* 读取FLASH芯片ID号 */
    w25xxxID = W25XXX_ReadID();
    printf("w25xxxID: %08lX\n", (uint32_t)w25xxxID); // 打印读取到的芯片ID
    /* 根据芯片型号，判断容量大小 */
    w25xxxType = 0x00;        // 初始化芯片类型
    w25xxxSectorCount = 0x00; // 初始化扇区数量
    w25xxxSectorSize = 0x00;  // 初始化扇区大小
    switch (w25xxxID)         // 根据芯片ID选择不同的容量
    {
    /* W25XXX系列芯片 */
    case W25X10_FLASH_ID: /* 0xEF3011-----1M bit */
        count = 1;        // 1M bit
        break;
    case W25X20_FLASH_ID: /* 0xEF3012-----2M bit */
        count = 2;        // 2M bit
        break;
    case W25X40_FLASH_ID: /* 0xEF3013-----4M bit */
        count = 4;        // 4M bit
        break;
    case W25X80_FLASH_ID: /* 0xEF4014-----8M bit */
        count = 8;        // 8M bit
        break;
    case W25Q16_FLASH_ID1: /* 0xEF3015-----16M bit */
    case W25Q16_FLASH_ID2: /* 0xEF4015-----16M bit */
        count = 16;        // 16M bit
        break;
    case W25Q32_FLASH_ID1: /* 0xEF4016-----32M bit */
    case W25Q32_FLASH_ID2: /* 0xEF6016-----32M bit */
        count = 32;        // 32M bit
        break;
    case W25Q64_FLASH_ID1: /* 0xEF4017-----64M bit */
    case W25Q64_FLASH_ID2: /* 0xEF6017-----64M bit */
        count = 64;        // 64M bit
        break;
    case W25Q128_FLASH_ID1: /* 0xEF4018-----128M bit */
    case W25Q128_FLASH_ID2: /* 0xEF6018-----128M bit */
        count = 128;        // 128M bit
        break;

    case W25Q256_FLASH_ID1: /* 0xEF4019-----256M bit */
    case W25Q256_FLASH_ID2: /* 0xEF6019-----256M bit */
        count = 256;        // 256M bit
        break;
    default:
        if ((w25xxxID != 0xFFFFFFFF) || (w25xxxID != 0x00000000)) // 如果ID不是无效ID
        {
            count = 16; // 默认容量设置为16MB
        }
        else
        {
            count = 0x00; // 无效ID，容量设置为0
        }
        break;
    }
    /* 将容量从Mbit转换为字节，计算Flash芯片的总字节数 */
    count = ((uint32_t)count * 1024) * ((uint32_t)1024 / 8); // Mbit转换为字节
    /* 保存Flash芯片的扇区数和扇区大小 */
    if (count)
    {
        // 一个扇区4KB
        w25xxxSectorCount = count / 4096; // 计算扇区数量
        w25xxxSectorSize = 4096;          // 设置扇区大小
    }
}

/*******************************************************************************
 * Function Name  : W25XXX_Erase_Sector
 * Description    : FLASH扇区数据擦除
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_Erase_Sector(uint32_t address)
{
    uint8_t temp;
    W25XXX_WriteEnable();
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_SECTOR_ERASE);
    W25XXX_SPI_SendByte((uint8_t)(address >> 16));
    W25XXX_SPI_SendByte((uint8_t)(address >> 8));
    W25XXX_SPI_SendByte((uint8_t)address);
    W25XXX_PIN_CS_HIGH();
    do
    {
        temp = W25XXX_ReadStatusReg();
    } while (temp & 0x01);
}

/*******************************************************************************
 * Function Name  : W25XXX_RD_Block_Start
 * Description    : FLASH块数据读取开始
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_RD_Block_Start(uint32_t address)
{
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_READ);
    W25XXX_SPI_SendByte((uint8_t)(address >> 16));
    W25XXX_SPI_SendByte((uint8_t)(address >> 8));
    W25XXX_SPI_SendByte((uint8_t)address);
}

/*******************************************************************************
 * Function Name  : W25XXX_RD_Buffer
 * Description    : FLASH块数据读取
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_RD_Buffer(uint8_t *pbuf, uint32_t len)
{
    while (len--)
    {
        *pbuf++ = W25XXX_SPI_ReadByte();
    }
}

/*******************************************************************************
 * Function Name  : W25XXX_RD_Block_End
 * Description    : FLASH块数据读取结束
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_RD_Block_End(void)
{
    W25XXX_PIN_CS_HIGH();
}

/*******************************************************************************
 * Function Name  : W25XXX_WR_Page
 * Description    : 写入一块数据
 *                  注：当前程序不支持跨页写数据
 * Input          : address----准备写的首地址
 *                  len--------准备写的数据长度
 *                  *pbuf------准备写入的缓冲区地址
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_WR_Page(uint8_t *pbuf, uint32_t address, uint32_t len)
{
    uint8_t temp;
    W25XXX_WriteEnable();
    W25XXX_PIN_CS_LOW();
    W25XXX_SPI_SendByte(CMD_W25XXX_BYTE_PROG);
    W25XXX_SPI_SendByte((uint8_t)(address >> 16));
    W25XXX_SPI_SendByte((uint8_t)(address >> 8));
    W25XXX_SPI_SendByte((uint8_t)address);
    if (len > SPI_FLASH_PerWritePageSize)
    {
        len = SPI_FLASH_PerWritePageSize;
    }
    while (len--)
    {
        W25XXX_SPI_SendByte(*pbuf++);
    }
    W25XXX_PIN_CS_HIGH();
    do
    {
        temp = W25XXX_ReadStatusReg();
    } while (temp & 0x01);
}

/*******************************************************************************
 * Function Name  : W25XXX_WR_Block
 * Description    : 写入一块数据
 * Input          : address----准备写的首地址
 *                  len--------准备写的数据长度
 *                  *pbuf------准备写入的缓冲区地址
 * Output         : None
 * Return         : None
 *******************************************************************************/
void W25XXX_WR_Block(uint8_t *pbuf, uint32_t address, uint32_t len)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = address % SPI_FLASH_PageSize;
    count = SPI_FLASH_PageSize - Addr;
    NumOfPage = len / SPI_FLASH_PageSize;
    NumOfSingle = len % SPI_FLASH_PageSize;

    if (Addr == 0)
    {
        if (NumOfPage == 0)
        {
            W25XXX_WR_Page(pbuf, address, len);
        }
        else
        {
            while (NumOfPage--)
            {
                W25XXX_WR_Page(pbuf, address, SPI_FLASH_PageSize);
                address += SPI_FLASH_PageSize;
                pbuf += SPI_FLASH_PageSize;
            }
            W25XXX_WR_Page(pbuf, address, NumOfSingle);
        }
    }
    else
    {
        if (NumOfPage == 0)
        {
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                W25XXX_WR_Page(pbuf, address, count);
                address += count;
                pbuf += count;
                W25XXX_WR_Page(pbuf, address, temp);
            }
            else
            {
                W25XXX_WR_Page(pbuf, address, len);
            }
        }
        else
        {
            len -= count;
            NumOfPage = len / SPI_FLASH_PageSize;
            NumOfSingle = len % SPI_FLASH_PageSize;
            W25XXX_WR_Page(pbuf, address, count);
            address += count;
            pbuf += count;
            while (NumOfPage--)
            {
                W25XXX_WR_Page(pbuf, address, SPI_FLASH_PageSize);
                address += SPI_FLASH_PageSize;
                pbuf += SPI_FLASH_PageSize;
            }
            if (NumOfSingle != 0)
            {
                W25XXX_WR_Page(pbuf, address, NumOfSingle);
            }
        }
    }
}

// 读取指定地址的数据
void W25XXX_RD_Block(uint8_t *pbuf, uint32_t address, uint32_t len)
{
    W25XXX_PIN_CS_LOW();                             // 使能芯片选择信号
    SPI1_ReadWrite_Byte(CMD_W25XXX_READ);            // 发送读取数据命令
    SPI1_ReadWrite_Byte((uint8_t)((address) >> 16)); // 发送地址的高8位
    SPI1_ReadWrite_Byte((uint8_t)((address) >> 8));  // 发送地址的中间8位
    SPI1_ReadWrite_Byte((uint8_t)address);           // 发送地址的低8位
    while (len--)
    {
        *pbuf++ = SPI1_ReadWrite_Byte(0XFF); // 读取指定长度的数据
    }
    W25XXX_PIN_CS_HIGH(); // 禁用芯片选择信号
}
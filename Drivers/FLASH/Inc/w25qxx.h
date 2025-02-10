/********************************** (C) COPYRIGHT *******************************
 * File Name          : SPI_FLAH.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : SPI FLASH操作头文件
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: 该软件（修改或未修改）和二进制文件用于南京青恒微电子公司制造的
 * 微控制器。
 *******************************************************************************/
#ifndef __W25QXX_H
#define __W25QXX_H

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* 头文件包含 */
#include <stdio.h>
#include <string.h>
#include <stdint.h> // 引入标准数据类型头文件

/******************************************************************************/
/* SPI FLASH相关引脚定义 */
#define W25XXX_PIN_CS_LOW() (GPIOA->BCR = GPIO_Pin_2)   // 拉低FLASH芯片片选引脚
#define W25XXX_PIN_CS_HIGH() (GPIOA->BSHR = GPIO_Pin_2) // 拉高FLASH芯片片选引脚

/******************************************************************************/
/* SPI闪存操作指令定义 */
#define CMD_W25XXX_READ 0x03               /* 读取闪存内存，速度为25 MHz */
#define CMD_W25XXX_SECTOR_ERASE 0x20       /* 擦除4 KB内存区域 */
#define CMD_W25XXX_BYTE_PROG 0x02          /* 编程一个字节数据 */
#define CMD_W25XXX_RDSR 0x05               /* 读取状态寄存器 */
#define CMD_W25XXX_EWSR 0x50               /* 启用写状态寄存器 */
#define CMD_W25XXX_WREN 0x06               /* 启用写操作 */
#define CMD_W25XXX_WRDI 0x04               /* 禁用写操作 */
#define CMD_W25XXX_RELEASE_POWER_DOWN 0xAB /* 唤醒内存 */
#define CMD_W25XXX_POWER_DOWN 0xB9         /* 进入低功耗模式 */
#define CMD_W25XXX_CHIP_ERASE 0xC7         /* 擦除整片内存 */
#define CMD_W25XXX_MANUF_ID 0x90           /* uint16_t 低位ID */
#define CMD_W25XXX_JEDEC_ID 0x9F           /* 读取JEDEC 高位ID */

/******************************************************************************/
/* FLASH操作相关的填充值定义 */
#define DEF_DUMMY_BYTE 0xFF /* 无效字节，通常用于占位 */

/******************************************************************************/
/* FLASH操作相关参数定义 */
#define SPI_FLASH_SectorSize 4096      /* SPI闪存每个扇区的大小为4096字节 */
#define SPI_FLASH_PageSize 256         /* SPI闪存每个页面的大小为256字节 */
#define SPI_FLASH_PerWritePageSize 256 /* 每次写入页面的大小为256字节 */

/******************************************************************************/
/* SPI FLASH芯片类型定义 */
#define DEF_TYPE_W25XXX 0 /* W25XXX系列闪存芯片 */

/******************************************************************************/
/* SPI FLASH芯片型号定义 */

/* W25XXX系列芯片型号ID */
#define W25X10_FLASH_ID 0xEF3011   /* 1M bit的闪存芯片 */
#define W25X20_FLASH_ID 0xEF3012   /* 2M bit的闪存芯片 */
#define W25X40_FLASH_ID 0xEF3013   /* 4M bit的闪存芯片 */
#define W25X80_FLASH_ID 0xEF4014   /* 8M bit的闪存芯片 */
#define W25Q16_FLASH_ID1 0xEF3015  /* 16M bit的闪存芯片 */
#define W25Q16_FLASH_ID2 0xEF4015  /* 16M bit的闪存芯片 */
#define W25Q32_FLASH_ID1 0xEF4016  /* 32M bit的闪存芯片 */
#define W25Q32_FLASH_ID2 0xEF6016  /* 32M bit的闪存芯片 */
#define W25Q64_FLASH_ID1 0xEF4017  /* 64M bit的闪存芯片 */
#define W25Q64_FLASH_ID2 0xEF6017  /* 64M bit的闪存芯片 */
#define W25Q128_FLASH_ID1 0xEF4018 /* 128M bit的闪存芯片 */
#define W25Q128_FLASH_ID2 0xEF6018 /* 128M bit的闪存芯片 */
#define W25Q256_FLASH_ID1 0xEF4019 /* 256M bit的闪存芯片 */
#define W25Q256_FLASH_ID2 0xEF6019 /* 256M bit的闪存芯片 */

    /******************************************************************************/
    /* 外部变量声明 */

    /* SPI闪存芯片相关变量 */
    extern volatile uint8_t w25xxxType;         /* FLASH芯片类型：0表示W25XXX系列 */
    extern volatile uint32_t w25xxxID;          /* FLASH芯片的ID */
    extern volatile uint32_t w25xxxSectorCount; /* FLASH芯片的扇区数量 */
    extern volatile uint16_t w25xxxSectorSize;  /* FLASH芯片每个扇区的大小 */

    /******************************************************************************/
    /* 外部函数声明 */

    /* 初始化FLASH操作相关端口 */
    extern uint8_t W25XXX_Init(void);

    /* 发送一个字节到SPI闪存 */
    extern uint8_t W25XXX_SPI_SendByte(uint8_t byte);

    /* 从SPI闪存读取一个字节 */
    extern uint8_t W25XXX_SPI_ReadByte(void);

    /* 读取SPI闪存芯片的ID */
    extern uint32_t W25XXX_ReadID(void);

    /* 启用FLASH芯片的写操作 */
    extern void W25XXX_WriteEnable(void);

    /* 禁用FLASH芯片的写操作 */
    extern void W25XXX_WriteDisable(void);

    /* 读取FLASH芯片的状态寄存器 */
    extern uint8_t W25XXX_ReadStatusReg(void);

    /* 检查FLASH芯片的状态 */
    extern void W25XXX_IC_Check(void);

    /* 擦除指定地址的FLASH扇区 */
    extern void W25XXX_Erase_Sector(uint32_t address);

    /* 开始读取一个FLASH数据块 */
    extern void W25XXX_RD_Block_Start(uint32_t address);

    /* 读取指定长度的FLASH数据块 */
    extern void W25XXX_RD_Buffer(uint8_t *pbuf, uint32_t len);

    /* 结束读取FLASH数据块 */
    extern void W25XXX_RD_Block_End(void);

    /* 向FLASH指定地址写入数据块 */
    extern void W25XXX_WR_Block(uint8_t *pbuf, uint32_t address, uint32_t len);

    extern void W25XXX_RD_Block(uint8_t *pbuf, uint32_t address, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __W25QXX_H */

/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v30x_usbhs_device.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/11/20
 * Description        : USB2.0 高速设备操作相关头文件
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * 注意：该软件（无论是否修改过）和二进制文件仅供南京清华微电子生产的
 * 微控制器使用。
 *******************************************************************************/
#ifndef __CH32V30X_USBHS_DEVICE_H__
#define __CH32V30X_USBHS_DEVICE_H__

/*******************************************************************************/
/* 头文件包含 */
#include "debug.h"
#include "string.h"
#include "ch32v30x_usb.h"
#include "usb_desc.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************/
/* 宏定义 */

/* 通用设置 */
#define pUSBHS_SetupReqPak ((PUSB_SETUP_REQ)USBHS_EP0_Buf) // 设置USB设备的请求包指针

#define DEF_UEP_IN 0x80  // 端点IN标志
#define DEF_UEP_OUT 0x00 // 端点OUT标志

/* 端点编号 */
#define DEF_UEP_BUSY 0x01 // 端点忙标志
#define DEF_UEP_FREE 0x00 // 端点空闲标志
#define DEF_UEP_NUM 16    // 端点数量
#define DEF_UEP0 0x00     // 端点0
#define DEF_UEP1 0x01     // 端点1
#define DEF_UEP2 0x02     // 端点2
#define DEF_UEP3 0x03     // 端点3
#define DEF_UEP4 0x04     // 端点4
#define DEF_UEP5 0x05     // 端点5
#define DEF_UEP6 0x06     // 端点6
#define DEF_UEP7 0x07     // 端点7
#define DEF_UEP8 0x08     // 端点8
#define DEF_UEP9 0x09     // 端点9
#define DEF_UEP10 0x0A    // 端点10
#define DEF_UEP11 0x0B    // 端点11
#define DEF_UEP12 0x0C    // 端点12
#define DEF_UEP13 0x0D    // 端点13
#define DEF_UEP14 0x0E    // 端点14
#define DEF_UEP15 0x0F    // 端点15

/* USB端点控制寄存器基地址 */
#define USBHSD_UEP_CFG_BASE 0x40023410
#define USBHSD_UEP_BUF_MOD_BASE 0x40023418
#define USBHSD_UEP_RXDMA_BASE 0x40023420
#define USBHSD_UEP_TXDMA_BASE 0x4002345C
#define USBHSD_UEP_TXLEN_BASE 0x400234DC
#define USBHSD_UEP_TXCTL_BASE 0x400234DE

/* 设置端点控制 */
#define USBHSD_UEP_TX_EN(N) ((uint16_t)(0x01 << N))        // 启用端点传输
#define USBHSD_UEP_RX_EN(N) ((uint16_t)(0x01 << (N + 16))) // 启用端点接收
#define USBHSD_UEP_DOUBLE_BUF(N) ((uint16_t)(0x01 << N))   // 启用双缓冲

#define DEF_UEP_DMA_LOAD 0 // 使用DMA传输数据
#define DEF_UEP_CPY_LOAD 1 // 使用memcpy将数据移到缓冲区

/* 端点DMA地址配置 */
#define USBHSD_UEP_RXDMA(N) (*((volatile uint32_t *)(USBHSD_UEP_RXDMA_BASE + (N - 1) * 0x04)))
#define USBHSD_UEP_RXBUF(N) ((uint8_t *)(*((volatile uint32_t *)(USBHSD_UEP_RXDMA_BASE + (N - 1) * 0x04))) + 0x20000000)
#define USBHSD_UEP_TXCTRL(N) (*((volatile uint8_t *)(USBHSD_UEP_TXCTL_BASE + (N - 1) * 0x04)))
#define USBHSD_UEP_TXDMA(N) (*((volatile uint32_t *)(USBHSD_UEP_TXDMA_BASE + (N - 1) * 0x04)))
#define USBHSD_UEP_TXBUF(N) ((uint8_t *)(*((volatile uint32_t *)(USBHSD_UEP_TXDMA_BASE + (N - 1) * 0x04))) + 0x20000000)
#define USBHSD_UEP_TLEN(N) (*((volatile uint16_t *)(USBHSD_UEP_TXLEN_BASE + (N - 1) * 0x04)))

/* USB速度类型 */
#define USBHS_SPEED_TYPE_MASK ((uint8_t)(0x03)) // USB速度掩码
#define USBHS_SPEED_LOW ((uint8_t)(0x02))       // 低速模式
#define USBHS_SPEED_FULL ((uint8_t)(0x00))      // 全速模式
#define USBHS_SPEED_HIGH ((uint8_t)(0x01))      // 高速模式

/* 测试模式 */
#define TEST_MASK 0x03
#define TEST_SE0 0x00    // 测试SE0
#define TEST_PACKET 0x01 // 测试数据包
#define TEST_J 0x02      // 测试J状态
#define TEST_K 0x03      // 测试K状态

    /******************************************************************************/
    /* 变量声明 */

    /* 设置请求值 */
    extern const uint8_t *pUSBHS_Descr; // USB描述符指针

    /* 设置请求 */
    extern volatile uint8_t USBHS_SetupReqCode;   // 请求代码
    extern volatile uint8_t USBHS_SetupReqType;   // 请求类型
    extern volatile uint16_t USBHS_SetupReqValue; // 请求值
    extern volatile uint16_t USBHS_SetupReqIndex; // 请求索引
    extern volatile uint16_t USBHS_SetupReqLen;   // 请求长度

    /* USB设备状态 */
    extern volatile uint8_t USBHS_DevConfig;      // USB设备配置
    extern volatile uint8_t USBHS_DevAddr;        // USB设备地址
    extern volatile uint8_t USBHS_DevSleepStatus; // USB设备睡眠状态
    extern volatile uint8_t USBHS_DevEnumStatus;  // USB设备枚举状态

    /* 端点传输忙标志 */
    extern volatile uint8_t USBHS_Endp_Busy[]; // 端点传输忙标志数组

    /* 端点缓冲区 */
    extern __attribute__((aligned(4))) uint8_t USBHS_EP0_Buf[]; // 端点0缓冲区

    /********************************************************************************/
    /* 函数声明 */
    extern void USBHS_RCC_Init(void);                                                         // 初始化USBHS时钟
    extern void USBHS_Device_Endp_Init(void);                                                 // 初始化USB设备端点
    extern void USBHS_Device_Init(FunctionalState sta);                                       // 初始化USB设备
    extern void USBHS_Device_SetAddress(uint32_t address);                                    // 设置USB设备地址
    extern void USBHS_IRQHandler(void);                                                       // USBHS中断处理函数
    extern void USBHS_Sleep_WakeUp_Cfg(void);                                                 // USBHS睡眠唤醒配置
    extern uint8_t USBHS_Endp_DataUp(uint8_t endp, uint8_t *pbuf, uint16_t len, uint8_t mod); // 端点数据上传函数

#ifdef __cplusplus
}
#endif

#endif /* __CH32V30X_USBHS_DEVICE_H__ */

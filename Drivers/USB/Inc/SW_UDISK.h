/********************************** (C) COPYRIGHT *******************************
 * File Name          : SW_UDISK.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : SW_UDISK.c 的头文件
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * 注意：该软件（无论是否修改过）和二进制文件仅供南京清华微电子生产的
 * 微控制器使用。
 *******************************************************************************/
#ifndef __SW_UDISK_H__
#define __SW_UDISK_H__

#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* BulkOnly Mass Storage设备特殊类请求 */
#define CMD_UDISK_RESET 0xFF       // 重置命令
#define CMD_UDISK_GET_MAX_LUN 0xFE // 获取最大逻辑单元号命令

/******************************************************************************/
/* USB大容量存储类SCSI命令 */
#define CMD_U_TEST_READY 0x00           // 测试准备命令
#define CMD_U_REZERO_UNIT 0x01          // 复位单元命令
#define CMD_U_REQUEST_SENSE 0x03        // 请求感觉命令
#define CMD_U_FORMAT_UNIT 0x04          // 格式化单元命令
#define CMD_U_INQUIRY 0x12              // 查询命令
#define CMD_U_MODE_SELECT 0x15          // 模式选择命令
#define CMD_U_RELEASE 0x17              // 释放命令
#define CMD_U_MODE_SENSE 0x1A           // 模式感知命令
#define CMD_U_START_STOP 0x1B           // 启动/停止命令
#define CMD_U_SEND_DIAG 0x1D            // 发送诊断命令
#define CMD_U_PREVT_REMOVE 0x1E         // 移除命令
#define CMD_U_READ_FORMAT_CAPACITY 0x23 // 读取格式化容量命令
#define CMD_U_READ_CAPACITY 0x25        // 读取容量命令
#define CMD_U_READ10 0x28               // 读取10命令
#define CMD_U_WRITE10 0x2A              // 写入10命令
#define CMD_U_SEEK10 0x2B               // 定位10命令
#define CMD_U_WR_VERIFY10 0x2E          // 写入验证10命令
#define CMD_U_VERIFY10 0x2F             // 验证10命令
#define CMD_U_SYNC_CACHE 0x35           // 同步缓存命令
#define CMD_U_READ_TOC 0x43             // 读取Toc命令
#define CMD_U_MODE_SENSE2 0x5A          // 模式感知2命令
#define CMD_U_READ12 0xA8               // 读取12命令
#define CMD_U_WRITE12 0xAA              // 写入12命令

/******************************************************************************/
/* 指定当前小容量U盘大小为32K */
#define MY_UDISK_SIZE 0x00000040

    /******************************************************************************/
    /* BulkOnly传输结构定义 */
    typedef union _BULK_ONLY_CMD
    {
        uint8_t buf[31];
        struct
        {
            uint8_t mCBW_Sig[4];     // CBW标识
            uint8_t mCBW_Tag[4];     // CBW标签
            uint8_t mCBW_DataLen[4]; // 数据长度
            uint8_t mCBW_Flag;       // 标志
            uint8_t mCBW_LUN;        // 逻辑单元号
            uint8_t mCBW_CB_Len;     // CB命令长度
            uint8_t mCBW_CB_Buf[16]; // CB命令内容
        } mCBW;
        struct
        {
            uint8_t mCSW_Sig[4];     // CSW标识
            uint8_t mCSW_Tag[4];     // CSW标签
            uint8_t mCSW_Residue[4]; // 残余数据
            uint8_t mCSW_Status;     // CSW状态
        } mCSW;
        struct
        {
            uint8_t ErrorCode;      // 错误代码
            uint8_t Reserved1;      // 保留字段
            uint8_t SenseKey;       // 感觉键
            uint8_t Information[4]; // 信息
            uint8_t SenseLength;    // 感觉长度
            uint8_t Reserved2[4];   // 保留字段
            uint8_t SenseCode;      // 感觉代码
            uint8_t SenseCodeQua;   // 感觉代码质量
            uint8_t Reserved3[4];   // 保留字段
        } ReqSense;
    } BULK_ONLY_CMD;

    /******************************************************************************/
    /* 当前U盘相关宏定义(根据需要可以修改) */

#define DEF_DEBUG_PRINTF 1     // 启用调试打印
#define MEDIUM_INTERAL_FLASH 1 // 内部闪存存储介质
#define MEDIUM_SPI_W25XXX 2     // SPI闪存存储介质

// #define STORAGE_MEDIUM             MEDIUM_INTERAL_FLASH
#define STORAGE_MEDIUM MEDIUM_SPI_W25XXX // 设置存储介质为SPI闪存

#if (STORAGE_MEDIUM == MEDIUM_SPI_W25XXX)
#define DEF_CFG_DISK_SEC_SIZE 4096                  /* 磁盘扇区大小 */
#define DEF_FLASH_SECTOR_SIZE 4096                  /* FLASH扇区大小 */
#define DEF_UDISK_SECTOR_SIZE DEF_CFG_DISK_SEC_SIZE /* U盘扇区大小 */
#elif (STORAGE_MEDIUM == MEDIUM_INTERAL_FLASH)
#define DEF_CFG_DISK_SEC_SIZE 512                   /* 磁盘扇区大小 */
#define DEF_FLASH_SECTOR_SIZE 512                   /* FLASH扇区大小 */
#define DEF_UDISK_SECTOR_SIZE DEF_CFG_DISK_SEC_SIZE /* U盘扇区大小 */
#endif

#define DEF_UDISK_PACK_512 512 // U盘数据包大小为512字节
#define DEF_UDISK_PACK_64 64   // U盘数据包大小为64字节

/******************************************************************************/
/* 当前U盘状态相关宏定义 */
#define DEF_UDISK_EN_FLAG 0x01 // U盘使能标志

/******************************************************************************/
/* 当前U盘传输状态相关宏定义 */
#define DEF_UDISK_BLUCK_UP_FLAG 0x01   // U盘块上传标志
#define DEF_UDISK_BLUCK_DOWN_FLAG 0x02 // U盘块下载标志
#define DEF_UDISK_CSW_UP_FLAG 0x04     // U盘CSW上传标志

    /******************************************************************************/
    /* 常量和变量外扩 */
    extern volatile uint8_t Udisk_CBW_Tag_Save[4]; // 保存CBW标签
    extern volatile uint8_t Udisk_Sense_Key;       // 感觉键
    extern volatile uint8_t Udisk_Sense_ASC;       // 感觉ASC
    extern volatile uint8_t Udisk_CSW_Status;      // CSW状态

    extern volatile uint32_t UDISK_Transfer_DataLen; // 数据传输长度
    extern volatile uint32_t UDISK_Cur_Sec_Lba;      // 当前扇区LBA
    extern volatile uint16_t UDISK_Sec_Pack_Count;   // 扇区数据包数量
    extern volatile uint16_t UDISK_Pack_Size;        // 数据包大小

    extern BULK_ONLY_CMD mBOC; // BulkOnly命令结构体

    extern volatile uint8_t Udisk_Status;          // U盘状态
    extern volatile uint8_t Udisk_Transfer_Status; // U盘传输状态
    extern volatile uint32_t Udisk_Capability;     // U盘容量

    extern uint8_t UDISK_Inquity_Tab[];              // U盘查询表
    extern uint8_t const UDISK_Rd_Format_Capacity[]; // U盘格式化容量
    extern uint8_t const UDISK_Rd_Capacity[];        // U盘容量
    extern uint8_t const UDISK_Mode_Sense_1A[];      // 模式感知1A
    extern uint8_t const UDISK_Mode_Senese_5A[];     // 模式感知5A

    /******************************************************************************/
    /* 函数外扩 */
    extern void UDISK_CMD_Deal_Status(uint8_t key, uint8_t asc, uint8_t status); // 处理命令状态
    extern void UDISK_CMD_Deal_Fail(void);                                       // 处理命令失败
    extern void UDISK_SCSI_CMD_Deal(void);                                       // 处理SCSI命令
    extern void UDISK_Bulk_UpData(void);                                         // 上传数据
    extern void UDISK_Up_CSW(void);                                              // 上传CSW
    extern void UDISK_Up_OnePack(void);                                          // 上传单个数据包
    extern void UDISK_Out_EP_Deal(uint8_t *pbuf, uint16_t packlen);              // 处理外部端点
    extern void UDISK_In_EP_Deal(void);                                          // 处理输入端点
    extern void UDISK_Down_OnePack(uint8_t *pbuf, uint16_t packlen);             // 下载单个数据包

#ifdef __cplusplus
}
#endif

#endif /* __SW_UDISK_H__ */

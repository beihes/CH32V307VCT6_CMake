/*
 * usbDesc.h
 *
 *  Created on: 2025年1月28日
 *      Author: 26448
 */

#ifndef DRIVERS_USB_INC_USB_DESC_H_
#define DRIVERS_USB_INC_USB_DESC_H_

/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : usb_desc.c 的头文件
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * 注意：该软件（无论是否修改过）和二进制文件仅供南京清华微电子生产的
 * 微控制器使用。
 *******************************************************************************/

#include "debug.h"

/******************************************************************************/
// 全局定义
/* 文件版本 */
#define DEF_FILE_VERSION 0x01
/* USB设备信息定义 */
#define DEF_USB_VID 0x1A86 // 厂商ID (Vendor ID)
#define DEF_USB_PID 0xFE10 // 产品ID (Product ID)

/* USB设备描述符，设备序列号(bcdDevice) */
#define DEF_IC_PRG_VER DEF_FILE_VERSION

/******************************************************************************/
// USB设备端点大小定义
#define DEF_USBD_UEP0_SIZE 64 /* USB HS/FS 设备端点0的大小 */
/* HS（高速模式） */
#define DEF_USBD_HS_PACK_SIZE 512      /* USB HS设备最大批量/中断包大小 */
#define DEF_USBD_HS_ISO_PACK_SIZE 1024 /* USB HS设备最大同步包大小 */
/* FS（全速模式） */
#define DEF_USBD_FS_PACK_SIZE 64       /* USB FS设备最大批量/中断包大小 */
#define DEF_USBD_FS_ISO_PACK_SIZE 1023 /* USB FS设备最大同步包大小 */
/* LS（低速模式） */
#define DEf_USBD_LS_UEP0_SIZE 8  /* USB LS设备端点0的大小 */
#define DEF_USBD_LS_PACK_SIZE 64 /* USB LS设备最大中断包大小 */

/* HS端点大小 */
#define DEF_USB_EP1_HS_SIZE DEF_USBD_HS_PACK_SIZE
#define DEF_USB_EP2_HS_SIZE DEF_USBD_HS_PACK_SIZE
#define DEF_USB_EP3_HS_SIZE DEF_USBD_HS_PACK_SIZE
#define DEF_USB_EP4_HS_SIZE DEF_USBD_HS_PACK_SIZE
#define DEF_USB_EP5_HS_SIZE DEF_USBD_HS_PACK_SIZE
#define DEF_USB_EP6_HS_SIZE DEF_USBD_HS_PACK_SIZE
/* FS端点大小 */
#define DEF_USB_EP1_FS_SIZE DEF_USBD_FS_PACK_SIZE
#define DEF_USB_EP2_FS_SIZE DEF_USBD_FS_PACK_SIZE
#define DEF_USB_EP3_FS_SIZE DEF_USBD_FS_PACK_SIZE
#define DEF_USB_EP4_FS_SIZE DEF_USBD_FS_PACK_SIZE
#define DEF_USB_EP5_FS_SIZE DEF_USBD_FS_PACK_SIZE
#define DEF_USB_EP6_FS_SIZE DEF_USBD_FS_PACK_SIZE
/* LS端点大小 */
/* ... */

/******************************************************************************/
// USB设备描述符长度，如果某个描述符不存在，则长度设置为0
#define DEF_USBD_DEVICE_DESC_LEN ((uint8_t)MyDevDescr[0])                                            // 设备描述符的长度
#define DEF_USBD_CONFIG_FS_DESC_LEN ((uint16_t)MyCfgDescr_FS[2] + (uint16_t)(MyCfgDescr_FS[3] << 8)) // FS配置描述符长度
#define DEF_USBD_CONFIG_HS_DESC_LEN ((uint16_t)MyCfgDescr_HS[2] + (uint16_t)(MyCfgDescr_HS[3] << 8)) // HS配置描述符长度
#define DEF_USBD_REPORT_DESC_LEN 0                                                                   // 报告描述符的长度
#define DEF_USBD_LANG_DESC_LEN ((uint16_t)MyLangDescr[0])                                            // 语言描述符的长度
#define DEF_USBD_MANU_DESC_LEN ((uint16_t)MyManuInfo[0])                                             // 制造商描述符的长度
#define DEF_USBD_PROD_DESC_LEN ((uint16_t)MyProdInfo[0])                                             // 产品描述符的长度
#define DEF_USBD_SN_DESC_LEN ((uint16_t)MySerNumInfo[0])                                             // 序列号描述符的长度
#define DEF_USBD_QUALFY_DESC_LEN ((uint16_t)MyQuaDesc[0])                                            // 设备合格描述符的长度
#define DEF_USBD_BOS_DESC_LEN ((uint16_t)MyBOSDesc[2] + (uint16_t)(MyBOSDesc[3] << 8))               // BOS描述符的长度
#define DEF_USBD_FS_OTH_DESC_LEN (DEF_USBD_CONFIG_HS_DESC_LEN)                                       // FS其他描述符的长度
#define DEF_USBD_HS_OTH_DESC_LEN (DEF_USBD_CONFIG_FS_DESC_LEN)                                       // HS其他描述符的长度

/******************************************************************************/
// 外部变量声明
extern const uint8_t MyDevDescr[];    // 设备描述符
extern const uint8_t MyCfgDescr_FS[]; // 全速配置描述符
extern const uint8_t MyCfgDescr_HS[]; // 高速配置描述符
extern const uint8_t MyLangDescr[];   // 语言描述符
extern const uint8_t MyManuInfo[];    // 制造商描述符
extern const uint8_t MyProdInfo[];    // 产品描述符
extern const uint8_t MySerNumInfo[];  // 序列号描述符
extern const uint8_t MyQuaDesc[];     // 设备合格描述符
extern const uint8_t MyBOSDesc[];     // BOS描述符
extern uint8_t TAB_USB_FS_OSC_DESC[]; // USB全速模式的其他速度配置描述符
extern uint8_t TAB_USB_HS_OSC_DESC[]; // USB高速模式的其他速度配置描述符

#endif /* DRIVERS_USB_INC_USB_DESC_H_ */

/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : usb device descriptor, configuration descriptor,
 *                      string descriptors and other descriptors.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "usb_desc.h"

/* 设备描述符 */
const uint8_t MyDevDescr[] = {
    0x12,                                              // bLength (描述符长度)
    0x01,                                              // bDescriptorType (设备描述符)
    0x00, 0x02,                                        // bcdUSB (USB版本 2.00)
    0x00,                                              // bDeviceClass (设备类)
    0x00,                                              // bDeviceSubClass (设备子类)
    0x00,                                              // bDeviceProtocol (设备协议)
    DEF_USBD_UEP0_SIZE,                                // bMaxPacketSize0 (最大包大小 64字节)
    (uint8_t)DEF_USB_VID, (uint8_t)(DEF_USB_VID >> 8), // idVendor (厂商ID)
    (uint8_t)DEF_USB_PID, (uint8_t)(DEF_USB_PID >> 8), // idProduct (产品ID)
    DEF_IC_PRG_VER, 0x00,                              // bcdDevice (设备版本号)
    0x01,                                              // iManufacturer (制造商字符串索引)
    0x02,                                              // iProduct (产品字符串索引)
    0x00,                                              // iSerialNumber (序列号字符串索引)
    0x01                                               // bNumConfigurations (配置数量)
};

/* USB配置描述符（高速模式） */
const uint8_t MyCfgDescr_HS[] = {
    /* 配置描述符 */
    0x09,       // bLength (描述符长度)
    0x02,       // bDescriptorType (配置描述符)
    0x20, 0x00, // wTotalLength (配置描述符总长度)
    0x01,       // bNumInterfaces (接口数)
    0x01,       // bConfigurationValue (配置值)
    0x00,       // iConfiguration (配置字符串索引)
    0xC0,       // bmAttributes (自供电)
    0x32,       // bMaxPower (最大功率 100mA)

    /*****************************************************************/
    /* 接口描述符（UDisk） */
    0x09, // bLength (描述符长度)
    0x04, // bDescriptorType (接口描述符)
    0x00, // bInterfaceNumber (接口编号 0)
    0x00, // bAlternateSetting (备用设置)
    0x02, // bNumEndpoints (端点数)
    0x08, // bInterfaceClass (接口类，0x08表示大容量存储设备)
    0x06, // bInterfaceSubClass (接口子类)
    0x50, // bInterfaceProtocol (协议)
    0x00, // iInterface (接口字符串索引)

    /* 端点描述符 */
    0x07,       // bLength (描述符长度)
    0x05,       // bDescriptorType (端点描述符)
    0x82,       // bEndpointAddress (端点地址，IN端点，设备到主机)
    0x02,       // bmAttributes (端点属性，批量传输)
    0x00, 0x02, // wMaxPacketSize (最大包大小 512字节)
    0x00,       // bInterval (传输间隔)

    /* 端点描述符 */
    0x07,       // bLength (描述符长度)
    0x05,       // bDescriptorType (端点描述符)
    0x03,       // bEndpointAddress (端点地址，OUT端点，主机到设备)
    0x02,       // bmAttributes (端点属性，批量传输)
    0x00, 0x02, // wMaxPacketSize (最大包大小 512字节)
    0x00,       // bInterval (传输间隔)
};

/* 配置描述符（全速模式） */
const uint8_t MyCfgDescr_FS[] = {
    /* 配置描述符 */
    0x09,       // bLength (描述符长度)
    0x02,       // bDescriptorType (配置描述符)
    0x20, 0x00, // wTotalLength (配置描述符总长度)
    0x01,       // bNumInterfaces (接口数)
    0x01,       // bConfigurationValue (配置值)
    0x00,       // iConfiguration (配置字符串索引)
    0xC0,       // bmAttributes (自供电)
    0x32,       // bMaxPower (最大功率 100mA)

    /*****************************************************************/
    /* 接口描述符（UDisk） */
    0x09, // bLength (描述符长度)
    0x04, // bDescriptorType (接口描述符)
    0x00, // bInterfaceNumber (接口编号 0)
    0x00, // bAlternateSetting (备用设置)
    0x02, // bNumEndpoints (端点数)
    0x08, // bInterfaceClass (接口类，0x08表示大容量存储设备)
    0x06, // bInterfaceSubClass (接口子类)
    0x50, // bInterfaceProtocol (协议)
    0x00, // iInterface (接口字符串索引)

    /* 端点描述符 */
    0x07,       // bLength (描述符长度)
    0x05,       // bDescriptorType (端点描述符)
    0x82,       // bEndpointAddress (端点地址，IN端点，设备到主机)
    0x02,       // bmAttributes (端点属性，批量传输)
    0x40, 0x00, // wMaxPacketSize (最大包大小 64字节)
    0x00,       // bInterval (传输间隔)

    /* 端点描述符 */
    0x07,       // bLength (描述符长度)
    0x05,       // bDescriptorType (端点描述符)
    0x03,       // bEndpointAddress (端点地址，OUT端点，主机到设备)
    0x02,       // bmAttributes (端点属性，批量传输)
    0x40, 0x00, // wMaxPacketSize (最大包大小 64字节)
    0x00,       // bInterval (传输间隔)
};

/* 语言描述符 */
const uint8_t MyLangDescr[] = {
    0x04, 0x03, 0x09, 0x04 // 语言描述符：美国英语（0x0409）
};

/* 制造商描述符 */
const uint8_t MyManuInfo[] = {
    0x0E, 0x03, 'w', 0, 'c', 0, 'h', 0, '.', 0, 'c', 0, 'n', 0}; // 制造商名称：wch.cn

/* 产品描述符 */
const uint8_t MyProdInfo[] = {
    0x16, 0x03, 'C', 0, 'H', 0, '3', 0, '0', 0, 'x', 0, 'U', 0, 'D', 0, 'i', 0, 's', 0, 'k', 0}; // 产品名称：CH300x UDisk

/* 序列号描述符 */
const uint8_t MySerNumInfo[] = {
    0x16, 0x03, '0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0, '9', 0}; // 序列号：0123456789

/* 设备合格描述符 */
const uint8_t MyQuaDesc[] = {
    0x0A, 0x06, 0x00, 0x02, 0xFF, 0xFF, 0xFF, 0x40, 0x01, 0x00}; // 设备合格描述符

/* 设备BOS描述符 */
const uint8_t MyBOSDesc[] = {
    0x05, 0x0F, 0x0C, 0x00, 0x01, // 设备BOS描述符
    0x07, 0x10, 0x02, 0x02, 0x00, 0x00, 0x00};

/* USB全速模式的其他速度配置描述符 */
uint8_t TAB_USB_FS_OSC_DESC[sizeof(MyCfgDescr_HS)] = {
    0x09, 0x07};

/* USB高速模式的其他速度配置描述符 */
uint8_t TAB_USB_HS_OSC_DESC[sizeof(MyCfgDescr_HS)] = {
    0x09, 0x07};

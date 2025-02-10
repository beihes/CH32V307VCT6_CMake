/*
 * fatOP.h
 *
 *  Created on: 2025年2月2日
 *      Author: 26448
 */

#ifndef DRIVERS_FLASH_INC_FATOP_H_
#define DRIVERS_FLASH_INC_FATOP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "diskio.h"
#include "sdCard.h"
#include "w25qxx.h"
#include "ff.h"

#define ERROR 1
#define SUCCESS 0

    typedef struct FileData
    {
        FATFS fat;                 // 文件系统对象
        FRESULT opEnd;             // 操作结果
        FIL file;                  // 文件对象
        UINT length;               // 数据长度
        uint32_t size;             // 文件大小
        BYTE dataFileBuffer[1024]; // 要读出的数据
    } FileData;

    // 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
    void FatFs_Check(void);

    // 计算设备容量
    void FatFs_GetVolume(void);

    // 文件创建和写入测试
    int8_t FatFs_FileTest(void);

    void Read_DataFile(void);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_FLASH_INC_FATOP_H_ */

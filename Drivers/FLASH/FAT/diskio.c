/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* FatFs 低级磁盘 I/O 模块 (示例代码)                                  */
/* 适用于 CH32V307，需实现具体存储设备驱动                           */
/*-----------------------------------------------------------------------*/

#include "ff.h"     /* FatFs 头文件 */
#include "diskio.h" /* 磁盘 I/O 头文件 */
#include "rtc.h"
#ifdef SPI_SD
#include "spi2.h" // 假设SD卡驱动代码在spi2.h中
#endif

#ifdef SPI_W25XXX
#include "spi1.h"
#endif
#include "sdCard.h"
#include "w25qxx.h"

// 初始化函数
DSTATUS disk_initialize(BYTE pdrv)
{
    if (pdrv == 1)
        return RES_OK;
    else
        return STA_NOINIT;
}

DSTATUS disk_status(
    BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
    if (pdrv == 1)
    {
        DSTATUS stat = STA_NOINIT;
        uint32_t ID = W25XXX_ReadID();
        if (W25Q32_FLASH_ID1 == ID || W25Q32_FLASH_ID2 == ID)
        {
            stat &= ~STA_NOINIT;
            return stat;
        }
    }
    return STA_NOINIT;
}

// 读取扇区
DRESULT disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
    if (!count)
        return RES_PARERR;
    if (pdrv == 1)
    {
        W25XXX_RD_Block(buff, sector << 12, count << 12);
        return RES_OK;
    }
    return RES_ERROR;
}

// 写入扇区
DRESULT disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
    if (!count)
        return RES_PARERR;
    if (pdrv == 1)
    {
        uint32_t write_addr = sector << 12; // 以4K字节为单位
        W25XXX_Erase_Sector(write_addr);
        // 写入一个扇区的数据
        W25XXX_WR_Block((uint8_t *)buff, write_addr, count << 12); // 写入扇区
        return RES_OK;
    }
    return RES_ERROR;
}

// 获取状态
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    switch (cmd)
    {
    case CTRL_SYNC:
        return RES_OK; // 同步命令，通常没有操作
    case GET_SECTOR_COUNT:
        *(DWORD *)buff = w25xxxSectorCount; // 返回Flash的扇区总数
        return RES_OK;
    case GET_SECTOR_SIZE:
        *(WORD *)buff = SPI_FLASH_SectorSize; // 返回块大小，通常是512字节
        return RES_OK;
    case GET_BLOCK_SIZE:
        *(DWORD *)buff = 1; // 这个返回值一般是1
        return RES_OK;
    default:
        return RES_ERROR; // 未定义的命令
    }
}

static CalendarObj calendar;
DWORD get_fattime(void)
{
    calendar = *getCalendarObjData();
    return ((DWORD)(calendar.year - 1980) << 25) | ((DWORD)(calendar.month) << 21) | ((DWORD)(calendar.date) << 16) | ((DWORD)(calendar.hour) << 11) | ((DWORD)(calendar.min) << 5) | ((DWORD)(calendar.sec) >> 1);
}

/*
 * fatOP.c
 *
 *  Created on: 2025年2月2日
 *      Author: 26448
 */

#include "fatOP.h"

/********************************************** 变量定义 *******************************************/

FATFS sFLASH_FatFs;           // 文件系统对象
FRESULT MyFile_Res;           // 操作结果
BYTE sFLASH_ReadBuffer[1024]; // 要读出的数据

//	函数：FatFs_Check
//	功能：进行FatFs文件系统的挂载
//
void FatFs_Check(void) // 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
{
    BYTE work[FF_MAX_SS];

    MyFile_Res = f_mount(&sFLASH_FatFs, "1:", 1); // 初始化SPI Flash，并挂载FatFs

    if (MyFile_Res == FR_OK) // 判断是否挂载成功
    {
        printf("\r\nSPI Flash文件系统挂载成功\r\n");
    }
    else
    {
        printf("SPI Flash还未创建文件系统，即将格式化\r\n");

        MyFile_Res = f_mkfs("1:", FM_FAT, 0, work, sizeof work); // 格式化，FAT32，簇默认大小16K

        if (MyFile_Res == FR_OK) // 判断是否格式化成功
            printf("SPI Flash格式化成功！\r\n");
        else
            printf("格式化失败，请检查或更换SPI Flash！\r\n");
    }
}

//	函数：FatFs_GetVolume
//	功能：计算设备的容量，包括总容量和剩余容量
//
void FatFs_GetVolume(void) // 计算设备容量
{
    FATFS *fs;                           // 定义结构体指针
    uint32_t sFLASH_CardCapacity = 0;    // SD卡的总容量
    uint32_t sFLASH_FreeCapacity = 0;    // SD卡空闲容量
    DWORD fre_clust, fre_sect, tot_sect; // 空闲簇，空闲扇区数，总扇区数

    f_getfree("1:", &fre_clust, &fs); // 获取设备剩余的簇

    tot_sect = (fs->n_fatent - 2) * fs->csize; // 总扇区数量 = 总的簇 * 每个簇包含的扇区数
    fre_sect = fre_clust * fs->csize;          // 计算剩余的可用扇区数

    sFLASH_CardCapacity = tot_sect * 4096 / 1024; // 总容量 = 总扇区数 * 每扇区的字节数 / 1K
    sFLASH_FreeCapacity = fre_sect * 4096 / 1024; // 计算剩余的容量，单位为KB

    printf("-------------------获取设备容量信息-----------------\r\n");
    printf("SPI Flash容量：%ld KB\r\n", sFLASH_CardCapacity);
    printf("SPI Flash剩余：%ld KB\r\n", sFLASH_FreeCapacity);
}

//	函数：FatFs_FileTest
//	功能：进行文件写入和读取测试
//

int8_t FatFs_FileTest(void) // 文件创建和写入测试
{
    uint8_t i = 0;
    uint16_t BufferSize = 0;
    FIL MyFile;                                                 // 文件对象
    UINT MyFile_Num;                                            //	数据长度
    BYTE MyFile_WriteBuffer[] = "STM32 SPI Flash 文件系统测试"; // 要写入的数据

    printf("-------------FatFs 文件创建和写入测试---------------\r\n");
    MyFile_Res = f_open(&MyFile, "1:FatFs Test.txt", FA_CREATE_ALWAYS | FA_WRITE); // 打开文件，若不存在则创建该文件
    if (MyFile_Res == FR_OK)
    {
        printf("文件打开/创建成功，准备写入数据...\r\n");

        MyFile_Res = f_write(&MyFile, MyFile_WriteBuffer, sizeof(MyFile_WriteBuffer), &MyFile_Num); // 向文件写入数据
        if (MyFile_Res == FR_OK)
        {
            printf("写入成功，写入内容为：\r\n");
            printf("%s\r\n", MyFile_WriteBuffer);
        }
        else
        {
            printf("文件写入失败，请检查SPI Flash或重新格式化!\r\n");
            f_close(&MyFile); // 关闭文件
            return ERROR;
        }
        f_close(&MyFile); // 关闭文件
    }
    else
    {
        printf("无法打开/创建文件，请检查SPI Flash或重新格式化!\r\n");
        f_close(&MyFile); // 关闭文件
        return ERROR;
    }

    printf("-------------FatFs 文件读取测试---------------\r\n");

    BufferSize = sizeof(MyFile_WriteBuffer) / sizeof(BYTE);                       // 计算写入的数据长度
    MyFile_Res = f_open(&MyFile, "1:data.txt", FA_OPEN_EXISTING | FA_READ); // 打开文件，若不存在则创建该文件
    MyFile_Res = f_read(&MyFile, sFLASH_ReadBuffer, BufferSize, &MyFile_Num);     // 读取文件
    if (MyFile_Res == FR_OK)
    {
        printf("文件读取成功，正在校验数据...\r\n");

        for (i = 0; i < BufferSize; i++)
        {
            if (MyFile_WriteBuffer[i] != sFLASH_ReadBuffer[i]) // 校验数据
            {
                printf("校验失败，请检查SPI Flash或重新格式化!\r\n");
                f_close(&MyFile); // 关闭文件
                return ERROR;
            }
        }
        printf("校验成功，读出的数据为：\r\n");
        printf("%s\r\n", sFLASH_ReadBuffer);
    }
    else
    {
        printf("无法读取文件，请检查SPI Flash或重新格式化!\r\n");
        f_close(&MyFile); // 关闭文件
        return ERROR;
    }

    f_close(&MyFile); // 关闭文件
    return SUCCESS;
}

void Read_DataFile(void)
{
    FATFS dataFileFat;   // 文件系统对象
    FRESULT dataFileRes; // 操作结果
    FIL dataFile;        // 文件对象
    UINT dataFileLen;    //	数据长度
    uint32_t dataFileSize = 1024;
    BYTE dataFileBuffer[1024]; // 要读出的数据
    dataFileRes = f_mount(&dataFileFat, "1:", 1);
    if (dataFileRes == FR_OK)
    {
        dataFileRes = f_open(&dataFile, "1:data.txt", FA_OPEN_EXISTING | FA_READ);
        dataFileRes = f_read(&dataFile, dataFileBuffer, dataFileSize, &dataFileLen); // 读取文件
        if (dataFileRes == FR_OK)
        {
            for (uint16_t i = 0; i < dataFileLen; i++)
            {
                printf("%c", dataFileBuffer[i]);
            }
            printf("\n");
        }
        f_close(&dataFile);
    }
    f_unmount("1:");
}
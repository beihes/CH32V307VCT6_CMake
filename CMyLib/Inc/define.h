/*
 * define.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_DEFINE_H_
#define CMYLIB_INC_DEFINE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "assert.h"
#include "ch32v30x.h"
#include "ctype.h"
#include "debug.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SPI_FLASH_MOD 0 // 1为SD，0为W25Q64

#if SPI_FLASH_MOD == 1
#define SPI_SD
#elif SPI_FLASH_MOD == 0
#define SPI_W25XXX
#endif

    uint8_t Time_Out_Sec(uint32_t time1, uint32_t *time2, uint8_t midTime);

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_DEFINE_H_ */

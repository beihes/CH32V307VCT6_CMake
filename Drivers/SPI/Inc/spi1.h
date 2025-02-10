/*
 * spi1.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef DRIVERS_SPI_INC_SPI1_H_
#define DRIVERS_SPI_INC_SPI1_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "cMyLib.h"

//当前SPI用于W25XXX
void SPI1_Init(void);
uint8_t SPI1_ReadWrite_Byte(uint8_t TxData);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_SPI_INC_SPI1_H_ */

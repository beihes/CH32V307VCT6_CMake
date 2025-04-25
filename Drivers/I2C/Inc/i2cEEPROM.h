/*
 * i2cEEPROM.h
 *
 *  Created on: 2025年2月10日
 *      Author: 26448
 */

#ifndef DRIVERS_I2C_INC_I2CEEPROM_H_
#define DRIVERS_I2C_INC_I2CEEPROM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "i2cx.h"

/**********************************************************************
*@Note:
AT24Cxx
    I2C interface routine to operate EEPROM peripheral.
    I2C1_SCL(PB10)\I2C1_SDA(PB11).
    This example uses EEPROM for AT24Cxx series.
Steps:
    READ EEPROM:Start + 0xA0 + 16bit Data Address + Start + 0xA1 + Read Data + Stop.
    WRITE EERPOM:Start + 0xA0 + 16bit Data Address + Write Data + Stop.
*******************************************************************************/

/* EERPOM DATA ADDRESS Length Definition */
#define AT24CXX_Address_8bit 0
#define AT24CXX_Address_16bit 1

/* EERPOM DATA ADDRESS Length Selection */
// #define Address_Lenth    AT24CXX_Address_8bit
#define Address_Lenth AT24CXX_Address_16bit

#define AT24C32 0xA0

    void AT24CXX_Init(void);
    uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);
    void AT24CXX_WriteOneByte(uint16_t writeAddr, uint8_t dataToWrite);
    void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
    void AT24CXX_Write(uint16_t writeAddr, uint8_t *pBuffer, uint16_t numToWrite);

    void AT24CXX_Test();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_I2C_INC_I2CEEPROM_H_ */

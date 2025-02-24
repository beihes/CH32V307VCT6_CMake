/*
 * i2cOLED.h
 *
 *  Created on: 2025年2月24日
 *      Author: 26448
 */

#ifndef DRIVERS_I2C_INC_I2COLED_H_
#define DRIVERS_I2C_INC_I2COLED_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "i2cx.h"

#define OLED_COMMAND_ADDRESS 0x00
#define OLED_WRITE_ADDRESS 0x40
#define OLED_ADDRESS 0x78

    void OLED_WriteOneByte(uint16_t writeAddr, uint8_t dataToWrite);
    void OLED_Init(void);
    void OLED_Clear(void);
    void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
    void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
    void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
    void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
    void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
    void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_I2C_INC_I2COLED_H_ */

/*
 * i2cx.h
 *
 *  Created on: 2025年2月10日
 *      Author: 26448
 */

#ifndef DRIVERS_I2C_INC_I2CX_H_
#define DRIVERS_I2C_INC_I2CX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"

    typedef uint8_t DriverAddr;

    void I2C1_Init(uint32_t bound, uint16_t address);
    void I2C2_Init(uint32_t bound, uint16_t address);

    void I2CX_ReadOneByte_Start(I2C_TypeDef *I2CX, DriverAddr driverAddr);
    void I2CX_ReadOneByte_8Bit(I2C_TypeDef *I2CX, uint16_t ReadAddr);
    void I2CX_ReadOneByte_16Bit(I2C_TypeDef *I2CX, uint16_t ReadAddr);
    uint8_t I2CX_ReadOneByte_End(I2C_TypeDef *I2CX, DriverAddr driverAddr);

    void I2CX_WriteOneByte_Start(I2C_TypeDef *I2CX, DriverAddr driverAddr);
    void I2CX_WriteOneByte_8Bit(I2C_TypeDef *I2CX, uint16_t writeAddr);
    void I2CX_WriteOneByte_16Bit(I2C_TypeDef *I2CX, uint16_t writeAddr);
    void I2CX_WriteOneByte_End(I2C_TypeDef *I2CX, uint8_t dataToWrite);
#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_I2C_INC_I2CX_H_ */

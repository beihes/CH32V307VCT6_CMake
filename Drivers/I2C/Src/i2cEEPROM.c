/*
 * i2cEEPROM.c
 *
 *  Created on: 2025年2月10日
 *      Author: 26448
 */

#include "i2cEEPROM.h"

/*********************************************************************
 * @fn      AT24CXX_Init
 *
 * @brief   Initializes AT24xx EEPROM.
 *
 * @return  none
 */
void AT24CXX_Init(void)
{
    I2C2_Init(100000, 0xA0);
}

/*********************************************************************
 * @fn      AT24CXX_ReadOneByte
 *
 * @brief   Read one data from EEPROM.
 *
 * @param   ReadAddr - Read frist address.
 *
 * @return  temp - Read data.
 */
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{
    I2CX_ReadOneByte_Start(I2C2, 0xA0);
#if (Address_Lenth == AT24CXX_Address_8bit)
    I2CX_ReadOneByte_8Bit(I2C2, ReadAddr);
#elif (Address_Lenth == AT24CXX_Address_16bit)
    I2CX_ReadOneByte_16Bit(I2C2, ReadAddr);
#endif
    return I2CX_ReadOneByte_End(I2C2, 0xA0);
}

/*********************************************************************
 * @fn      AT24CXX_WriteOneByte
 *
 * @brief   Write one data to EEPROM.
 *
 * @param   writeAddr - Write frist address.
 *
 * @return  dataToWrite - Write data.
 */
void AT24CXX_WriteOneByte(uint16_t writeAddr, uint8_t dataToWrite)
{
    I2CX_WriteOneByte_Start(I2C2, 0xA0);
#if (Address_Lenth == AT24CXX_Address_8bit)
    I2CX_WriteOneByte_8Bit(I2C2, writeAddr);
#elif (Address_Lenth == AT24CXX_Address_16bit)
    I2CX_WriteOneByte_16Bit(I2C2, writeAddr);
#endif
    I2CX_WriteOneByte_End(I2C2, dataToWrite);
}

/*********************************************************************
 * @fn      AT24CXX_Read
 *
 * @brief   Read multiple data from EEPROM.
 *
 * @param   ReadAddr - Read frist address. (AT24c02: 0~255)
 *          pBuffer - Read data.
 *          NumToRead - Data number.
 *
 * @return  none
 */
void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead)
{
    while (NumToRead)
    {
        *pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
        NumToRead--;
    }
}

/*********************************************************************
 * @fn      AT24CXX_Write
 *
 * @brief   Write multiple data to EEPROM.
 *
 * @param   writeAddr - Write frist address. (AT24c02: 0~255)
 *          pBuffer - Write data.
 *          numToWrite - Data number.
 *
 * @return  none
 */
void AT24CXX_Write(uint16_t writeAddr, uint8_t *pBuffer, uint16_t numToWrite)
{
    while (numToWrite--)
    {
        AT24CXX_WriteOneByte(writeAddr, *pBuffer);
        writeAddr++;
        pBuffer++;
        Delay_Ms(2);
    }
}

void AT24CXX_Test()
{
    char midStr[16] = "CH32V307VCT6";
    printf("Start Write 24Cxx....\r\n");
    AT24CXX_Write(100, (uint8_t *)midStr, sizeof(midStr));
    printf("24Cxx Write Sucess!\r\n");

    char getStr[16];
    printf("Start Read 24Cxx....\r\n");
    AT24CXX_Read(100, (uint8_t *)getStr, sizeof(midStr));
    printf("The Data Readed Is: \r\n");
    printf("%s\r\n", getStr);
}
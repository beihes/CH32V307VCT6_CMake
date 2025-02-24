/*
 * usbControl.c
 *
 *  Created on: 2025年2月3日
 *      Author: 26448
 */

#include "usbControl.h"
#include "sdCard.h"

uint8_t usbState = DISABLE;
uint8_t sdState = DISABLE;

uint8_t Key_ControlUSB(void)
{
    if (getKeyPB03Data()->midTime > 3 && usbState == DISABLE)
    {
        printf("UDisk is ENABLE!\n");
        USBHS_Device_Init(ENABLE);
        LED_PIN_GREEN_LOW();
        LED_PIN_RED_HIGH();
        while (getKeyPB03Data()->midTime > 3)
        {
        }
        LED_PIN_RED_LOW();
        usbState = ENABLE;
    }
    else if (usbState == ENABLE)
    {
        printf("UDisk is DISABLE!\n");
        USBHS_Device_Init(DISABLE);
        usbState = DISABLE;
    }
    if (getKeyPB03Data()->midTime == 2 && sdState == DISABLE)
    {
        printf("sd OPEN!\n");
        SD_Init();
        Show_SDCard_Info();
        sdState = ENABLE;
    }
    else if (getKeyPB03Data()->midTime != 2 && sdState == ENABLE)
    {
        printf("sd CLOSE!\n");
        SD_PowerOFF();
        sdState = DISABLE;
    }

    return usbState;
}

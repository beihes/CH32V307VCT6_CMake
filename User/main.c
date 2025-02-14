/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "app.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
// 本例程采用YD-CH32V307VCT6开发板
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%ld\r\n", SystemCoreClock);
    printf("ChipID:%08lx\r\n", DBGMCU_GetCHIPID());
    printf("CH32V307VCT6_CMake\r\n");

    LED_Init();
    Key_Init();
    AT24CXX_Init();
    AT24CXX_Test();

    SD_Pin_Init();
    SD_Init();

    /* The code is initializing the TIM1 timer and the RTC (Real-Time Clock) module. */
    TIM1_Base_Init(65535, SystemCoreClock / 1000000 - 1);
    printf("RTC:%d\n", RTC_Init());
#if (STORAGE_MEDIUM == MEDIUM_SPI_W25XXX)
    printf("W25XXX FLASH Init\r\n");
    /* SPI flash init */
    W25XXX_Init();
    /* FLASH ID check */
    W25XXX_IC_Check();
#endif

    /* Enable Udisk */
    Udisk_Capability = w25xxxSectorCount;
    Udisk_Status |= DEF_UDISK_EN_FLAG;

    /* USB20 device init */
    USBHS_RCC_Init();
    USBHS_Device_Init(DISABLE);
    Read_DataFile();
    printf("初始化完成\n");

    while (1)
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_4, getKeyPB03Data()->state);
        Key_ControlUSB();
    }
}

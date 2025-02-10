/*
 * key.c
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#include "key.h"

KeyData keyPB03 = {.endTime = 0, .midTime = 0, .num = 0, .state = 0, .startTime = 0};

void Key_PB03_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* GPIOB ----> EXTI_Line3 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = KeyPreemption;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = KeySub;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        printf("key:%d\n",keyPB03.num);
        keyPB03.startTime = getCalendarObjData()->second;
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0)
            ;
        keyPB03.endTime = getCalendarObjData()->second;
        keyPB03.midTime = (uint8_t)(keyPB03.endTime - keyPB03.startTime);
        keyPB03.startTime = 0;
        keyPB03.endTime = 0;
        keyPB03.num++;
        if (keyPB03.num == 0xff)
        {
            keyPB03.num = 0;
        }
        (keyPB03.state == 0) ? (keyPB03.state = 1) : (keyPB03.state = 0);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

KeyData *getKeyPB03Data()
{
    return &keyPB03;
}

void Key_Init()
{
    Key_PB03_Init();
}
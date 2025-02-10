/*
 * led.c
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */
#include "led.h"

void LED_GPIOA_15_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    LED_PIN_RED_HIGH();
}

void LED_GPIOB_04_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    LED_PIN_GREEN_HIGH();
}

void LED_Init()
{
    LED_GPIOA_15_Init();
    LED_GPIOB_04_Init();
    Delay_Ms(1000);
    LED_PIN_RED_LOW();
    LED_PIN_GREEN_LOW();
}
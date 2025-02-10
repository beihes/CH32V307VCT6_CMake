/*
 * led.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef DRIVERS_LED_LED_H_
#define DRIVERS_LED_LED_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"

/* LED相关引脚定义 */
#define LED_PIN_RED_LOW() (GPIOA->BCR = GPIO_Pin_15)    // 拉低LED Red引脚
#define LED_PIN_RED_HIGH() (GPIOA->BSHR = GPIO_Pin_15)  // 拉高LED Red引脚
#define LED_PIN_GREEN_LOW() (GPIOB->BCR = GPIO_Pin_4)   // 拉低LED Green引脚
#define LED_PIN_GREEN_HIGH() (GPIOB->BSHR = GPIO_Pin_4) // 拉高LED Green引脚

    void LED_GPIOA_15_Init();
    void LED_GPIOB_04_Init();

    void LED_Init();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_LED_LED_H_ */

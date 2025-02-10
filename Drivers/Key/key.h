/*
 * key.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef DRIVERS_KEY_KEY_H_
#define DRIVERS_KEY_KEY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "cMyLib.h"
#include "rtc.h"

typedef struct KeyData
{
    uint8_t state;
    uint8_t num;
    uint32_t startTime;
    uint32_t endTime;
    uint8_t midTime;
}KeyData;

void Key_PB03_Init();
void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
KeyData* getKeyPB03Data();

void Key_Init();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_KEY_KEY_H_ */

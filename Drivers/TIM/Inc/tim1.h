/*
 * tim1.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef DRIVERS_TIM_INC_TIM1_H_
#define DRIVERS_TIM_INC_TIM1_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"

extern volatile uint8_t CalibrationFlag;
extern volatile uint8_t Calibration_STA;
void TIM1_Base_Init(uint16_t arr, uint16_t psc);
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_TIM_INC_TIM1_H_ */

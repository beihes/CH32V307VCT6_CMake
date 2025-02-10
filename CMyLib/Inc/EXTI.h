/*
 * EXTI.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_EXTI_H_
#define CMYLIB_INC_EXTI_H_

#ifdef __cplusplus
extern "C"
{
#endif

    enum PreemptionPriority
    {
        NONEPreemption,
        USART1Preemption,
        USART2Preemption = 1,
        KeyPreemption = 1,
        USART3Preemption,
    };
    enum SubPriority
    {
        NONE,
        NONESub,
        USART1Sub,
        USART2Sub = 2,
        KeySub = 2,
        USART3Sub,
    };

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_EXTI_H_ */

/*
 * define.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_DEFINE_H_
#define CMYLIB_INC_DEFINE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "assert.h"
#include "ch32v30x.h"
#include "ctype.h"
#include "debug.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

    uint8_t Time_Out_Sec(uint32_t time1, uint32_t *time2, uint8_t midTime);

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_DEFINE_H_ */

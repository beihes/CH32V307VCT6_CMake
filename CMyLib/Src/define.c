/*
 * define.c
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#include "define.h"

uint8_t Time_Out_Sec(uint32_t time1, uint32_t *time2, uint8_t midTime)
{
    if (*time2 + midTime < time1)
    {
        *time2 = midTime;
        return 1;
    }
    return 0;
}
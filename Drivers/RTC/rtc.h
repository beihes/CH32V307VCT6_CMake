/*
 * rtc.h
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#ifndef DRIVERS_RTC_RTC_H_
#define DRIVERS_RTC_RTC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "tim1.h"

#define PPM_PER_STEP 0.9536743 // 10^6/2^20.
#define PPM_PER_SEC 0.3858025  // 10^6/(30d*24h*3600s).

    typedef struct CalendarObj
    {
        volatile uint8_t hour;
        volatile uint8_t min;
        volatile uint8_t sec;
        volatile uint16_t msec;

        volatile uint16_t year;
        volatile uint8_t month;
        volatile uint8_t date;
        volatile uint8_t week;
        volatile uint32_t second;
    } CalendarObj;

    uint8_t RTC_Init(void);
    uint8_t Is_Leap_Year(uint16_t year);
    uint8_t RTC_Alarm_Set(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec);
    uint8_t RTC_Get(void);
    uint8_t RTC_Get_Week(uint16_t year, uint8_t month, uint8_t day);
    uint8_t RTC_Set(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec);
    void RTC_Calibration(uint16_t FastSecPer30days);
    void RTC_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

    CalendarObj *getCalendarObjData();
    void Print_CalendarObj();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_RTC_RTC_H_ */

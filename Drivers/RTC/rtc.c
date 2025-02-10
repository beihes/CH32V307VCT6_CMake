/*
 * rtc.c
 *
 *  Created on: 2025年1月27日
 *      Author: 26448
 */

#include "rtc.h"

/* Global define */

/* Global Variable */
extern volatile uint8_t CalibrationFlag;
extern volatile uint32_t CalibrationTIMCir;
volatile uint32_t CalibrationVal = 0;
volatile uint8_t Calibration_STA = 0;

const uint8_t table_week[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
const uint8_t mon_table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

CalendarObj calendar;

/*********************************************************************
 * @fn      RTC_NVIC_Config
 *
 * @brief   Initializes RTC Int.
 *
 * @return  none
 */
static void RTC_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*********************************************************************
 * @fn      RTC_Init
 *
 * @brief   Initializes RTC collection.
 *
 * @return  1 - Init Fail
 *          0 - Init Success
 */
uint8_t RTC_Init(void)
{
    uint8_t temp = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_ClearITPendingBit(RTC_IT_SEC);
    /* Is it the first configuration */

    BKP_DeInit();
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && temp < 250)
    {
        temp++;
        Delay_Ms(20);
    }
    if (temp >= 250)
        return 1;
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForLastTask();
    RTC_WaitForSynchro();
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
    RTC_EnterConfigMode();
    /*Deliberately speeding up the clock*/
    RTC_SetPrescaler(32766);
    RTC_WaitForLastTask();
    RTC_Set(2025, 1, 1, 0, 0, 0); /* Setup Time */
    RTC_ExitConfigMode();
    BKP_WriteBackupRegister(BKP_DR1, 0XA1A1);

    RTC_NVIC_Config();
    RTC_Get();

    while (CalibrationFlag == 0)
        ;

    if (CalibrationVal < 1000000)
    {
        uint16_t FastSecPer30days = (1000000 - CalibrationVal) * 3600 * 24 * 30 / 1000000;
        RTC_Calibration(FastSecPer30days);
    }
    return 0;
}

/*********************************************************************
 * @fn      Is_Leap_Year
 *
 * @brief   Judging whether it is a leap year.
 *
 * @param   year
 *
 * @return  1 - Yes
 *          0 - No
 */
uint8_t Is_Leap_Year(uint16_t year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}

/*********************************************************************
 * @fn      RTC_Set
 *
 * @brief   Set Time.
 *
 * @param   Struct of _calendar_obj
 *
 * @return  1 - error
 *          0 - success
 */
uint8_t RTC_Set(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec)
{
    uint16_t t;
    u32 seccount = 0;
    if (syear < 1970 || syear > 2099)
        return 1;
    for (t = 1970; t < syear; t++)
    {
        if (Is_Leap_Year(t))
            seccount += 31622400;
        else
            seccount += 31536000;
    }
    smon -= 1;
    for (t = 0; t < smon; t++)
    {
        seccount += (u32)mon_table[t] * 86400;
        if (Is_Leap_Year(syear) && t == 1)
            seccount += 86400;
    }
    seccount += (u32)(sday - 1) * 86400;
    seccount += (u32)hour * 3600;
    seccount += (u32)min * 60;
    seccount += sec;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_SetCounter(seccount);
    RTC_WaitForLastTask();
    return 0;
}

/*********************************************************************
 * @fn      RTC_Alarm_Set
 *
 * @brief   Set Alarm Time.
 *
 * @param   Struct of _calendar_obj
 *
 * @return  1 - error
 *          0 - success
 */
uint8_t RTC_Alarm_Set(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec)
{
    uint16_t t;
    u32 seccount = 0;
    if (syear < 1970 || syear > 2099)
        return 1;
    for (t = 1970; t < syear; t++)
    {
        if (Is_Leap_Year(t))
            seccount += 31622400;
        else
            seccount += 31536000;
    }
    smon -= 1;
    for (t = 0; t < smon; t++)
    {
        seccount += (u32)mon_table[t] * 86400;
        if (Is_Leap_Year(syear) && t == 1)
            seccount += 86400;
    }
    seccount += (u32)(sday - 1) * 86400;
    seccount += (u32)hour * 3600;
    seccount += (u32)min * 60;
    seccount += sec;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_SetAlarm(seccount);
    RTC_WaitForLastTask();

    return 0;
}

/*********************************************************************
 * @fn      RTC_Get
 *
 * @brief   Get current time.
 *
 * @return  1 - error
 *          0 - success
 */
uint8_t RTC_Get(void)
{
    static uint16_t daycnt = 0;
    u32 timecount = 0;
    u32 temp = 0;
    uint16_t temp1 = 0;
    timecount = RTC_GetCounter();
    temp = timecount / 86400;
    if (daycnt != temp)
    {
        daycnt = temp;
        temp1 = 1970;
        while (temp >= 365)
        {
            if (Is_Leap_Year(temp1))
            {
                if (temp >= 366)
                    temp -= 366;
                else
                {
                    break;
                }
            }
            else
                temp -= 365;
            temp1++;
        }
        calendar.year = temp1;
        temp1 = 0;
        while (temp >= 28)
        {
            if (Is_Leap_Year(calendar.year) && temp1 == 1)
            {
                if (temp >= 29)
                    temp -= 29;
                else
                    break;
            }
            else
            {
                if (temp >= mon_table[temp1])
                    temp -= mon_table[temp1];
                else
                    break;
            }
            temp1++;
        }
        calendar.month = temp1 + 1;
        calendar.date = temp + 1;
    }
    temp = timecount % 86400;
    calendar.hour = temp / 3600;
    calendar.min = (temp % 3600) / 60;
    calendar.sec = (temp % 3600) % 60;
    calendar.week = RTC_Get_Week(calendar.year, calendar.month, calendar.date);
    return 0;
}

/*********************************************************************
 * @fn      RTC_Get_Week
 *
 * @brief   Get the current day of the week.
 *
 * @param   year/month/day
 *
 * @return  week
 */
uint8_t RTC_Get_Week(uint16_t year, uint8_t month, uint8_t day)
{
    uint16_t temp2;
    uint8_t yearH, yearL;

    yearH = year / 100;
    yearL = year % 100;
    if (yearH > 19)
        yearL += 100;
    temp2 = yearL + yearL / 4;
    temp2 = temp2 % 7;
    temp2 = temp2 + day + table_week[month - 1];
    if (yearL % 4 == 0 && month < 3)
        temp2--;
    return (temp2 % 7);
}

/*********************************************************************
 * @fn      RTC_Calibration
 *
 * @brief   The function `RTC_Calibration` calculates a calibration step value based on a given fast seconds per
 *        30 days value.
 *
 * @param   FastSecPer30days The `FastSecPer30days` parameter represents the number of fast seconds in a
 *        30-day period. This value is used to calculate the calibration step for the RTC (Real-Time Clock)
 *        based on the deviation from the ideal timekeeping.
 *
 * @return  none
 */
void RTC_Calibration(uint16_t FastSecPer30days)
{
    float Deviation = 0.0;
    uint8_t CalibStep = 0;

    Deviation = FastSecPer30days * PPM_PER_SEC;
    Deviation /= PPM_PER_STEP;
    CalibStep = (uint8_t)Deviation;
    if (Deviation >= (CalibStep + 0.5))
        CalibStep += 1;
    if (CalibStep > 127)
        CalibStep = 127;

    BKP_SetRTCCalibrationValue(CalibStep);
    printf("Calibration cab: %d\n", CalibStep);
}

/*********************************************************************
 * @fn      RTC_IRQHandler
 *
 * @brief   This function handles RTC Handler.
 *
 * @return  none
 */
void RTC_IRQHandler(void)
{
    if (CalibrationFlag)
    {
        if (RTC_GetITStatus(RTC_IT_SEC) != RESET) /* Seconds interrupt */
        {
            RTC_Get();
        }
        if (RTC_GetITStatus(RTC_IT_ALR) != RESET) /* Alarm clock interrupt */
        {
            RTC_ClearITPendingBit(RTC_IT_ALR);
            RTC_Get();
        }
        //printf("%d-%02d-%02d  %d  %02d:%02d:%02d\r\n", calendar.year, calendar.month, calendar.date, calendar.week, calendar.hour, calendar.min, calendar.sec);
    }
    else
    {
        if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
        {
            if (Calibration_STA == 0)
            {
                CalibrationTIMCir = 0;
                TIM1->CNT = 0;
                TIM1->CTLR1 |= TIM_CEN;
                Calibration_STA = 1;
            }
            else if (Calibration_STA == 1)
            {

                TIM1->CTLR1 &= ~TIM_CEN;
                CalibrationVal = TIM1->CNT + CalibrationTIMCir * 65536;
                CalibrationVal < 1000000 ? printf("Calibration val = %ld\n", 1000000 - CalibrationVal) : printf("Calibration val = %ld\n", CalibrationVal - 1000000);

                TIM1->CNT = 0;
                Calibration_STA = 0;
                CalibrationFlag = 1;
            }
        }
    }
    RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW);
    RTC_WaitForLastTask();
}

CalendarObj *getCalendarObjData()
{
    calendar.second=RTC_GetCounter();
    calendar.msec=(32767-RTC_GetDivider())*1000/32767;
    printf("second:%ld\tmsec:%d\n", calendar.second, calendar.msec);
    return &calendar;
}

void Print_CalendarObj()
{
    printf("\tY|\tM|\tD|\tWeek|\tHour|\tMin|\tSec\n");
    printf("%d-%d-%d  %d  %d:%d:%d\r\n", calendar.year, calendar.month, calendar.date, calendar.week, calendar.hour, calendar.min, calendar.sec);
    calendar.second=RTC_GetCounter();
    calendar.msec=(32767-RTC_GetDivider())*1000/32767;
    printf("second:%ld\tmsec:%d\n", calendar.second, calendar.msec);
}

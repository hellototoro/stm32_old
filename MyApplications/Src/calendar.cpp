/*
 * calendar.cpp
 *
 *  Created on: 2021年8月14日
 *      Author: huang
 */

#include <Inc/calendar.hpp>

namespace MyApplications {

calendar::calendar() {
    // TODO Auto-generated constructor stub

}

/**
  * @brief 赋值默认设置，以便在设置时间时不用关心其他设置
  * @param None
  * @retval None
  */
void calendar::init(void)
{
    RTC_Time.Hours = 10;
    RTC_Time.Minutes = 0;
    RTC_Time.Seconds = 0;
    RTC_Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RTC_Time.StoreOperation = RTC_STOREOPERATION_RESET;

    RTC_Date.WeekDay = RTC_WEEKDAY_MONDAY;
    RTC_Date.Month = RTC_MONTH_JANUARY;
    RTC_Date.Date = 1;
    RTC_Date.Year = 21;
}

RTC_TimeTypeDef calendar::getRTC_Time(void)
{
    //时间和日期必须都要读取，且顺序不能改变
    //@note You must call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values
    HAL_RTC_GetTime(RtcHandle, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(RtcHandle, &RTC_Date, RTC_FORMAT_BIN);
    return RTC_Time;
}

RTC_DateTypeDef calendar::getRTC_Date(void)
{
    //时间和日期必须都要读取，且顺序不能改变
    //@note You must call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values
    HAL_RTC_GetTime(RtcHandle, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(RtcHandle, &RTC_Date, RTC_FORMAT_BIN);
    return RTC_Date;
}


void calendar::setRTC_Time(uint8_t hour, uint8_t minutes, uint8_t seconds)
{
    //step1 设置时间
    RTC_Time.Hours = hour;
    RTC_Time.Minutes = minutes;
    RTC_Time.Seconds = seconds;
    if (HAL_RTC_SetTime(RtcHandle, &RTC_Time, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
}

void calendar::setRTC_Date(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday)
{
    RTC_Date.WeekDay = weekday;
    RTC_Date.Month = RTC_ByteToBcd2(month);
    RTC_Date.Date = day;
    RTC_Date.Year = year;
    if (HAL_RTC_SetDate(RtcHandle, &RTC_Date, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
}

calendar::~calendar() {
    // TODO Auto-generated destructor stub
}

} /* namespace MyApplications */

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

void calendar::init(void)
{

}

RTC_TimeTypeDef calendar::getRTC_Time(void)
{
	HAL_RTC_GetTime(RtcHandle, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(RtcHandle, &RTC_Date, RTC_FORMAT_BIN);
    return RTC_Time;
}

void calendar::setRTC_Time(void)
{
    RTC_TimeTypeDef _RTC_Time;
    RTC_DateTypeDef _RTC_Date;
    _RTC_Time.Hours = 21;
    _RTC_Time.Minutes = 58;
    _RTC_Time.Seconds = 0;
    _RTC_Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    _RTC_Time.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(RtcHandle, &_RTC_Time, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
    _RTC_Date.WeekDay = RTC_WEEKDAY_SATURDAY;
    _RTC_Date.Month = RTC_MONTH_AUGUST;
    _RTC_Date.Date = 14;
    _RTC_Date.Year = 21;

    if (HAL_RTC_SetDate(RtcHandle, &_RTC_Date, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
}

calendar::~calendar() {
    // TODO Auto-generated destructor stub
}

} /* namespace MyApplications */

/*
 * calendar.hpp
 *
 *  Created on: 2021年8月14日
 *      Author: huang
 */

#ifndef CALENDAR_HPP_
#define CALENDAR_HPP_

#include "main.h"

namespace MyApplications {

class calendar {
public:
    calendar();
    void init(void);
    void setRTC_Time(uint8_t hour, uint8_t minutes, uint8_t seconds);
    void setRTC_Date(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday);
    RTC_TimeTypeDef getRTC_Time(void);
    RTC_DateTypeDef getRTC_Date(void);
    virtual ~calendar();
private:
    RTC_TimeTypeDef RTC_Time;
    RTC_DateTypeDef RTC_Date;
};

} /* namespace MyApplications */

#endif /* CALENDAR_HPP_ */

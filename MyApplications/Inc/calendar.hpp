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
    void setRTC_Time(void);
    RTC_TimeTypeDef getRTC_Time(void);
    virtual ~calendar();
private:
    RTC_TimeTypeDef RTC_Time;
    RTC_DateTypeDef RTC_Date;
};

} /* namespace MyApplications */

#endif /* CALENDAR_HPP_ */

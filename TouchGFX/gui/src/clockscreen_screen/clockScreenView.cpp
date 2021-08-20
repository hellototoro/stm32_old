#include <gui/clockscreen_screen/clockScreenView.hpp>
#include <led/led.hpp>
#include "Inc/calendar.hpp"

extern MyApplications::calendar rtc_Calendar;
extern MyDrivers::led led1;

clockScreenView::clockScreenView()
{

}

void clockScreenView::setupScreen()
{
    clockScreenViewBase::setupScreen();

    //add by huangjian at 2021.08.14
    updateRTC_Time();
}

void clockScreenView::tearDownScreen()
{
    clockScreenViewBase::tearDownScreen();
}

void clockScreenView::updateRTC_Time(void)
{
    if (clock.isVisible()) {
        RTC_TimeTypeDef RTC_Time = rtc_Calendar.getRTC_Time();
        clock.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
    }
}

void clockScreenView::setTimer(void)
{
    rtc_Calendar.setRTC_Time(10,10,0);
    led1.toggle();
}

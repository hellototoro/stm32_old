/*
 * tftlcd.hpp
 *
 *  Created on: Aug 5, 2021
 *      Author: huang
 */

#ifndef MYDRIVERS_TFTLCD_TFTLCD_HPP_
#define MYDRIVERS_TFTLCD_TFTLCD_HPP_

namespace MyDrivers {

#include "main.h"
#include "Inc/display.hpp"

enum class displayDir{
    vertical = 0,
    horizontal
};

class tftlcd : public MyApplications::display {
public:
    tftlcd();
    virtual void showChar(uint16_t x,uint16_t y,char ch);
    virtual void showString(uint16_t x,uint16_t y,char* str);
    virtual void showPicture(uint16_t x,uint16_t y,char* pic);
    virtual void displayOn(void);
    virtual void displayOff(void);
    virtual MyApplications::display::display_info getInfo(void);
    virtual ~tftlcd();

private:
    void init(void);
    void setCursor(uint16_t x,uint16_t y);
    void setWindow(uint16_t x,uint16_t y,uint16_t width,uint16_t height);
    void setDisplayDir(displayDir _displayDir);
};

} /* namespace MyDrivers */

#endif /* MYDRIVERS_TFTLCD_TFTLCD_HPP_ */

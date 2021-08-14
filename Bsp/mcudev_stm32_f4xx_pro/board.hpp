/*
 * board.hpp
 *
 *  Created on: 2021年8月9日
 *      Author: huang
 */

#ifndef MCUDEV_STM32_F4XX_PRO_BOARD_HPP_
#define MCUDEV_STM32_F4XX_PRO_BOARD_HPP_

#include <display/Inc/display.hpp>
#include "main.h"

class board : public MyDrivers::lcd {
public:
    board();

    virtual void init(void);
    virtual void setCursor(uint16_t x,uint16_t y);
    virtual void setWindow(uint16_t x,uint16_t y,uint16_t width,uint16_t height);
    virtual void setDisplayDir(MyDrivers::displayDir _displayDir);
    virtual void showChar(uint16_t x,uint16_t y,char ch);
    virtual void showString(uint16_t x,uint16_t y,char* str);
    virtual void showPicture(uint16_t x,uint16_t y,char* pic);
    virtual void displayOn(void);
    virtual void displayOff(void);
    virtual display_info getInfo(void);

    virtual ~board();
};

#endif /* MCUDEV_STM32_F4XX_PRO_BOARD_HPP_ */

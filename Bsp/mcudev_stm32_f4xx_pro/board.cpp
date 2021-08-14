/*
 * board.cpp
 *
 *  Created on: 2021年8月9日
 *      Author: huang
 */

#include <mcudev_stm32_f4xx_pro/board.hpp>

board::board() {
	// TODO Auto-generated constructor stub

}

/* ***************************************************************************
 *
 *                        lcd 
 * 
 * 
 * **************************************************************************/
void board::init(void)
{
    
}

void board::setCursor(uint16_t x,uint16_t y)
{
    
}

void board::setWindow(uint16_t x,uint16_t y,uint16_t width,uint16_t height)
{
    
}

void board::setDisplayDir(MyDrivers::displayDir _displayDir)
{
    
}

void board::showChar(uint16_t x,uint16_t y,char ch)
{
    
}

void board::showString(uint16_t x,uint16_t y,char* str)
{
    
}

void board::showPicture(uint16_t x,uint16_t y,char* pic)
{
    
}

void board::displayOn(void)
{
    
}

void board::displayOff(void)
{
    
}

board::display_info board::getInfo(void)
{
    
}
/******************************* lcd end ************************************/


board::~board() {
	// TODO Auto-generated destructor stub
}


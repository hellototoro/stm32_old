/*
 * tftlcd.hpp
 *
 *  Created on: Aug 5, 2021
 *      Author: huang
 */

#ifndef MYDRIVERS_TFTLCD_TFTLCD_HPP_
#define MYDRIVERS_TFTLCD_TFTLCD_HPP_

#include "main.h"
#include "Components/s6d04d1/s6d04d1.hpp"
#include <display/Fonts/fonts.h>

namespace MyDrivers {

#define LCD_OK         0x00
#define LCD_ERROR      0x01
#define LCD_TIMEOUT    0x02

enum class Line_ModeTypdef {
    CENTER_MODE          = 0x01,    /* Center mode */
    RIGHT_MODE           = 0x02,    /* Right mode  */
    LEFT_MODE            = 0x03     /* Left mode   */
};

/** 
  * @brief  LCD color  
  */ 
enum class lcd_color {
    BLUE          = 0x001F,
    GREEN         = 0x07E0,
    RED           = 0xF800,
    CYAN          = 0x07FF,
    MAGENTA       = 0xF81F,
    YELLOW        = 0xFFE0,
    LIGHTBLUE     = 0x841F,
    LIGHTGREEN    = 0x87F0,
    LIGHTRED      = 0xFC10,
    LIGHTCYAN     = 0x87FF,
    LIGHTMAGENTA  = 0xFC1F,
    LIGHTYELLOW   = 0xFFF0,
    DARKBLUE      = 0x0010,
    DARKGREEN     = 0x0400,
    DARKRED       = 0x8000,
    DARKCYAN      = 0x0410,
    DARKMAGENTA   = 0x8010,
    DARKYELLOW    = 0x8400,
    WHITE         = 0xFFFF,
    LIGHTGRAY     = 0xD69A,
    GRAY          = 0x8410,
    DARKGRAY      = 0x4208,
    BLACK         = 0x0000,
    BROWN         = 0xA145,
    ORANGE        = 0xFD20
};

class display : public s6d04d1 {
public:
    display();
    void showChar(uint16_t x,uint16_t y,char ch);
    void showString(uint16_t x,uint16_t y,char* str);
    void showPicture(uint16_t x,uint16_t y,char* pic);
    void setTextColor(lcd_color Color);
    void clear(lcd_color Color);
    void clearStringLine(uint16_t Line);
    void displayStringAtLine(uint16_t Line, uint8_t *ptr);
    void displayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Line_ModeTypdef Mode);
    void displayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);
    uint32_t getDisplayAddress();
    ~display();

private:
    class _DrawProp {
    public:
        lcd_color TextColor;
        lcd_color BackColor;
        sFONT    *pFont; 
    } DrawProp;
    class Point {
    public:
        int16_t X;
        int16_t Y;
    }; 
    
};

} /* namespace MyDrivers */

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font24


#endif /* MYDRIVERS_TFTLCD_TFTLCD_HPP_ */

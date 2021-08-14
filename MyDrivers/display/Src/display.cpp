/*
 * lcd.cpp
 *
 *  Created on: Aug 5, 2021
 *      Author: huang
 */

#include <display/Inc/display.hpp>

namespace MyDrivers {

display::display() {
	// TODO Auto-generated constructor stub
  DrawProp.BackColor = lcd_color::WHITE;
  DrawProp.pFont     = &Font24;
  DrawProp.TextColor = lcd_color::BLACK;

}

/**
  * @brief  Sets the LCD text color.
  * @param  Color: Text color code RGB(5-6-5)
  */
void display::setTextColor(lcd_color Color)
{
  DrawProp.TextColor = Color;
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: Color of the background
  */
void display::clear(lcd_color Color)
{ 
  uint32_t counter = 0;
  lcd_color color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = Color;
  
  for(counter = 0; counter < getPixelHeight(); counter++)
  {
	drawHLine(static_cast<uint16_t>(DrawProp.TextColor), 0, counter, getPixelWidth());
  }
  DrawProp.TextColor = color_backup; 
  setTextColor(DrawProp.TextColor);
}


display::~display() {
	// TODO Auto-generated destructor stub
}

} /* namespace MyDrivers */

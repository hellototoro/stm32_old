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

enum class displayDir{
    vertical = 0,
    horizontal
};

class tftlcd {
public:
	tftlcd();
	void init(void);
	void setCursor(uint16_t x,uint16_t y);
	void setWindow(uint16_t x,uint16_t y,uint16_t width,uint16_t height);
	void setDisplayDir(displayDir _displayDir);
	virtual ~tftlcd();
};

} /* namespace MyDrivers */

#endif /* MYDRIVERS_TFTLCD_TFTLCD_HPP_ */

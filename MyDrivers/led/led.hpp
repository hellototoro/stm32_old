/*
 * led.h
 *
 *  Created on: Aug 1, 2021
 *      Author: huang
 */

#ifndef MYDRIVERS_LED_LED_H_
#define MYDRIVERS_LED_LED_H_

#include "main.h"

namespace MyDrivers {

enum class led_number {
	number1 = 1,
	number2
};

class led {
public:
	led(int _number);
	void on(void);
	void off(void);
	void toggle(void);
private:
	void switch_led(bool_switch _switch);
	int number;
};
}

#endif /* MYDRIVERS_LED_LED_H_ */

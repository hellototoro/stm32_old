/*
 * led.cpp
 *
 *  Created on: Aug 1, 2021
 *      Author: huang
 */

#include <led/led.hpp>

namespace MyDrivers {

led::led(int _number) : number { _number }
{
}

void led::switch_led(bool_switch _switch)
{
	switch(number)
	{
		case static_cast<int>(led_number::number1):
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, static_cast<GPIO_PinState>(_switch));
			break;
		case static_cast<int>(led_number::number2):
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, static_cast<GPIO_PinState>(_switch));
			break;
		default:
			break;
	}
}

void led::on(void)
{
	switch_led(OFF);
}

void led::off(void)
{
	switch_led(ON);
}

void led::toggle(void)
{
	switch(number)
	{
		case static_cast<int>(led_number::number1):
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			break;
		case static_cast<int>(led_number::number2):
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
			break;
		default:
			break;
	}
}

}

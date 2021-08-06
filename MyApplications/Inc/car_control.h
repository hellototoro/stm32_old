/**
  ******************************************************************************
  * @file    car_control.h
  * @brief   小车控制应用程序
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
#ifndef __CAR_CONTROL_H
#define __CAR_CONTROL_H

#include "main.h"

//typedef enum {
//	front = 0,
//	back,
//	left,
//	right
//}Car_info;

typedef struct {
	int16_t speed;
	int8_t h_dir;
	int8_t v_dir;
}Car_control;


extern Car_control Car;


extern void Car_init(void);
extern void Car_monitor(void);


#endif

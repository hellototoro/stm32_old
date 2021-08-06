/*
 * hw_iic.h
 *
 *  Created on: Aug 2, 2021
 *      Author: huang
 */

#ifndef MYDRIVERS_HW_IIC_INC_HW_IIC_H_
#define MYDRIVERS_HW_IIC_INC_HW_IIC_H_

#include "main.h"


extern void CAMERA_IO_Init(void);
extern void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
extern uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg);
extern void CAMERA_Delay(uint32_t Delay);

#endif /* MYDRIVERS_HW_IIC_INC_HW_IIC_H_ */

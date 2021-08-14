/*
 * touch.h
 *
 *  Created on: 2018. 12. 7.
 *      Author: chand
 */

#ifndef COMPONENTS_FT5316_FT5316_H_
#define COMPONENTS_FT5316_FT5316_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//FT5206 部分寄存器定义 
#define FT_DEVIDE_MODE 			0x00   		//FT5206模式控制寄存器
#define FT_REG_NUM_FINGER       0x02		//触摸状态寄存器

#define FT_TP1_REG 				0X03	  	//第一个触摸点数据地址
#define FT_TP2_REG 				0X09		//第二个触摸点数据地址
#define FT_TP3_REG 				0X0F		//第三个触摸点数据地址
#define FT_TP4_REG 				0X15		//第四个触摸点数据地址
#define FT_TP5_REG 				0X1B		//第五个触摸点数据地址  
 

#define	FT_ID_G_LIB_VERSION		0xA1		//版本		
#define FT_ID_G_MODE 			0xA4   		//FT5206中断模式控制寄存器
#define FT_ID_G_THGROUP			0x80   		//触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE	0x88   		//激活状态周期设置寄存器

#define CT_MAX_TOUCH 5    //电容屏支持的点数,固定为5点

typedef struct
{
	uint16_t x[CT_MAX_TOUCH]; 		//当前坐标
	uint16_t y[CT_MAX_TOUCH];		//电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
}touchPad;


extern uint8_t touchIrq;

extern uint8_t initTouch();
extern void toucuProc();
extern void input_sync();
extern uint8_t *getTouchPtr();
extern uint8_t *getTouchQualityKeyPtr();

#ifdef __cplusplus
}
#endif

#endif /* COMPONENTS_FT5316_FT5316_H_ */

#ifndef __SCCB_H
#define __SCCB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//IO��������
//#define SCCB_SDA_IN()  {GPIOD->MODER&=~(3<<(7*2));GPIOD->MODER|=0<<7*2;}	//PD7 ����
//#define SCCB_SDA_OUT() {GPIOD->MODER&=~(3<<(7*2));GPIOD->MODER|=1<<7*2;} 	//PD7 ���

#define IIC_DELAY 1000

//IO��������	 
//#define SCCB_SCL    		PDout(6)	 	//SCL
//#define SCCB_SDA    		PDout(7) 		//SDA	 

//#define SCCB_READ_SDA    	PDin(7)  		//����SDA    
#define SCCB_ID   			0X60  			//OV2640��ID
//#define SCCB_ID 0X42///OV7670��ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
uint8_t SCCB_WR_Byte(uint8_t dat);
uint8_t SCCB_RD_Byte(void);
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data);
uint8_t SCCB_RD_Reg(uint8_t reg);

#ifdef __cplusplus
}
#endif

#endif

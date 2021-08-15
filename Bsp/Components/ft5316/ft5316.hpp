/*
 * ft5316.hpp
 *
 *  Created on: Aug 15, 2021
 *      Author: huang
 */

#ifndef COMPONENTS_FT5316_FT5316_HPP_
#define COMPONENTS_FT5316_FT5316_HPP_

#include "hw_iic/hw_iic.hpp"



class ft5316 {
public:
    ft5316(I2C_HandleTypeDef *_touchPad_IIC_Handle);
    bool init(void);
    void readData(uint16_t &x, uint16_t &y);
    virtual ~ft5316();
private:
    I2C_HandleTypeDef *touchPad_IIC_Handle;
    MyDrivers::hw_iic ft5316_iic;
    //touchDataDef touchData;
};

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

#endif /* COMPONENTS_FT5316_FT5316_HPP_ */

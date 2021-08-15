/*
 * ft5316.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: huang
 */

#include <Components/ft5316/ft5316.hpp>
#include "cmsis_os.h"

#define FT5316_I2C_ID     0x70

const uint16_t FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};


ft5316::ft5316(I2C_HandleTypeDef *_touchPad_IIC_Handle) : 
touchPad_IIC_Handle { _touchPad_IIC_Handle }{
    // TODO Auto-generated constructor stub
    ft5316_iic.init(touchPad_IIC_Handle, FT5316_I2C_ID);
}

bool ft5316::init(void)
{
    uint8_t buffer[2]; 
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_RESET);//��λOV2640
    HAL_Delay(20);
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_SET);//
    HAL_Delay(100);
    ft5316_iic.writeByte(FT_DEVIDE_MODE, 0x00);	//进入正常操作模式 
    ft5316_iic.writeByte(FT_ID_G_MODE, 0x00);		//查询模式 
    ft5316_iic.writeByte(FT_ID_G_THGROUP, 22);	//设置触摸有效值，越小越灵敏	
    ft5316_iic.writeByte(FT_ID_G_PERIODACTIVE, 12); //激活周期，不能小于12，最大14
    //读取版本号，参考值：0x3003
    ft5316_iic.readBytes(FT_ID_G_LIB_VERSION, &buffer[0], 2);  
    if((buffer[0]==0X30&&buffer[1]==0X03)||buffer[1]==0X01||buffer[1]==0X02)//版本:0X3003/0X0001/0X0002
    {
        //printf("CTP ID:%x\r\n",((uint16_t)temp[0]<<8)+temp[1]);
        return false;
    }  
    return true;
}

//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
void ft5316::readData(uint16_t &x, uint16_t &y)
{
    uint8_t buffer[4];
    for( uint8_t i = 0; i < 1; i++ ){
        ft5316_iic.readBytes(FT5206_TPX_TBL[i], buffer, 4);//读取XY坐标值 
        y = ( (uint16_t)( buffer[0] & 0X0F ) << 8) + buffer[1];
        x = ( (uint16_t)( buffer[2] & 0X0F ) << 8) + buffer[3];
    }
}

ft5316::~ft5316() {
    // TODO Auto-generated destructor stub
}


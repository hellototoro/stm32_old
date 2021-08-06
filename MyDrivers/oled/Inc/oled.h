/*
 * @Author: your name
 * @Date: 2021-05-25 16:27:16
 * @LastEditTime: 2021-05-28 11:08:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /rosserial_stm32/Bsp/oled/Inc/oled.h
 */
#ifndef _OLED_H_
#define _OLED_H_

#include "main.h"
#include "stm32_iic.h"

class oled 
{
public:
    void init(void);
    void SetPos(uint8_t x,uint8_t y);
    void Fill(uint8_t fill_Data);
    void CLS(void);
    void On(void);
    void Off(void);
    void ShowStr(uint8_t x,uint8_t y,const char ch[],uint8_t TextSize);
    void Lcd_Address(uint8_t page,uint8_t column);
    void Clear_Screen(void);
    void Display_Frame(void);
private:
    Stm32IIC oled_iic;
};

#endif



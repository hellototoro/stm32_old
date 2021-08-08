/**
  ******************************************************************************
  * @file    TFT_LCD.h
  * @brief   TFT LCD����������Ҫʹ��CubeMX����FSMC��
  *          ��ʼ������
	* @data    2021-7-27
	* @author  jee
  ******************************************************************************
  */
#ifndef __TFT_LCD_H
#define __TFT_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define  LCD_SIZE_X		240
#define  LCD_SIZE_Y		400

typedef struct {
	uint16_t width;     //LCD ���
	uint16_t height;    //LCD �߶�
	uint16_t id;	    //LCD ID
	uint8_t  dir;    	//LCD ����
	uint16_t wramcmd;		//开始写gram指令
	uint16_t setxcmd;		//设置x坐标指令
	uint16_t setycmd;		//设置y坐标指令
    struct {
        uint16_t front;
        uint16_t back;
    }color;
}LCD_devTypeDef;

typedef enum {
    vertical = 0,
    horizontal
}LCD_DisplayDirTypeDef;

typedef enum {
    WHITE       = 0xFFFFU,
    BLACK       = 0x0000U,
    YELLOW      = 0x001FU,
    BRED        = 0XF81FU,
    GRED        = 0XFFE0U,
    RED         = 0X07FFU,
    GBLUE       = 0xF800U,
    MAGENTA     = 0xF81FU,
    GREEN       = 0x07E0U,
    CYAN        = 0x7FFFU,
    BLUE        = 0x001FU,
    BROWN       = 0XBC40U, //��ɫ
    BRRED       = 0XFC07U, //�غ�ɫ
    GRAY        = 0X8430U, //��ɫ
    DARKBLUE    = 0X01CFU,	//����ɫ
    LIGHTBLUE   = 0X7D7CU,	//ǳ��ɫ  
    GRAYBLUE    = 0X5458U, //����ɫ
    LIGHTGREEN  = 0X841FU, //ǳ��ɫ
    LIGHTGRAY   = 0XEF5BU, //ǳ��ɫ(PANNEL)
    LGRAY       = 0XC618U, //ǳ��ɫ(PANNEL),���屳��ɫ
    LGRAYBLUE   = 0XA651U, //ǳ����ɫ(�м����ɫ)
    LBBLUE      = 0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
}LCD_ColorTypeDef;


/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
typedef struct
{
  __IO uint16_t REG;
  __IO uint16_t RAM;

}LCD_CONTROLLER_TypeDef;
#define TFT_LCD_BASE           (0x6C000000UL + 0x0000007EUL)
#define TFT_LCD                ((LCD_CONTROLLER_TypeDef *) TFT_LCD_BASE)

/* �������� */
extern LCD_devTypeDef lcd_dev;


/* ȫ�ֺ������� */
extern void LCD_Init(void);
extern void _LCD_Init(void);
extern void LCD_SetWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);
extern void LCD_SetColor(uint16_t front, uint16_t back);
extern void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
extern void LCD_ShowChinese16X14(uint16_t x, uint16_t y, char *cn);
extern void LCD_ShowChinese32X29(uint16_t x, uint16_t y, char *cn);
extern void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,char *p);
extern void LCD_Show_xNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
extern void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);
extern void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint8_t *pic);
extern void LCD_Clear(uint16_t color);
extern void LCD_WriteRAM_Prepare(void);
extern void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
extern void LCD_ShowPicture2(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint16_t *pic);
extern void LCD_IO_WriteMultipleData(uint16_t* pData, uint32_t Size);

#define R7               0x0007
#define R32              0x0200
#define R33              0x0201
#define R34              0x0202
#define R80              0x0210
#define R81              0x0211
#define R82              0x0212
#define R83              0x0213
#define R3               0x0003

#ifdef __cplusplus
}
#endif


#endif

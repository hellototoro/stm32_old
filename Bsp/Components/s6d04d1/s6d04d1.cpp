/*
 * s6d04d1.cpp
 *
 *  Created on: 2021年8月9日
 *      Author: huang
 */

#include <Components/s6d04d1/s6d04d1.hpp>

s6d04d1::s6d04d1() {
    dir = displayDir::horizontal;
    mode = scanMode::R2L_D2U;
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void s6d04d1::displayOn(void)
{
    LCD_IO_WriteReg(DISPON);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void s6d04d1::displayOff(void)
{
    LCD_IO_WriteReg(DISPOFF);
}

/**
  * @brief  Prepare to write GRAM   
  * @param  None
  * @retval None
  */
void s6d04d1::prepareWrite(void)
{
    LCD_IO_WriteReg(RAMWR);
}

/**
  * @brief  Get the LCD pixel Width.
  * @param  None
  * @retval The Lcd Pixel Width
  */
uint16_t s6d04d1::getPixelWidth(void)
{
 return width;
}

/**
  * @brief  Get the LCD pixel Height.
  * @param  None
  * @retval The Lcd Pixel Height
  */
uint16_t s6d04d1::getPixelHeight(void)
{
 return height;
}

uint32_t s6d04d1::getRamAddress(void)
{
    return readRamAddress();
}

/**
  * @brief  Get the s6d04d1 ID.
  * @param  None
  * @retval The s6d04d1 ID 
  */
uint16_t s6d04d1::readID(void)
{
    LCD_IO_WriteReg(RDID2);
    LCD_IO_ReadRamData();//Dummy read 
    id = LCD_IO_ReadRamData();
    return id;
}

/**
  * @brief  Set Cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void s6d04d1::setCursor(uint16_t Xpos,uint16_t Ypos)
{
    LCD_IO_WriteReg(CASET); 
    LCD_IO_WriteData(Xpos>>8);
    LCD_IO_WriteData(Xpos&0XFF);
    LCD_IO_WriteReg(PASET);
    LCD_IO_WriteData(Ypos>>8);
    LCD_IO_WriteData(Ypos&0XFF);
}

/**
  * @brief  Write pixel.   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  RGBCode: the RGB pixel color
  * @retval None
  */
void s6d04d1::writePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
  /* Set Cursor */
  setCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  prepareWrite();

  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteMultipleData(&RGBCode, 1);
}

/**
  * @brief  Read pixel.
  * @param  None
  * @retval The RGB pixel color
  */
uint16_t s6d04d1::readPixel(uint16_t Xpos, uint16_t Ypos)
{
    /* Set Cursor */
    setCursor(Xpos, Ypos);
    
    /* Read 16-bit Reg */
    LCD_IO_WriteReg(RAMRD);
    LCD_IO_ReadRamData();//Dummy read 
    return (LCD_IO_ReadRamData());
}

/**
  * @brief  Writes to the selected LCD register.
  * @param  LCDReg: Address of the selected register.
  * @param  LCDRegValue: Value to write to the selected register.
  * @retval None
  */
void s6d04d1::writeReg(uint8_t LCDReg, uint16_t LCDRegValue)
{
  LCD_IO_WriteReg(LCDReg);
  
  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteMultipleData(&LCDRegValue, 1);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  LCDReg: address of the selected register.
  * @retval LCD Register Value.
  */
uint16_t s6d04d1::readReg(uint8_t LCDReg)
{ 
  /* Read 16-bit Reg */
  return (LCD_IO_ReadData(LCDReg));
}

/**
  * @brief  Sets a display window
  * @param  Xpos:   specifies the X bottom left position.
  * @param  Ypos:   specifies the Y bottom left position.
  * @param  Height: display window height.
  * @param  Width:  display window width.
  * @retval None
  */
void s6d04d1::setDisplayWindow(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t height)
{
    uint16_t twidth,theight;
    twidth = (Xpos + width) > this->width ? this->width : (Xpos + width -1);
    theight = (Ypos + height) > this->height ? this->height : (Ypos + height -1);
    LCD_IO_WriteReg(CASET); 
    LCD_IO_WriteData(Xpos >> 8); 
    LCD_IO_WriteData(Xpos & 0XFF);	 
    LCD_IO_WriteData(twidth >> 8); 
    LCD_IO_WriteData(twidth & 0XFF);  
    LCD_IO_WriteReg(PASET); 
    LCD_IO_WriteData(Ypos >> 8); 
    LCD_IO_WriteData(Ypos & 0XFF); 
    LCD_IO_WriteData(theight >> 8); 
    LCD_IO_WriteData(theight & 0XFF); 
}

/**
  * @brief  设置扫模模式
  * @param  scanMode:   扫描模式见此枚举变量.
  * @retval None
  */
void s6d04d1::setScanMode(scanMode mode)
{
    uint16_t regValue = 0;

    switch (mode)
    {
    case scanMode::L2R_U2D:
        if (dir == displayDir::vertical) {
            regValue |= (0<<7)|(0<<6)|(0<<5);
        } else {
            regValue |= (1<<7)|(0<<6)|(1<<5);
        }
        break;
    case scanMode::L2R_D2U:
        if (dir == displayDir::vertical) {
            regValue |= (1<<7)|(0<<6)|(0<<5); 
        } else {
            regValue |= (1<<7)|(1<<6)|(1<<5);
        }
        break;
    case scanMode::R2L_U2D:
        if (dir == displayDir::vertical) {
            regValue |= (0<<7)|(1<<6)|(0<<5);
        } else {
            regValue |= (0<<7)|(0<<6)|(1<<5); 
        }
        break;
    case scanMode::R2L_D2U:
        if (dir == displayDir::vertical) {
            regValue |= (1<<7)|(1<<6)|(0<<5);
        } else {
            regValue |= (0<<7)|(1<<6)|(1<<5);
        }
        break;
    case scanMode::U2D_L2R:
        if (dir == displayDir::vertical) {
            regValue |= (0<<7)|(0<<6)|(1<<5);
        } else {
            regValue |= (1<<7)|(0<<6)|(0<<5); 
        }
        break;
    case scanMode::U2D_R2L:
        if (dir == displayDir::vertical) {
            regValue |= (0<<7)|(1<<6)|(1<<5);
        } else {
            regValue |= (0<<7)|(0<<6)|(0<<5); 
        }
        break;
    case scanMode::D2U_L2R:
        if (dir == displayDir::vertical) {
            regValue |= (1<<7)|(0<<6)|(1<<5); 
        } else {
            regValue |= (1<<7)|(1<<6)|(0<<5); 
        }
        break;
    case scanMode::D2U_R2L:
        if (dir == displayDir::vertical) {
            regValue |= (1<<7)|(1<<6)|(1<<5); 
        } else {
            regValue |= (0<<7)|(1<<6)|(0<<5);
        }
        break;
    
    default:
        break;
    }
    LCD_IO_WriteReg(MADCTL);
    LCD_IO_WriteData(regValue);
    LCD_IO_WriteReg(CASET); 
    LCD_IO_WriteData(0);
    LCD_IO_WriteData(0);
    LCD_IO_WriteData((width-1) >> 8);
    LCD_IO_WriteData((width-1) & 0XFF);
    LCD_IO_WriteReg(PASET); 
    LCD_IO_WriteData(0);
    LCD_IO_WriteData(0);
    LCD_IO_WriteData((height-1) >> 8);
    LCD_IO_WriteData((height-1) & 0XFF);  
}

/**
  * @brief  设置显示方向
  * @param  displayDir:   显示方向：横屏和竖屏
  * @retval None
  */
void s6d04d1::setDisplayDir(displayDir _displayDir)
{
    dir = _displayDir;
    switch (dir)
    {
    case displayDir::vertical://竖屏
        width = 240;
        height = 400;
        break;
    
    case displayDir::horizontal://横屏
        width = 400;
        height = 240;
        break;
    default:
        break;
    }
    setScanMode(mode);	//默认扫描方向
}

/**
  * @brief  Draw vertical line.
  * @param  RGBCode: Specifies the RGB color   
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void s6d04d1::drawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
    uint16_t counter = 0;

    /* Set Cursor */
    setCursor(Xpos, Ypos); 

    /* Prepare to write GRAM */
    prepareWrite();

    /* Write 16-bit GRAM Reg */
    for(counter = 0; counter < Length; counter++)
    {
        LCD_IO_WriteData(RGBCode);
    }  
}

/**
  * @brief  Draw vertical line.
  * @param  RGBCode: Specifies the RGB color    
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void s6d04d1::drawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t counter = 0;

  /* set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  //ili9325_WriteReg(LCD_REG_3, 0x1010);
  
  /* Set Cursor */
  setCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  prepareWrite();

  /* Write 16-bit GRAM Reg */
  for(counter = 0; counter < Length; counter++)
  {
    LCD_IO_WriteData(RGBCode);
  }
  
  /* set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  //ili9325_WriteReg(LCD_REG_3, 0x1018);  
}

//画线
// startXpos, startYpos:起点坐标
// endXpos, endYpos:终点坐标  
void s6d04d1::drawLine(uint16_t RGBCode, uint16_t startXpos, uint16_t startYpos, uint16_t endXpos, uint16_t endYpos)
{
    int xerr = 0, yerr = 0, distance; 
    int incx, incy; 
    int delta_x = endXpos - startXpos; //计算坐标增量 
    int delta_y = endYpos - startYpos; 
    int uRow = startXpos; 
    int uCol = startYpos; 
    if( delta_x > 0 )
        incx = 1; //设置单步方向 
    else if( delta_x == 0 )
        incx = 0;//垂直线 
    else {
        incx = -1;
        delta_x = -delta_x;
    } 
    if( delta_y > 0 )
        incy = 1; 
    else if( delta_y == 0 )
        incy = 0;//水平线 
    else {
        incy = -1;
        delta_y = -delta_y;
    } 
    if( delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴 
    else 
        distance = delta_y; 
    for( uint16_t i = 0; i <= distance+1; i++ )//画线输出 
    {  
        writePixel(uRow,uCol,RGBCode);//画点 
        xerr += delta_x ; 
        yerr += delta_y ; 
        if( xerr > distance ) 
        { 
            xerr -= distance; 
            uRow += incx; 
        } 
        if( yerr > distance ) 
        { 
            yerr -= distance; 
            uCol += incy; 
        } 
    }  
}    

/**
  * @brief  Displays a bitmap picture.
  * @param  BmpAddress: Bmp picture address.
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD    
  * @retval None
  */
void s6d04d1::drawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
    uint32_t index = 0, size = 0;
    /* Read bitmap size */
    size = *(volatile uint16_t *) (pbmp + 2);
    size |= (*(volatile uint16_t *) (pbmp + 4)) << 16;
    /* Get bitmap data address offset */
    index = *(volatile uint16_t *) (pbmp + 10);
    index |= (*(volatile uint16_t *) (pbmp + 12)) << 16;
    size = (size - index)/2;
    pbmp += index;
    /* Set GRAM write direction and BGR = 1 */
    /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
    /* AM=1 (address is updated in vertical writing direction) */
    //ili9325_WriteReg(LCD_REG_3, 0x1008);

    /* Set Cursor */
    setCursor(Xpos, Ypos);  
    
    /* Prepare to write GRAM */
    prepareWrite();
    
    LCD_IO_WriteMultipleData((uint16_t*)pbmp, size);
    
    /* Set GRAM write direction and BGR = 1 */
    /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
    /* AM = 1 (address is updated in vertical writing direction) */
    //ili9325_WriteReg(LCD_REG_3, 0x1018);
}

/**
  * @brief  Displays picture.
  * @param  pdata: picture address.
  * @param  Xpos: Image X position in the LCD
  * @param  Ypos: Image Y position in the LCD
  * @param  Xsize: Image X size in the LCD
  * @param  Ysize: Image Y size in the LCD
  * @retval None
  */
void s6d04d1::drawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  uint32_t size = 0;

  size = (Xsize * Ysize);

  /* Set Cursor */
  setCursor(Xpos, Ypos);  
  
  /* Prepare to write GRAM */
  prepareWrite();
 
  LCD_IO_WriteMultipleData((uint16_t*)pdata, size);
}

void s6d04d1::init(void)
{
    LCD_Delay(100);
    readID();

    /*   init start    */
    LCD_IO_WriteReg(0xf4);
    LCD_IO_WriteData(0x59);
    LCD_IO_WriteData(0x59);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteData(0x11);
        
    LCD_IO_WriteReg(0xf5);
    LCD_IO_WriteData(0x12);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteData(0xf0);
    LCD_IO_WriteData(0x00);
    LCD_Delay(10);
        
    LCD_IO_WriteReg(0xf3);
    LCD_IO_WriteData(0xff);
    LCD_IO_WriteData(0x2a);
    LCD_IO_WriteData(0x2a);
    LCD_IO_WriteData(0x0a);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x72);
    LCD_IO_WriteData(0x72);
    LCD_IO_WriteData(0x20);
    
    LCD_IO_WriteReg(0x3a);
    LCD_IO_WriteData(0x55);
    
    LCD_IO_WriteReg(0xf2);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);//04
    LCD_IO_WriteData(0x1a);
    LCD_IO_WriteData(0x1a);
    
    LCD_IO_WriteReg(0xf6);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteData(0x88);//88
    LCD_IO_WriteData(0x10);
    
    LCD_IO_WriteReg(0xf7);
    LCD_IO_WriteData(0x0d);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x0e);
    LCD_IO_WriteData(0x1c);
    LCD_IO_WriteData(0x29);
    LCD_IO_WriteData(0x2d);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteData(0x0e);
    LCD_IO_WriteData(0x12);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteData(0x1e);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xf8);
    LCD_IO_WriteData(0x0d);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x0e);
    LCD_IO_WriteData(0x1c);
    LCD_IO_WriteData(0x29);
    LCD_IO_WriteData(0x2d);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteData(0x0e);
    LCD_IO_WriteData(0x12);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteData(0x1e);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xf9);
    LCD_IO_WriteData(0x1e);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x0a);
    LCD_IO_WriteData(0x19);
    LCD_IO_WriteData(0x23);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteData(0x3f);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x16);
    LCD_IO_WriteData(0x19);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xfA);
    LCD_IO_WriteData(0x0D);
    LCD_IO_WriteData(0x11);
    LCD_IO_WriteData(0x0A);
    LCD_IO_WriteData(0x19);
    LCD_IO_WriteData(0x23);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteData(0x3f);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x16);
    LCD_IO_WriteData(0x19);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xfB);
    LCD_IO_WriteData(0x0D);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x0E);
    LCD_IO_WriteData(0x1C);
    LCD_IO_WriteData(0x29);
    LCD_IO_WriteData(0x2D);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteData(0x0E);
    LCD_IO_WriteData(0x12);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteData(0x1E);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xfC);
    LCD_IO_WriteData(0x0D);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteData(0x0E);
    LCD_IO_WriteData(0x1C);
    LCD_IO_WriteData(0x29);
    LCD_IO_WriteData(0x2D);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteData(0x0E);
    LCD_IO_WriteData(0x12);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteData(0x1E);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteData(0x22);
    LCD_IO_WriteData(0x22);
    
    LCD_IO_WriteReg(0xFD);
    LCD_IO_WriteData(0x11);
    LCD_IO_WriteData(0x01);
    
    LCD_IO_WriteReg(0x36);
    LCD_IO_WriteData(0x08);
    
    LCD_IO_WriteReg(0x35);
    LCD_IO_WriteData(0x80);
    
    LCD_IO_WriteReg(0x2A);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0xEF);
    
    LCD_IO_WriteReg(0x2B);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteData(0x8F);
    
    LCD_IO_WriteReg(0xF1);
    LCD_IO_WriteData(0x5A);
    
    LCD_IO_WriteReg(0xFF);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteData(0x40);
    
    LCD_IO_WriteReg(0x11);
    LCD_Delay(120);
    
    LCD_IO_WriteReg(0xF1);
    LCD_IO_WriteData(0x00);
    /*   init end    */

    displayOn();
    setDisplayDir(dir);		//默认为竖屏
    setCursor(0, 0);
    prepareWrite();
}

s6d04d1::~s6d04d1() {
    // TODO Auto-generated destructor stub
}


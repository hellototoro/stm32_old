/*
 * s6d04d1.hpp
 *
 *  Created on: 2021年8月9日
 *      Author: huang
 */

#ifndef COMPONENTS_S6D04D1_S6D04D1_HPP_
#define COMPONENTS_S6D04D1_S6D04D1_HPP_

#include "main.h"
#include "Components/common/board.h"

enum class scanMode{
    L2R_U2D = 0,    //从左到右,从上到下
    L2R_D2U,        //从左到右,从下到上
    R2L_U2D,        //从右到左,从上到下
    R2L_D2U,        //从右到左,从下到上

    U2D_L2R,        //从上到下,从左到右
    U2D_R2L,        //从上到下,从右到左
    D2U_L2R,        //从下到上,从左到右
    D2U_R2L         //从下到上,从右到左
};

enum class displayDir{
    vertical = 0,
    horizontal
};

class s6d04d1 {
public:
    s6d04d1();
    uint16_t readID(void);
    void init(void);
    void prepareWrite(void);
    void setCursor(uint16_t Xpos,uint16_t Ypos);
    void setDisplayWindow(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t height);
    void setScanMode(scanMode mode);
    void setDisplayDir(displayDir _displayDir);
    uint16_t getPixelWidth(void);
    uint16_t getPixelHeight(void);

    void writePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
    uint16_t readPixel(uint16_t Xpos, uint16_t Ypos);
    void writeReg(uint8_t LCDReg, uint16_t LCDRegValue);
    uint16_t readReg(uint8_t LCDReg);
    void drawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length);
    void drawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length);
    void drawLine(uint16_t RGBCode, uint16_t startXpos, uint16_t startYpos, uint16_t endXpos, uint16_t endYpos);
    void drawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);
    void drawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata);

    void displayOn(void);
    void displayOff(void);

    virtual ~s6d04d1();

private:
    uint16_t width;
    uint16_t height;
    displayDir dir;
    scanMode mode;
    uint16_t id;
};

//s6d04d1 reg
#define CASET   0x2A    //Column Address Set 
#define PASET   0x2B    //Page Address Set 
#define RAMWR   0x2C    //Memory Write
#define RAMRD   0x2E    //Memory Read
#define MADCTL  0x36    //Memory Data Access Control
#define DISPON  0x29    //Display on
#define DISPOFF 0x28    //Display off
#define RDID2   0xDB    // ID Definition

#endif /* COMPONENTS_S6D04D1_S6D04D1_HPP_ */

/*
 * ft5316.c
 *
 *  Created on: 2021. 8. 12.
 *      Author: chand
 */
#include "Components/ft5316/ft5316.h"
#include "hw_iic/Inc/hw_iic.h"
#include <string.h>
#include "cmsis_os.h"

#define max_point_num 5

#define FT5316_I2C_ID     0x70

#define TOUCH_I2C_ID   FT5316_I2C_ID

//extern USBD_HandleTypeDef hUsbDeviceFS;
//extern uint8_t USBD_HID_SendReport (USBD_HandleTypeDef  *pdev, uint8_t *report, uint16_t len);

uint8_t touchIrq = 0;
//static uint16_t oldX[max_point_num]={0,};
//static uint16_t oldY[max_point_num]={0,};
//static uint16_t oldid[max_point_num];
//static uint8_t p_point_num = 0;


//https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/touch-and-pen-support
const uint8_t touchQualityKey[] = {
        0x05, //reportid
        0xfc, 0x28, 0xfe, 0x84, 0x40, 0xcb, 0x9a, 0x87, 0x0d, 0xbe, 0x57, 0x3c, 0xb6, 0x70, 0x09, 0x88,
        0x07, 0x97, 0x2d, 0x2b, 0xe3, 0x38, 0x34, 0xb6, 0x6c, 0xed, 0xb0, 0xf7, 0xe5, 0x9c, 0xf6, 0xc2,
        0x2e, 0x84, 0x1b, 0xe8, 0xb4, 0x51, 0x78, 0x43, 0x1f, 0x28, 0x4b, 0x7c, 0x2d, 0x53, 0xaf, 0xfc,
        0x47, 0x70, 0x1b, 0x59, 0x6f, 0x74, 0x43, 0xc4, 0xf3, 0x47, 0x18, 0x53, 0x1a, 0xa2, 0xa1, 0x71,
        0xc7, 0x95, 0x0e, 0x31, 0x55, 0x21, 0xd3, 0xb5, 0x1e, 0xe9, 0x0c, 0xba, 0xec, 0xb8, 0x89, 0x19,
        0x3e, 0xb3, 0xaf, 0x75, 0x81, 0x9d, 0x53, 0xb9, 0x41, 0x57, 0xf4, 0x6d, 0x39, 0x25, 0x29, 0x7c,
        0x87, 0xd9, 0xb4, 0x98, 0x45, 0x7d, 0xa7, 0x26, 0x9c, 0x65, 0x3b, 0x85, 0x68, 0x89, 0xd7, 0x3b,
        0xbd, 0xff, 0x14, 0x67, 0xf2, 0x2b, 0xf0, 0x2a, 0x41, 0x54, 0xf0, 0xfd, 0x2c, 0x66, 0x7c, 0xf8,
        0xc0, 0x8f, 0x33, 0x13, 0x03, 0xf1, 0xd3, 0xc1, 0x0b, 0x89, 0xd9, 0x1b, 0x62, 0xcd, 0x51, 0xb7,
        0x80, 0xb8, 0xaf, 0x3a, 0x10, 0xc1, 0x8a, 0x5b, 0xe8, 0x8a, 0x56, 0xf0, 0x8c, 0xaa, 0xfa, 0x35,
        0xe9, 0x42, 0xc4, 0xd8, 0x55, 0xc3, 0x38, 0xcc, 0x2b, 0x53, 0x5c, 0x69, 0x52, 0xd5, 0xc8, 0x73,
        0x02, 0x38, 0x7c, 0x73, 0xb6, 0x41, 0xe7, 0xff, 0x05, 0xd8, 0x2b, 0x79, 0x9a, 0xe2, 0x34, 0x60,
        0x8f, 0xa3, 0x32, 0x1f, 0x09, 0x78, 0x62, 0xbc, 0x80, 0xe3, 0x0f, 0xbd, 0x65, 0x20, 0x08, 0x13,
        0xc1, 0xe2, 0xee, 0x53, 0x2d, 0x86, 0x7e, 0xa7, 0x5a, 0xc5, 0xd3, 0x7d, 0x98, 0xbe, 0x31, 0x48,
        0x1f, 0xfb, 0xda, 0xaf, 0xa2, 0xa8, 0x6a, 0x89, 0xd6, 0xbf, 0xf2, 0xd3, 0x32, 0x2a, 0x9a, 0xe4,
        0xcf, 0x17, 0xb7, 0xb8, 0xf4, 0xe1, 0x33, 0x08, 0x24, 0x8b, 0xc4, 0x43, 0xa5, 0xe5, 0x24, 0xc2
};


struct __packed touchHid_t {
    uint8_t tip;
    uint8_t num;
    uint16_t x;
    uint16_t y;
    uint8_t width;
    uint8_t height;

};
struct __packed multiTouchHid_t {
    uint8_t report;
    struct touchHid_t touch[max_point_num];
    uint16_t count;
    uint8_t id;
};
struct multiTouchHid_t multiTouch;

void tpd_down(uint16_t x, uint16_t y, uint16_t p)
{
    multiTouch.touch[multiTouch.id].tip = 0x01;
    multiTouch.touch[multiTouch.id].num = p;   //contact id
    multiTouch.touch[multiTouch.id].x = x;
    multiTouch.touch[multiTouch.id].y = y;
    multiTouch.touch[multiTouch.id].width = 0x30; //width of contact
    multiTouch.touch[multiTouch.id].height = 0x30;
    multiTouch.id++;

}
void tpd_up(uint16_t x, uint16_t y, uint16_t p)
{
    multiTouch.touch[multiTouch.id].tip = 0x00;
    //multiTouch.touch[multiTouch.id].num = multiTouch.id;
    multiTouch.touch[multiTouch.id].num = p;
    //multiTouch.touch[multiTouch.id].x = x;
    //multiTouch.touch[multiTouch.id].y = y;
    multiTouch.touch[multiTouch.id].width = 0;
    multiTouch.touch[multiTouch.id].height = 0;
    multiTouch.id++;

}

void input_sync()
{
    multiTouch.report = 0x01;
    multiTouch.count++;
    /*
    for(int i=0;i<multiTouch.id;i++)
    {
        printf("\n[%d:%d] x : %d, y : %d, %d\n",multiTouch.id, multiTouch.touch[i].tip, multiTouch.touch[i].x,multiTouch.touch[i].y, multiTouch.count);
    }*/
    //HAL_UART_Transmit_IT(&huart3, (uint8_t*)&multiTouch, sizeof(multiTouch));
    //++USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&multiTouch, sizeof(struct multiTouchHid_t));
    multiTouch.id=0;
    for(int i=0;i<max_point_num;i++)
    {
        memset(&multiTouch.touch[i], 0x00, sizeof(struct touchHid_t));
    }
}


uint8_t *getTouchPtr()
{
    return (uint8_t*)&multiTouch;
}


//for windows
uint8_t *getTouchQualityKeyPtr()
{
    return (uint8_t*)&touchQualityKey;
}

//interrupt Pen IRQ
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
///{
//	if(GPIO_Pin == GPIO_PIN_9)
//	{
//		touchIrq = 1;
//	}
//}

void io_init(void)
{
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_RESET);//��λOV2640
    HAL_Delay(20);
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_SET);//
    HAL_Delay(100);
}

uint8_t initTouch()
{
    uint8_t temp[2]; 
    //reset
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    //HAL_Delay(10);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    //HAL_Delay(10);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    //HAL_Delay(10);
    io_init();

    TOUCH_PAD_IO_Write(TOUCH_I2C_ID, FT_DEVIDE_MODE, 0x00);	//进入正常操作模式 
    TOUCH_PAD_IO_Write(TOUCH_I2C_ID, FT_ID_G_MODE, 0x00);		//查询模式 
    TOUCH_PAD_IO_Write(TOUCH_I2C_ID, FT_ID_G_THGROUP, 22);	//设置触摸有效值，越小越灵敏	
    TOUCH_PAD_IO_Write(TOUCH_I2C_ID, FT_ID_G_PERIODACTIVE, 12); //激活周期，不能小于12，最大14
    //读取版本号，参考值：0x3003
    TOUCH_PAD_IO_multiRead(TOUCH_I2C_ID, FT_ID_G_LIB_VERSION, &temp[0], 2);  
    if((temp[0]==0X30&&temp[1]==0X03)||temp[1]==0X01||temp[1]==0X02)//版本:0X3003/0X0001/0X0002
    {
        //printf("CTP ID:%x\r\n",((uint16_t)temp[0]<<8)+temp[1]);
        return 0;
    }  
    return 1;
    /*multiTouch.count = 0;
    multiTouch.id=0;
    for(int i=0;i<max_point_num;i++)
    {
        memset(&multiTouch.touch[i], 0x00, sizeof(struct touchHid_t));
    }*/
}

//void toucuProc(I2C_HandleTypeDef hi2c1)
/*void toucuProc()
{
    uint8_t point_num;
    uint8_t i;
    uint16_t x[max_point_num];
    uint16_t y[max_point_num];

    uint16_t id[max_point_num];

    uint8_t dat[100];

    if(touchIrq)
    {
        touchIrq=0;

        //readI2C(TOUCH_I2C_ID, 0x00, dat, 40);
        TOUCH_PAD_IO_multiRead(TOUCH_I2C_ID, 0x00, dat, 40);
        //HAL_I2C_Mem_Read(&hi2c1, TOUCH_I2C_ID, 0x00, I2C_MEMADD_SIZE_8BIT, (uint8_t *)dat, 40, 200);

        //HAL_I2C_Master_Receive_DMA()
        //device mode[6:4]
        //0 Work Mode
        //4 Factory Mode
        if((dat[0] & 0x70) != 0)
            return;

        //Number of Touch points
        point_num =  dat[2] & 0x0f;

        if(point_num > max_point_num)
            point_num = max_point_num;

        for(i = 0; i < point_num; i++)
        {
            //03H [7:6] Event Flag - not used
            // 0 : down
            // 1 : up
            // 2 : contact
            // 3 : reserved
            //05H [7:4] Touch ID
            // [3:0] Touch ID of Touch Point

            //03H [3:0] MSB of Touch X Position in pixels [11:8]
            //04H [7:0] LSB of Touch X Position in pixels [7:0]
            //05H [3:0] MSB of Touch Y Position in pixels [11:8]
            //06H [7:0] LSB of Touch Y Position in pixels [7:0]

            x[i] = (((uint16_t)dat[3+6*i]&0x0F)<<8)|dat[3+6*i+1];
            y[i] = (((uint16_t)dat[3+6*i+2]&0x0F)<<8)|dat[3+6*i+3];

            id[i] = dat[5+6*i]>>4;

            if(x[i] > 1024)
                x[i] = 1024;
            if(y[i] > 600)
                y[i] = 600;
            x[i] = (x[i]*2048)/1024;// touch range ( 0 ~ 1024 ) to USB HID range (0 ~  2048)
            y[i] = (y[i]*2048)/600; // touch range ( 0 ~ 1024 ) to USB HID range (0 ~  2048)

            tpd_down(x[i], y[i], id[i]);


            for(uint8_t c = 0; c < point_num; c++)
            {
                if(id[i] == oldid[c])
                {
                    oldid[c]=255;
                }

            }

        }
        //input_sync();


        for(i=0; i < point_num; i++)
        {
            if(oldid[i]!=255)
            {
                    tpd_up(x[i], y[i], oldid[i]);

            }
            oldid[i] = id[i];
        }
        input_sync();

    }
}*/

const uint16_t FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};
touchPad ft5315;
extern osMessageQId mid_MsgQueueHandle;
extern osSemaphoreId touchSignalHandle;
//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
void toucuProc()
{
    uint8_t buf[4];
    osSemaphoreWait (touchSignalHandle, osWaitForever);
    for( uint8_t i = 0; i < 1; i++ ){
        TOUCH_PAD_IO_multiRead(TOUCH_I2C_ID, FT5206_TPX_TBL[i], buf, 4);//读取XY坐标值 
        ft5315.y[i] = ( (uint16_t)( buf[0] & 0X0F ) << 8) + buf[1];
        ft5315.x[i] = ( (uint16_t)( buf[2] & 0X0F ) << 8) + buf[3];
        osMessagePut (mid_MsgQueueHandle, (uint32_t)(&ft5315), osWaitForever);
    }
}
 

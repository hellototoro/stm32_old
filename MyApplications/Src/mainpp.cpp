#include "Inc/mainpp.hpp"
#include <led/Inc/led.h>
#include <print/Inc/print.h>
#include "Components/sram/mcudev_stm32_f4xx_pro_sram.h"
#include <TouchGFXHAL.hpp>
#include "display/Inc/tftlcd_picture.h"
#include "Components/ft5316/ft5316.h"
#include <Inc/calendar.hpp>
#include "cmsis_os.h"

//bsp_camera camera;
MyApplications::calendar rtc_Calendar;
led led1(1);
led led2(2);
extern osSemaphoreId touchSignalHandle;




//#define CAMERA_FRAME_BUFFER               0x64000000
//#define CAMERA_I2C_ADDRESS                    0x60
//#define I2C_TIMEOUT  100 /*<! Value of Timeout when I2C communication fails */
//#define BSP_I2C_SPEED                            100000
//#define I2C_DUTYCYCLE_2                 0x00000000U
//#define EVAL_I2Cx                            I2C2

//CAMERA_DrvTypeDef  *camera_drv;
//extern I2C_HandleTypeDef  *heval_I2c;
//extern DCMI_HandleTypeDef *DCMI_Handle;
//uint32_t current_resolution;

void led2_toggle(void)
{
    led2.toggle();
}


void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    //LCD_SetWindow(0,0,lcd_dev.width,lcd_dev.height);
    //LCD_SetCursor(0,0);
    //LCD_WriteRAM_Prepare();		//开始写入GRAM
    //led1.toggle();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == LCD_TE_SIGNAL_Pin)
    {
        //bool PinStatus = (HAL_GPIO_ReadPin(LCD_TE_SIGNAL_GPIO_Port, LCD_TE_SIGNAL_Pin) == GPIO_PIN_SET ? true : false);
        TE_Handler();
    } else if (GPIO_Pin == TOUCH_IRQ_Pin) {
        //touchIrq = 1;
        osSemaphoreRelease (touchSignalHandle);
    }
}


void setup(void)
{
    tftlcd.s6d04d1::init();
    initTouch();
    rtc_Calendar.init();
    //tftlcd.s6d04d1::drawRGBImage(0, 0, 400, 240, (uint8_t *)gImage_ff);

    //camera.init(CAMERA_R320x240);
    //ov2640_set_rgb565_mode(CAMERA_I2C_ADDRESS);
    //ov2640_set_output_size(CAMERA_I2C_ADDRESS,320,lcd_dev.height);
    //LCD_SetWindow(0,0,lcd_dev.width,lcd_dev.height);
    //LCD_WriteRAM_Prepare();		//开始写入GRAM

    //camera.continuousStart((uint8_t *)&TFT_LCD->RAM);
    //HAL_DCMI_Start_DMA(DCMI_Handle, DCMI_MODE_CONTINUOUS, (uint32_t)(&TFT_LCD->RAM),  1);
    //sram_test();
}

void loop(void)
{
    toucuProc();
    //TE_Handler();
    //if(image_updata)
    //{
    //	image_updata = 0;
    //	LCD_ShowPicture2(0, 0, 400, 240,(uint16_t *)FrameBuffer);
    //	HAL_DCMI_Resume(DCMI_Handle);
    //}
}

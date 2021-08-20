#include "Inc/mainpp.hpp"
#include <TouchGFXHAL.hpp>
#include <Components/ft5316/ft5316.hpp>
#include "camera/camera.hpp"
#include <led/led.hpp>
#include <Inc/calendar.hpp>
#include "cmsis_os.h"

ft5316 touchPad(I2C_Handle);
MyApplications::calendar rtc_Calendar;
MyDrivers::camera MyCamera(I2C_Handle, CAMERA_R320x240);
MyDrivers::led led1(1);
MyDrivers::led led2(2);

extern osMessageQId mid_MsgQueueHandle;
extern osSemaphoreId touchSignalHandle;

osThreadId touchPadTaskHandle;
uint32_t touchPadTaskBuffer[ 128 ];
osStaticThreadDef_t touchPadTaskControlBlock;
void StartTouchPadTask(void const * argument);

void led2_toggle(void)
{
    led2.toggle();
}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    tftlcd.setDisplayWindow(80,0,320,240);
    tftlcd.prepareWrite();
    led2_toggle();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == LCD_TE_SIGNAL_Pin)
    {
        //bool PinStatus = (HAL_GPIO_ReadPin(LCD_TE_SIGNAL_GPIO_Port, LCD_TE_SIGNAL_Pin) == GPIO_PIN_SET ? true : false);
        TE_Handler();
    } else if (GPIO_Pin == TOUCH_IRQ_Pin) {
        osSemaphoreRelease (touchSignalHandle);
    }
}


void setup(void)
{
    tftlcd.s6d04d1::init();
    touchPad.init();
    MyCamera.init();
    rtc_Calendar.init();


    //创建触摸板任务
    /* definition and creation of touchPadTask */
    osThreadStaticDef(touchPadTask, StartTouchPadTask, osPriorityNormal, 0, 128, touchPadTaskBuffer, &touchPadTaskControlBlock);
    touchPadTaskHandle = osThreadCreate(osThread(touchPadTask), NULL);

    /*tftlcd.clear(MyDrivers::lcd_color::BLUE);
    MyCamera.setOutputSize(320,240);
    tftlcd.setDisplayWindow(80,0,320,240);
    tftlcd.prepareWrite();
    MyCamera.continuousStart((uint8_t *)tftlcd.getDisplayAddress());
    while(1);*/
}

void loop(void)
{
    led1.toggle();
    osDelay(1000);
}


/**
* @brief Function implementing the touchPadTask thread.
* @param argument: Not used
* @retval None
*/
void StartTouchPadTask(void const * argument)
{
    touchDataDef touchData;
    /* Infinite loop */
    for(;;)
    {
        osSemaphoreWait (touchSignalHandle, osWaitForever);
        do  {
            touchPad.readData(touchData.x[0], touchData.y[0]);
            osMessagePut (mid_MsgQueueHandle, (uint32_t)(&touchData), osWaitForever);
            osDelay(100);
        } while(HAL_GPIO_ReadPin(TOUCH_IRQ_GPIO_Port, TOUCH_IRQ_Pin) == GPIO_PIN_RESET);
    }
}

#ifndef __OV7670_H
#define __OV7670_H
 
#include "main.h"
 
//===============以下引脚定义需要修改============
#define SCCB_ID 0X42
//#define SCCB_SDA GPIOC,GPIO_Pin_1
//#define SCCB_SCL GPIOC,GPIO_Pin_0
 
//#define DCMI_HSYNC_PIN			GPIOA,GPIO_Pin_4
//#define DCMI_HSYNC_PIN_S		GPIOA,GPIO_PinSource4
//#define DCMI_PIXCLK_PIN			GPIOA,GPIO_Pin_6
//#define DCMI_PIXCLK_PIN_S		GPIOA,GPIO_PinSource6
//#define DCMI_VSYNC_PIN			GPIOB,GPIO_Pin_7
//#define DCMI_VSYNC_PIN_S		GPIOB,GPIO_PinSource7
// 
//#define DCMI_D0_PIN					GPIOC,GPIO_Pin_6
//#define DCMI_D0_PIN_S				GPIOC,GPIO_PinSource6
//#define DCMI_D1_PIN					GPIOC,GPIO_Pin_7
//#define DCMI_D1_PIN_S				GPIOC,GPIO_PinSource7
//#define DCMI_D2_PIN					GPIOE,GPIO_Pin_0
//#define DCMI_D2_PIN_S				GPIOE,GPIO_PinSource0
//#define DCMI_D3_PIN					GPIOE,GPIO_Pin_1
//#define DCMI_D3_PIN_S				GPIOE,GPIO_PinSource1
//#define DCMI_D4_PIN					GPIOE,GPIO_Pin_4
//#define DCMI_D4_PIN_S				GPIOE,GPIO_PinSource4
//#define DCMI_D5_PIN					GPIOB,GPIO_Pin_6
//#define DCMI_D5_PIN_S				GPIOB,GPIO_PinSource6
//#define DCMI_D6_PIN					GPIOB,GPIO_Pin_8
//#define DCMI_D6_PIN_S				GPIOB,GPIO_PinSource8
//#define DCMI_D7_PIN					GPIOB,GPIO_Pin_9
//#define DCMI_D7_PIN_S				GPIOB,GPIO_PinSource9
//================================================
 
#define QVGA_LINE_PIX 160	//QVGA一行多少字
 
#define NOW_USE_FRAME (!CamNowFrame)		//获取存放好数据的帧
 
extern int ov_frame;
extern int ov_line;				//引用不安全
extern unsigned short OV7670_Frame[2][120][160];		//75KB
extern unsigned int OV7670_LineBuf[QVGA_LINE_PIX];
extern int CamNowFrame;		//引用不安全
 
 
void Ov7670_SysClock_Init(void);
int check_camera(void);
void OV7670_Reg_Init(void);
void OV7670_DCMI_Init(uint16_t DCMI_CaptureMode,int PrePriority,int SubPriority);
void OV7670_DMA_LineCircular(int PrePriority,int SubPriority);
void DCMI_Start(uint32_t pData, uint32_t Length);		//DCMI启动传输
void DCMI_Stop(void);			//DCMI关闭传输
void CameraStart(void);		//开始采集一帧
int IsCameraReady(void);	//一帧是否已经完成
 
/*双缓冲图像处理方法
while(!check_camera());
OV7670_Reg_Init();
OV7670_DCMI_Init(DCMI_CaptureMode_Continuous,0,1);
OV7670_DMA_LineCircular(0,0);
DCMI_Start();
CameraStart();
while(1)
{
	if(IsCameraReady())
	{
		CameraStart();
		//TODO:
		//Image Process,50ms/20fps
		for(i=0;i<120;i++)
			for(j=0;j<160;j++)
				LCD_Fast_DrawPoint(j,i,OV7670_Frame[NOW_USE_FRAME][i][j]);
	}
}
*/
 
#define CAMST_WaitStart	0
#define CAMST_Start			1
#define CAMST_WaitImg		2
#define CAMST_ImgReady	3
#define CAMST_ImgError	4	//图像出错状态
 
extern int CamState;	//引用不安全
 
#endif

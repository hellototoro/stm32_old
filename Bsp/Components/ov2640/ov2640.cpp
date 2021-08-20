#include <Components/ov2640/ov2640.hpp>
#include "Components/ov2640/ov2640cfg.h"

ov2640::ov2640(I2C_HandleTypeDef *_touchPad_IIC_Handle) : 
camera_IIC_Handle { _touchPad_IIC_Handle }{
    // TODO Auto-generated constructor stub
    ov2640_iic.init(camera_IIC_Handle, OV2640_ADDRESS_ID);
}

void ov2640::resetChip(void)
{
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_RESET);//
    HAL_Delay(10);
    HAL_GPIO_WritePin(DCMI_RESET_GPIO_Port, DCMI_RESET_Pin, GPIO_PIN_SET);//
    HAL_Delay(100);
}

uint8_t ov2640::init(uint32_t resolution)
{
    //uint16_t buffer;
    //resetChip();

    ov2640_iic.writeByte(OV2640_DSP_RA_DLMT, 0x01);
    ov2640_iic.writeByte(OV2640_SENSOR_COM7, 0x80);
    HAL_Delay(200);

    /*ov2640_iic.writeByte(OV2640_DSP_RA_DLMT, 0x01);	//����sensor�Ĵ���
    ov2640_iic.writeByte(OV2640_SENSOR_COM7, 0x80);	//��λOV2640
    HAL_Delay(50);
    buffer = ov2640_iic.readByte(OV2640_SENSOR_MIDH);	//��ȡ����ID �߰�λ
    buffer <<= 8;
    buffer |= ov2640_iic.readByte(OV2640_SENSOR_MIDL);	//��ȡ����ID �Ͱ�λ
    if( buffer != OV2640_MID )
    {
        //printf("MID:%d\r\n",buffer);
        return 1;
    }
    buffer = ov2640_iic.readByte(OV2640_SENSOR_PIDH);	//��ȡ����ID �߰�λ
    buffer <<= 8;
    buffer |= ov2640_iic.readByte(OV2640_SENSOR_PIDL);	//��ȡ����ID �Ͱ�λ
    if(buffer != OV2640_PID)
    {
        //printf("HID:%d\r\n",buffer);
        return 2;
    }*/


  /* Initialize OV2640 */
    switch (resolution)
    {
    case CAMERA_R160x120:
        {
        for(uint32_t index=0; index<(sizeof(OV2640_QQVGA)/2); index++)
        {
            ov2640_iic.writeByte(OV2640_QQVGA[index][0], OV2640_QQVGA[index][1]);
            HAL_Delay(1);
        } 
        break;
        }    
    case CAMERA_R320x240:
        {
        for(uint32_t index=0; index<(sizeof(OV2640_QVGA)/2); index++)
        {
            ov2640_iic.writeByte(OV2640_QVGA[index][0], OV2640_QVGA[index][1]);
            HAL_Delay(1);
        } 
        break;
        }
    case CAMERA_R480x272:
        {
        for(uint32_t index=0; index<(sizeof(OV2640_480x272)/2); index++)
        {
            ov2640_iic.writeByte(OV2640_480x272[index][0], OV2640_480x272[index][1]);
            HAL_Delay(2);
        }
        break;
        }
    case CAMERA_R640x480:
        {
        for(uint32_t index=0; index<(sizeof(OV2640_VGA)/2); index++)
        {
            ov2640_iic.writeByte(OV2640_VGA[index][0], OV2640_VGA[index][1]);
            HAL_Delay(2);
        }
        break;
        }    
    default:
        {
        break;
        }
    }
    return 0x00; 	//ok
}

/**
  * @brief  Read the OV2640 Camera identity.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval the OV2640 ID
  */
uint16_t ov2640::readID(void)
{
    /* Initialize I2C */
    //CAMERA_IO_Init();
    
    /* Prepare the sensor to read the Camera ID */
    ov2640_iic.writeByte(OV2640_DSP_RA_DLMT, 0x01);
    
    /* Get the camera ID */
    return (ov2640_iic.readByte(OV2640_SENSOR_PIDH));
}


//OV2640切换为RGB565ģ模式
void ov2640::set_rgb565_mode(void) 
{
    for(uint16_t i = 0; i < (sizeof(OV2640_QVGA)/2); i++)
    {
        ov2640_iic.writeByte(OV2640_QVGA[i][0],OV2640_QVGA[i][1]);
    } 
} 


//OV2640切换为JPEG模式
void ov2640::set_jpeg_mode(void)
{
    uint16_t i=0;
    //设置:YUV422格式
    for( i = 0; i < (sizeof(ov2640_yuv422_reg_tbl)/2); i++)
    {
        ov2640_iic.writeByte(ov2640_yuv422_reg_tbl[i][0],ov2640_yuv422_reg_tbl[i][1]);
    }

    //设置:输出JPEG数据
    for( i = 0; i < (sizeof(ov2640_jpeg_reg_tbl)/2); i++)
    {
        ov2640_iic.writeByte(ov2640_jpeg_reg_tbl[i][0],ov2640_jpeg_reg_tbl[i][1]);
    }
}

//OV2640自动曝光等级设置
//level:0~4
void ov2640::auto_exposure(uint8_t level)
{
    uint8_t i;
    uint8_t *p=(uint8_t*)OV2640_AUTOEXPOSURE_LEVEL[level];
    for(i=0;i<4;i++)
    {
        ov2640_iic.writeByte(p[i*2],p[i*2+1]);
    }
}
//白平衡设置
//0:自动
//1:太阳sunny
//2,阴天cloudy
//3,办公室office
//4,家里home
void ov2640::light_mode(uint8_t mode)
{
    uint8_t regccval=0X5E;//Sunny
    uint8_t regcdval=0X41;
    uint8_t regceval=0X54;
    switch(mode)
    {
        case 0://auto
            ov2640_iic.writeByte(0XFF,0X00);
            ov2640_iic.writeByte(0XC7,0X00);//AWB ON
            return;
        case 2://cloudy
            regccval=0X65;
            regcdval=0X41;
            regceval=0X4F;
            break;
        case 3://office
            regccval=0X52;
            regcdval=0X41;
            regceval=0X66;
            break;
        case 4://home
            regccval=0X42;
            regcdval=0X3F;
            regceval=0X71;
            break;
    }
    ov2640_iic.writeByte(0XFF,0X00);
    ov2640_iic.writeByte(0XC7,0X40);	//AWB OFF
    ov2640_iic.writeByte(0XCC,regccval);
    ov2640_iic.writeByte(0XCD,regcdval);
    ov2640_iic.writeByte(0XCE,regceval);
}
//色度设置
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void ov2640::color_saturation(uint8_t sat)
{
    uint8_t reg7dval=((sat+2)<<4)|0X08;
    ov2640_iic.writeByte(0XFF,0X00);
    ov2640_iic.writeByte(0X7C,0X00);
    ov2640_iic.writeByte(0X7D,0X02);
    ov2640_iic.writeByte(0X7C,0X03);
    ov2640_iic.writeByte(0X7D,reg7dval);
    ov2640_iic.writeByte(0X7D,reg7dval);
}
//亮度设置
//0:(0X00)-2
//1:(0X10)-1
//2,(0X20) 0
//3,(0X30)+1
//4,(0X40)+2
void ov2640::brightness(uint8_t bright)
{
  ov2640_iic.writeByte(0xff, 0x00);
  ov2640_iic.writeByte(0x7c, 0x00);
  ov2640_iic.writeByte(0x7d, 0x04);
  ov2640_iic.writeByte(0x7c, 0x09);
  ov2640_iic.writeByte(0x7d, bright<<4);
  ov2640_iic.writeByte(0x7d, 0x00);
}
//对比度设置
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void ov2640::contrast(uint8_t contrast)
{
    uint8_t reg7d0val=0X20;//默认为普通模式
    uint8_t reg7d1val=0X20;
      switch(contrast)
    {
        case 0://-2
            reg7d0val=0X18;
            reg7d1val=0X34;
            break;
        case 1://-1
            reg7d0val=0X1C;
            reg7d1val=0X2A;
            break;
        case 3://1
            reg7d0val=0X24;
            reg7d1val=0X16;
            break;
        case 4://2
            reg7d0val=0X28;
            reg7d1val=0X0C;
            break;
    }
    ov2640_iic.writeByte(0xff,0x00);
    ov2640_iic.writeByte(0x7c,0x00);
    ov2640_iic.writeByte(0x7d,0x04);
    ov2640_iic.writeByte(0x7c,0x07);
    ov2640_iic.writeByte(0x7d,0x20);
    ov2640_iic.writeByte(0x7d,reg7d0val);
    ov2640_iic.writeByte(0x7d,reg7d1val);
    ov2640_iic.writeByte(0x7d,0x06);
}
//特效设置
//0:普通模式
//1,负片
//2,黑白
//3,偏红色
//4,偏绿色
//5,偏蓝色
//6,复古
void ov2640::special_effects(uint8_t eft)
{
    uint8_t reg7d0val=0X00;//默认为普通模式
    uint8_t reg7d1val=0X80;
    uint8_t reg7d2val=0X80;
    switch(eft)
    {
        case 1://负片
            reg7d0val=0X40;
            break;
        case 2://黑白
            reg7d0val=0X18;
            break;
        case 3://偏红色
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0XC0;
            break;
        case 4://偏绿色
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0X40;
            break;
        case 5://偏蓝色
            reg7d0val=0X18;
            reg7d1val=0XA0;
            reg7d2val=0X40;
            break;
        case 6://复古
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0XA6;
            break;
    }
    ov2640_iic.writeByte(0xff,0x00);
    ov2640_iic.writeByte(0x7c,0x00);
    ov2640_iic.writeByte(0x7d,reg7d0val);
    ov2640_iic.writeByte(0x7c,0x05);
    ov2640_iic.writeByte(0x7d,reg7d1val);
    ov2640_iic.writeByte(0x7d,reg7d2val);
}
//彩条测试
//sw:0,关闭彩条
//   1,开启彩条(注意OV2640的彩条是叠加在图像上面的)
void ov2640::color_bar(uint8_t sw)
{
    uint8_t reg;
    ov2640_iic.writeByte(0XFF,0X01);
    reg=ov2640_iic.readByte(0X12);
    reg&=~(1<<1);
    if(sw)reg|=1<<1;
    ov2640_iic.writeByte(0X12,reg);
}
//设置图像输出窗口
//sx,sy,起始地址
//width,height:宽度(对应:horizontal)和高度(对应:vertical)
void ov2640::window_set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
    uint16_t endx;
    uint16_t endy;
    uint8_t temp;
    endx=sx+width/2;	//V*2
     endy=sy+height/2;

    ov2640_iic.writeByte(0XFF,0X01);
    temp=ov2640_iic.readByte(0X03);				//读取Vref之前的值
    temp&=0XF0;
    temp|=((endy&0X03)<<2)|(sy&0X03);
    ov2640_iic.writeByte(0X03,temp);				//设置Vref的start和end的最低2位
    ov2640_iic.writeByte(0X19,sy>>2);			//设置Vref的start高8位
    ov2640_iic.writeByte(0X1A,endy>>2);			//设置Vref的end的高8位

    temp=ov2640_iic.readByte(0X32);				//读取Href之前的值
    temp&=0XC0;
    temp|=((endx&0X07)<<3)|(sx&0X07);
    ov2640_iic.writeByte(0X32,temp);				//设置Href的start和end的最低3位
    ov2640_iic.writeByte(0X17,sx>>3);			//设置Href的start高8位
    ov2640_iic.writeByte(0X18,endx>>3);			//设置Href的end的高8位
}
//设置图像输出大小

//OV2640输出图像的大小(分辨率),完全由改函数确定
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
//返回值:0,设置成功
//    其他,设置失败
uint8_t ov2640::set_output_size(uint16_t width,uint16_t height)
{
    uint16_t outh;
    uint16_t outw;
    uint8_t temp; 

    if(width%4)return 1;
    if(height%4)return 2;

    outw=width/4;
    outh=height/4; 

    ov2640_iic.writeByte(0XFF,0X00);	
    ov2640_iic.writeByte(0XE0,0X04);			
    ov2640_iic.writeByte(0X5A,outw&0XFF);		//设置OUTW的低八位
    ov2640_iic.writeByte(0X5B,outh&0XFF);		//设置OUTH的低八位
    temp=(outw>>8)&0X03;
    temp|=(outh>>6)&0X04;
    ov2640_iic.writeByte(0X5C,temp);				//设置OUTH/OUTW的高位
    ov2640_iic.writeByte(0XE0,0X00);
    return 0;
}
//设置图像开窗大小
//由:OV2640_ImageSize_Set确定传感器输出分辨率从大小.
//该函数则在这个范围上面进行开窗,用于OV2640_OutSize_Set的输出
//注意:本函数的宽度和高度,必须大于等于OV2640_OutSize_Set函数的宽度和高度
//     OV2640_OutSize_Set设置的宽度和高度,根据本函数设置的宽度和高度,由DSP
//     自动计算缩放比例,输出给外部设备.
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
//返回值:0,设置成功
//    其他,设置失败
uint8_t ov2640::imageWin_set(uint16_t offx,uint16_t offy,uint16_t width,uint16_t height)
{
    uint16_t hsize;
    uint16_t vsize;
    uint8_t temp;
    if(width%4)return 1;
    if(height%4)return 2;
    hsize=width/4;
    vsize=height/4;
    ov2640_iic.writeByte(0XFF,0X00);
    ov2640_iic.writeByte(0XE0,0X04);
    ov2640_iic.writeByte(0X51,hsize&0XFF);		//设置H_SIZE的低八位
    ov2640_iic.writeByte(0X52,vsize&0XFF);		//设置V_SIZE的低八位
    ov2640_iic.writeByte(0X53,offx&0XFF);		//设置offx的低八位
    ov2640_iic.writeByte(0X54,offy&0XFF);		//设置offy的低八位
    temp=(vsize>>1)&0X80;
    temp|=(offy>>4)&0X70;
    temp|=(hsize>>5)&0X08;
    temp|=(offx>>8)&0X07;
    ov2640_iic.writeByte(0X55,temp);				//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
    ov2640_iic.writeByte(0X57,(hsize>>2)&0X80);	//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
    ov2640_iic.writeByte(0XE0,0X00);	
    return 0;
}
//该函数设置图像尺寸大小,也就是所选格式的输出分辨率
//UXGA:1600*1200,SVGA:800*600,CIF:352*288
//width,height:图像宽度和图像高度
//返回值:0,设置成功
//    其他,设置失败
uint8_t ov2640::imageSize_set(uint16_t width,uint16_t height)
{
    uint8_t temp;
    ov2640_iic.writeByte(0XFF,0X00);
    ov2640_iic.writeByte(0XE0,0X04);
    ov2640_iic.writeByte(0XC0,(width)>>3&0XFF);		//设置HSIZE的10:3位
    ov2640_iic.writeByte(0XC1,(height)>>3&0XFF);		//设置VSIZE的10:3位
    temp=(width&0X07)<<3;
    temp|=height&0X07;
    temp|=(width>>4)&0X80;
    ov2640_iic.writeByte(0X8C,temp);
    ov2640_iic.writeByte(0XE0,0X00);
    return 0;
}


void ov2640::control_led(bool_switch led_switch)
{
    if (led_switch == ON) {
        HAL_GPIO_WritePin(DCMI_CH1_GPIO_Port, DCMI_CH1_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(DCMI_CH1_GPIO_Port, DCMI_CH1_Pin, GPIO_PIN_RESET);
    }
}

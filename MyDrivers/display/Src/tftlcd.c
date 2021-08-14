/**
  ******************************************************************************
  * @file    TFT_LCD.c
  * @brief   TFT LCD����������Ҫʹ��CubeMX����FSMC��
  *          ��ʼ������
	* @data    2021-7-27
	* @author  jee
  ******************************************************************************
  */
#include <display/Inc/tftlcd.h>
#include <display/Inc/tftlcd_font.h>
#include <display/Inc/tftlcd_picture.h>
#include "print/Inc/print.h"


/**************��������***************/
LCD_devTypeDef lcd_dev;

/**
  * @brief  Writes register value.
  */
static void FSMC_BANK1NORSRAM4_WriteData(uint16_t Data)
{
  /* Write 16-bit Data */
  TFT_LCD->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: 
  * @retval None
  */
static void FSMC_BANK1NORSRAM4_WriteReg(uint16_t Reg)
{
  /* Write 16-bit Index, then Write Reg */
  TFT_LCD->REG = Reg;
}

/**
  * @brief  Reads register value.
  * @retval Read value
  */
static uint16_t FSMC_BANK1NORSRAM4_ReadData(uint16_t Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  TFT_LCD->REG = Reg;
  /* Read 16-bit Reg */
  return (TFT_LCD->RAM);
}

/**
  * @brief  Writes data on LCD data register.
  * @param  RegValue: Data to be written
  * @retval None
  */
void LCD_IO_WriteData(uint16_t RegValue)
{
    FSMC_BANK1NORSRAM4_WriteData(RegValue);
}


/**
  * @brief  Writes register on LCD register.
  * @param  Reg: Register to be written
  */
void LCD_IO_WriteReg(uint16_t Reg)
{
  FSMC_BANK1NORSRAM4_WriteReg(Reg);
}

/**
  * @brief  Reads data from LCD data register.
  * @param  Reg: Register to be read
  * @retval Read data.
  */
uint16_t LCD_IO_ReadData(uint16_t Reg)
{
  /* Read 16-bit Reg */
  return (FSMC_BANK1NORSRAM4_ReadData(Reg));
}

/*void LCD_IO_WriteMultipleData(uint16_t* pData, uint32_t Size)
{
	uint32_t  i;

	for (i = 0; i < Size; i++)
	{
		//LCD->LCD_RAM=pData[i];
		LCD_IO_WriteData(pData[i]);
	}
}*/

//写寄存器
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void LCD_WriteCmd(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD_IO_WriteReg(LCD_Reg);
	LCD_IO_WriteData(LCD_RegValue);
}

//开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_IO_WriteReg(lcd_dev.wramcmd);
}

/**
  * @brief  Wait for loop in ms.
  * @param  Delay in ms.
  */
void LCD_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    if( lcd_dev.dir == 1 )
    	Xpos = lcd_dev.width - 1 -Xpos;//横屏其实就是调转x,y坐标
    LCD_WriteCmd(lcd_dev.setxcmd, Xpos);
    LCD_WriteCmd(lcd_dev.setycmd, Ypos);
}

void LCD_Scan_Dir(uint8_t dir)
{
    switch (dir)
    {
        case 0:
        {
            LCD_WriteCmd(0x0001, 0x0100);
            LCD_WriteCmd(0x0003, 0x1030);
            break;
        }
        case 1:
        {
            LCD_WriteCmd(0x0001, 0x0100);
            LCD_WriteCmd(0x0003, 0x1038);
            break;
        }
        default :
            break;
    }
}

void LCD_SetDisplayDir(LCD_DisplayDirTypeDef DisplayDir)
{
    lcd_dev.dir = DisplayDir;
	lcd_dev.wramcmd=R34;
    switch (lcd_dev.dir)
    {
        case vertical:
        {
            lcd_dev.height=400;
            lcd_dev.width=240;
            lcd_dev.setxcmd=R32;
            lcd_dev.setycmd=R33;
            break;
        }
        case horizontal:
        {
            lcd_dev.height=240;
            lcd_dev.width=400;
            lcd_dev.setxcmd=R33;
            lcd_dev.setycmd=R32;
            break;
        }
        default :
            break;
    }
    LCD_Scan_Dir(lcd_dev.dir);
}

void LCD_SetWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint16_t hsaval,heaval,vsaval,veaval;
	width=sx+width-1;
	height=sy+height-1;
    if(lcd_dev.dir==1)//横屏
    {
        //窗口值
        hsaval=sy;
        heaval=height;
        vsaval=lcd_dev.width-width-1;
        veaval=lcd_dev.width-sx-1;
    }else
    {
        hsaval=sx;
        heaval=width;
        vsaval=sy;
        veaval=height;
    }
    //设置寄存器值
    LCD_WriteCmd(0x0210,hsaval);
    LCD_WriteCmd(0x0211,heaval);
    LCD_WriteCmd(0x0212,vsaval);
    LCD_WriteCmd(0x0213,veaval);
    LCD_SetCursor(sx,sy);	//设置光标位置
}

void LCD_SetColor(uint16_t front, uint16_t back)
{
    lcd_dev.color.front = front;
    lcd_dev.color.back = back;
}

void LCD_Clear(uint16_t color)
{
	uint32_t index = 0;
	uint32_t totalpoint = lcd_dev.width;
	totalpoint *= lcd_dev.height; 			//得到总点数
 	LCD_SetCursor(0x00,0x0000);	//设置光标位置
	LCD_WriteRAM_Prepare();     		//开始写入GRAM
	for(index = 0; index < totalpoint; index++)
	{
		TFT_LCD->RAM = color;
	}
}

//��������
//color:Ҫ���������ɫ
void LCD_FillColor(uint16_t color)
{
	uint16_t i, j;

	LCD_SetWindow(0, 0, lcd_dev.width, lcd_dev.height);	 //��������
	LCD_WriteRAM_Prepare();
  	for(i=0; i<lcd_dev.width; i++)
	{
		for (j=0; j<lcd_dev.height; j++)
		{
			LCD_IO_WriteData(color);
		}
	} 
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{	   
	LCD_SetCursor(x, y);
	LCD_WriteCmd(lcd_dev.wramcmd,color);
} 

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t;
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x > 0) {
        incx=1; //���õ������� 
    } else if(delta_x == 0) {
        incx=0;//��ֱ�� 
    } else {
        incx=-1;
        delta_x = -delta_x;
    } 
    
	if(delta_y > 0) {
        incy=1; 
    } else if(delta_y == 0) {
        incy=0;//ˮƽ�� 
    } else {
        incy=-1;
        delta_y=-delta_y;
    } 
    
    distance = (delta_x > delta_y) ? delta_x : delta_y;//ѡȡ�������������� 
   
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr > distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr > distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=ascii_1608[num][t];	//����1608����
		else if(size==24)temp=ascii_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80) {
                LCD_DrawPoint(x,y,lcd_dev.color.front);
            } else if(mode==0) {
                LCD_DrawPoint(x,y,lcd_dev.color.back);
            }
			temp<<=1;
			y++;
			if(y>=lcd_dev.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcd_dev.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   

//m^n����
//����ֵ:m^n�η�.
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)result*=m;    
	return result;
}	

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_Show_xNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
}

//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,char *p)
{         
	uint8_t x0=x;
	uint16_t width = lcd_dev.width + x;
	uint16_t height = lcd_dev.height + y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

void LCD_ShowChinese32X29(uint16_t x, uint16_t y, char *cn)
{
	uint8_t i, j, wordNum;
	uint16_t color;
	uint16_t x0=x;
	uint16_t y0=y;
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<sizeof(CnChar32x29)/118; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			    &&(CnChar32x29[wordNum].Index[1]==*(cn+1))
                &&(CnChar32x29[wordNum].Index[2]==*(cn+2)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawPoint(x,y,lcd_dev.color.front);
						} 						
						else
						{
							LCD_DrawPoint(x,y,lcd_dev.color.back);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 3;
		x += 32;
		x0=x;
	}
}	

void LCD_ShowChinese16X14(uint16_t x, uint16_t y, char *cn)
{
	uint8_t i, j, wordNum;
	uint16_t color;
	uint16_t x0=x;
	uint16_t y0=y;
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<sizeof(CnChar16x14)/30; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar16x14[wordNum].Index[0]==*cn)
			    &&(CnChar16x14[wordNum].Index[1]==*(cn+1))
                &&(CnChar16x14[wordNum].Index[2]==*(cn+2)))
			{
				for(i=0; i<28; i++) 
				{	//MSK��λ��
					color=CnChar16x14[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawPoint(x,y,lcd_dev.color.front);
						} 						
						else
						{
							LCD_DrawPoint(x,y,lcd_dev.color.back);
						} 
						color<<=1;
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							if((y-y0)==14)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 3;
		x += 16;
		x0=x;
	}
}	

void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint8_t *pic)
{
	uint16_t temp = 0;
	long tmp=0,num=0;
	//LCD_SetWindow(x, y, x+wide, y+high);
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_IO_WriteData(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}

void LCD_ShowPicture2(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint16_t *pic)
{
	//uint16_t temp = 0;
	long tmp=0,num=0;
	LCD_SetCursor(0,0);
	//LCD_SetWindow(x, y, x+wide-1, y+high-1);
	LCD_WriteRAM_Prepare();
	num = wide * high ;
	do
	{
		//temp = pic[tmp];
		//temp = temp << 8;
		//temp = temp | pic[tmp];
		LCD_IO_WriteData(pic[tmp++]);//�����ʾ
		//tmp += 1;
	}
	while(tmp < num);
}

void LCD_BacklightControl(bool_switch Backlight)
{
    if (Backlight == ON) {
//        HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
    } else {
//        HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
    }
}


void LCD_Init(void)
{
	LCD_Delay(50);
	lcd_dev.id = LCD_IO_ReadData(0X0000);
 	//printf("LCD ID: %0X\r\n",lcd_dev.id); //��ӡLCD ID
	
	LCD_IO_WriteReg(0x0000);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0000);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0000);LCD_IO_WriteData(0x0000);
//	for(i=500; i>0; i--);

	LCD_IO_WriteReg(0x0400);LCD_IO_WriteData(0x6200);
	LCD_IO_WriteReg(0x0008);LCD_IO_WriteData(0x0808);

	LCD_IO_WriteReg(0x0300);LCD_IO_WriteData(0x0C00);
	LCD_IO_WriteReg(0x0301);LCD_IO_WriteData(0x5A0B);
	LCD_IO_WriteReg(0x0302);LCD_IO_WriteData(0x0906);
	LCD_IO_WriteReg(0x0303);LCD_IO_WriteData(0x1017);
	LCD_IO_WriteReg(0x0304);LCD_IO_WriteData(0x2300);
	LCD_IO_WriteReg(0x0305);LCD_IO_WriteData(0x1700);
	LCD_IO_WriteReg(0x0306);LCD_IO_WriteData(0x6309);
	LCD_IO_WriteReg(0x0307);LCD_IO_WriteData(0x0C09);
	LCD_IO_WriteReg(0x0308);LCD_IO_WriteData(0x010C);
	LCD_IO_WriteReg(0x0309);LCD_IO_WriteData(0x2232);



	LCD_IO_WriteReg(0x0010);LCD_IO_WriteData(0x0016);
	LCD_IO_WriteReg(0x0011);LCD_IO_WriteData(0x0101);
	LCD_IO_WriteReg(0x0012);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0013);LCD_IO_WriteData(0x0001);

	LCD_IO_WriteReg(0x0100);LCD_IO_WriteData(0x0330);
	LCD_IO_WriteReg(0x0101);LCD_IO_WriteData(0x0336);
	LCD_IO_WriteReg(0x0103);LCD_IO_WriteData(0x1000);

	LCD_IO_WriteReg(0x0280);LCD_IO_WriteData(0x6100);
	LCD_IO_WriteReg(0x0102);LCD_IO_WriteData(0xBBB4);
//	for(i=500; i>0; i--);

	LCD_IO_WriteReg(0x0001);LCD_IO_WriteData(0x0100);
	LCD_IO_WriteReg(0x0002);LCD_IO_WriteData(0x0100);
	LCD_IO_WriteReg(0x0003);LCD_IO_WriteData(0x1030);
	LCD_IO_WriteReg(0x0009);LCD_IO_WriteData(0x0001);
	LCD_IO_WriteReg(0x000C);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0090);LCD_IO_WriteData(0x0800);
	LCD_IO_WriteReg(0x000F);LCD_IO_WriteData(0x0000);

	LCD_IO_WriteReg(0x0210);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0211);LCD_IO_WriteData(0x00EF);
	LCD_IO_WriteReg(0x0212);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0213);LCD_IO_WriteData(0x018F);         //;400


	LCD_IO_WriteReg(0x0500);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0501);LCD_IO_WriteData(0x0000);
	LCD_IO_WriteReg(0x0502);LCD_IO_WriteData(0x005F);

	LCD_IO_WriteReg(0x0401);LCD_IO_WriteData(0x0001);
	LCD_IO_WriteReg(0x0404);LCD_IO_WriteData(0x0000);
//	for(i=500; i>0; i--);

	LCD_IO_WriteReg(0x0007);LCD_IO_WriteData(0x0100);
//	for(i=500; i>0; i--);

	LCD_IO_WriteReg(0x0202);
    
	LCD_SetDisplayDir(horizontal);		//0������  1������  Ĭ������
	LCD_FillColor(GRED);
	LCD_SetWindow(0, 0, 400, 240);
	//LCD_ShowPicture(0, 0, 400, 240,(uint8_t *)gImage_ff);
	LCD_BacklightControl(ON);
    //LCD_SetWindow(0,0,lcd_dev.width,lcd_dev.height);
    //LCD_WriteRAM_Prepare();		//开始写入GRAM
}

#include "ov2640/Inc/sccb.h"

#define SCCB_SDA(x)  HAL_GPIO_WritePin(DCMI_SDA_GPIO_Port, DCMI_SDA_Pin, (GPIO_PinState)(x))
#define SCCB_SCL(x)  HAL_GPIO_WritePin(DCMI_SCL_GPIO_Port, DCMI_SCL_Pin, (GPIO_PinState)(x))

//��ʼ��SCCB�ӿ� 
void SCCB_Init(void)
{
    
}	

void delay_us(__IO uint32_t nCount)
{
//    for (; nCount != 0;nCount--);
    __IO uint32_t u32Loop=nCount;

    while(u32Loop--)
    {
        #ifdef __mips__
        __asm__ __volatile__ ("nop");
        #endif

        #ifdef __AEONR2__
        __asm__ __volatile__ ("l.nop");
        #endif

        #ifdef __arm__
        __asm__ __volatile__ ("mov r0, r0");
        #endif
    }
}

void sda_out(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.Pin = DCMI_SDA_Pin;
    GPIO_InitStructer.Mode = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(DCMI_SDA_GPIO_Port, &GPIO_InitStructer);
}

void sda_in(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.Pin = DCMI_SDA_Pin;
    GPIO_InitStructer.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DCMI_SDA_GPIO_Port, &GPIO_InitStructer);

}

uint8_t sda_read()
{
    return (uint8_t)(HAL_GPIO_ReadPin(DCMI_SDA_GPIO_Port, DCMI_SDA_Pin));
}



//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
    SCCB_SDA(1);     //�����߸ߵ�ƽ	   
    SCCB_SCL(1);	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(IIC_DELAY);  
    SCCB_SDA(0);
    delay_us(IIC_DELAY);	 
    SCCB_SCL(0);	    //�����߻ָ��͵�ƽ��������������Ҫ	  
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    SCCB_SDA(0);
    delay_us(IIC_DELAY);	 
    SCCB_SCL(1);	
    delay_us(IIC_DELAY); 
    SCCB_SDA(1);	
    delay_us(IIC_DELAY);
}  
//����NA�ź�
void SCCB_No_Ack(void)
{
	delay_us(IIC_DELAY);
	SCCB_SDA(1);	
	SCCB_SCL(1);	
	delay_us(IIC_DELAY);
	SCCB_SCL(0);	
	delay_us(IIC_DELAY);
	SCCB_SDA(0);	
	delay_us(IIC_DELAY);
}
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��. 
uint8_t SCCB_WR_Byte(uint8_t dat)
{
	uint8_t j,res;	 
	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80)SCCB_SDA(1);	
		else SCCB_SDA(0);
		dat<<=1;
		delay_us(IIC_DELAY);
		SCCB_SCL(1);	
		delay_us(IIC_DELAY);
		SCCB_SCL(0);		   
	}			 
	sda_in();		//����SDAΪ���� 
	delay_us(IIC_DELAY);
	SCCB_SCL(1);			//���յھ�λ,���ж��Ƿ��ͳɹ�
	delay_us(IIC_DELAY);
	if(sda_read())res=1;  //SDA=1����ʧ�ܣ�����1
	else res=0;         //SDA=0���ͳɹ�������0
	SCCB_SCL(0);		 
	sda_out();		//����SDAΪ���    
	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp=0,j;    
	sda_in();		//����SDAΪ����  
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		delay_us(IIC_DELAY);
		SCCB_SCL(1);
		temp=temp<<1;
		if(sda_read())temp++;   
		delay_us(IIC_DELAY);
		SCCB_SCL(0);
	}	
	sda_out();		//����SDAΪ���    
	return temp;
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data)
{
	uint8_t res=0;
	SCCB_Start(); 					//����SCCB����
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//д����ID	  
	delay_us(IIC_DELAY*10);
  	if(SCCB_WR_Byte(reg))res=1;		//д�Ĵ�����ַ	  
	delay_us(IIC_DELAY*10);
  	if(SCCB_WR_Byte(data))res=1; 	//д����	 
  	SCCB_Stop();	  
  	return	res;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
uint8_t SCCB_RD_Reg(uint8_t reg)
{
	uint8_t val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(SCCB_ID);		//д����ID	  
	delay_us(IIC_DELAY*2);
  	SCCB_WR_Byte(reg);			//д�Ĵ�����ַ	  
	delay_us(IIC_DELAY*2);
	SCCB_Stop();   
	delay_us(IIC_DELAY);	   
	//���üĴ�����ַ�󣬲��Ƕ�
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//���Ͷ�����	  
	delay_us(IIC_DELAY*2);
  	val=SCCB_RD_Byte();		 	//��ȡ����
  	SCCB_No_Ack();
  	SCCB_Stop();
  	return val;
}
















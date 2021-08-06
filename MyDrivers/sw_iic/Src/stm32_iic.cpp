#include "sw_iic/Inc/stm32_iic.h"

GPIO_TypeDef* IIC_SCL_PORT[] = {DCMI_SCL_GPIO_Port, DCMI_SCL_GPIO_Port, DCMI_SCL_GPIO_Port};
GPIO_TypeDef* IIC_SDA_PORT[] = {DCMI_SDA_GPIO_Port, DCMI_SDA_GPIO_Port, DCMI_SDA_GPIO_Port};

const uint16_t  IIC_SCL_PIN[] = {DCMI_SCL_Pin, DCMI_SCL_Pin, DCMI_SCL_Pin};
const uint16_t  IIC_SDA_PIN[] = {DCMI_SDA_Pin, DCMI_SDA_Pin, DCMI_SDA_Pin};

Stm32IIC::Stm32IIC()
{
    SwIicDly = I2C_SPEED_MAPPING_100K;
}

void Stm32IIC::iic_delay(void)
{
    __IO uint32_t u32Loop = SwIicDly;

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

void Stm32IIC::update(IIC_TypeDef iic_)
{
    SwIicDly = I2C_SPEED_MAPPING_100K;
    iic = iic_;
}

void Stm32IIC::sda_out(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.Pin = IIC_SDA_PIN[this->iic];
    GPIO_InitStructer.Mode = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(IIC_SDA_PORT[this->iic], &GPIO_InitStructer);
}

void  Stm32IIC::sda_in(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.Pin = IIC_SDA_PIN[this->iic];
    GPIO_InitStructer.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(IIC_SDA_PORT[this->iic], &GPIO_InitStructer);

}

int Stm32IIC::sda_read()
{
    return static_cast<int>(HAL_GPIO_ReadPin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic]));
}

void  Stm32IIC::Start(void)
{
    sda_out();
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_SET);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET);
    iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_RESET);
    iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET);
}

void Stm32IIC::Stop(void)
{   
    sda_out();
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET); 			//SCL_L
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_RESET);			//SDA_L
    iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET); 				//SCL_H
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_SET);	 			//SDA_H
    iic_delay(IIC_DELAY);
}

//函数原型:		uint8_t Stm32IIC::Read_Ack(void)
// 功 能:	    读取ACK
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t Stm32IIC::Receive_Ack(void)
{
	uint8_t ucErrTime=0;
    sda_in();
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET); 				//SCL_H	
    iic_delay(IIC_DELAY);
	while(sda_read())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			Stop();
			return 1;
		}
	}
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET);			//SCL_L
    return 0;
}

//产生ACK应答
void Stm32IIC::Send_Ack(void)
{
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET); 				//SCL_H	
    sda_out();
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_RESET);			//SDA_L
	iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET); 				//SCL_H	
	iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET); 				//SCL_H	
}

//不产生ACK应答		    
void Stm32IIC::Send_NAck(void)
{
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET); 				//SCL_H	
	sda_out();
    HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], GPIO_PIN_SET);			//SDA_L
	iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET); 				//SCL_H	
	iic_delay(IIC_DELAY);
    HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET); 				//SCL_H	
}					 				     

//函数原型:		void Stm32IIC::Write_OneByte(uint8_t Dat)
//功　　能:	    写入、发送一个字节的数据
//输入	Dat     写入的数据
void Stm32IIC::Send_Byte(uint8_t Data)
{
    uint8_t i;  
    sda_out();
    for(i=0;i<8;i++)
    { 
        HAL_GPIO_WritePin(IIC_SDA_PORT[this->iic], IIC_SDA_PIN[this->iic], (GPIO_PinState)((Data&0x80)>>7));	 		//SDA_H
        Data <<= 1;
		iic_delay(IIC_DELAY);   //对TEA5767这三个延时都是必须的
        HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET);			//SCL_L
		iic_delay(IIC_DELAY); 
        HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET);			//SCL_L
		iic_delay(IIC_DELAY);
    }
}

//函数原型:		uint8_t Stm32IIC::Read_OneByte(void)
//功　　能:	    读取、接收一个字节的数据
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t Stm32IIC::Receive_Byte(uint8_t ack)
{  
    uint8_t data,i;
    sda_in();
    for( i = 0, data = 0; i < 8 ; i++)
    {
        HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_RESET);			//SCL_L
        iic_delay(IIC_DELAY);
        HAL_GPIO_WritePin(IIC_SCL_PORT[this->iic], IIC_SCL_PIN[this->iic], GPIO_PIN_SET); 				//SCL_H
        data <<= 1;
        if(sda_read()) 
            data++;   
		iic_delay(IIC_DELAY); 
    }
    if (!ack)
        Send_NAck();//发送nACK
    else
        Send_Ack(); //发送ACK   
    return data;
}

//函数原型:		int Stm32IIC::Write_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
//功　　能:	    向指定的地址写入、发送数据一定长度的字符串或数组
int Stm32IIC::Write_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    int i;
    Write_OneByte(addr << 1 );
    if (!Wait_Ack_Reply()) 
    {
        Stop();
        return 1;
    }
    Write_OneByte(reg);
    Wait_Ack_Reply();
    for (i = 0; i < len; i++) 
    {
        Write_OneByte(data[i]);
        if (!Wait_Ack_Reply()) 
        {
            Stop();
            return 0;
        }
    }
    Stop();
    return 0;

}

//函数原型:		int Stm32IIC::Read_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
//功　　能:	    读取、接收指定地址一定长度的字符串或数组
int Stm32IIC::Read_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    Write_OneByte(addr << 1);
    if (!Wait_Ack_Reply()) 
    {
        Stop();
        return 1;
    }
    Write_OneByte(reg);
    Wait_Ack_Reply();
    Start();
    Write_OneByte((addr << 1)+1);
    Wait_Ack_Reply();
    while (len) {
        if (len == 1)
            *buf = Read_Byte_Ack(0);
        else
            *buf = Read_Byte_Ack(1);
        buf++;
        len--;
    }
    Stop();
    return 0;
}

//函数原型:		uint8_t Stm32IIC::Read_DeviceAddr_OneByte(uint8_t Addr,uint8_t addr)
//功　　能:	    读取指定设备 指定寄存器的一个值
//输入	Addr    目标设备地址
//		addr	寄存器地址
//返回   读出来的值
uint8_t Stm32IIC::Read_DeviceAddr_OneByte(uint8_t Addr,uint8_t addr)
{
    uint8_t res=0;
    Start();	
    Write_OneByte(Addr);	   //发送写命令
    res++;
    Wait_Ack_Reply();
    Write_OneByte(addr); res++;  //发送地址
    Wait_Ack_Reply();	  
    //IIC_Stop();//产生一个停止条件	
    Start();
    Write_OneByte(Addr+1); res++;          //进入接收模式			   
    Wait_Ack_Reply();
    res=Read_Byte_Ack(0);	   
    Stop();//产生一个停止条件
    return res;
}

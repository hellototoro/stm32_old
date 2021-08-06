#ifndef __STM32_I2C_H
#define __STM32_I2C_H

#include "stm32f4xx.h"
#include "main.h"

#define STM32F4xx  // Change for your device

#ifdef STM32F4xx
typedef enum {
#define I2C_SPEED_MAPPING_400K           50
#define I2C_SPEED_MAPPING_350K           60
#define I2C_SPEED_MAPPING_300K           70
#define I2C_SPEED_MAPPING_250K           80
#define I2C_SPEED_MAPPING_200K          100
#define I2C_SPEED_MAPPING_150K          135
#define I2C_SPEED_MAPPING_100K          135
}
#elif defined(STM32F1xx)
#define I2C_SPEED_MAPPING_400K           50
#define I2C_SPEED_MAPPING_350K           60
#define I2C_SPEED_MAPPING_300K           70
#define I2C_SPEED_MAPPING_250K           80
#define I2C_SPEED_MAPPING_200K          100
#define I2C_SPEED_MAPPING_150K          135
#define I2C_SPEED_MAPPING_100K          135//200
#else
#define I2C_SPEED_MAPPING_400K           50
#define I2C_SPEED_MAPPING_350K           60
#define I2C_SPEED_MAPPING_300K           70
#define I2C_SPEED_MAPPING_250K           80
#define I2C_SPEED_MAPPING_200K          100
#define I2C_SPEED_MAPPING_150K          135
#define I2C_SPEED_MAPPING_100K          135//200
#endif

#define SWIIC_READ      0
#define SWIIC_WRITE     1
#define I2C_CHECK_PIN_DUMMY     100
#define I2C_ACKNOWLEDGE         _LOW
#define I2C_NON_ACKNOWLEDGE     _HIGH
#define I2C_ACCESS_DUMMY_TIME   3

#define HIBYTE(value)  ((BYTE)((value) / 0x100))
#define LOBYTE(value)  ((BYTE)(value))

#define IIC_DELAY 4
#define BUFFER_LENGTH 64

/** IIC Config **/
typedef enum {
    CAMERA = 0,//板载IMU
    IMU = 1,
    OLED_S = 2,
    IIC_END = 3
}IIC_TypeDef; 

class Stm32IIC
{   
public:
    Stm32IIC();
    void update(IIC_TypeDef iic_);                                                           	//指定使用哪个设备
    void sda_out(void);																			//SDA输出模式配置
    void sda_in(void);																			//SDA输入模式配置
    int sda_read();                                                                            //读取SDA数据
    void Start(void);																			//开始启动信号函数
    void Stop(void); 																			//停止信号函数
    uint8_t Receive_Ack(void);																		//读取ACK
    void Send_Ack() ;
    void Send_NAck() ;
    void Send_Byte(uint8_t Data);															//写入一个字节
    uint8_t Receive_Byte(uint8_t ack);																		//读取一个字节										
    int Write_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);					//向指定地址写入数据（数组）
    int Read_Addr_Data(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);					//读取指定地址的数据（数组）
private:
    void iic_delay(void);

private:
    uint32_t SwIicDly;
    IIC_TypeDef iic; 
};
#endif






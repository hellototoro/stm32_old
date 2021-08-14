/**
  ******************************************************************************
  * @file    bluetooth.c
  * @brief   ����Ӧ�ó���
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
//#include <display/Inc/tftlcd.h>
#include "../../MyApplications/Inc/bluetooth.h"

#include "../../MyApplications/Inc/car_control.h"
#include "../../MyApplications/Inc/static_queue.h"


/* �������� */
Bluetooth_data rec;
static_queue bluetooth_queue;


/* �ⲿ�������� */
extern UART_HandleTypeDef *BluetoothUart;


void Bluetooth_read(void);


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == BluetoothUart) {
        Bluetooth_read();
    }
}

uint8_t getCheckSum(uint8_t *buf, uint16_t size)
{
    uint16_t sum = 0x00;
    for(uint16_t i = 0; i < size; i++) {
        sum += buf[i];
    }
    return (uint8_t)sum;
}

void Bluetooth_read(void)
{
    if(rec.buff[BLUETOOTH_DATA_LEN-2] 
        == getCheckSum(&rec.buff[1], BLUETOOTH_DATA_LEN-3)) {
        QueueEn(&bluetooth_queue,&rec);
        Bluetooth_receiveData();
    }
}

void Bluetooth_receiveData(void)
{
    HAL_UART_Receive_IT(BluetoothUart, rec.buff, BLUETOOTH_DATA_LEN);
}

void Bluetooth_analysisRecData(void (*Car_function)(void))
{
    if(!QueueIsEmpty(&bluetooth_queue)) {
        Bluetooth_data received;
        QueueDe(&bluetooth_queue, &received);
        Car.h_dir = received.buff[1];
        Car.v_dir = received.buff[2];
        Car.speed = (received.buff[4]<<8) | received.buff[3];
        Car_function();
    }
}

void Bluetooth_init(void)
{
    bluetooth_queue.front = 0;
    bluetooth_queue.rear = 0;
}


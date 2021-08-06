/**
  ******************************************************************************
  * @file    bluetooth.h
  * @brief   ¿∂—¿”¶”√≥Ã–Ú
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "main.h"

#define BLUETOOTH_DATA_LEN  7

typedef struct {
    uint8_t buff[BLUETOOTH_DATA_LEN];
}Bluetooth_data;

extern void Bluetooth_init(void);
extern void Bluetooth_receiveData(void);
extern void Bluetooth_analysisRecData(void (*Car_function)(void));

#endif

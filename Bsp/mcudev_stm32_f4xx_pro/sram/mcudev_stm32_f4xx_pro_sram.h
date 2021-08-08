#ifndef MCUDEV_STM32_F4XX_PRO_SRAM_H
#define MCUDEV_STM32_F4XX_PRO_SRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define SRAM_OK         0x00
#define SRAM_ERROR      0x01

#define SRAM_DEVICE_ADDR  ((uint32_t)0x68000000)
#define SRAM_DEVICE_SIZE  ((uint32_t)0x100000)  /* SRAM device size in Bytes */  

uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);

#ifdef __cplusplus
}
#endif

#endif

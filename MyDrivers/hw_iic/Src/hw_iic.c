/*
 * hw_iic.c
 *
 *  Created on: Aug 2, 2021
 *      Author: huang
 */

/**************************** I2C Routines ************************************/
#include "hw_iic/Inc/hw_iic.h"


#define I2C_TIMEOUT  1000 /*<! Value of Timeout when I2C communication fails */


extern I2C_HandleTypeDef *I2C_Handle;

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the IOE comunication BUS */
  //HAL_I2C_DeInit(I2C_Handle);

  /* Re-Initiaize the IOE comunication BUS */
  //I2Cx_Init();
  HAL_I2C_MspInit(I2C_Handle);
  HAL_I2C_Init(I2C_Handle);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Data to be read
  */
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;

  status = HAL_I2C_Mem_Read(I2C_Handle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2C_TIMEOUT);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }

  return Value;
}

/**
  * @brief  Reads a multi data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @status Data to be read
  */
static uint8_t I2Cx_multiRead(uint8_t Addr, uint8_t Reg, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(I2C_Handle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Size, I2C_TIMEOUT);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }

  return status;
}


/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(I2C_Handle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2C_TIMEOUT);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occured */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress Internal memory address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
//static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
//{
//  HAL_StatusTypeDef status = HAL_OK;
//
//  status = HAL_I2C_Mem_Read(I2C_Handle, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, I2C_TIMEOUT);
//
//  /* Check the communication status */
//  if(status != HAL_OK)
//  {
//    /* I2C error occured */
//    I2Cx_Error(Addr);
//  }
//  return status;
//  }

/**
  * @brief  Write a value in a register of the device through BUS in using DMA mode
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  MemAddress Internal memory address
  * @param  Buffer: The target register value to be written
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
//static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
//{
//  HAL_StatusTypeDef status = HAL_OK;
//
//  status = HAL_I2C_Mem_Write(I2C_Handle, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, I2C_TIMEOUT);
//
//  /* Check the communication status */
//  if(status != HAL_OK)
//  {
//    /* Re-Initiaize the I2C Bus */
//    I2Cx_Error(Addr);
//  }
//  return status;
//}

/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
  * @retval HAL status
  */
//static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
//{
//  return (HAL_I2C_IsDeviceReady(I2C_Handle, DevAddress, Trials, I2C_TIMEOUT));
//}


/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/
/***************************** LINK CAMERA ************************************/

/**
  * @brief  Initializes Camera low level.
  */
void CAMERA_IO_Init(void)
{
  //I2Cx_Init();
}

/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  */
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Read data
  */
uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Camera delay.
  * @param  Delay: Delay in ms
  */
void CAMERA_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/
/***************************** LINK TOUCH PAD ************************************/
/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  */
void TOUCH_PAD_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Read data
  */
uint8_t TOUCH_PAD_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Read data
  */
uint8_t TOUCH_PAD_IO_multiRead(uint8_t Addr, uint8_t Reg, uint8_t *pData, uint16_t Size)
{
  return I2Cx_multiRead(Addr, Reg, pData, Size);
}

/**
  * @brief  Camera delay.
  * @param  Delay: Delay in ms
  */
void TOUCH_PAD_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}


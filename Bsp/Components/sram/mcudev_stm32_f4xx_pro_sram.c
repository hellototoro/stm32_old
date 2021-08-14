#include "Components/sram/mcudev_stm32_f4xx_pro_sram.h"

/**
  * @brief  Reads an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress : Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory   
  * @retval SRAM status
  */
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{ 
  if(HAL_SRAM_Read_16b(SRAM_Handle, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Reads an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress : Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory   
  * @retval SRAM status
  */
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  if(HAL_SRAM_Read_DMA(SRAM_Handle, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Writes an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory   
  * @retval SRAM status
  */
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) 
{ 
  if(HAL_SRAM_Write_16b(SRAM_Handle, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  }
}

/**
  * @brief  Writes an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory   
  * @retval SRAM status
  */
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) 
{
  if(HAL_SRAM_Write_DMA(SRAM_Handle, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    return SRAM_ERROR;
  }
  else
  {
    return SRAM_OK;
  } 
}

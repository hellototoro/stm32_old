#include "Components/common/board.h"

/*************************************************
 *               FSMC
 * **********************************************/
typedef struct
{
  __IO uint16_t REG;
  __IO uint16_t RAM;
}LCD_CONTROLLER_TypeDef;

#define FMC_BANK1NORSRAM4_BASE  (0x6C000000UL + 0x0000007EUL)
#define FMC_BANK1NORSRAM4       ((LCD_CONTROLLER_TypeDef *) FMC_BANK1NORSRAM4_BASE)

/**
  * @brief  Writes register value.
  */
static void FSMC_BANK1NORSRAM4_WriteData(uint16_t Data)
{
  /* Write 16-bit Data */
  FMC_BANK1NORSRAM4->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: 
  * @retval None
  */
static void FSMC_BANK1NORSRAM4_WriteReg(uint16_t Reg)
{
  /* Write 16-bit Index, then Write Reg */
  FMC_BANK1NORSRAM4->REG = Reg;
}

/**
  * @brief  Reads register value.
  * @retval Read value
  */
static uint16_t FSMC_BANK1NORSRAM4_ReadData(uint16_t Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  FMC_BANK1NORSRAM4->REG = Reg;
  /* Read 16-bit Reg */
  return (FMC_BANK1NORSRAM4->RAM);
}

/**
  * @brief  Reads ram value.
  * @retval Read value
  */
static uint16_t FSMC_BANK1NORSRAM4_ReadRamData(void)
{
  /* Read 16-bit ram */
  return (FMC_BANK1NORSRAM4->RAM);
}

/**
  * @brief  Writes data on LCD data register.
  * @param  RegValue: Data to be written
  * @retval None
  */
void LCD_IO_WriteData(uint16_t DataValue)
{
    FSMC_BANK1NORSRAM4_WriteData(DataValue);
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

/**
  * @brief  Reads data from LCD ram.
  * @param  Reg: Register to be read
  * @retval Read data.
  */
uint16_t LCD_IO_ReadRamData(void)
{
  /* Read 16-bit Reg */
  return (FSMC_BANK1NORSRAM4_ReadRamData());
}

/**
  * @brief  Write register value.
  * @param  pData Pointer on the register value
  * @param  Size Size of byte to transmit to the register
  */
void LCD_IO_WriteMultipleData(__IO uint16_t *pData, uint32_t Size)
{
    for (uint32_t counter = 0; counter < Size; counter++)
    {
        FSMC_BANK1NORSRAM4_WriteData(pData[counter]);
    }
}

void LCD_Delay(uint32_t delay)
{
    HAL_Delay(delay);
}

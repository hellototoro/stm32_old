/**
  ******************************************************************************
  * @file    print.c
  * @brief   TFT LCD����������Ҫʹ��CubeMX����FSMC��
  *          ��ʼ������
	* @data    2021-7-27
	* @author  jee
  ******************************************************************************
  */
#include "print/Inc/print.h"
#include "main.h"


extern UART_HandleTypeDef *UartHandle;

//#define KEIL_USE_MICROLIB
#define IS_CUBEIDE
#if defined(KEIL_USE_MICROLIB)||defined(IS_CUBEIDE)
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
#else
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
    HAL_UART_Transmit(UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
#endif

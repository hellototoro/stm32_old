/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef TIM_HandleTypeDef PWM_HandleTypeDef;
typedef TIM_HandleTypeDef Encoder_HandleTypeDef;
typedef enum {
    OFF = 0,
    ON
}bool_switch;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define right_front_motor_A_Pin GPIO_PIN_6
#define right_front_motor_A_GPIO_Port GPIOF
#define right_front_motor_B_Pin GPIO_PIN_7
#define right_front_motor_B_GPIO_Port GPIOF
#define DCMI_CH1_Pin GPIO_PIN_8
#define DCMI_CH1_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define left_front_motor_A_Pin GPIO_PIN_0
#define left_front_motor_A_GPIO_Port GPIOC
#define left_front_motor_B_Pin GPIO_PIN_1
#define left_front_motor_B_GPIO_Port GPIOC
#define right_back_motor_encoderA_Pin GPIO_PIN_0
#define right_back_motor_encoderA_GPIO_Port GPIOA
#define right_back_motor_encoderB_Pin GPIO_PIN_1
#define right_back_motor_encoderB_GPIO_Port GPIOA
#define left_front_motor_pwm_Pin GPIO_PIN_2
#define left_front_motor_pwm_GPIO_Port GPIOA
#define right_front_motor_pwm_Pin GPIO_PIN_3
#define right_front_motor_pwm_GPIO_Port GPIOA
#define left_back_motor_A_Pin GPIO_PIN_4
#define left_back_motor_A_GPIO_Port GPIOC
#define left_back_motor_B_Pin GPIO_PIN_5
#define left_back_motor_B_GPIO_Port GPIOC
#define TOUCH_IRQ_Pin GPIO_PIN_1
#define TOUCH_IRQ_GPIO_Port GPIOB
#define TOUCH_IRQ_EXTI_IRQn EXTI1_IRQn
#define LCD_TE_SIGNAL_Pin GPIO_PIN_15
#define LCD_TE_SIGNAL_GPIO_Port GPIOB
#define LCD_TE_SIGNAL_EXTI_IRQn EXTI15_10_IRQn
#define left_back_motor_encoderA_Pin GPIO_PIN_8
#define left_back_motor_encoderA_GPIO_Port GPIOA
#define left_back_motor_encoderB_Pin GPIO_PIN_9
#define left_back_motor_encoderB_GPIO_Port GPIOA
#define DCMI_SCL_Pin GPIO_PIN_6
#define DCMI_SCL_GPIO_Port GPIOD
#define DCMI_SDA_Pin GPIO_PIN_7
#define DCMI_SDA_GPIO_Port GPIOD
#define right_back_motor_A_Pin GPIO_PIN_13
#define right_back_motor_A_GPIO_Port GPIOG
#define right_back_motor_B_Pin GPIO_PIN_14
#define right_back_motor_B_GPIO_Port GPIOG
#define DCMI_RESET_Pin GPIO_PIN_15
#define DCMI_RESET_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */
extern PWM_HandleTypeDef *left_front_motor_pwm;
extern PWM_HandleTypeDef *right_front_motor_pwm;
extern PWM_HandleTypeDef *left_back_motor_pwm;
extern PWM_HandleTypeDef *right_back_motor_pwm;
extern DCMI_HandleTypeDef *DCMI_Handle;
extern SRAM_HandleTypeDef *SRAM_Handle;
extern DMA_HandleTypeDef *SRAMToLCD_DMA_Handle;
extern RTC_HandleTypeDef *RtcHandle;
extern I2C_HandleTypeDef *I2C_Handle;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

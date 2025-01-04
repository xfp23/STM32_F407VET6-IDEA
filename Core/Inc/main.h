/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stdint.h"
#include "encoder.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
typedef struct {
	uint8_t system_1ms :1;
	uint8_t system_10ms :1;
	uint8_t system_100ms :1;
	uint8_t system_500ms :1;
	uint8_t Reverve_bit :4;
}System_Tim_Flag;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define ON (1)
#define OFF (0)
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_KEY_Pin GPIO_PIN_0
#define USER_KEY_GPIO_Port GPIOA
#define USER_KEY_EXTI_IRQn EXTI0_IRQn
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define USER_LED_Pin GPIO_PIN_2
#define USER_LED_GPIO_Port GPIOB
#define ENCODE_A_Pin GPIO_PIN_10
#define ENCODE_A_GPIO_Port GPIOB
#define ENCODE_A_EXTI_IRQn EXTI15_10_IRQn
#define ENCODE_B_Pin GPIO_PIN_11
#define ENCODE_B_GPIO_Port GPIOB
#define ENCODE_B_EXTI_IRQn EXTI15_10_IRQn
#define SD_CARD_DET_Pin GPIO_PIN_3
#define SD_CARD_DET_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
extern System_Tim_Flag systemTim;
extern void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
extern volatile Encoder_Class_t encoder;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

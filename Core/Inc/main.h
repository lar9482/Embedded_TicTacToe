/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Red_21_Pin GPIO_PIN_0
#define Red_21_GPIO_Port GPIOC
#define Red_13_Pin GPIO_PIN_1
#define Red_13_GPIO_Port GPIOC
#define Red_12_Pin GPIO_PIN_2
#define Red_12_GPIO_Port GPIOC
#define Red_11_Pin GPIO_PIN_3
#define Red_11_GPIO_Port GPIOC
#define Green_13_Pin GPIO_PIN_5
#define Green_13_GPIO_Port GPIOA
#define Green_21_Pin GPIO_PIN_6
#define Green_21_GPIO_Port GPIOA
#define Green_22_Pin GPIO_PIN_7
#define Green_22_GPIO_Port GPIOA
#define ROW_0_Pin GPIO_PIN_5
#define ROW_0_GPIO_Port GPIOC
#define ROW_0_EXTI_IRQn EXTI9_5_IRQn
#define Green_33_Pin GPIO_PIN_0
#define Green_33_GPIO_Port GPIOB
#define COL_1_Pin GPIO_PIN_1
#define COL_1_GPIO_Port GPIOB
#define COL_0_Pin GPIO_PIN_2
#define COL_0_GPIO_Port GPIOB
#define COL_3_Pin GPIO_PIN_14
#define COL_3_GPIO_Port GPIOB
#define COL_2_Pin GPIO_PIN_15
#define COL_2_GPIO_Port GPIOB
#define ROW_1_Pin GPIO_PIN_6
#define ROW_1_GPIO_Port GPIOC
#define ROW_1_EXTI_IRQn EXTI9_5_IRQn
#define Green_31_Pin GPIO_PIN_7
#define Green_31_GPIO_Port GPIOC
#define ROW_2_Pin GPIO_PIN_8
#define ROW_2_GPIO_Port GPIOC
#define ROW_2_EXTI_IRQn EXTI9_5_IRQn
#define ROW_3_Pin GPIO_PIN_9
#define ROW_3_GPIO_Port GPIOC
#define ROW_3_EXTI_IRQn EXTI9_5_IRQn
#define Green_23_Pin GPIO_PIN_8
#define Green_23_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define Red_22_Pin GPIO_PIN_15
#define Red_22_GPIO_Port GPIOA
#define Red_31_Pin GPIO_PIN_10
#define Red_31_GPIO_Port GPIOC
#define Red_32_Pin GPIO_PIN_11
#define Red_32_GPIO_Port GPIOC
#define Red_23_Pin GPIO_PIN_12
#define Red_23_GPIO_Port GPIOC
#define Red_33_Pin GPIO_PIN_2
#define Red_33_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define Green_12_Pin GPIO_PIN_4
#define Green_12_GPIO_Port GPIOB
#define Green_11_Pin GPIO_PIN_5
#define Green_11_GPIO_Port GPIOB
#define Green_32_Pin GPIO_PIN_6
#define Green_32_GPIO_Port GPIOB
#define Green_31B7_Pin GPIO_PIN_7
#define Green_31B7_GPIO_Port GPIOB
#define Green_23B8_Pin GPIO_PIN_8
#define Green_23B8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

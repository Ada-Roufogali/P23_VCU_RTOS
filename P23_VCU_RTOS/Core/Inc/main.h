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
#include "stm32h7xx_hal.h"

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
#define SD_COIL_Pin GPIO_PIN_3
#define SD_COIL_GPIO_Port GPIOE
#define IMD_Pin GPIO_PIN_5
#define IMD_GPIO_Port GPIOE
#define AIRM_Pin GPIO_PIN_13
#define AIRM_GPIO_Port GPIOC
#define AMS_Pin GPIO_PIN_0
#define AMS_GPIO_Port GPIOF
#define AIRP_Pin GPIO_PIN_2
#define AIRP_GPIO_Port GPIOF
#define ASB_Pin GPIO_PIN_4
#define ASB_GPIO_Port GPIOF
#define BRF_Pin GPIO_PIN_7
#define BRF_GPIO_Port GPIOF
#define ANALOG4_Pin GPIO_PIN_1
#define ANALOG4_GPIO_Port GPIOC
#define BRR_Pin GPIO_PIN_2
#define BRR_GPIO_Port GPIOC
#define APPS1_Pin GPIO_PIN_1
#define APPS1_GPIO_Port GPIOA
#define TS_OFF_Pin GPIO_PIN_2
#define TS_OFF_GPIO_Port GPIOA
#define APPS2_Pin GPIO_PIN_5
#define APPS2_GPIO_Port GPIOA
#define STEERING_Pin GPIO_PIN_4
#define STEERING_GPIO_Port GPIOC
#define HRR_Pin GPIO_PIN_1
#define HRR_GPIO_Port GPIOB
#define HFR_Pin GPIO_PIN_14
#define HFR_GPIO_Port GPIOF
#define HFL_Pin GPIO_PIN_9
#define HFL_GPIO_Port GPIOE
#define HRL_Pin GPIO_PIN_13
#define HRL_GPIO_Port GPIOE
#define SIGNAL1_Pin GPIO_PIN_10
#define SIGNAL1_GPIO_Port GPIOB
#define PRIMARY_RX_Pin GPIO_PIN_12
#define PRIMARY_RX_GPIO_Port GPIOB
#define PRIMARY_TX_Pin GPIO_PIN_13
#define PRIMARY_TX_GPIO_Port GPIOB
#define BSPD_Pin GPIO_PIN_15
#define BSPD_GPIO_Port GPIOB
#define MCU2_Pin GPIO_PIN_9
#define MCU2_GPIO_Port GPIOD
#define SIGNAL2_Pin GPIO_PIN_3
#define SIGNAL2_GPIO_Port GPIOG
#define SIGNAL3_Pin GPIO_PIN_5
#define SIGNAL3_GPIO_Port GPIOG
#define SIGNAL4_Pin GPIO_PIN_7
#define SIGNAL4_GPIO_Port GPIOG
#define MCU1_Pin GPIO_PIN_8
#define MCU1_GPIO_Port GPIOA
#define MOTOR_RX_Pin GPIO_PIN_11
#define MOTOR_RX_GPIO_Port GPIOA
#define MOTOR_TX_Pin GPIO_PIN_12
#define MOTOR_TX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define AUTO_Pin GPIO_PIN_2
#define AUTO_GPIO_Port GPIOD
#define MOTOR_Pin GPIO_PIN_4
#define MOTOR_GPIO_Port GPIOD
#define DETECTION_Pin GPIO_PIN_5
#define DETECTION_GPIO_Port GPIOB
#define PRIMARY_Pin GPIO_PIN_6
#define PRIMARY_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

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
#include "stm32f0xx_hal.h"

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
#define Channel1Current_Pin GPIO_PIN_0
#define Channel1Current_GPIO_Port GPIOA
#define Channel2Current_Pin GPIO_PIN_1
#define Channel2Current_GPIO_Port GPIOA
#define HighVoltageShort_Pin GPIO_PIN_2
#define HighVoltageShort_GPIO_Port GPIOA
#define HighVoltage_Pin GPIO_PIN_3
#define HighVoltage_GPIO_Port GPIOA
#define ConverterPWM_Pin GPIO_PIN_4
#define ConverterPWM_GPIO_Port GPIOA
#define Channel2_Pin GPIO_PIN_6
#define Channel2_GPIO_Port GPIOA
#define BatteryVoltage_Pin GPIO_PIN_7
#define BatteryVoltage_GPIO_Port GPIOA
#define ChargingIndicator_Pin GPIO_PIN_0
#define ChargingIndicator_GPIO_Port GPIOB
#define ChargerCurrent_Pin GPIO_PIN_1
#define ChargerCurrent_GPIO_Port GPIOB
#define Channel1_Pin GPIO_PIN_8
#define Channel1_GPIO_Port GPIOA
#define TestLED_Pin GPIO_PIN_15
#define TestLED_GPIO_Port GPIOA
#define Button1_Pin GPIO_PIN_3
#define Button1_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_4
#define Button2_GPIO_Port GPIOB
#define Button3_Pin GPIO_PIN_5
#define Button3_GPIO_Port GPIOB
#define Button4_Pin GPIO_PIN_6
#define Button4_GPIO_Port GPIOB
#define Button5_Pin GPIO_PIN_7
#define Button5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "shared_variables.h"

#define F_CLK1 275000000UL
#define F_CLK2 275000000UL /* FOR TIM 1 */
#define prescaler1 8
#define prescaler2 12 /* FOR TIM 1 */

/* TIM 1 (CH3) -> HRL | TIM 1 (CH1) -> HFL | TIM 3 (CH4) -> HRR | TIM 24 (CH4) -> HFR */
volatile uint8_t hrr_state,hfr_state,hrl_state,hfl_state;
volatile uint16_t TIM1_OVC1,TIM1_OVC3,TIM3_OVC,TIM24_OVC;
volatile uint32_t TIM1_VAL1_1,TIM1_VAL1_2,TIM1_VAL2_1,TIM1_VAL2_2,TIM3_VAL1,TIM3_VAL2,TIM24_VAL1,TIM24_VAL2,TIM1_TICKS1,
TIM1_TICKS3,TIM3_TICKS,TIM24_TICKS,
TIM1_CLK,TIM3_CLK,TIM24_CLK,TIM1_FREQ1,TIM1_FREQ3,TIM3_FREQ,TIM24_FREQ,last_measurement;
uint16_t rpm_fl,rpm_fr,rpm_rl,rpm_rr;
volatile uint8_t rpm_c;
volatile uint32_t rpm_rr_test[2];
/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim24;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICFilter = 3;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 8-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 3;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}
/* TIM24 init function */
void MX_TIM24_Init(void)
{

  /* USER CODE BEGIN TIM24_Init 0 */

  /* USER CODE END TIM24_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM24_Init 1 */

  /* USER CODE END TIM24_Init 1 */
  htim24.Instance = TIM24;
  htim24.Init.Prescaler = 8-1;
  htim24.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim24.Init.Period = 65535;
  htim24.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim24.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_IC_Init(&htim24) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim24, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 3;
  if (HAL_TIM_IC_ConfigChannel(&htim24, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM24_Init 2 */

  /* USER CODE END TIM24_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PE9     ------> TIM1_CH1
    PE13     ------> TIM1_CH3
    */
    GPIO_InitStruct.Pin = HFL_Pin|HRL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PB1     ------> TIM3_CH4
    */
    GPIO_InitStruct.Pin = HRR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(HRR_GPIO_Port, &GPIO_InitStruct);

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* tim_icHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_icHandle->Instance==TIM24)
  {
  /* USER CODE BEGIN TIM24_MspInit 0 */

  /* USER CODE END TIM24_MspInit 0 */
    /* TIM24 clock enable */
    __HAL_RCC_TIM24_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**TIM24 GPIO Configuration
    PF14     ------> TIM24_CH4
    */
    GPIO_InitStruct.Pin = HFR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_TIM24;
    HAL_GPIO_Init(HFR_GPIO_Port, &GPIO_InitStruct);

    /* TIM24 interrupt Init */
    HAL_NVIC_SetPriority(TIM24_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM24_IRQn);
  /* USER CODE BEGIN TIM24_MspInit 1 */

  /* USER CODE END TIM24_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /**TIM1 GPIO Configuration
    PE9     ------> TIM1_CH1
    PE13     ------> TIM1_CH3
    */
    HAL_GPIO_DeInit(GPIOE, HFL_Pin|HRL_Pin);

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /**TIM3 GPIO Configuration
    PB1     ------> TIM3_CH4
    */
    HAL_GPIO_DeInit(HRR_GPIO_Port, HRR_Pin);

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* tim_icHandle)
{

  if(tim_icHandle->Instance==TIM24)
  {
  /* USER CODE BEGIN TIM24_MspDeInit 0 */

  /* USER CODE END TIM24_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM24_CLK_DISABLE();

    /**TIM24 GPIO Configuration
    PF14     ------> TIM24_CH4
    */
    HAL_GPIO_DeInit(HFR_GPIO_Port, HFR_Pin);

    /* TIM24 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM24_IRQn);
  /* USER CODE BEGIN TIM24_MspDeInit 1 */

  /* USER CODE END TIM24_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim){
	last_measurement = xTaskGetTickCount();
	if(htim == &htim1){
		if(htim1.Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			if(hfl_state == 0){
				TIM1_VAL1_1 = TIM1->CCR1;
				TIM1_OVC1 = 0;
				hfl_state = 1;
			}
			else{
				/* Maybe assign this section to a thread. Careful of priorities! */
				TIM1_VAL1_2 = TIM1->CCR1;
				TIM1_TICKS1 = TIM1_VAL1_2 + (TIM1_OVC1*65535) - TIM1_VAL1_1;
				TIM1_FREQ1 = TIM1_CLK / TIM1_TICKS1;
				TIM1_FREQ1 = TIM1_FREQ1*60.0/8;
				rpm_fl = TIM1_FREQ1;
				hfl_state = 0;
			}
		}
		else if(htim1.Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			if(hrl_state == 0){
				TIM1_VAL2_1 = TIM1->CCR3;
				TIM1_OVC3 = 0;
				hrl_state = 1;
			}
			else{
				/* Maybe assign this section to a thread. Careful of priorities! */
				TIM1_VAL2_2 = TIM1->CCR3;
				TIM1_TICKS3 = TIM1_VAL2_2 + (TIM1_OVC3*65535) - TIM1_VAL2_1;
				TIM1_FREQ3 = TIM1_CLK / TIM1_TICKS3;
				TIM1_FREQ3 = TIM1_FREQ3*60.0/8;
				rpm_rl = TIM1_FREQ3;
				hrl_state = 0;
			}
		}
	}
	if(htim == &htim3){
		if(hrr_state == 0){
			TIM3_VAL1 = TIM3->CCR4;
			TIM3_OVC = 0;
			hrr_state = 1;
		}
		else{
			TIM3_VAL2 = TIM3->CCR4;
			TIM3_TICKS = TIM3_VAL2 + (TIM3_OVC*65535) - TIM3_VAL1;
			TIM3_FREQ = TIM3_CLK / TIM3_TICKS;
			TIM3_FREQ = TIM3_FREQ*60.0/8;
			rpm_rr = TIM3_FREQ;

			/* Used when testing the spacers! */
//			rpm_rr_test[0] += rpm_rr;
//			rpm_c++;
//			if(rpm_c ==0){
//				rpm_rr_test[1]=rpm_rr_test[0]/256;
//				rpm_rr_test[0]=0;
//			}
			hrr_state = 0;
		}
	}
	if(htim == &htim24){
		if(hfr_state == 0){
			TIM24_VAL1 = TIM24->CCR4;
			TIM24_OVC = 0;
			hfr_state = 1;
		}
		else{
			TIM24_VAL2 = TIM24->CCR4;
			TIM24_TICKS = TIM24_VAL2 + (TIM24_OVC*65535) - TIM24_VAL1;
			TIM24_FREQ = TIM24_CLK / TIM24_TICKS;
			TIM24_FREQ = TIM24_FREQ*60.0/8;
			rpm_fr = TIM24_FREQ;
			hfr_state = 0;
		}
	}
}

void HardwareTimersStart(){
	TIM1_CLK = F_CLK1/prescaler1;
	TIM3_CLK = F_CLK1/prescaler1;
	TIM24_CLK = F_CLK2/prescaler2;

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim24);
	HAL_TIM_IC_Start_IT(&htim24, TIM_CHANNEL_4);

}
/* USER CODE END 1 */

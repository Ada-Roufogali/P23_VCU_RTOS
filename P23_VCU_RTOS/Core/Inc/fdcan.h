/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.h
  * @brief   This file contains all the function prototypes for
  *          the fdcan.c file
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
#ifndef __FDCAN_H__
#define __FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_HandleTypeDef hfdcan2;

extern FDCAN_HandleTypeDef hfdcan3;

/* USER CODE BEGIN Private defines */

/* PC STATUS */
typedef enum{
	DV_READY_MSG = 0x02,
	MISSION_FINISHED_MSG = 0x08,
	PC_ERROR_MSG = 0x0F
}PC_STATUS_Struct_t;

/* MISSIONS */
typedef enum{
	ACCEL      = 1,
	SKIDPAD    = 2,
	AUTOX      = 4,
	TRACKDRIVE = 8,
	EBS_TEST   = 16,
	INSPECTION = 32,
	MANUAL     = 64
}EventStruct_t;

/* AS STATUS MESSAGE */
typedef enum{
	AS_OFF_MSG       = 1,
	AS_READY_MSG     = 2,
	AS_DRIVING_MSG   = 4,
	AS_FINISHED_MSG  = 8,
	AS_EMERGENCY_MSG = 16,
}ASStatusMSG_t;

/* AS STATUS DECISION */
typedef enum{
	AS_OFF       = 61,
	AS_READY     = 378,
	AS_DRIVING   = 250,
	AS_FINISHED  = 769,
	AS_EMERGENCY
}ASStatus_t;

typedef enum{
	/* Motor FDCAN */

	/* Primary FDCAN */
	PRIMARY_FROM_DASH_1 = 0x309,
	PRIMARY_FROM_DASH_2 = 0x313,
	PRIMARY_FROM_ASB_1  = 0x310,
	PRIMARY_FROM_ACCU   = 0x301,

	PRIMARY_TO_TELEM_1  = 0x305,
	PRIMARY_TO_TELEM_2  = 0x306,
	PRIMARY_TO_TELEM_3  = 0x181,
	PRIMARY_TO_DASH_1   = 0x307,
	PRIMARY_TO_DASH_2   = 0x308,

	/* Autonomous FDCAN */
	AUTONOMOUS_FROM_PC_1   = 0x302,
	AUTONOMOUS_FROM_PC_2   = 0x275,
	AUTONOMOUS_FROM_DASH_1 = 0x304,
	AUTONOMOUS_FROM_ASB_1  = 0x305,
	AUTONOMOUS_FROM_ASB_2  = 0x303,
	AUTONOMOUS_FROM_RES    = 0x191,

	AUTONOMOUS_AS_STATUS   = 0x306,
	AUTONOMOUS_TO_ASB_1    = 0x280,
	AUTONOMOUS_TO_DASH_1   = 0x281,
	AUTONOMOUS_TO_PC_1     = 0x301,
	AUTONOMOUS_TO_PC_2     = 0x300,
	AUTONOMOUS_TO_RES      = 0x00
}FDCAN_IDs_t;

typedef struct Missions{
	EventStruct_t event;
	uint8_t autonomous,manual,locked;
}MissionStruct;

/* FDCAN1 - MOTOR */
typedef struct Motor{
	FDCAN_FilterTypeDef Filter;
	FDCAN_TxHeaderTypeDef TxHeader;
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t TxData[8], RxData[8];
}MotorStruct;

/* FDCAN2 - PRIMARY */
typedef struct Primary{
	FDCAN_FilterTypeDef Filter;
	FDCAN_TxHeaderTypeDef TxHeader;
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t TxData[8], RxData[8];
}PrimaryStruct;

/* FDCAN3 - AUTO */
typedef struct Auto{
	FDCAN_FilterTypeDef Filter;
	FDCAN_TxHeaderTypeDef TxHeader;
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t TxData[8], RxData[8];
}AutoStruct;

/* SEND ONCE VARIABLES */
typedef struct SendOnce{
	FDCAN_HandleTypeDef hfdcan;
	FDCAN_TxHeaderTypeDef TxHeader;
	uint8_t TxData[8];
}SendOnceStruct;
/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);
void MX_FDCAN2_Init(void);
void MX_FDCAN3_Init(void);

/* USER CODE BEGIN Prototypes */
void FDCAN_Start();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */


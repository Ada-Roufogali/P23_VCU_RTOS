/*
 * Autonomous_Software.c
 *
 *  Created on: Apr 29, 2023
 *      Author: adaro
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "shared_variables.h"

uint32_t initial_check_value;
uint32_t Fake_Status,Fake_EBS;
uint8_t cnt;
uint8_t as_ready_delay;

ASStatus_t AS_STATUS = AS_OFF;

void Initial_Check_Task(void *argument){
	uint8_t flag = 0;

	while(1){
		xTaskNotifyWait(0,ULONG_MAX,&initial_check_value,500);
		if(initial_check_value == 1){
			flag = 0;
			cnt  = 0;
			SendOnceMSG.hfdcan = hfdcan3;
			SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_TO_ASB_1;
			SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
			SendOnceMSG.TxData[0] = 0x01;
			xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
		}
		else if(initial_check_value == 2 && cnt < 10){
			flag = 0;
			cnt += 1;
		}
		else if(initial_check_value == 2 && cnt == 10){
			flag = 0;
			cnt  = 0;
			SendOnceMSG.hfdcan = hfdcan3;
			SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_TO_ASB_1;
			SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
			SendOnceMSG.TxData[0] = 0x02;
			xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
		}
		else if(!flag){
			flag = 1;
			cnt  = 0;
			initial_check_previous = 0;
			initial_check_current = 0;
			SendOnceMSG.hfdcan = hfdcan3;
			SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_TO_ASB_1;
			SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
			SendOnceMSG.TxData[0] = 0x02;
			xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
		}
		osDelay(5);
	}
}

void ASB_Heartbeat_Task(void *argument){
	while(1){
		xEventGroupWaitBits(xAS_Status_EventGroup,AUTONOMOUS_MODE,pdFALSE,pdTRUE,portMAX_DELAY);
		xTaskNotifyWait(0,ULONG_MAX,&initial_check_value,200);

		if(initial_check_value == 1){
			SendOnceMSG.hfdcan = hfdcan3;
			SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_TO_ASB_1;
			SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
			SendOnceMSG.TxData[0] = 0x01;
			xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
		}
		osDelay(5);
	}
}

void AS_Status_Task(void *argument){
	while(1){
		AS_Status_EventBits = xEventGroupWaitBits(xAS_Status_EventGroup,AUTONOMOUS_MODE,pdFALSE,pdTRUE,portMAX_DELAY);
		AS_STATUS = (ASStatus_t)AS_Status_EventBits;
		switch(ebs_activated){
		case 0:
			switch(AS_Status_EventBits){
			case AS_OFF:
				as_ready_delay = 0;
				SendOnceMSG.hfdcan = hfdcan3;
				SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
				SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
				SendOnceMSG.TxData[0] = AS_OFF_MSG;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				SendOnceMSG.hfdcan = hfdcan2;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
				break;
			case AS_READY:
				DV_Ready_EventBits = xEventGroupWaitBits(xDV_Ready_EventGroup,DV_READY,pdTRUE,pdTRUE,portMAX_DELAY);
				if(AS_Status_EventBits == 378){
					SendOnceMSG.hfdcan = hfdcan3;
					SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
					SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
					SendOnceMSG.TxData[0] = AS_READY_MSG;
					xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

					SendOnceMSG.hfdcan = hfdcan2;
					xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

					if(!as_ready_delay){
						osDelay(5000);
						as_ready_delay = 1;
					}
				}
				break;
			case AS_DRIVING:
				as_ready_delay = 0;
				SendOnceMSG.hfdcan = hfdcan3;
				SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
				SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
				SendOnceMSG.TxData[0] = AS_DRIVING_MSG;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				SendOnceMSG.hfdcan = hfdcan2;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				xTaskNotify(Enable_Inverter,0,eNoAction);
				xTaskNotify(Autonomous_Torque_Command,0,eNoAction);
				break;
			default:
				as_ready_delay = 0;
				AS_STATUS = AS_OFF;
				SendOnceMSG.hfdcan = hfdcan3;
				SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
				SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
				SendOnceMSG.TxData[0] = AS_OFF_MSG;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				SendOnceMSG.hfdcan = hfdcan2;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
				break;
			}
			break;
		case 3:
			switch(AS_Status_EventBits){
			case AS_FINISHED:
				as_ready_delay = 0;
				SendOnceMSG.hfdcan = hfdcan3;
				SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
				SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
				SendOnceMSG.TxData[0] = AS_FINISHED_MSG;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				SendOnceMSG.hfdcan = hfdcan2;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
				break;
			default:
				as_ready_delay = 0;
				AS_STATUS = AS_EMERGENCY;
				SendOnceMSG.hfdcan = hfdcan3;
				SendOnceMSG.TxHeader.Identifier = AUTONOMOUS_AS_STATUS;
				SendOnceMSG.TxHeader.DataLength = FDCAN_DLC_BYTES_1;
				SendOnceMSG.TxData[0] = AS_EMERGENCY_MSG;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);

				SendOnceMSG.hfdcan = hfdcan2;
				xQueueSendToBack(xSendOnceQueue,&SendOnceMSG,portMAX_DELAY);
				break;
			}
			break;
		default:
			break;
		}
		osDelay(150);
	}
}

/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Admin
 */
#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void) {
	//current_index_task = 0;						// 0->current_index_task
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task (i);
	}
	//Error_code_G= 0;
	//Timer_init();
	//Watchdog_init();
}
void SCH_Update(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		if (SCH_tasks_G[i].pTask) {
			if (SCH_tasks_G[i].Delay <= 0) {
				SCH_tasks_G[i].RunMe ++;			//flag
				if (SCH_tasks_G[i].Period) {	 	// Co lap
					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				}
			}else {									//Delay > 0
				SCH_tasks_G[i].Delay --;
			}
		}
	}
}

unsigned char SCH_Add_Task(void (*pFunction)(),  unsigned int DELAY,  unsigned int PERIOD) {
	unsigned char i = 0;

	//find a gap
	while ((SCH_tasks_G[i].pTask != 0) && (i < SCH_MAX_TASKS)) {
		i++;
	}

	// Not find gap
	if (i == SCH_MAX_TASKS) {
		//Error_code_G=ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[i].pTask = pFunction;
	SCH_tasks_G[i].Delay = DELAY / TICK ;
	SCH_tasks_G[i].Period = PERIOD / TICK ;
	SCH_tasks_G[i].RunMe = 0;

	//SCH_tasks_G[i].TaskID = i; // Luu giu vi tri he thong
	return i;					//Return the position
}

void SCH_Dispatch_Tasks(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		if (SCH_tasks_G[i].RunMe > 0) { 			// nhu kiem tra flag
			(*SCH_tasks_G[i].pTask)(); 				// tro den nhiem vu cu the
			SCH_tasks_G[i].RunMe--;

			// ONE-SHOT
			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete_Task(i);
			}
		}
	}
	 //SCH_Report_Status();// Report system status
	 //SCH_Go_To_Sleep();// The scheduler enters idlemode at this point
}

unsigned char SCH_Delete_Task(uint32_t ID) {
	if(SCH_tasks_G[ID].pTask == 0 || ID >= SCH_MAX_TASKS){
		 //Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK
		return RETURN_ERROR;
	}
	SCH_tasks_G[ID].pTask = 0x0000;
	SCH_tasks_G[ID].Delay = 0;
	SCH_tasks_G[ID].Period = 0;
	SCH_tasks_G[ID].RunMe = 0;
	return RETURN_NORMAL; // return status
}
//void SCH_Go_To_Sleep(void)
//{
//	HAL_SuspendTick();
//	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
//	HAL_ResumeTick();
//}

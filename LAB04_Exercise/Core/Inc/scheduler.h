/*
 * scheduler.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#define TICK 			10
#define RETURN_ERROR 	0
#define RETURN_NORMAL 	1
typedef struct{
	void (*pTask)(void);		//Ko co ham nao thi gan bang NULL
	uint32_t 	Delay;
	uint32_t	Period;			// 0: one-shot task
	uint8_t		RunMe;			// incremented when task is execute
								// flag: run if > 0

	uint32_t	TaskID;			// Hiện thực tác vụ
}sTasks;

#define SCH_MAX_TASKS		40
void SCH_Init(void);

unsigned char  SCH_Add_Task (void (*pFunction)(),
							unsigned int DELAY,
							unsigned int PERIOD);

void SCH_Update(void);			// Như timerrun

void SCH_Dispatch_Tasks(void);	// Kiểm tra 1 flag, gọi trong while(1)

unsigned char SCH_Delete_Task(uint32_t ID);
//void SCH_Go_To_Sleep(void);

#endif /* INC_SCHEDULER_H_ */

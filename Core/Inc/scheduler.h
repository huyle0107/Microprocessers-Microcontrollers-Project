/*
 * scheduler.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdint.h>

#define SCH_MAX_TASKS	40
#define DELAY 10

void SCH_Update(void);

int SCH_Add_Task(void (*funcPointer)(), uint32_t delay, uint32_t period);

void SCH_Delete_Task(uint32_t);

void SCH_Dispatch_Tasks(void);

void SCH_Force_End(void);

#endif /* INC_SCHEDULER_H_ */

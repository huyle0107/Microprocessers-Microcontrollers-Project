/*
 * scheduler.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Admin
 */


#include "scheduler.h"
#include "sched.h"

struct sTask
{
	struct sTask *left, *right;
	void (*funcPointer)();
	uint32_t delay, period, taskID;
	uint8_t run_flag;
}*sTaskList = 0;

char str[100];
uint8_t tracker[SCH_MAX_TASKS], mutex_lock;

void SCH_Find_Position(struct sTask *index)
{
	if(index == sTaskList)
	{
		return;
	}
	struct sTask *iterator = sTaskList;
	//Not yet found position
	uint8_t check = 0;
	while(iterator->delay <= index->delay)
	{
		if(iterator == sTaskList) check += 1;
		if(check == 2) break;
		index->delay -= iterator->delay;
		iterator = iterator->right;
	}

	//Found position
	if(index->delay == 0) index->run_flag = 1;
	index->right = iterator;
	index->left = iterator->left;
	iterator->left->right = index;
	iterator->left = index;

	//Update the immediately after
	if(iterator != sTaskList)
	{
		iterator->delay -= index->delay;
		if(iterator->delay == 0) iterator->run_flag = 1;
	}
}

int SCH_Add_Task(void (*funcPointer)(), uint32_t delay, uint32_t period)
{
	if(!funcPointer)
	{
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "ADD TASK: Function pointer invalid\r\n"), 200);
		return -1;
	}
	uint32_t runnerID = 0;
	while((runnerID < SCH_MAX_TASKS) && (tracker[runnerID]))
	{
		runnerID += 1;
	}
	if(runnerID == SCH_MAX_TASKS)
	{
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "ADD TASK: Scheduler full\r\n"), 200);
		return -1;
	}
	else tracker[runnerID] = 1;
	mutex_lock = 1;

	struct sTask *curTask = (struct sTask*)malloc(sizeof(struct sTask));
	curTask->delay = delay / DELAY;
	curTask->period = period / DELAY;
	curTask->funcPointer = funcPointer;
	curTask->taskID = runnerID;
	curTask->run_flag = 0;

	if(sTaskList)
	{
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "ADD TASK: Added %lu\r\n", curTask->taskID), 200);
		SCH_Find_Position(curTask);
	}
	else
	{
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "ADD TASK: Added first %lu\r\n", curTask->taskID), 200);
		curTask->left = curTask;
		curTask->right = curTask;
		sTaskList = curTask;
	}
	mutex_lock = 0;
	return runnerID;
}

void SCH_Update()
{
	if((sTaskList) && (!sTaskList->run_flag) && (!mutex_lock))
	{
		if(sTaskList->delay > 0) sTaskList->delay -= 1;
		if(sTaskList->delay <= 0) sTaskList->run_flag = 1;
	}
	timerRun();
}

void SCH_Dispatch_Tasks()
{
	mutex_lock = 1;
	while((sTaskList) && (sTaskList->run_flag))
	{
		(*sTaskList->funcPointer)();
		if(sTaskList->period == 0)
		{
			struct sTask *toDelete = sTaskList;
			sTaskList = sTaskList->right;
			SCH_Delete_Task(toDelete->taskID);
		}
		else
		{
			struct sTask *toFind = sTaskList;
			sTaskList->right->left = sTaskList->left;
			sTaskList->left->right = sTaskList->right;
			sTaskList = sTaskList->right;
			toFind->run_flag = 0;
			toFind->delay = toFind->period;
			SCH_Find_Position(toFind);
		}
	}
	mutex_lock = 0;

	// Enter low-power mode (Sleep mode). The MCU will wake up on the next interrupt
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Delete_Task(uint32_t index)
{
	if(tracker[index])
	{
		tracker[index] = 0;
		struct sTask *iterator = sTaskList;
		while(iterator->taskID != index)
		{
			iterator = iterator->right;
		}
		iterator->right->left = iterator->left;
		iterator->left->right = iterator->right;
		free(iterator);
	}
}


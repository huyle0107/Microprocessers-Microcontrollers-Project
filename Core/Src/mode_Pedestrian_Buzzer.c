/*
 * Pedestrian_Buzzer.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Admin
 */

#include <mode_Pedestrian_Buzzer.h>

int buzzer_flag = 1;

void resetBuzzer()
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}

void setBuzzer(int number)
{
	int value = 5 - number;

	if (buzzer_flag == 1)
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, value);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
	}

	buzzer_flag = 1 - buzzer_flag;
}

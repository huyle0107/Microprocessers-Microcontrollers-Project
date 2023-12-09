/*
 * Pedestrian.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Admin
 */

#include <mode_Pedestrian.h>

char str[100];

void check_press()
{
	if(is_button_pressed(3) && status < 20)
	{
		setTimer4(20000);
		Pedes_press = 1;
		HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "PEDESTRIAN -- Time: 20\r\n"), 1000);
	}
}
void Pedestrian_behavior()
{
	check_press();
	if (Pedes_press == 1)
	{
		switch (status)
		{
			case RED_GREEN:
				resetBuzzer();
				HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, SET);
				HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, RESET);
				break;

			case RED_YELLOW:
				setBuzzer(counter_led1);
				HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, SET);
				HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, RESET);
				break;

			case GREEN_RED:
				resetBuzzer();
				HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, RESET);
				HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, SET);
				break;

			case YELLOW_RED:
				setBuzzer(counter_led2);
				HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, SET);
				HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, SET);
				break;

			default:
				break;
		}

		if(timer4_flag == 1)
		{
			HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, RESET);
			HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, RESET);
			Pedes_press = 0;
			resetBuzzer();
		}
	}
}


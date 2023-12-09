/*
 * mode_1.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Admin
 */

#include "main.h"
#include "software_timer.h"
#include "global.h"

char str[50];

void SwitchMode2()
{
	HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, RESET);
	HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);
	HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
	HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

	// Turn off the Pedestrian led and Buzzer
	Pedes_press = 0;
	resetBuzzer();
	HAL_GPIO_WritePin(LED_PED_0_GPIO_Port, LED_PED_0_Pin, RESET);
	HAL_GPIO_WritePin(LED_PED_1_GPIO_Port, LED_PED_1_Pin, RESET);

	status = MODE2;

	counter_led1 = 20;
	counter_led2 = 20;

	setTimer1(1000);
	setTimer2(20000);
}

void auto_mode()
{
	switch (status)
	{
		case INIT:
			status = RED_GREEN;

			counter_led1 = 50;
			counter_led2 = 46;

			setTimer1(1000);		//timer 1 to countdown the number display on LED
			setTimer2(47000);		//timer 2 to perform 2 traffic light

			break;

		case RED_GREEN:
			//Write pin for first traffic light:	RED
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, SET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);

			//Write pin for second traffic light:	GREEN
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, SET);

			if (timer1_flag == 1)
			{
				setTimer1(1000);

				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 1: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 2: GREEN\r\nTime:%d\r\n\r\n", counter_led2), 1000);
			}

			if (timer2_flag == 1)
			{
				status = RED_YELLOW;

				counter_led2 = 3;

				setTimer1(1000);
				setTimer2(4000);
			}

			if(is_button_pressed(0)) SwitchMode2();

			//check whether user increases time or not.
			check_button_add_time();

			break;

		case RED_YELLOW:
			//Write pin for first traffic light:	RED
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, SET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);

			//Write pin for second traffic light:	YELLOW
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, SET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, SET);

			if (timer1_flag == 1)
			{
				setTimer1(1000);

				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 1: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 2: YELLOW\r\nTime:%d\r\n\r\n", counter_led2), 1000);
			}

			if (timer2_flag == 1)
			{
				status = GREEN_RED;

				counter_led1 = 46;
				counter_led2 = 50;

				setTimer1(1000);
				setTimer2(47000);
			}

			if(is_button_pressed(0)) SwitchMode2();

			//check whether user increases time or not.
			check_button_add_time();

			break;

		case GREEN_RED:
			//Write pin for first traffic light:	GREEN
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, RESET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, SET);

			//Write pin for second traffic light:	RED
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, SET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

			if (timer1_flag == 1)
			{
				setTimer1(1000);

				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 1: GREEN\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 2: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);
			}

			if (timer2_flag == 1)
			{
				status = YELLOW_RED;

				counter_led1 = 3;

				setTimer1(1000);
				setTimer2(4000);
			}

			if(is_button_pressed(0)) SwitchMode2();

			//check whether user increases time or not.
			check_button_add_time();

			break;

		case YELLOW_RED:
			//Write pin for first traffic light:	YELLOW
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, SET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, SET);

			//Write pin for second traffic light:	RED
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, SET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

			if (timer1_flag == 1)
			{
				setTimer1(1000);

				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 1: YELLOW\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Road 2: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);
			}

			if (timer2_flag == 1)
			{
				status = INIT;
			}

			if(is_button_pressed(0)) SwitchMode2();

			//check whether user increases time or not.
			check_button_add_time();

			break;

		default:
			break;
	}
}


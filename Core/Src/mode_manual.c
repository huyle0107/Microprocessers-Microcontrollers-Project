/*
 * mode_2.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Admin
 */

#include <mode_tuning.h>
#include "main.h"
#include "software_timer.h"
#include "input_reading.h"
#include "global.h"

char str[50];

void manual_mode()
{
	switch (status)
	{
		case MODE2:
			//Write pin for first traffic light:	RED
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, SET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);

			//Write pin for second traffic light:	GREEN
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, SET);

			if(timer1_flag == 1)
			{
				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "MANUAL: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "MANUAL: GREEN\r\nTime:%d\r\n\r\n", counter_led2), 1000);

				setTimer1(1000);
			}

			//Switch to M3 mode
			if(timer2_flag == 1)
			{
				HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, RESET);
				HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);
				HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
				HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

				status = MODE3;

				counter_led1 = 20;
				counter_led2 = 20;

				setTimer1(1000);	//Timer 1 to countdown the number display on 2 Led.
				setTimer2(20000);	//Timer 2 is the quantity of time machine in mode 2 without increasing time.
			}

			// Switch to automatic mode
			if(is_button_pressed(0))
			{
				status = INIT;
			}

			//check whether user increases time or not.
			check_button_add_time();

			break;

		case MODE3:
			//Write pin for first traffic light:	GREEN
			HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, RESET);
			HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, SET);

			//Write pin for second traffic light:	RED
			HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, SET);
			HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

			if(timer1_flag == 1)
			{
				counter_led1--;
				counter_led2--;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "MANUAL: GREEN\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "MANUAL: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);

				setTimer1(1000);
			}

			//Switch to M3 mode
			if(timer2_flag == 1)
			{
				HAL_GPIO_WritePin(LED_00_GPIO_Port, LED_00_Pin, RESET);
				HAL_GPIO_WritePin(LED_01_GPIO_Port, LED_01_Pin, RESET);
				HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, RESET);
				HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, RESET);

				status = MODE2;

				counter_led1 = 20;
				counter_led2 = 20;

				setTimer1(1000);	//Timer 1 to countdown the number display on 2 Led.
				setTimer2(20000);	//Timer 2 is the quantity of time machine in mode 2 without increasing time.
			}

			// Switch to automatic mode
			if(is_button_pressed(0))
			{
				status = INIT;
			}

			//check whether user increases time or not.
			check_button_add_time();

			break;

		default:
			break;

	}
}

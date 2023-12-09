/*
 * add_time_button.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Admin
 */

#include <mode_tuning.h>
#include "input_reading.h"
#include "global.h"
#include "software_timer.h"

char str[50];

void check_button_add_time()
{
	if(is_button_pressed(1) || is_button_pressed_1s(1))
	{
		tunning_led += 100;
	}

	if(is_button_pressed(2))
	{
		adding_time(tunning_led);
		switch (status)
		{
			case RED_GREEN:
				counter_led1 = counter_led1 + (tunning_led / 100);
				counter_led2 = counter_led2 + (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: GREEN\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			case RED_YELLOW:
				counter_led1 = counter_led1 + (tunning_led / 100);
				counter_led2 = counter_led2 + (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: YELLOW\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			case GREEN_RED:
				counter_led1 = counter_led1 + (tunning_led / 100);
				counter_led2 = counter_led2 + (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: GREEN\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			case YELLOW_RED:
				counter_led1 = counter_led1 + (tunning_led / 100);
				counter_led2 = counter_led2 + (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: YELLOW\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			case MODE2:
				counter_led1 = (tunning_led / 100);
				counter_led2 = (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: GREEN\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			case MODE3:
				counter_led1 = (tunning_led / 100);
				counter_led2 = (tunning_led / 100);
				tunning_led = 0;

				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: GREEN\r\nTime:%d\r\n", counter_led1), 1000);
				HAL_UART_Transmit(&huart2,(void*)str,sprintf(str, "Tuning: RED\r\nTime:%d\r\n\r\n", counter_led2), 1000);
				break;

			default:
				break;
		}
	}
}

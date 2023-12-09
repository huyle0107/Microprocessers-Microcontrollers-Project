/*
 * global.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "input_reading.h"
#include "main.h"

#define INIT 			0

// Use for mode 1
#define RED_GREEN		11
#define RED_YELLOW		12
#define GREEN_RED		13
#define YELLOW_RED		14

// Use for mode 2
#define MODE2			20

// Use for mode 3
#define MODE3			30

extern int counter_led1;
extern int counter_led2;
extern int tunning_led;
extern int status;
extern int Pedes_press;

#endif /* INC_GLOBAL_H_ */

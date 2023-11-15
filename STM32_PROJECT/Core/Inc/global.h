/*
 * global.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#include "input_reading.h"
#include "software_timer.h"

#define RED_INIT 5
#define YELLOW_INIT 2
#define GREEN_INIT 3
extern int red_val, green_val, yellow_val;
extern int red_temp, green_temp, yellow_temp;
extern int mode;
extern uint32_t			prescaller;
extern uint32_t			counter;

extern uint32_t			count_inter;
void LedTimeDurationInit();
int getMode();
#endif /* INC_GLOBAL_H_ */

/*
 * global.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */


#include "global.h"

int mode = 1;
int red_val, green_val, yellow_val;
int red_temp, green_temp, yellow_temp;


void LedTimeDurationInit() {
	red_val = RED_INIT;
	green_val = GREEN_INIT;
	yellow_val = YELLOW_INIT;

	red_temp = red_val;
	yellow_temp = green_val;
	green_temp = yellow_val;
}

int getMode() {
	return mode;
}

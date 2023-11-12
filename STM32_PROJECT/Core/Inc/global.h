/*
 * global.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define RED_INIT 10
#define YELLOW_INIT 3
#define GREEN_INIT 7
extern int red_val, green_val, yellow_val;
extern int red_temp, green_temp, yellow_temp;
extern int mode;
void LedTimeDurationInit();
int getMode();
#endif /* INC_GLOBAL_H_ */

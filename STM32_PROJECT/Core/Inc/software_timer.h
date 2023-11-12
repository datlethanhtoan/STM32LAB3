/*
 * software_timer.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;

int get_timer0_flag();
void setTimer0(int duration);
int get_timer1_flag();
void setTimer1(int duration);
int get_timer2_flag();
void setTimer2(int duration);
int get_timer3_flag();
void setTimer3(int duration);

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */








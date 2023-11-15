/*
 * display_led.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */


#include "display_led.h"
#include "global.h"
#include "main.h"
#include "software_timer.h"

void display7SEG(int num)
 {
	switch(num)
	{
		 case 0:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,1);
			break;
		 case 1:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0  |GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5 |GPIO_PIN_6, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2,0);
			 break;
		 case 2:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_6 |GPIO_PIN_3 |GPIO_PIN_4 , 0);
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 |GPIO_PIN_5,1);
			break;
		 case 3:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_6 |GPIO_PIN_3 |GPIO_PIN_2 , 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4 |GPIO_PIN_5,1);
			  break;
		 case 4:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5 |GPIO_PIN_1 |GPIO_PIN_6 |GPIO_PIN_2 , 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_3 |GPIO_PIN_4,1);
			break;
		 case 5:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_5| GPIO_PIN_6, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 |GPIO_PIN_4 ,1);
			break;
		 case 6:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_6 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,1);
			break;
		 case 7:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5 |GPIO_PIN_6, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0  | GPIO_PIN_1 | GPIO_PIN_2,0);
				break;
		 case 8:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5|GPIO_PIN_6, 0);
				break;
		 case 9:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_6 |GPIO_PIN_5, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,1);
			break;
		 default:
			break;
	 }
 }
enum LEDState {RED, YELLOW, GREEN};

int count1 = RED_INIT;
int count2 = GREEN_INIT;


enum LEDState state1 = RED;
enum LEDState state2 = GREEN;

// sau khi thuc hien cac mode 2 3 4 can set lai gia tri dem cho mode 1
void resetCountValue() {
	count1 = red_val;
	count2 = green_val;
	state1 = RED;
	state2 = GREEN;
}

// run mode 1
void Mode_1(){
	count1--;
	count2--;
	switch(state1){
		case RED:
			HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
			HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
			if(count1 < 0)
			{
				count1 = green_val - 1;
				state1 = GREEN;
				HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 0);
			}
			break;
		case YELLOW:
			HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 0);
			HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
			if(count1 < 0)
			{
				count1 = red_val - 1;
				state1 = RED;
				HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 0);
				HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
			}
			break;
		case GREEN:
			HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
			HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 0);
			if(count1 < 0)
			{
				count1 = yellow_val - 1;
				state1 = YELLOW;
				HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 0);
				HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
			}
			break;
		default:
			break;


	}

	switch(state2){
			case RED:
				HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 0);
				HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
				if(count2 < 0)
				{
					count2 = green_val - 1;
					state2 = GREEN;
					HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 0);
				}
				break;
			case YELLOW:
				HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 0);
				HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
				if(count2 < 0)
				{
					count2 = red_val - 1;
					state2 = RED;
					HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 0);
					HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
				}
				break;
			case GREEN:
				HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 0);
				if(count2 <  0)
				{
					count2 = yellow_val - 1;
					state2 = YELLOW;
					HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 0);
					HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
				}
				break;
			default:
				break;


		}
}

// return ve cac gia tri de display 7SEG cho tung mode
static int get7SEGval_1(){
	switch (mode){
		case 1:
			return count1;
		case 2:
			return red_temp;
		case 3:
			return yellow_temp;
		case 4:
			return green_temp;
		default:
			break;
	}
	return 0;
}


static int get7SEGval_2(){
	switch (mode){
		case 1:
			return count2;
		case 2:
			return red_temp;
		case 3:
			return yellow_temp;
		case 4:
			return green_temp;
		default:
			break;
	}
	return 0;
}

// display led giao thong theo tung mode
void LedDisplayMode(){
	switch(mode)
	{
		case 1:
			if(get_timer0_flag())
			{
				setTimer0(count_inter); ///
				Mode_1();

			}
			break;
		case 2:
			if(get_timer0_flag())
			{
				setTimer0((int)(0.5*count_inter));
				HAL_GPIO_TogglePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin);
				HAL_GPIO_TogglePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin);


				HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin,1);
				HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
			}
			break;
		case 3:
			if(get_timer0_flag())
			{
				setTimer0((int)(0.5*count_inter));
				HAL_GPIO_TogglePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin);
				HAL_GPIO_TogglePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin);


				HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
			}
			break;
		case 4:
			if(get_timer0_flag())
			{
				setTimer0((int)(0.5*count_inter));
				HAL_GPIO_TogglePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin);
				HAL_GPIO_TogglePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin);


				HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin,1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
				HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 1);
			}
			break;
		default:
			break;
	}
}

// scanning 7SEG
// neu la mode_1: cac 7SEG  bieu dien thoi gian cho led giao thong
// neu la cac mode con lai: 2 led se bieu dien mode va 2 led se hien thi thoi gian set value
void LedScanning(){
	static int index = 0;
	if(mode == 1)
	{
		switch (index) {
			case 0:
				// value
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);

				//mode
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);

				display7SEG( get7SEGval_1()/10);
				index = 1;
				break;
			case 1:
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);

				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
				display7SEG( get7SEGval_1()%10);
				index = 2;
				break;
			case 2:
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);

				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
				display7SEG(get7SEGval_2() / 10);
				index = 3;
				break;
			case 3:
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);

				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
				display7SEG(get7SEGval_2() % 10);
				index = 0;
				break;
			default:
				break;
		}
	}
	else{
		switch (index) {
					case 0:
						// value
						HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);

						//mode
						HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);

						display7SEG(0);
						index = 1;
						break;
					case 1:
						HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);

						HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
						display7SEG( mode);
						index = 2;
						break;
					case 2:
						HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);

						HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
						display7SEG(get7SEGval_2() / 10);
						index = 3;
						break;
					case 3:
						HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);

						HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
						display7SEG(get7SEGval_2() % 10);
						index = 0;
						break;
					default:
						break;
				}
	}
}








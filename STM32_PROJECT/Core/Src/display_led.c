/*
 * display_led.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Administrator
 */


#include "display_led.h"
#include "global.h"
#include "main.h"


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

void resetCountValue() {
	count1 = red_value;
	count2 = green_value;
	state1 = RED;
	state2 = GREEN;
}

void Mode(){
	count1--;
	count2--;
	switch(state1){
		case RED:
			HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
			HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
			if(count1 <= 0)
			{
				count1 = green_val;
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
			if(count1 <= 0)
			{
				count1 = red_val;
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
			if(count1 <= 0)
			{
				count1 = yellow_val;
				state1 = RED;
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
				if(count1 <= 0)
				{
					count2 = green_val;
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
				if(count1 <= 0)
				{
					count2 = red_val;
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
				if(count1 <= 0)
				{
					count2 = yellow_val;
					state2 = RED;
					HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin, 0);
					HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
				}
				break;
			default:
				break;


		}
}















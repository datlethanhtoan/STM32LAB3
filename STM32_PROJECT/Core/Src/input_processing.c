

#include "global.h"
#include "input_reading.h"
#include "main.h"
enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState[3] = {BUTTON_RELEASED};

// doc gia tri mode
void UpdateMode(){
	switch (buttonState[0])
	{
		case BUTTON_RELEASED:
			if(is_button_pressed(0))
			{
				buttonState[0] = BUTTON_PRESSED;
				mode++;
				if(mode == 2)
				{
					HAL_GPIO_WritePin(YELLOW_LIGHT_1_GPIO_Port, YELLOW_LIGHT_1_Pin, 1);
					HAL_GPIO_WritePin(YELLOW_LIGHT_2_GPIO_Port, YELLOW_LIGHT_2_Pin,1);
					HAL_GPIO_WritePin(GREEN_LIGHT_1_GPIO_Port, GREEN_LIGHT_1_Pin, 1);
					HAL_GPIO_WritePin(GREEN_LIGHT_2_GPIO_Port, GREEN_LIGHT_2_Pin, 1);
					HAL_GPIO_WritePin(RED_LIGHT_1_GPIO_Port, RED_LIGHT_1_Pin, 1);
					HAL_GPIO_WritePin(RED_LIGHT_2_GPIO_Port, RED_LIGHT_2_Pin, 1);
				}
				if(mode >= 5)
				{
					mode = 1;
					resetCountValue();
				}
			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(0))
			{
				buttonState[0] = BUTTON_RELEASED;
			}
			break;
		default:
			break;

	}
}

// second button: dat gia tri thoi gian moi
static void increaseTempValue(){
	switch(mode){
		case 2: //led redd
			red_temp++;
			if(red_temp >= 100) red_temp = 0;
			break;
		case 3: // led yellow
			yellow_temp++;
			if(yellow_temp >= 100) yellow_temp = 0;
		case 4: // led green
			green_temp++;
			if(green_temp >= 100) green_temp = 0;
		default:
			break;
	}
}

// third button:  dat gia tri moi
// mode2:
//B1: diff = gia tri moi - gia tri cu
//B2: gan gia tri moi vao vao bien chinh thuc
//B3: cong gia tri cua diff vao den xanh de lam can bang lai thoi gian giua ba den tin hieu
// lam tuong tu voi 2 den tin hieu con lai
static void setNewDurationValue()
{
	int diff = 0;
	switch(mode){
		case 2:
			diff = red_temp  - red_val;
			red_val = red_temp;
			green_val += diff;
			green_temp += diff;
			break;
		case 3:
			diff = yellow_temp  - yellow_val;
			yellow_val = yellow_temp;
			red_val += diff;
			red_temp += diff;
			break;
		case 4:
			diff = green_temp  - green_val;
			green_val = green_temp;
			red_val += diff;
			red_temp += diff;
			break;
		default:
			break;
	}

}

// doc gia tri nut nhan
//buttonState[1]: second button
// buttonState[2]: third button
void fsm_for_input_processing(void){
	switch(buttonState[1]){
		case BUTTON_RELEASED:
			if(is_button_pressed(1)){
				buttonState[1] = BUTTON_PRESSED;
				//INCREASE VALUE OF PORT A BY ONE UNIT
				increaseTempValue();
			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(1)){
				buttonState[1] = BUTTON_RELEASED;
			} else {
				if(is_button_pressed_1s(1)){
					buttonState[1] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					increaseTempValue();
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(1)){
				buttonState[1] = BUTTON_RELEASED;
			}
			else{
				if(is_button_held(1)){

					resetCountValue();
					increaseTempValue();
				}
			}
			//todo
			break;
		default:
			break;
	}


	switch (buttonState[2]) {
		case BUTTON_RELEASED:
			if (is_button_pressed(2)) {
				buttonState[2] = BUTTON_PRESSED;
				setNewDurationValue();
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(2)) {
				buttonState[2] = BUTTON_RELEASED;
			}
			break;
		default:
			break;
	}

}

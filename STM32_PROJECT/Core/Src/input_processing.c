

#include "global.h"
#include "input_reading.h"

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState[3] = {BUTTON_RELEASED};

void UpdateMode(){
	switch (buttonState[0])
	{
		case BUTTON_RELEASED:
			if(is_button_pressed(0))
			{
				buttonState[0] = BUTTON_PRESSED;
				mode++;
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


static void increaseTempValue(){
	switch(mode){
		case 2:
			red_temp++;
			if(red_temp >= 100) red_temp = 0;
			break;
		case 3:
			yellow_temp++;
			if(yellow_temp >= 100) yellow_temp = 0;
		case 4:
			green_temp++;
			if(green_temp >= 100) green_temp = 0;
		default:
			break;
	}
}


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



#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "software_timer.h"
void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);
void init_buffer();
void reset_flagForButtonHold(unsigned char index);
unsigned char is_button_held(unsigned char index);

#endif /* INC_INPUT_READING_H_ */

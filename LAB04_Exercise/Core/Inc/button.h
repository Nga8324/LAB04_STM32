/*
 * button.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
#define NORMAL_STATE 	GPIO_PIN_SET
#define PRESSED_STATE 	GPIO_PIN_RESET

int isButton1Pressed();
void getKeyInput();

#endif /* INC_BUTTON_H_ */

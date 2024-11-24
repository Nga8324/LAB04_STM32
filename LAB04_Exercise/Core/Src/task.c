/*
 * task.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Admin
 */

#include "task.h"

void System_Initialization(){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(Button1_GPIO_Port, Button1_Pin, GPIO_PIN_SET);
}
void taskA(){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
void taskB(){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
void taskC(){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}
void taskD(){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
void taskE(){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}
void taskF(){
	if(isButton1Pressed()){
		HAL_GPIO_TogglePin(LED_BUTTON_GPIO_Port, LED_BUTTON_Pin);
	}
}

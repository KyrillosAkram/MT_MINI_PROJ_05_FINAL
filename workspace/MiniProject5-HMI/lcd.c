/*
 *TODO documenting lcd.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Kyrillos
 */

#include "lcd.h"
#include <avr/io.h>
#include <stdlib.h>
void LCD_init(){
	GPIO_setupPinDirection(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_COMMAND_PORT_ID,LCD_PIN_RS_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_COMMAND_PORT_ID,LCD_PIN_RW_ID,PIN_OUTPUT);

#if		LCD_4BITS_MODE
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,((LCD_DATA_FIRST_PIN_ID)+0),PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,((LCD_DATA_FIRST_PIN_ID)+1),PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,((LCD_DATA_FIRST_PIN_ID)+2),PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,((LCD_DATA_FIRST_PIN_ID)+3),PIN_OUTPUT);
	LCD_sendCommand(LCD_CMD_MODE_4BITS_1);
	LCD_sendCommand(LCD_CMD_MODE_4BITS_2);
	LCD_sendCommand(LCD_CMD_USE_2_LINES_5X7_DOTS_FOR_4BIT_MODE);
#else
	  /*LCD_8BITS_MODE*/
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	LCD_sendCommand(LCD_CMD_USE_2_LINES_5X7_DOTS_FOR_8BITS_MODE);
#endif
	LCD_sendCommand(LCD_CMD_DISPLAY_ON_CURSOR_OFF);
	LCD_sendCommand(LCD_CMD_CLEAR_DISPLAY);
	LCD_sendCommand(LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_0);

}

void LCD_sendCommand(LCD_Command_t a_command){
#if LCD_4BITS_MODE
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RS_ID,LOGIC_LOW);
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RW_ID,LOGIC_LOW);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_HIGH);
	LCD_DELAY();
	/*GPIO_writePort(LCD_DATA_PORT_ID,a_command);*/
	GPIO_INSERT_SUCCESSIVE_BITS(LCD_DATA_OUTPUT,LCD_DATA_FIRST_PIN_ID,(4u),((a_command>>4)&(0x0f)));
	LCD_DELAY();
	GPIO_INSERT_SUCCESSIVE_BITS(LCD_DATA_OUTPUT,LCD_DATA_FIRST_PIN_ID,(4u),((a_command)&(0x0f)));
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_LOW);
	LCD_DELAY();
#elif LCD_8BITS_MODE
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RS_ID,LOGIC_LOW);
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RW_ID,LOGIC_LOW);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_HIGH);
	LCD_DELAY();
	GPIO_writePort(LCD_DATA_PORT_ID,a_command);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_LOW);
	LCD_DELAY();
#endif
}

void LCD_displayCharacter(char a_char){
#if LCD_4BITS_MODE
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RS_ID,LOGIC_HIGH);
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RW_ID,LOGIC_LOW);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_HIGH);
	LCD_DELAY();
	/*GPIO_writePort(LCD_DATA_PORT_ID,a_command);*/
	GPIO_INSERT_SUCCESSIVE_BITS(LCD_DATA_OUTPUT,LCD_DATA_FIRST_PIN_ID,(4u),((a_char>>4)&(0x0f))) ;
	LCD_DELAY();
	GPIO_INSERT_SUCCESSIVE_BITS(LCD_DATA_OUTPUT,LCD_DATA_FIRST_PIN_ID,(4u),((a_char)&(0x0f))) ;
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_LOW);
	LCD_DELAY();
#elif LCD_8BITS_MODE
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RS_ID,LOGIC_HIGH);
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_RW_ID,LOGIC_LOW);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_HIGH);
	LCD_DELAY();
	GPIO_writePort(LCD_DATA_PORT_ID,a_char);
	LCD_DELAY();
	GPIO_writePin(LCD_COMMAND_PORT_ID,LCD_PIN_E_ID,LOGIC_LOW);
	LCD_DELAY();
#endif
}

void LCD_displayString(const char* a_string){
	uint8 counter=0;
	while(a_string[counter]!='\0'){
		LCD_displayCharacter(a_string[counter++]);
	}
}

void LCD_moveCursor(uint8 a_row,uint8 a_col){
	switch (a_row) {
		case 0:
			LCD_sendCommand((LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_0) +a_col);
			break;

		case 1:
			LCD_sendCommand((LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_1) +a_col);
			break;

		case 2:
			LCD_sendCommand((LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_2) +a_col);
			break;

		case 3:
			LCD_sendCommand((LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_3) +a_col);
			break;

		default:

			break;
	}
}

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,char* a_string){
#if LCD_ROW_NUM >(2u)
#error LCD MODULE SUPPORTS MAX 2 LINES LCD
#endif
	LCD_moveCursor(a_row,a_col);
	LCD_displayString(a_string);
}


void LCD_clearScreen(){
	LCD_sendCommand(LCD_CMD_CLEAR_DISPLAY);
	LCD_moveCursor(0,0);
}

void LCD_cleanScreen(){
	for (uint8 row=0 ;row<LCD_ROW_NUM;row++){
		LCD_moveCursor(row,0);
		for(uint8 i=0;i<LCD_ROW_WIDTH;i++){
			LCD_displayCharacter(' ');
		}
	}
	LCD_moveCursor(0,0);
}
void LCD_intgerToString(int8 a_intger,char* a_buffer_ptr){
	itoa(a_intger,a_buffer_ptr,10);
	LCD_displayString(a_buffer_ptr);
}

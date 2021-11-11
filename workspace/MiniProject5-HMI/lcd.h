/*
 * TODO documenting lcd.h
 *
 *  Created on: Oct 13, 2021
 *      Author: Kyrillos
 */

#ifndef LCD_H_
#define LCD_H_

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include <util/delay.h>


/****************************************************
 *				Types deceleration					*
 ****************************************************/

typedef enum{
	LCD_CMD_CLEAR_DISPLAY 						= 0x01,
	LCD_CMD_RETURN_HOME								  ,
	LCD_CMD_SHIFT_CURSOR_LEFT					= 0x04,
	LCD_CMD_SHIFT_DISPLAY_RIGHT		  				  ,
	LCD_CMD_SHIFT_CURSOR_RIGHT		  				  ,
	LCD_CMD_SHIFT_DISPLAY_LEFT		  				  ,
	LCD_CMD_DISPLAY_OFF_CURSOR_OFF					  ,
	LCD_CMD_DISPLAY_OFF_CURSOR_ON				= 0x0A,
	LCD_CMD_DISPLAY_ON_CURSOR_OFF				= 0x0C,
	LCD_CMD_DISPLAY_ON_CURSOR_ON				= 0x0E,
	LCD_CMD_DISPLAY_ON_CURSOR_BLINKING			= 0x0F,
	LCD_CMD_SHIFT_CURSOR_POSITION_LEFT				  ,
	LCD_CMD_SHIFT_CURSOR_POSITION_RIGHT			= 0x14,
	LCD_CMD_SHIFT_ENTIRE_DISPLAY_LEFT			= 0x18,
	LCD_CMD_SHIFT_CURSOR_DISPLAY_RIGHT			= 0x1C,
	LCD_CMD_MOVE_CURSOR							= 0x80,
	LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_0		= 0x80,
	LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_1		= 0xC0,
	LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_2		= 0x90,
	LCD_CMD_MOVE_CURSOR_TO_START_OF_LINE_3		= 0xD0,
	LCD_CMD_USE_1_LINES_5X7_DOTS_FOR_8BITS_MODE	= 0x30,
	LCD_CMD_USE_2_LINES_5X7_DOTS_FOR_8BITS_MODE	= 0x38,
	LCD_CMD_USE_1_LINES_5X7_DOTS_FOR_4BIT_MODE	= 0x20,
	LCD_CMD_USE_2_LINES_5X7_DOTS_FOR_4BIT_MODE	= 0x28,
	LCD_CMD_MODE_4BITS_1						= 0x32,
	LCD_CMD_MODE_4BITS_2							  ,
	LCD_CMD_MODE_8BITS_1LINES					= 0x30,
	LCD_CMD_MODE_8BITS_2LINES					= 0x38
}LCD_Command;

typedef enum{
	START_OF_LINE_0 =0x00,
	START_OF_LINE_1 =0x40,
	START_OF_LINE_2 =0x10,
	START_OF_LINE_3 =0x50
}LCD_Display_Line;

/****************************************************
 *  		Module macros and configuration         *
 ****************************************************/
#define LCD_8BITS_MODE TRUE
#define LCD_4BITS_MODE FALSE
#define LCD_DATA_PORT_ID PORTC_ID
#define LCD_DATA_PORT PORTC
#define LCD_DATA_OUTPUT PORTC
#define LCD_DATA_INPUT PINC
#define LCD_DATA_FIRST_PIN_ID 0
#define LCD_COMMAND_PORT_ID PORTD_ID
#define LCD_COMMAND_PORT PORTD
#define LCD_COMMAND_OUTPUT PORTD
#define LCD_COMMAND_INPUT PIND
#define LCD_PIN_RS_ID PIN5_ID
#define LCD_PIN_RW_ID PIN6_ID
#define LCD_PIN_E_ID PIN7_ID
#define LCD_ROW_WIDTH (16u)
#define LCD_ROW_NUM (2u)
//#define LCD_MEMORY_USAGE_OPTIMIZATION


#ifdef LCD_MEMORY_USAGE_OPTIMIZATION
#define LCD_Command_t char 	/* uint8 -> for less memory usage or LCD_Command (enum)  */
/*#define LCD_Display_Position_t uint8*/
#else
#define LCD_Command_t LCD_Command
/*#define LCD_Display_Position_t LCD_Display_Position*/
#endif
/*--------------------------------------------------*/


/****************************************************
 *  			Module macro functions	         	*
 ****************************************************/
#if F_CPU < 1000000000UL
#define LCD_DELAY() _delay_us(1)
#else
/*TODO optimize lcd delay*/
#warning "LCD_DELAY() not optimized"
#define LCD_DELAY() _delay_us(1)
#endif
/*--------------------------------------------------*/

/****************************************************
 *				Functions deceleration				*
 ****************************************************/
void LCD_init();
void LCD_sendCommand(LCD_Command_t a_command);
void LCD_displayCharacter(char a_char);
void LCD_displayString(const char* a_string);
void LCD_moveCursor(uint8 a_row,uint8 a_col);
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,char* a_string);
void LCD_clearScreen();
void LCD_cleanScreen();
void LCD_intgerToString(int8 a_intger,char* a_buffer_ptr);
/*--------------------------------------------------*/

#endif /* LCD_H_ */

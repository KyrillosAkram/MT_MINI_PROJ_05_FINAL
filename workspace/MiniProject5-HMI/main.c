/*
 * main.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Kyrillos
 * Description: this MCU manage the following :
 * 					1-LCD
 * 					2-Keypad
 * 					3-CTRL_MCU
 */

/* Dependencies */
#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"

/* Configuration macros */
#define PASSWORD_SIZE (5)
#define DOOR_OPERATION_DELAY_SECONDS (15)
#define DOOR_HOLDING_DELAY_SECONDS (3)
#define EMERGENCY_DELAY_SECONDS (10)
#define LCD_DELAY_MS (50)
#define LCD_DELAY_USED (0)


/* Application's defined types*/
/* 		The set of HMI_MCU Commands */
typedef enum{
	UART_CMD_MCU_READY=10 ,
	UART_CMD_ITS_FIRST_USE_FOR_SYSTEM,
	UART_CMD_GET_PASSWORD,
	UART_CMD_POST_PASSWORD,
	UART_CMD_TRIGGER_EMERGENCY,
	UART_CMD_OPEN_DOOR,

	UART_CMD_NO_CMD=0xFF

}UART_cmdType;


char buffer0[PASSWORD_SIZE]={0};


/* Function declaration section */

/*
 * Description: takes the password 2 times form user and save it
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_firstTime(void);

/*
 * Description: display open door and change password
 * 				if any option has been choosed call askpassword function
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_homeScreen(void);

/*
 * Description: ask user the password for 3 times
 * 				if pass unblock next stage
 * 				else trigger emergency state for 60s
 * 				by send emergency command to CTRL_MCU and display emergency
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			0x00 or 0xFF as unsigned int of 1 byte
 */
uint8 PROGRAM_askPassword(void);

/*
 * Description: take the new password form user 1 time and
 * 				send it back to CTRL_MCU to save it in external EEPROM
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_changePassword(void);

/*
 * Description: send open door command to CTRL_MCU and display the operation status
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_openDoor(void);

/*
 * Description: set each element by null terminator
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void clear_buffer(void);
/*------------------------------------------------------------------*/


int main(){
/* setup section */
	GPIO_setupPortDirection(PORTB_ID,PORT_OUTPUT);
	/*uart init section*/
	{
		UART_configType s_uart_config={
				9600,
				UART_TX_RX,
				UART_PARITY_DISABLED,
				UART_STOPBIT_1_BIT,
				UART_OPERATING_MODE_ASYNC,
				UART_ASYNC_MODE_SPEED_DOUBLE,
				UART_INTERRUPT_OFF
		};
		UART_init(&s_uart_config);
	}

	LCD_init();




	while(UART_recieveByte()!=UART_CMD_MCU_READY);
	UART_sendByte(UART_CMD_ITS_FIRST_USE_FOR_SYSTEM);
	uint8 systemFirstUse =UART_recieveByte();

	if(systemFirstUse==0){
		PROGRAM_firstTime();
	}

	loop_for_ever{
		PROGRAM_homeScreen();
	}
}


/*
 * Description: takes the password 2 times form user and save it
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_firstTime(void){
	/* request password two time to save it */
	uint8 matched=0;
	while(!matched){

		LCD_displayStringRowColumn(0,0,"  enter password");
		LCD_moveCursor(1,0);
		GPIO_setupPortDirection(PORTB_ID,PORT_OUTPUT);
		for(uint8 i=0;i<PASSWORD_SIZE;i++){
			buffer0[i]=(char)KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			GPIO_writePort(PORTB_ID,buffer0[i]);
		}
		_delay_ms(500);
		for(uint8 i=0;i<PASSWORD_SIZE;i++){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"  one more time");
			LCD_moveCursor(1,0);
			if(buffer0[i]!=(char)KEYPAD_getPressedKey()){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"unmatched");
				_delay_ms(1000);
				matched=0;
				break;
			}else{
				LCD_displayCharacter('*');
				matched=1;
			}
		}
	}
	UART_sendByte(UART_CMD_POST_PASSWORD);
	UART_sendString((const uint8*)buffer0);
	clear_buffer();
}

/*
 * Description: display open door and change password
 * 				if any option has been choosed call askpassword function
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_homeScreen(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+:Open door");
	LCD_displayStringRowColumn(1,0,"-:Change Password");
	uint8 pressedKey='X';
	while(!(pressedKey=='+'||pressedKey=='-')){
		pressedKey=KEYPAD_getPressedKey();
		_delay_ms(100);
	}

	uint8 result=PROGRAM_askPassword();
	if(result==UART_CMD_TRIGGER_EMERGENCY){
		return;
	}

	switch (pressedKey) {
		case '+':
			PROGRAM_openDoor();
			break;
		case '-':
			PROGRAM_changePassword();
			break;
		default:
			break;
	}
	return;
}

/*
 * Description: take the new password form user 1 time and
 * 				send it back to CTRL_MCU to save it in external EEPROM
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_changePassword(void){
	clear_buffer();
	LCD_clearScreen();
	LCD_displayString("enter new pass");
	LCD_moveCursor(1,0);
	for(uint8 i=0;i<PASSWORD_SIZE;i++){
		buffer0[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
	}
	UART_sendByte(UART_CMD_POST_PASSWORD);
	UART_sendString(buffer0);

}

/*
 * Description: send open door command to CTRL_MCU and display the operation status
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void PROGRAM_openDoor(void){
	UART_sendByte(UART_CMD_OPEN_DOOR);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Opening ...");
	for(uint8 i=0;i<DOOR_OPERATION_DELAY_SECONDS;i++)_delay_ms(1000);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Holding ...");
	for(uint8 i=0;i<DOOR_HOLDING_DELAY_SECONDS;i++)_delay_ms(1000);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Closing ...");
	for(uint8 i=0;i<DOOR_OPERATION_DELAY_SECONDS;i++)_delay_ms(1000);

}

uint8 PROGRAM_askPassword(void){
	uint8 counter=3,marks;
	clear_buffer();
	UART_sendByte(UART_CMD_GET_PASSWORD);
	UART_receiveString(buffer0);

	while(counter){
		counter--;
		marks=0;
		LCD_clearScreen();
		LCD_displayString("  enter password");
		LCD_moveCursor(1,0);
		for(uint8 i=0;i<PASSWORD_SIZE;i++){
			GPIO_writePort(PORTB_ID, buffer0[i]);
			if(buffer0[i]!=KEYPAD_getPressedKey()){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"unmatched");
				_delay_ms(500);
				break;
			}else{
				marks++;
				LCD_displayCharacter('*');
			}
		}
		if(marks==PASSWORD_SIZE){
			return 0;
		}
		_delay_ms(500);

	}

	if(counter==0){
		UART_sendByte(UART_CMD_TRIGGER_EMERGENCY);
		LCD_clearScreen();
		_delay_ms(LCD_DELAY_MS);
		LCD_displayString(" !! EMERGENCY !!");
		uint8 ticks=EMERGENCY_DELAY_SECONDS;
		while(ticks){
			ticks--;
			_delay_ms(1000);
		}
		return UART_CMD_TRIGGER_EMERGENCY;
	}

}

/*
 * Description: set each element by null terminator
 * Args:
 * 		inputs:
 * 			void
 * 		output:
 * 			void
 */
void clear_buffer(){
	for(uint8 i=0; i<sizeof(buffer0);i++){
		buffer0[i]=0;
	}
}

/*
 * main.c
 *
 *  Created on: Nov 7, 2021
 *      Author: Kyrillos
 * Description: this MCU executes HMI_MCU commands and managing
 * 				the following peripherals :
 * 					1-External I2C EEPROM
 * 					2-Door's DC motor
 * 					4-Buzzer
 */

/* Dependencies */
#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"
#include "std_types.h"
#include "uart.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "twi.h"
#include "external_eeprom.h"

/* Configuration macros */
#define PASSWORD_SIZE (5)
#define DOOR_OPERATION_DELAY_SECONDS (15)
#define DOOR_HOLDING_DELAY_SECONDS (3)
#define EMERGENCY_DELAY_SECONDS (10)
#define E3PROM_DELAY_MS (50) /* as External EEPROM need at least 10ms between each read/write operation*/

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


/* 		The address of checking first use byte */
typedef enum{
	E3PROM_ADDRESS_FIRST_USAGE=PASSWORD_SIZE+1
}E3PROM_AddressType;
/*------------------------------------------------------------------*/

/* Function declaration section */

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


/* Global variables definition */

/*	the following array to store any string */
char buffer0[PASSWORD_SIZE]={0};

/*	used to store HMI_MCU commands*/
uint8 g_HMICMD=UART_CMD_NO_CMD;

/*-----------------------------------------------------------------*/


int main(){
	/* Setup and initialization section*/

	PWM_ConfigType s_DcMOTOR_Config={

			{/* timer configuration for 250Hz*/
					0,							/*TCNT initial value	*/
					127,						/*OCR  compare value 50%*/
					3,							/*WGM  fast PWM 		*/
					DC_MOTOR_TIMER_ID,			/*Timer ID				*/
					OFF,						/*interrupt not used	*/
					TIMER2_PRESCALER_CLK_64		/*prescaler factor		*/
			},
			PWM_NORMAL,							/*non inverting			*/
			DC_MOTOR_PWM_ID						/*compare unit (PWM) ID	*/
	};

	/*DcMotor_Init makes dcmotor rotate so followed by rotate stop*/
	DcMotor_Init(&s_DcMOTOR_Config);
	DcMotor_Rotate(&s_DcMOTOR_Config,DC_MOTOR_STOP,0);


	/*===============================================
	 * sorry for bad configuration readablilty
	 *===============================================*/

	PWM_ConfigType s_buzzerConfig={
			{/* timer configuration for 250Hz*/
					0,							/*TCNT initial value	*/
					127,						/*OCR  compare value 50%*/
					3,							/*WGM  fast PWM 		*/
					BUZZER_TIMER_ID,			/*Timer ID				*/
					BUZZER_TIMEOUT_CALLBACK,	/*interrupt not used	*/
					TIMER0_PRESCALER_CLK_64		/*prescaler factor		*/
			},
			PWM_NORMAL,							/*non inverting			*/
			BUZZER_PWM_ID						/*compare unit (PWM) ID	*/
	};

	/*as TWI config structure used one time so make local for {} to be popped form stack right after initialization*/
	{
		TWI_ConfigType s_twi_config={
			0x02,								/*boudrate register value			*/
			0b0000001,							/*slave address value				*/
			0,									/*disable general call recognation	*/
			TWI_PRESCALER_1						/*prescaler factor					*/
		};
		TWI_init(&s_twi_config);
	}


	/*as UART config structure used one time so make local for {} to be popped form stack right after initialization*/
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



	/*	the following line to inform HMI MCU that it's ready for responding HMI's commands
	 *	to make the operation on both MCUs synchronized */
	UART_sendByte(UART_CMD_MCU_READY);

	/*super loop section*/
	loop_for_ever{
		/*ready and waiting coming HMI's commands*/
		switch (UART_recieveByte()) {

			case UART_CMD_ITS_FIRST_USE_FOR_SYSTEM:
				/*read the speacified location for information of it is first time run the system*/
				EEPROM_readByte(E3PROM_ADDRESS_FIRST_USAGE,(uint8 *)&buffer0[PASSWORD_SIZE+2]);

				/*the default value of not used before is 0xFF */
				if(buffer0[PASSWORD_SIZE+2]==0xFF){
					/*the condition pass in case not used before*/
					UART_sendByte(0x00);
				}else{
					/*in case it used before*/
					UART_sendByte(0xFF);
				}
				break;


			case UART_CMD_GET_PASSWORD:
				clear_buffer();
				for(uint8 i=0;i<PASSWORD_SIZE;i++){
					EEPROM_readByte(i,(uint8 *)&buffer0[i]);
					_delay_ms(E3PROM_DELAY_MS);
				}
				UART_sendString((const uint8 *)buffer0);
				break;


			case UART_CMD_POST_PASSWORD:
				clear_buffer();
				UART_receiveString((uint8 *)buffer0);
				for(uint8 i=0;i<PASSWORD_SIZE;i++){
					EEPROM_writeByte(i,buffer0[i]);
					_delay_ms(E3PROM_DELAY_MS);
				}
				EEPROM_writeByte(E3PROM_ADDRESS_FIRST_USAGE,0x00);
				clear_buffer();
				break;

			case UART_CMD_TRIGGER_EMERGENCY:
				BUZZER_init(&s_buzzerConfig);
				for(uint8 i=0;i<EMERGENCY_DELAY_SECONDS;i++)_delay_ms(1000);
				BUZZER_deinit(BUZZER_PWM_ID);
				break;

			case UART_CMD_OPEN_DOOR:
				DcMotor_Rotate(&s_DcMOTOR_Config,DC_MOTOR_CW,25);
				for(uint8 i=0;i<DOOR_OPERATION_DELAY_SECONDS;i++)_delay_ms(1000);

				DcMotor_Rotate(&s_DcMOTOR_Config,DC_MOTOR_STOP,0);
				for(uint8 i=0;i<DOOR_HOLDING_DELAY_SECONDS;i++)_delay_ms(1000);

				DcMotor_Rotate(&s_DcMOTOR_Config,DC_MOTOR_A_CW,25);
				for(uint8 i=0;i<DOOR_OPERATION_DELAY_SECONDS;i++)_delay_ms(1000);

				DcMotor_Rotate(&s_DcMOTOR_Config,DC_MOTOR_STOP,0);

				break;

			default:
				break;
		}
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

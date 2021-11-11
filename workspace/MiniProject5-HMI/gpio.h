/*============================================================
 * gpio.h
 *
 * 		Module: GPIO
 *
 *  Created on: Oct 8, 2021
 *
 *      Author: Kyrillos
 *
 * Description: gpio module aims to abstract
 * 				ports and pins changes ,and
 * 				this implementation works
 * 				fine cross AVR8 MCUs ,with
 * 				minimum changes as possible
 *
 *
 ===============================================================*/

#ifndef GPIO_H_
#define GPIO_H_
#include "std_types.h"
#include "common_macros.h"

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PIN0_ID 0u
#define PIN1_ID 1u
#define PIN2_ID 2u
#define PIN3_ID 3u
#define PIN4_ID 4u
#define PIN5_ID 5u
#define PIN6_ID 6u
#define PIN7_ID 7u

#define PORTA_ID 0u
#define PORTB_ID 1u
#define PORTC_ID 2u
#define PORTD_ID 3u



typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/***************************************************
 * 					macro function                 *
 ***************************************************/

/*
 * Description: used only for setup usage or one time
 * 				to improve performance but
 * 				increase code size
 * 				not valid for run time
 * */
/*TODO reimplement the following macro funtions */
#define GPIO_READ_PIN(PORT_CHAR,PIN_ID) ((PORT##(PORT_CHAR))>>PIN_ID)&0x01
#define GPIO_READ_PORT_BY_CHAR(PORT_CHAR) (PORT##(PORT_CHAR))
#define GPIO_WRITE_PIN(PORT_CHAR,PIN_ID,DATA) (((PORT##(PORT_CHAR)))=(DATA)?((PORT##(PORT_CHAR))|(1<<(PIN_ID))):((PORT##(PORT_CHAR))&(~(1<<(PIN_ID)))))
#define GPIO_WRITE_PORT(PORT_CHAR,DATA) (PORT##(PORT_CHAR))=(DATA)
#define GPIO_SETUP_PORT_DIRECTION(PORT_CHAR,DIRECTION) ((DDR##PORT_CHAR)=(DIRECTION))
#define GPIO_SETUP_PIT_DIRECTION(PORT_CHAR,PIN_ID,DIRECTION) (((DDR##(PORT_CHAR)))=(DIRECTION)?((DDR##(PORT_CHAR))|(1<<(PIN_ID))):((PORT##(PORT_CHAR))&(~(1<<(PIN_ID)))))
#define GPIO_INSERT_SUCCESSIVE_BITS(REG,BIT_NUM,NUM_BITS,DATA) REG=(((((REG)&(~(((1<<(NUM_BITS))-1)<<(BIT_NUM))))|(((1<<(NUM_BITS))-1)&(DATA))<<(BIT_NUM))));
/*TODO will deleted after check if it's junk
#define GPIO_READ_PORT(A_PORTX_ID) (PORTX)*/


/*----------------------------------------------------*/


/*****************************************************
 * 				Functions deceleration               *
 *****************************************************/

/*
 * Description: generic and suitable for runtime
 * 				using port or pin id
 */
uint8 GPIO_readPin(uint8 a_portId,uint8 a_pinId);
uint8 GPIO_readPort(uint8 a_portId);
void GPIO_writePin(uint8 a_portId,uint8 a_pinId,boolean a_data);
void GPIO_writePort(uint8 a_portId,uint8 a_data);
/*TODO GPIO_writeFirstNPins function*/
void GPIO_writeFirstNPins(uint8 a_portId,uint8 a_firstNPins,uint8 a_data);
void GPIO_setupPortDirection(uint8 a_portId,GPIO_PortDirectionType a_direction);
void GPIO_setupPinDirection(uint8 a_portId,uint8 a_pinId,GPIO_PinDirectionType a_direction);
void GPIO_setupFirstNPins(uint8 a_portId,uint8 a_firstNPins,GPIO_PinDirectionType a_direction);

#endif /* GPIO_H_ */

/*
 * timer.h
 *
 *  Created on: Nov 1, 2021
 *      Author: Kyrillos
 * Description: this driver to use timers only not the attched peripheral
 * 				and this means to use output compare unit
 * 				configered by PWM
 * 				and to use input capture unit use ICU driver
 *	 	  TODO:complete documentation
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>

#define PRESCALER_BITS_NUM (3u)
#if _AVR_IOM16_H_ | _AVR_IOM32_H_
#define CTC0 (1u) /*WGM01*/
#define CTC1 (3u) /*WGM12*/
#define CTC2 (1u) /*WGM01*/
#define CTC1_TOP_OCR1A 	(4u)
#define CTC1_TOP_ICR1	(12u)
#endif






typedef enum{
	TIMER_CALLBACK_TIMER2_COMP,
	TIMER_CALLBACK_TIMER1_COMPA,
	TIMER_CALLBACK_TIMER1_COMPB,
	TIMER_CALLBACK_TIMER0_COMP,
	TIMER_CALLBACK_TIMER2_OVF,
	TIMER_CALLBACK_TIMER1_OVF,
	TIMER_CALLBACK_TIMER0_OVF
}Timer_CallBackType;


/*
 * Descrption: Timer interrupt status
 */
typedef enum{
	TIMER_INTERRUPT_OFF,
	TIMER_INTERRUPT_ON
}Timer_InterruptType;

/*
 * Descrption: including the only timer business modes
 */
typedef enum{
	TIMER_MODE_NORMAL,
	TIMER_MODE_CTC
}Timer_ModeType;

/*
 * Descrption: if any option not supported by selected timer
 * 			   simply it do nothing
 *   Warninig: for Timer 2 use macro
 */
typedef enum{
	/* avaliable options for timer 0 */
	TIMER0_PRESCALER_NO_CLOCK_SOURCE=0,
	TIMER0_PRESCALER_CLK_1,
	TIMER0_PRESCALER_CLK_8,
	TIMER0_PRESCALER_CLK_64,
	TIMER0_PRESCALER_CLK_256,
	TIMER0_PRESCALER_CLK_1024,
	TIMER0_External_CLOCK_ON_TPIN_FALLING_EDGE,
	TIMER0_External_CLOCK_ON_TPIN_RAISING_EDGE,

	/* avaliable options for timer 1 */
	TIMER1_PRESCALER_NO_CLOCK_SOURCE=0,
	TIMER1_PRESCALER_CLK_1,
	TIMER1_PRESCALER_CLK_8,
	TIMER1_PRESCALER_CLK_64,
	TIMER1_PRESCALER_CLK_256,
	TIMER1_PRESCALER_CLK_1024,
	TIMER1_External_CLOCK_ON_TPIN_FALLING_EDGE,
	TIMER1_External_CLOCK_ON_TPIN_RAISING_EDGE,

	/* avaliable options for timer 2 */
	TIMER2_PRESCALER_NO_CLOCK_SOURCE=0,
	TIMER2_PRESCALER_CLK_1,
	TIMER2_PRESCALER_CLK_8,
	TIMER2_PRESCALER_CLK_32,
	TIMER2_PRESCALER_CLK_64,
	TIMER2_PRESCALER_CLK_128,
	TIMER2_PRESCALER_CLK_256,
	TIMER2_PRESCALER_CLK_1024
}Timer_PrescalerType;

/*
 * Description: Available Timers
 */
typedef enum{
	TIMER0_ID,
	TIMER1_ID,
	TIMER2_ID
}Timer_IDType;

/*
 * Descrption: this bad arrange of vars for
 * 			   good memory optimization
 */
typedef struct{
	uint16 counter_init_value;
	uint16 compare_value;
	Timer_ModeType mode;/*could be reduced to 4 bits*/
	Timer_IDType timer_id:3;
	Timer_InterruptType interruptStatus:1;
	Timer_PrescalerType prescaler:PRESCALER_BITS_NUM;
}Timer_ConfigType;

/*
 * Description: Config and setup the selected timer with pointed configration structure
 * Args:
 * 		in :
 * 			Timer_ConfigType* config_ptr:
 * 			 => {
 *				uint16 counter_init_value;
 *				uint16 compare_value;
 *				Timer_ModeType mode; // normal:0 or CTC:1 but other options exist so choose carefully
 *				Timer_IDType timer_id:3; //selected timer
 *				Timer_PrescalerType prescaler:3;
 *				Timer_InterruptType interruptStatus:2;
 *				}
 *		out:
 *			void
 */
volatile static void(*callBack[7])();



void TIMER_init(Timer_ConfigType* config_ptr);

/*
 * Description: simply clear selected timer clock source
 */
void TIMER_deinit(Timer_IDType a_timer_id);

void TIMER_setCallBack(uint8 a_timer_callBack_id,void(*callBack_ptr)(void));
#endif /* TIMER_H_ */

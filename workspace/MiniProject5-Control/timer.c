/*
 * timer.c
 *
 *  Created on: Nov 2, 2021
 *      Author: Kyrillos
 * Description: this driver to use timers only not the attched peripheral
 * 				but with ability to reconfiger in run time
 * 				and this means to use output compare unit
 * 				configered by PWM
 * 				and to use input capture unit use ICU driver
 *
 * 		  Note: Timer2 not fully supported as async feature
 * 		  TODO:complete documentation
 */

/* Depencies */
#include "timer.h"
#include <avr/interrupt.h>


ISR(TIMER2_OVF_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER2_OVF]){
		(*callBack[TIMER_CALLBACK_TIMER2_OVF])();
	}
}


ISR(TIMER1_OVF_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER1_OVF]){
			(*callBack[TIMER_CALLBACK_TIMER1_OVF])();
		}
}



ISR(TIMER0_OVF_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER0_OVF]){
			(*callBack[TIMER_CALLBACK_TIMER0_OVF])();
		}
}


ISR(TIMER2_COMP_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER2_COMP]){
			(*callBack[TIMER_CALLBACK_TIMER2_COMP])();
		}
}


ISR(TIMER1_COMPA_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER1_COMPA]){
			(*callBack[TIMER_CALLBACK_TIMER1_COMPA])();
		}

}


ISR(TIMER1_COMPB_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER1_COMPB]){
			(*callBack[TIMER_CALLBACK_TIMER1_COMPB])();
		}

}



ISR(TIMER0_COMP_vect){
	if(NULL!=callBack[TIMER_CALLBACK_TIMER0_COMP]){
			(*callBack[TIMER_CALLBACK_TIMER0_COMP])();
		}

}

/*
 * Description: Config and setup the selected timer with pointed configration structure
 * Args:
 * 		in :
 * 			Timer_ConfigType* config_ptr:
 * 				{
 *				uint16 counter_init_value;
 *				uint16 compare_value;
 *				Timer_ModeType mode; // normal:0 or CTC:1 but other options exist so choose carefully
 *				Timer_IDType timer_id:3; //selected timer
 *				Timer_PrescalerType prescaler:3;
 *				Timer_InterruptType interruptStatus:2;
 *				}
 *		out:
 *			void
 * */
void TIMER_init(Timer_ConfigType* config_ptr){
	switch (config_ptr->timer_id) {
		case TIMER0_ID:

			/*to freeze timer and prevent it from increment TCNT0*/
			TCCR0&= ~FIRST_BITS_HIGH((PRESCALER_BITS_NUM));

			/*configering*/
			TCNT0=	(uint8)(config_ptr->counter_init_value);
			OCR0 =	(uint8)(config_ptr->compare_value);

			if(config_ptr->interruptStatus){
				/*
				 * from given mode it CTC0 bit or WGM01 indecates normal active overflow interrupt only
				 * and if CTC0 is true means OCF0 is activated and overflow disable
				 */
				REGESTER_INSERT_SUCCESSIVE_BITS(TIFR,0,2,((config_ptr->mode)&CTC0)?(0b10):(0b01));
			}else {
				REGESTER_INSERT_SUCCESSIVE_BITS(TIFR,0,2,0b00);
			}

			/*after the following timer works with new configation*/
			TCCR0=

					(((config_ptr->mode&BIT0)^BIT0)<<FOC0) |
					(((config_ptr->mode)&BIT0)<<WGM00)|(((config_ptr->mode)&BIT1)<<WGM01) |
					((config_ptr->prescaler)&FIRST_BITS_HIGH(3)) ;

			break;
		case TIMER1_ID:
			/*to freeze timer and prevent it from increment TCNT0*/
			TCCR1B&= ~FIRST_BITS_HIGH((PRESCALER_BITS_NUM));

			/*Configuring*/
			TCNT1=	(config_ptr->counter_init_value);
			if(config_ptr->mode){
				/*CTC and other*/
				switch(config_ptr->mode){
					case CTC1_TOP_OCR1A://0100
						/*TODO Test*/
						TCCR1A&=(~(FIRST_BITS_HIGH(2)))|	/*clear WGM10 and WGM11*/
								//(((TCCR1A>>COM1B0)&FIRST_BITS_HIGH(2))?(/*PWM*/OFF):(/*PWM ON*/1<<FOC1B))|
								//(((TCCR1A>>COM1A0)&FIRST_BITS_HIGH(2))?(/*PWM*/OFF):(/*PWM ON*/1<<FOC1A));
								((config_ptr->mode)&(FIRST_BITS_HIGH(2))?((OFF<<FOC1A)|(OFF<<FOC1B)):((ON<<FOC1A)|(ON<<FOC1B)))
								;
						REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1B,(WGM12),2,0b01);
						OCR1A=	(config_ptr->compare_value);

						/*
						 * I made cases intersection to reduce code size
						 */

					case CTC1_TOP_ICR1 ://1100
						/*
						 * Interrupt section
						 * note:
						 * 		due to specs of atmega 16/32 in case CTC mode
						 * 		the desired interrupt on OCF1A and trigger only
						 * 		when OCR1A be as TOP not ICR1 */

						if(config_ptr->interruptStatus){
							REGESTER_INSERT_BIT(TIMSK,OCIE1A,ON);
							REGESTER_INSERT_BIT(TIMSK,TOIE1,OFF);

						}
						if(config_ptr->mode==(CTC1_TOP_OCR1A)){
							break;
						}
						TCCR1A&=(~(FIRST_BITS_HIGH(2)))|	/*clear WGM10 and WGM11*/
								/*TODO TEST(1<<FOC1B)|(1<<FOC1A);*/		/*we assume that using this function only mean no pwm */
								((config_ptr->mode)&(FIRST_BITS_HIGH(2))?((OFF<<FOC1A)|(OFF<<FOC1B)):((ON<<FOC1A)|(ON<<FOC1B)));
						REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1B,(WGM12),2,0b11);
						ICR1 =	(config_ptr->compare_value);
						break;
					default:/* do nothing */
						break;
				}
			}else{
				/*normal mode
				 * so compare value is 0xFFFF
				 * we assume that using this function only mean no pwm */
				/*TODO TEST*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1A,((config_ptr->mode)&(FIRST_BITS_HIGH(2))?((OFF<<FOC1A)|(OFF<<FOC1B)):((ON<<FOC1A)|(ON<<FOC1B))),2,0b11);
				/*
				 * Interrupt section
				 * note:
				 * 		due to specs of atmega 16/32 in case CTC mode
				 * 		the desired interrupt on OCF1A and trigger only
				 * 		when OCR1A be as TOP not ICR1 */
				if(config_ptr->interruptStatus){
					REGESTER_INSERT_BIT(TIMSK,OCIE1A,OFF);
					REGESTER_INSERT_BIT(TIMSK,TOIE1,ON);

				}

			}

			/* if NO interrupt use */
			if(!config_ptr->interruptStatus){
				REGESTER_INSERT_BIT(TIMSK,OCIE1A,OFF);
				REGESTER_INSERT_BIT(TIMSK,TOIE1,OFF);
			}

			/*after the following timer works with new configuration*/
			TCCR1B|=((config_ptr->prescaler	)&FIRST_BITS_HIGH(3)) ;
			break;

		case TIMER2_ID:

			/*to freeze timer and prevent it from increment TCNT0*/
			TCCR2&= ~FIRST_BITS_HIGH((PRESCALER_BITS_NUM));

			/*Configuring*/
			TCNT2=	(uint8)(config_ptr->counter_init_value);
			OCR2 =	(uint8)(config_ptr->compare_value);

			if(config_ptr->interruptStatus){
				/*
				 * from given mode it CTC2 bit or WGM21 indecates normal active overflow interrupt only
				 * and if CTC2 is true means OCF2 is activated and overflow disable
				 */
				REGESTER_INSERT_SUCCESSIVE_BITS(TIFR,TOIE2,2,((config_ptr->mode)&CTC2)?(0b10):(0b01));
			}else {
				REGESTER_INSERT_SUCCESSIVE_BITS(TIFR,TOIE2,2,0b00);
			}

			/*after the following timer works with new configation*/
			TCCR2=

					(((config_ptr->mode&BIT0)^BIT0)<<FOC2) |
					(((config_ptr->mode)&BIT0)<<WGM20)|(((config_ptr->mode)&BIT1)<<WGM21) |
					((config_ptr->prescaler)&FIRST_BITS_HIGH(3)) ;

			break;
		default:
			/* do nothing */
			break;
	}
}
void TIMER_deinit(Timer_IDType a_timer_id){
	switch(a_timer_id){
	case TIMER0_ID:
		TCCR0&=~FIRST_BITS_HIGH(3);
		break;
	case TIMER1_ID:
		TCCR1B&=~FIRST_BITS_HIGH(3);
		break;
	case TIMER2_ID:
		TCCR2&=~FIRST_BITS_HIGH(3);
		break;
	default:
		/* do nothing */
		break;
	}
}
void TIMER_setCallBack(uint8 a_timer_callBack_id,void(*callBack_ptr)(void)){
	(callBack[a_timer_callBack_id])=callBack_ptr;
}

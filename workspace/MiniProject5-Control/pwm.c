/*
 * pwm.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Kyrillos
 */
#include "pwm.h"
#include "avr/io.h"








static volatile const int32 g_prescaler_factor01[5]={1,8,64,256,1024};
static volatile const int32 g_prescaler_factor2 [6]={1,8,32,64,256,1024};
/*
 * Note : this function will delete in next first release
 * Description :
 * 		initialize Timer 0 and output compare unit on the fly to
 * 		get PWM on OC0 with given duty cycle
 * Args:
 * 		In:
 * 			uint8 duty_cycle:
 *
 * 				* the percentage value of the desired duty cycle
 *
 * 				* the type of unsigned integer of 1 byte
 * */
void PWM_Timer0_Start(uint8 duty_cycle){
	OCR0=((uint8)(((uint32)(duty_cycle*255))/100));
	TCCR0|=
			(1<<WGM01)|(1<<WGM00)|
			(1<<COM01)|
			(1<<CS01);
}

/*
 *
 */
void PWM_init(PWM_ConfigType *config_ptr){
	//uint8 matched=1;
	switch(config_ptr->a_pwmID){
		case PWM0_ID:
			GPIO_setupPinDirection(PWM0_PORT_ID,PWM0_PIN,PIN_OUTPUT);
			if(config_ptr->timer_config.mode&BIT0){
				/*PWM mode*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR0,COM00,2,(0b10|(config_ptr->a_signalType))) ;
			}else{
				/*CTC mode*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR0,COM00,2,OC_PIN_TOGGLE) ;
			}

			break;

		case PWM1A_ID:
			GPIO_setupPinDirection(PWM1A_PORT_ID,PWM1A_PIN,PIN_OUTPUT);
			if(config_ptr->timer_config.mode&BIT0){
				/*PWM mode*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1A,COM1A0,2,(0b10|(config_ptr->a_signalType))) ;
			}else{
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1A,COM1A0,2,OC_PIN_TOGGLE);
			}
			break;

		case PWM1B_ID:
			GPIO_setupPinDirection(PWM1B_PORT_ID,PWM1B_PIN,PIN_OUTPUT);
			if(config_ptr->timer_config.mode&BIT0){
				/*PWM mode*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1B,COM1B0,2,(0b10|(config_ptr->a_signalType))) ;
			}else{
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1B,COM1B0,2,OC_PIN_TOGGLE) ;
			}
			break;

		case PWM2_ID:
			GPIO_setupPinDirection(PWM2_PORT_ID,PWM2_PIN,PIN_OUTPUT);
			if(config_ptr->timer_config.mode&BIT0){
				/*PWM mode*/
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR2,COM20,2,(0b10|(config_ptr->a_signalType))) ;
			}else{
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR2,COM20,2,OC_PIN_TOGGLE) ;
			}

			break;

		default:
			/*to exit without execute last common function*/
			return;
			break;
	}

	TIMER_init(&(config_ptr->timer_config));

}

/*
 * note: on fast pwm only now
 * TODO: more generic and
 */
void PWM_genrate_pwm(PWM_IDType a_pwmID,uint32 a_freq,uint8 a_dutyCycle,PWM_SignalType a_signalType){
	uint32 resultFreq=0;
	switch(a_pwmID){
	case PWM0_ID :
		for (uint8 i=0;i<5;i++){
			resultFreq=(uint32)((uint32)F_CPU)/((uint32)g_prescaler_factor01[i]*256);
			if(resultFreq>=(a_freq+PWM_FREQ_TOLERANCE)||resultFreq<=(a_freq+PWM_FREQ_TOLERANCE)){
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR0,COM00,2,(0b10|a_signalType));
				break;
			}
		}
		break;

	case PWM1A_ID:
		break;

	case PWM1B_ID:
		break;

	case PWM2_ID :
		for (uint8 i=0;i<6;i++){
			resultFreq=(uint32)((uint32)F_CPU)/((uint32)g_prescaler_factor2[i]*256);
			if(resultFreq>=(a_freq+PWM_FREQ_TOLERANCE)||resultFreq<=(a_freq+PWM_FREQ_TOLERANCE)){
				REGESTER_INSERT_SUCCESSIVE_BITS(TCCR2,COM20,2,(0b10|a_signalType));
				break;
			}
		}
		break;

	default:
		break;

	}

}

void PWM_deinit(PWM_IDType a_pwmID){
	switch(a_pwmID){
		case PWM0_ID:
			REGESTER_INSERT_SUCCESSIVE_BITS(TCCR0,COM00,2,OFF) ;
			break;

		case PWM1A_ID:
			REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1A,COM1A0,2,OFF) ;
			break;

		case PWM1B_ID:
			REGESTER_INSERT_SUCCESSIVE_BITS(TCCR1B,COM1B0,2,OFF);
			break;

		case PWM2_ID:
			REGESTER_INSERT_SUCCESSIVE_BITS(TCCR2,COM20,2,OFF);
			break;

		default:
			/*to exit without execute last common function*/
			return;
			break;
	}

}

void (*PWM_disconnect)(PWM_IDType a_pwmID)=PWM_deinit;

void PWM_changeDutyCycle(PWM_IDType a_pwmID,uint8 a_dutyCycle){
	switch (a_pwmID) {
	case PWM0_ID:
		OCR0=(uint8)((uint32) (a_dutyCycle*255)/100);
		break;
	case PWM2_ID:
		OCR2=(uint8)((uint32) (a_dutyCycle*255)/100);
		break;
	case PWM1A_ID:
		OCR1A=(uint16)((uint32) (a_dutyCycle*65536)/100);
		break;
	case PWM1B_ID:
		OCR1B=(uint16)((uint32) (a_dutyCycle*65536)/100);
		break;

		default:
			break;
	}
}

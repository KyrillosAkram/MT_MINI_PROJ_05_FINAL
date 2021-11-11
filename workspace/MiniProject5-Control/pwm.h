/*
 * pwm.h
 *
 *  Created on: Oct 17, 2021
 *      Author: Kyrillos
 */

#ifndef PWM_H_
#define PWM_H_
#include "gpio.h"
#include "timer.h"
#include <avr/io.h>

#define PWM_FREQ_TOLERANCE (50u)
#define PWM_ID_BITS (3u)


#if _AVR_IOM16_H_ | _AVR_IOM32_H_

#define PWM0_PORT_ID 	PORTB_ID
#define PWM0_PORT 		PORTB
#define PWM0_PIN		PIN3

#define PWM1A_PORT_ID 	PORTD_ID
#define PWM1A_PORT 		PORTD
#define PWM1A_PIN		PIN4

#define PWM1B_PORT_ID 	PORTD_ID
#define PWM1B_PORT 		PORTD
#define PWM1B_PIN		PIN5

#define PWM2_PORT_ID 	PORTD_ID
#define PWM2_PORT 		PORTD
#define PWM2_PIN		PIN7

#define OC_PIN_TOGGLE (1u)

#else
#error supports pwm and compare units on atmega 16/32 only
#endif

typedef enum{
	PWM0_ID,
	PWM1A_ID,
	PWM2_ID,
	PWM1B_ID
}PWM_IDType;

/*
typedef enum{
	TODO PWM_modeTypes enumerations
}PWM_modeType;
*/
typedef enum{
	PWM_NORMAL,
	PWM_INVERTED
}PWM_SignalType;


typedef struct{
	Timer_ConfigType timer_config;
	PWM_SignalType a_signalType:2;
	PWM_IDType a_pwmID:PWM_ID_BITS;
}PWM_ConfigType;



/*
 * Note : this function will delete in next first release
 *
 * Description :
 * 		initialize Timer 0 and output compare unit on the fly to
 * 		get PWM on OC0 with feeded duty cycle
 * Args:
 * 		In:
 * 			uint8 duty_cycle:
 *
 * 				* the precentage value of the desired duty cycle
 *
 * 				* the type of unsigned intger of 1 byte
 * */
void PWM_Timer0_Start(uint8 duty_cycle);

/*
 * Description :
 */
void PWM_init(PWM_ConfigType *config_ptr);
void PWM_genrate_pwm(PWM_IDType a_pwmID,uint32 a_freq,uint8 a_dutyCycle,PWM_SignalType a_mode);
void PWM_changeDutyCycle(PWM_IDType a_pwmID,uint8 a_dutyCycle);
void PWM_deinit(PWM_IDType a_pwmID);
extern void (*PWM_disconnect)(PWM_IDType a_pwmID);

#endif /* PWM_H_ */

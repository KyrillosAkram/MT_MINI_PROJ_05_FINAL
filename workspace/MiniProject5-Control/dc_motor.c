/*
 * dc_motor.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Kyrillos
 */


#include "dc_motor.h"
/****************************************************
 *  				Module constants	         	*
 ****************************************************/
const char* DC_MOTOR_on ="N ";
const char* DC_MOTOR_off="FF";
/*--------------------------------------------------*/


/*	the following line is a defining reference of g_DC_MOTOR_state to linker,
 *  so must init with hardcoded value not even const variable
 *  and assign the real initial value in DcMotor_Init
 *  all of this due to language limitaion with memory initialization */
volatile char* g_DC_MOTOR_state_ptr=(char*)0;


/*
 * Description : preparing the required hardware to be ready for using
 */
void DcMotor_Init(PWM_ConfigType *dc_motor_pwm_ptr){
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,PIN_OUTPUT);
	/*TODO remove PWM_Timer0_Start(OFF);*/

	PWM_init(dc_motor_pwm_ptr);

	/*initializing with desired value */
	g_DC_MOTOR_state_ptr=(char*)DC_MOTOR_off;
}

/*
 * Description :
 * 			1-  handling dcmotor state (off , cw,acw) and
 * 				rotating
 * 			2-  update g_DC_MOTOR_state_ptr
 * 				to point to a string represing state
 * Arg:
 * 		In:
 * 			DcMotor_State state :
 *
 * 				* this arg is higher periority than the following
 * 				  if it is OFF ,the next arg speed is useless
 * 				  else it indecating the rotating direction
 *
 * 				* the type size is signed integer of 2 byte
 *
 * 			uint8 speed:
 *
 * 				* is the percentage of the motor speed
 * 				  for example 25% ==> 25
 * 				  values from 0:100 else makes undefined behavior
 * 				  or even crash
 *
 * 				* if equals 0 makes motor stop and change state to off
 *
 * 				* the type size is unsigned integer of 1 byte
 *
 */
void DcMotor_Rotate(PWM_ConfigType *dc_motor_pwm_ptr ,DcMotor_State state,uint8 speed){
	/*PWM_Timer0_Start(speed);*/
	if(!speed)state=DC_MOTOR_STOP;
	switch (state) {
		case DC_MOTOR_CW:
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_LOW );
			g_DC_MOTOR_state_ptr=(char*)DC_MOTOR_on;
			break;
		case DC_MOTOR_A_CW:
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_LOW );
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_HIGH);
			g_DC_MOTOR_state_ptr=(char*)DC_MOTOR_on;
			break;
		case DC_MOTOR_STOP:
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_LOW );
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_LOW );
			g_DC_MOTOR_state_ptr=(char*)DC_MOTOR_off;
			break;

	}
	if(state==DC_MOTOR_STOP){
		PWM_deinit(dc_motor_pwm_ptr->a_pwmID);
	}else{
		PWM_init(dc_motor_pwm_ptr);
	}
}


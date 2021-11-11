/*
 * buzzer.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Kyrillos
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "pwm.h"

#define BUZZER_PWM_ID PWM0_ID
#define BUZZER_TIMER_ID TIMER0_ID
#define BUZZER_PORT_ID PWM0_PORT_ID
#define BUZZER_PIN_ID PWM0_PIN
#define BUZZER_TIMEOUT_CALLBACK (0)
#define BUZZER_CTC (1)

extern PWM_ConfigType es_buzzerConfig;



void BUZZER_init(PWM_ConfigType *buzzerConfig_ptr);



extern void (*BUZZER_deinit)(PWM_IDType a_pwmID);
#endif /* BUZZER_H_ */

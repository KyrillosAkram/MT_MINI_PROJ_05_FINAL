/*
 * buzzer.c
 *
 *  Created on: Nov 5, 2021
 *      Author: Kyrillos
 */

#include "buzzer.h"

#if BUZZER_CTC

/* wave with CTC tect */
PWM_ConfigType es_buzzerConfig={
		{//generate 250Hz
				0,
				124,
				2,
				BUZZER_TIMER_ID,
				BUZZER_TIMEOUT_CALLBACK,
				TIMER0_PRESCALER_CLK_64
		},
		1,
		BUZZER_PWM_ID
};
#else
/* wave with PWM tect */
PWM_ConfigType es_buzzerConfig={
		{//generate 250Hz
				0,
				127,
				3,
				BUZZER_TIMER_ID,
				BUZZER_TIMEOUT_CALLBACK,
				TIMER0_PRESCALER_CLK_64

		},
		PWM_NORMAL,
		BUZZER_PWM_ID
};
#endif
void BUZZER_init(PWM_ConfigType *buzzerConfig_ptr){
	PWM_init(buzzerConfig_ptr);
	/*PWM_disconnect(buzzerConfig_ptr->a_pwmID);*/
}

void (*BUZZER_deinit)(PWM_IDType a_pwmID)=PWM_deinit;



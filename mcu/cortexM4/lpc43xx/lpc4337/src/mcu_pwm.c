/*
 * mcu_pwm.c
 *
 *  Created on: Jul 2, 2017
 *      Author: pampa
 */

#include "mcu_pwm.h"
#include "chip.h"


extern void mcu_pwm_init(void){

	/* Source: https://www.lpcware.com/content/faq/how-use-sct-standard-pwm-using-lpcopen */
   /* Initialize the SCT as PWM and set frequency */
   Chip_SCTPWM_Init(LPC_SCT);
}

extern void configPWM(pwm_channel_t channel, uint32_t freq){

    Chip_SCTPWM_Init(LPC_SCT);

    Chip_SCTPWM_SetRate(LPC_SCT, freq);

    Chip_SCU_PinMux(SCTdataList[channel].port, SCTdataList[channel].pin, SCU_MODE_FUNC1, FUNC1);

    Chip_SCTPWM_SetOutPin(LPC_SCT, channel + 1, channel);

}

extern void mcu_pwm_start(void){
	Chip_SCTPWM_Start(LPC_SCT);
}

extern void mcu_pwm_setDutyCycle(pwm_channel_t channel, uint32_t duty){
	Chip_SCTPWM_SetDutyCycle(LPC_SCT, channel + 1, Chip_SCTPWM_PercentageToTicks(LPC_SCT, duty));
}

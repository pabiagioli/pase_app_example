/*
 * mcu_pwm.h
 *
 *  Created on: Jul 2, 2017
 *      Author: pampa
 */

#ifndef MCU_PWM_H_
#define MCU_PWM_H_

#include "stdint.h"

#define PWM_TOTALNUMBER   11   /* From PWM0 to PWM10 */

#define PWM_FREC          1000 /* 1Khz */
#define PWM_PERIOD        1000 /* 1000uS = 1ms*/


typedef struct{
   int8_t port;
   int8_t pin;
} pinConfigLpc4337_t;

typedef enum {PWM3,PWM0,PWM7,PWM4,PWM9,PWM8,PWM10,PWM6,PWM2=10,PWM1=12,PWM5} pwm_channel;

/* Enter a pwm number, get a sct number
 * Since this module works with pwm numbers, but uses sct channels to generate
 * the signal, its necessary to connect pwm number with the SctMap_t (sAPI_PeripheralMap.h).
 * This way the user sets "pwms", while using the sct peripheral internally*/
static const uint8_t pwmMap[PWM_TOTALNUMBER] = {
   /* PWM0 */  PWM0,  /* T_FIL1 */
   /* PWM1 */  PWM1, /* T_COL2 */
   /* PWM2 */  PWM2, /* T_COL0 */
   /* PWM3 */  PWM3,  /* T_FIL2 */
   /* PWM4 */  PWM4,  /* T_FIL3 */
   /* PWM5 */  PWM5, /* T_COL1 */
   /* PWM6 */  PWM6,  /* GPIO8  */
   /* PWM7 */  PWM7,  /* LED1   */
   /* PWM8 */  PWM8,  /* LED2   */
   /* PWM9 */  PWM9,  /* LED3   */
   /* PWM10 */ PWM10   /* GPIO2  */
};

/*
 * List of ports and pins corresponding to the sct channels.
 * Each channel is asociated with a CTOUT number. Some pins, like
 * LED 1 and LCD1, have the same channel, so you can only generate 1 signal
 * for both. Because of that only one of them will be used.
 */
static pinConfigLpc4337_t SCTdataList[] =
{
/* Sct n° | port | pin | name in board */
/* CTOUT0 */ { 4 , 2 }, /* T_FIL2 */
/* CTOUT1 */ { 4 , 1 }, /* T_FIL1 */
/* CTOUT2 */ { 2 , 10 }, /* LED1 (also for LCD1) */
/* CTOUT3 */ { 4 , 3 }, /* T_FIL3 */
/* CTOUT4 */ { 2 , 12 }, /* LED3 (also for LCD3) */
/* CTOUT5 */ { 2 , 11 }, /* LED2 (also for LCD2) */
/* CTOUT6 */ { 6 , 5 }, /* GPIO2 */
/* CTOUT7 */ { 6 , 12 }, /* GPIO8 */
/* CTOUT8 */ { 1 , 3 }, /* MDC / SPI_MISO */
/* CTOUT9 */ { 1 , 4 }, /* SPI_MOSI */
/* CTOUT10 */ { 1 , 5 }, /* T_COL0 */
/* CTOUT11 */ { 0 , 0 }, /* DO NOT USE */
/* CTOUT12 */ { 7 , 5 }, /* T_COL2 */
/* CTOUT13 */ { 7 , 4 } /* T_COL1 */
};


extern void mcu_pwm_init(void);
extern void configPWM(pwm_channel channel, uint32_t period);
extern void mcu_pwm_setDutyCycle(uint32_t duty);
extern void mcu_pwm_start(void);

#endif /* MCU_PWM_H_ */

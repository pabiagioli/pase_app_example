/* Copyright 2017, Gustavo Muro
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief PASE APP EXAMPLE
 **
 ** ejemplo de aplicación usando CIAA Firmware
 **
 **/

/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */

/*==================[inclusions]=============================================*/
#include "os.h"
#include "pase_app_example.h"
#include "bsp.h"
#include "mcu.h"

/*==================[macros and definitions]=================================*/

#define FIRST_START_DELAY_MS 0
#define PERIOD_TIMESTAMP_MS 1
#define PERIOD_RAMP_MS 20
#define FIRST_START_DELAY_MS 350
#define BAUD_RATE_UART 115200

/*==================[internal data declaration]==============================*/
static uint32_t TimeStampCounter = 0;
static fsm StateMachine = {.currentLED=RED, .fsm_status=PLAYER_IDLE, .dcycle=0, .direction = 0};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void eventInput1_callBack(mcu_gpio_pinId_enum id, mcu_gpio_eventTypeInput_enum evType)
{
	SetEvent(PlayStopTask, evPlayStopTask);
	//SetEvent(InputEvTask1, evTask);
}

static void eventInput2_callBack(mcu_gpio_pinId_enum id, mcu_gpio_eventTypeInput_enum evType)
{
	SetEvent(PauseResumeTask, evPauseResumeTask);
	//SetEvent(InputEvTask2, evTask);
}

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
	/* Starts the operating system in the Application Mode 1 */
	/* This example has only one Application Mode */
	StartOS(AppMode1);

	/* StartOs shall never returns, but to avoid compiler warnings or errors
	 * 0 is returned */
	return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
	ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
	bsp_init();

	mcu_gpio_setEventInput( MCU_GPIO_PIN_ID_38,
							MCU_GPIO_EVENT_TYPE_INPUT_FALLING_EDGE,
							eventInput1_callBack);

	mcu_gpio_setEventInput( MCU_GPIO_PIN_ID_42,
							MCU_GPIO_EVENT_TYPE_INPUT_RISING_EDGE,
							eventInput2_callBack);

	uartConfig(UART_USB, BAUD_RATE_UART);

	configPWM(2,1000);
	configPWM(5,1000);
	configPWM(4,1000);

	mcu_pwm_start();

	//SetRelAlarm(ActivateTimeStampTask, FIRST_START_DELAY_MS, PERIOD_TIMESTAMP_MS);
	//SetRelAlarm(ActivateTimeStampTask, FIRST_START_DELAY_MS, PERIOD_TIMESTAMP_MS);

	TerminateTask();
}

TASK(PlayStopTask)
{
	while (1)
	{
		//WaitEvent(evPlayStopTask);
		//ClearEvent(evPlayStopTask);
		switch(StateMachine.fsm_status)
		{
			case PLAYER_IDLE:
				StateMachine.fsm_status = PLAYER_PLAYING;
				uartWriteString(UART_USB,"Inicio Secuencia\n");
				break;
			case PLAYER_PLAYING:
				StateMachine.fsm_status = PLAYER_STOPPED;
				uartWriteString(UART_USB,"Secuencia Finalizada\n");
				break;
			case PLAYER_STOPPED:
				StateMachine.fsm_status = PLAYER_PLAYING;
				uartWriteString(UART_USB,"Inicio Secuencia\n");
				break;
		}
	}
}

TASK(PauseResumeTask)
{
	while (1)
	{
		//WaitEvent(evPauseResumeTask);
		//ClearEvent(evPauseResumeTask);
		switch(StateMachine.fsm_status)
		{
		case PLAYER_IDLE:
			break;
		case PLAYER_PLAYING:
			StateMachine.fsm_status = PLAYER_PAUSED;
			uartWriteString(UART_USB,"Secuencia Pausada\n");
			break;
		case PLAYER_PAUSED:
			StateMachine.fsm_status = PLAYER_PLAYING;
			uartWriteString(UART_USB,"Secuencia Reanudada\n");
			break;
		case PLAYER_STOPPED:
			break;
		}
	}
}

TASK(TimeStampTask)
{
	TimeStampCounter++;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


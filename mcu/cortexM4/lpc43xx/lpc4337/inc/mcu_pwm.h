#ifndef MCU_PWM_H
#define MCU_PWM_H

/*==================[inclusions]=============================================*/
#include "stdbool.h"
#include "stdint.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/
extern void mcu_pwm_init(void);
extern void mcu_pwm_config(mcu_gpio_pinId_enum pin, uint32_t period);
extern void mcu_pwm_setDutyCicle(uint32_t duty);

/*==================[external functions declaration]=========================*/

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MCU_GPIO_H */


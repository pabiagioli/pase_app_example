/*
 * mcu_uart.h
 *
 *  Created on: Jul 13, 2017
 *      Author: pampa
 */

#ifndef MCU_UART_H_
#define MCU_UART_H_

/* Define Boolean Data Type */
typedef uint8_t bool_t;

/* Define real Data Types (floating point) */
//typedef real32_t float;
//typedef real64_t double;

/* Define Tick Data Type */
typedef uint64_t tick_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/* Defined for sapi_uart.h */
typedef enum{
   UART_USB, UART_232, UART_485
} uartMap_t;

typedef enum{
   UART_RECEIVE_STRING_CONFIG,
   UART_RECEIVE_STRING_RECEIVING,
   UART_RECEIVE_STRING_RECEIVED_OK,
   UART_RECEIVE_STRING_TIMEOUT
} waitForReceiveStringOrTimeoutState_t;

typedef struct{
   waitForReceiveStringOrTimeoutState_t state;
   char*    string;
   uint16_t stringSize;
   uint16_t stringIndex;
   tick_t   timeout;
   delay_t  delay;
} waitForReceiveStringOrTimeout_t;

waitForReceiveStringOrTimeoutState_t waitForReceiveStringOrTimeout(uartMap_t uart, waitForReceiveStringOrTimeout_t* instance );
bool_t waitForReceiveStringOrTimeoutBlocking(uartMap_t uart, char* string, uint16_t stringSize, tick_t timeout );
void uartConfig(uartMap_t uart, uint32_t baudRate );
bool_t uartReadByte(uartMap_t uart, uint8_t* receivedByte );
void uartWriteByte(uartMap_t uart, uint8_t byte );
void uartWriteString(uartMap_t uart, char* str );

/* 0x28 0x000000A0 - Handler for ISR UART0 (IRQ 24) */
void UART0_IRQHandler(void);
/* 0x2a 0x000000A8 - Handler for ISR UART2 (IRQ 26) */
void UART2_IRQHandler(void);
/* 0x2b 0x000000AC - Handler for ISR UART3 (IRQ 27) */
void UART3_IRQHandler(void);


#endif /* MCU_UART_H_ */

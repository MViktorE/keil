/*
* 
* 
*/

#ifndef UART_CMSIS_M3_MVE_V0_H
#define UART_CMSIS_M3_MVE_V0_H

#include "main.h"

extern volatile uint8_t rxUartIt[8];
extern uint8_t rxCounter;
extern uint8_t rxUartOverflow;

void USART1_IRQHandler(void);
uint8_t uart_init(void);
uint8_t uart_send(uint8_t * txData, uint16_t dataLength);
uint8_t uart_resive(uint8_t * rxData);


#endif

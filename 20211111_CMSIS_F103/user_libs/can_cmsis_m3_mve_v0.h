/*
 * 2021.10.20 
 * Ver. 0
 * MVE
 * Work only with TX mailbox #0 !!!!!!!!!!!!!!
*/

#ifndef CAN_CMSIS_M3_MVE_V0_H
#define CAN_CMSIS_M3_MVE_V0_H

#include "main.h"

extern uint8_t flagRxCan;
extern uint32_t canRx0Data[3];
static uint8_t canRx0DataCounter = 0;

#define DATA_LENGTH_CODE 8 /* between 1 and 8 */

void CAN1_RX0_IRQHandler (void);  
uint8_t can_init(void);
uint8_t can1_send(uint8_t * pData, uint8_t dataLength, uint8_t mailboxNum);  
#endif

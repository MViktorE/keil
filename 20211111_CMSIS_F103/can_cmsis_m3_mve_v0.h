/*
 * 2021.10.20 
 * Ver. 0
 * MVE
*/

#ifndef CAN_CMSIS_M3_MVE_V0_H
#define CAN_CMSIS_M3_MVE_V0_H

#include "main.h"

void CAN1_RX0_IRQHandler (void);   /* !!!!write in main.c NVIC_EnableIRQ(CAN1_RX0_IRQn);!!! */
uint8_t can_init(void);

#endif
/*
 * systick_cmsis_m3_mve_v0.h
 *
 *  Created on: Jul 19, 2021
 *      Author: MVE
 *      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *      IN MAIN.C YOU MUST WRITE: 
 *      volatile uint32_t msTicks;      // global var
 *		SystemCoreClockUpdate();
 *      SysTick_Config(SystemCoreClock/1000); // 'prescaler' of SysTick for 1 ms
 *		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

#ifndef SYSTICK_CMSIS_M3_MVE_V0_H
#define SYSTICK_CMSIS_M3_MVE_V0_H

#include "main.h"

extern volatile uint32_t msTicks;

void SysTick_Handler(void);
void mve_delay(uint32_t dlyTicks);

#endif /* SYSTICK_CMSIS_M3_MVE_V0_H */

/*
 * systick_cmsis_m3_mve_v0.c
 *
 *  Created on: Jul 19, 2021
 *      Author: user
 */

#include "systick_cmsis_m3_mve_v0.h"
    
void SysTick_Handler(void){	//Enter here every 1 ms
	msTicks++;
}

void mve_delay(uint32_t dlyTicks){
	uint32_t curTicks;
	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks);
}

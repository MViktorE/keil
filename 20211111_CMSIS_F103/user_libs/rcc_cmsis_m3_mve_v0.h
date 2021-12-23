/*
* RCC Setting for STM32F103
* 2021.10.13
*/

#ifndef RCC_CMSIS_M3_MVE_V0_H
#define RCC_CMSIS_M3_MVE_V0_H

#include "main.h"

uint8_t rcc_init(void);                /* Set 36 MHz to ABP1 and SYSCLK from HSI */
uint8_t rcc_per_en(void); 

//RCC->CFGR |= RCC_CFGR_MCO_PLLCLK_DIV2; /* MCO: Microcontroller clock output - ResVal - 0xx: No clock  PA8 - out in Alter Function */ 

#endif

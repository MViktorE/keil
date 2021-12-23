#include "rcc_cmsis_m3_mve_v0.h"

uint8_t rcc_init(void){

    /* Using the default HSI sorce - 8 MHz */
    /* Checking that the HSI is working */
    for (uint8_t i=0; ; i++){
        if(RCC->CR & (1<<RCC_CR_HSIRDY_Pos))
          break;
        if(i == 255)
          return 1;          
    }
    
    /* RCC_CFGR Reset value: 0x0000 0000 */
    /* PLLSRC: PLLSRC: PLL entry clock source - Reset Value - 0 -> HSI oscillator clock / 2 selected as PLL input clock */
    /* HSI = 8 MHz */
    RCC->CFGR |= RCC_CFGR_PLLMULL9;     /* 0x000C0000 - PLL input clock*9 */
    RCC->CFGR |= RCC_CFGR_SW_1;         /* 0x00000002 - PLL selected as system clock */
    /* SYSCLK = 36 MHz */
    /*Also you can change another parameters:*/
    /* HPRE: AHB prescaler - Reset Value - 0 -> SYSCLK not divided */
    /* HCLK = 36 MHz (72 MHz MAX) */
    /* PPRE1: APB low-speed prescaler (APB1) - Reset Value - 0 -> 0xx: HCLK not divided */
    /* PPRE2: APB low-speed prescaler (APB2) - Reset Value - 0 -> 0xx: HCLK not divided */
    /* APB1 = APB2 = 36 MHz */
    /* ADCPRE: ADC prescaler - Reset Value - 0 -> PCLK2 divided by 2 */
    /* PLLXTPRE: HSE divider for PLL entry - ResVal - 0 -> HSE clock not divided */
    /* USBPRE: USB prescaler - ResVal - 0: PLL clock is divided by 1.5 */
    RCC->CR |=RCC_CR_PLLON;             /* 0x01000000 - PLL enable */
    for (uint8_t i=0; ; i++){
      if(RCC->CR & (1U<<RCC_CR_PLLRDY_Pos))
        break;
      if(i==255){
        RCC->CR &= ~(1U<<RCC_CR_PLLON_Pos);
        return 2;
      }
    }      
    return 0;
}

uint8_t rcc_per_en(void){
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;


    return 0;
}

#include "gpio_cmsis_m3_mve_v0.h"

uint8_t gpio_init(void){
    
    /* PORT A*/
    /* !!!ADD RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;!!!*/
    /* PA8 - MCO */
//    GPIOA->CRH	&= ~GPIO_CRH_CNF8;	// CNF8 = 00 
//    GPIOA->CRH	|= GPIO_CRH_CNF8_1;	// CNF8 = 10 -> AF Out | Push-pull (MCO)
//    GPIOA->CRH 	|= GPIO_CRH_MODE8;      // MODE8 = 11 -> Maximum output speed 50 MHz

  
    /* PORT C */
    /* !!!ADD RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;!!!*/
    /* PC13 - GPO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~GPIO_CRH_CNF13; // CNF13 = 00 -> GP Out | Push-pull 
    GPIOC->CRH |= GPIO_CRH_MODE13; // MODE13 = 11 -> Maximum output speed 50 MHz
   
    return 0;
//    GPIOA->CRH	&= ~GPIO_CRH_CNF8; // CNF8 = 00 -> GP Out | Push-pull 
}

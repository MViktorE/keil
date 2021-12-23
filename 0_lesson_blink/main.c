#include "main.h"

int main(void){
	/* turn on clock for GPIO C*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	GPIOC->CRH |= GPIO_CRH_MODE13;
	volatile uint32_t i = 0;
	while(1){
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		while(i<0xFFFF)
			i++;
		i = 0;
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		while(i<0xFFFF)
			i++;
		i = 0;
	}
}
	

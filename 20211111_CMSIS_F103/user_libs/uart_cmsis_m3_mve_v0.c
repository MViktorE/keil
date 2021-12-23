#include "uart_cmsis_m3_mve_v0.h"

void USART1_IRQHandler(void){
	if (USART1->SR & USART_SR_RXNE){                             /* Rx is not empty */
		rxUartIt[rxCounter] = (uint8_t)(USART1->DR & 0x00FF);
        rxCounter++;
		if (rxCounter>RX_DATA_LEN-1){
			rxCounter = 0;
		}
	}
	else{
		if(USART1->SR & USART_SR_ORE){                           /* Overrun error */
		    (void)USART1->DR;
		}
	    else if (USART1->SR & USART_SR_FE){                      /* Framing error */
            (void)USART1->DR;
		}
	}
}

uint8_t uart_init(void){
    /* PA9 - Tx; PA10 - Rx; */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Turn on UART1 clocking
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // Turn on GPIOA clocking

    /* PA9 - Tx */
	/* AF Out | Push-pull | CNF - 10 MODE - 11*/
	GPIOA->CRH &= ~(0x3UL << GPIO_CRH_CNF9_Pos);
    GPIOA->CRH |=  (0x2UL << GPIO_CRH_CNF9_Pos); 
    GPIOA->CRH |=  (0x3UL << GPIO_CRH_MODE9_Pos); /* Maximum output speed 50 MHz */
    /* PA10 - Rx */
    /* Input pull-up  CNF = 0b10  MODE = 0 PxODR = 1 */ 
    GPIOA->CRH &= ~(0x3UL << GPIO_CRH_CNF10_Pos);
	GPIOA->CRH |=  (0x1UL << GPIO_CRH_CNF10_Pos);
	GPIOA->CRH &= ~GPIO_CRH_MODE10;

    /* Turn on interrupts */
	NVIC_EnableIRQ(USART1_IRQn); 
	
	/* UART1 setting */
    if(!(USART1->CR1 & USART_CR1_UE)){
        /* CR1 - Reset Val = 0*/
		USART1->CR1 = 0;
		USART1->CR1 |= USART_CR1_TE;     /* Transmitter is enabled */ 
		USART1->CR1 |= USART_CR1_RE;     /* Receiver is enabled and begins searching for a start bit Bit 1*/ 
		USART1->CR1 |= USART_CR1_RXNEIE; /* RXNE interrupt enable*/
    }
	else return 1;
    //Async Mode
    USART1->CR2 = 0;
	USART1->CR3 = 0;
    /* Set speed = 9600 Baud/s */
    /* USARTDIV = Fck / (16 * BAUD) = 36e6/(16*9600) = 234.375
     * USART_BRR = 234,375 * 16 = 3750  */
	USART1->BRR = 3750;
    //Enable
    USART1->CR1 |= USART_CR1_UE;
    return 0;
}

uint8_t uart_send(uint8_t * txData, uint16_t dataLength){
    uint16_t ind = 0;
    while (ind<dataLength){
        while (!(USART1->SR & USART_SR_TXE)){} /* while TXE != 1 */
        USART1->DR = (uint16_t)txData[ind];
        ind++;
    }
    return 0;
}

uint8_t uart_resive(uint8_t * rxData){
	uint8_t flag = 1;
	uint8_t ind = 0	;
	while (flag) {
    if (USART1->SR & USART_SR_RXNE) {
		rxData[ind] = (uint8_t)(USART1->DR & 0xFF);
		ind++;
	}
	else flag = 0;
	uart_send(rxData, 3);
    }
	return 0;
}

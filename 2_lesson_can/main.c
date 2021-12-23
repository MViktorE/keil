#include "main.h"

#define DATA_LENGTH_CODE 8

uint8_t rcc_init(void);
uint8_t can_init(void);
uint8_t can_send(uint8_t * pData, uint8_t dataLength);

int main(void){
	volatile uint16_t counter = 0;
	uint8_t data[] = "ABCDEFGHIJ9";

	rcc_init();
	can_init();
	while(1){
		can_send(data, sizeof(data));
		while(counter<0xFFFF)
            counter++;
        counter = 0;
	}
}

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

uint8_t can_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN; /* turn on clocking for CAN */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* turn on clocking for GPIOA */
	/* PA11 - CAN_RX */
	GPIOA->CRH	&= ~GPIO_CRH_CNF11;     /* CNF11 = 00 */
	GPIOA->CRH	|= GPIO_CRH_CNF11_1;	/* CNF11 = 10 -> AF Out | Push-pull (CAN_RX) */
	GPIOA->CRH 	|= GPIO_CRH_MODE11;     /* MODE11 = 11 -> Maximum output speed 50 MHz */
	/* PA12 - CAN_TX */
	GPIOA->CRH	&= ~GPIO_CRH_CNF12;	    /* CNF12 = 00 */
	GPIOA->CRH	|= GPIO_CRH_CNF12_1;	/* CNF12 = 10 -> AF Out | Push-pull (CAN_TX) */
    GPIOA->CRH 	|= GPIO_CRH_MODE12;     /* MODE12 = 11 -> Maximum output speed 50 MHz */

	CAN1->MCR |= CAN_MCR_INRQ;          /* Initialization Request */
	CAN1->MCR |= CAN_MCR_NART;          /* Not autoretranslate transmission */
	CAN1->MCR |= CAN_MCR_AWUM;          /* Automatic Wakeup Mode */
	/* clean and set Prescaler = 9 */
	CAN1->BTR &= ~CAN_BTR_BRP;          
	CAN1->BTR |= 8U << CAN_BTR_BRP_Pos;
	/* clean and set T_1s = 13, T_2s = 2 */
    CAN1->BTR &= ~CAN_BTR_TS1;
    CAN1->BTR |= 12U << CAN_BTR_TS1_Pos;
	CAN1->BTR &= ~CAN_BTR_TS2;
	CAN1->BTR |=   1U << CAN_BTR_TS2_Pos;
	
	CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;                    /* data frame */
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE;                    /* standart ID */ 
	CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;
	CAN1->sTxMailBox[0].TIR |= (0x556U << CAN_TI0R_STID_Pos);
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;                  /* length of data in frame */
	CAN1->sTxMailBox[0].TDTR |= (DATA_LENGTH_CODE << CAN_TDT0R_DLC_Pos);
	CAN1->MCR &= ~CAN_MCR_INRQ;                                  /* go to normal mode */ 
    return 0;	
}

uint8_t can_send(uint8_t * pData, uint8_t dataLength){
	uint16_t i = 0;
	uint8_t j = 0;
	while (!(CAN1->TSR & CAN_TSR_TME0)){  
		i++;
		if (i>0xEFFF) return 1;
	}
	i = 0;
	CAN1->sTxMailBox[0].TDLR = 0;
	CAN1->sTxMailBox[0].TDHR = 0;
	while (i<dataLength){
		if (i>(DATA_LENGTH_CODE-1)){
			CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;                 /* Transmit Mailbox Request */
			dataLength -= i;
			j++;
			while (!(CAN1->TSR & CAN_TSR_TME0)){                      /* Transmit mailbox 0 empty? */
				i++;
				if (i>0xEFFF) return 1;
			}
			if (CAN1->TSR & CAN_TSR_TXOK0){}                          /* Tx OK? */
			//else return ((CAN1->ESR & CAN_ESR_LEC)>>CAN_ESR_LEC_Pos); /* return Last error code */
			i = 0;
			CAN1->sTxMailBox[0].TDLR = 0;
			CAN1->sTxMailBox[0].TDHR = 0;
		}
		if (i<4){
			CAN1->sTxMailBox[0].TDLR |= (pData[i+j*DATA_LENGTH_CODE]*1U << (i*8));
		}
		else{
			CAN1->sTxMailBox[0].TDHR |= (pData[i+j*DATA_LENGTH_CODE]*1U << (i*8-32));
		}
		i++;
	}
	CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ; /* Transmit Mailbox Request */
	if (CAN1->TSR & CAN_TSR_TXOK0) return 0;
	else return ((CAN1->ESR & CAN_ESR_LEC)>>CAN_ESR_LEC_Pos); /* return Last error code */ 

}


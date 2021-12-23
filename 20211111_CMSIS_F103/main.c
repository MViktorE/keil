#include "main.h"

volatile uint32_t msTicks = 0;

uint8_t flagRxCan = 0;
uint32_t canRx0Data[3]={0};

int main(){
    rcc_init();
    rcc_per_en();    
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000); // 'prescaler' of SysTick for 1 ms
    gpio_init();
    can_init();
    NVIC_EnableIRQ(CAN1_RX0_IRQn);


    if (CAN1->TSR & CAN_TSR_RQCP0)
        CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_TXRQ;
    if (CAN1->TSR & CAN_TSR_TXOK0)
        CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_TXRQ;
    if (CAN1->TSR & CAN_TSR_TERR0)
        CAN1->TSR |=CAN_TSR_ABRQ0;
    
    
    while(1){
        CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ; /* Transmit Mailbox Request */
        if (flagRxCan){
            GPIOC->BSRR = GPIO_BSRR_BS13;
            mve_delay(250);
            GPIOC->BSRR = GPIO_BSRR_BR13;
            flagRxCan = 0;
        }
        mve_delay(1000);
    }
}

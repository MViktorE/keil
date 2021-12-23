#include "main.h"

volatile uint32_t msTicks = 0;
volatile uint8_t rxUartIt[RX_DATA_LEN] = {0};
uint8_t rxCounter = 0;

uint8_t  flagRxCan;
uint32_t canRx0Data[3];

int main(){
	/* Init */
	rcc_init();
	gpio_init();
	uart_init();
	can_init();
	SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000); // 'prescaler' of SysTick for 1 ms
	
	/*Private variables*/
	uint8_t currentToRC[] = "x0.val="; /* for inst.: 75.78 A */
	uint8_t voltageToRC[] = "n0.val=";  /* for inst.: 970 V */
	uint8_t counter1[1] = {0x30};
	uint8_t strEnd[3]={0xFF, 0xFF, 0xFF};
	volatile uint16_t dataFromNextion = 0;
	

	uint8_t Temp1[] = "123456789@A";


	while(1){
        if (rxCounter){
			rxUartIt[rxCounter] = 0;			
			rxCounter = 0;
		}
		dataFromNextion = line_recognition_ciam(rxUartIt);
		if (dataFromNextion == 0x8002){
			uart_send(currentToRC, (uint16_t)strlen((char*)currentToRC));
			uart_send(counter1, 1);
			uart_send(strEnd, 3);
			dataFromNextion = 0;
//			rxUartIt[0] = 0;
		}
		if (dataFromNextion == 0x8004){
			uart_send(voltageToRC, (uint16_t)strlen((char*)voltageToRC));
			uart_send(counter1, 1);
			uart_send(strEnd, 3);
			dataFromNextion = 0;
//			rxUartIt[0] = 0;
		}
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		mve_delay(50);
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		mve_delay(50);
		counter1[0]++;
		if (counter1[0]>0x39)
			counter1[0] = 0x30;
		
//		can1_send((uint8_t*)Temp1, sizeof(Temp1), 0);
		can1_send((uint8_t*)rxUartIt, sizeof(rxUartIt), 0);
		}
}

//		nextion_send((uint8_t*)"t0",(uint8_t*)"txt",(uint8_t*)counter1);

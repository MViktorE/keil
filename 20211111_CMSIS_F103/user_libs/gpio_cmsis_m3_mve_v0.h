/*
 * 2021.10.14 
 * Ver. 0
 * MVE
*/

#ifndef GPIO_CMSIS_M3_MVE_V0_H
#define GPIO_CMSIS_M3_MVE_V0_H

/*
GPIOx_CRL - from 0 to 7 pin
GPIOx_CRH - fron 8 to 15 pin
Reset value: 0x4444 4444 = 

Reg N: 3    2   |    1    0
     CNF1 CNF0  |  MODE1 MODE0
ResVal 0    1   |    0    0 - 
--------------------------------------------------
                    CNF1 CNF0  |
GP Out | Push-pull   0    0    | MODE != 0
GP Out | Open-drain  0    1    | MODE != 0
AF Out | Push-pull   1    0    | MODE != 0
AF Out | Push-pull   1    1    | MODE != 0
----------------------------------------------
Input  | Analog         0    0    | MODE = 0
Input  | Input floating 0    1    | MODE = 0 RESET VALUE?
Input  | Input pull-dow 1    0    | MODE = 0 PxODR = 0
Input  | Input pull-up  1    0    | MODE = 0 PxODR = 1
-----------------------------------------------------------
MODE:
01 - Maximum output speed 10 MHz
10 - Maximum output speed 2 MHz
11 - Maximum output speed 50 MHz
*/

#include "main.h"

uint8_t gpio_init(void);

#endif

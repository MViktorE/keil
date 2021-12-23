/*
 * line_recognition_ciam_mve_v0.h
 *
 *  Created on: Oct 1, 2021
 *      Author: mve
 */

#ifndef INC_LINE_RECOGNITION_CIAM_MVE_V0_H_
#define INC_LINE_RECOGNITION_CIAM_MVE_V0_H_


#include "main.h"



uint16_t line_recognition_ciam(volatile uint8_t inputSring[]);
/*
 * string commands that the function accepts(max 8 bit):
 *
 * "sc_99.99" - set output current to 99.99 A    return 9999
 * "sv_1300"  - set output voltage to 1300 В     return 1300+0x4000           (14 бит 1)
 * "ch_on"	  - turn on                          return 0b1000 0000 0000 0001 (0x8001)
 * "ch_off"   - turn off                         return 0b1000 0000 0000 0000 (0x8000)
 * "get_ch_c" - send current value               return 0b1000 0000 0000 0010 (0x8002)
 * "get_ch_v" - send voltage value               return 0b1000 0000 0000 0100 (0x8004)
 * "JKF2dwsk" - in all other cases               return 0xFFFF    
 */

#endif /* INC_LINE_RECOGNITION_CIAM_MVE_V0_H_ */

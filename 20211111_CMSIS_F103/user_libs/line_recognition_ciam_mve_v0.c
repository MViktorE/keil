/*
 * line_recognition_ciam_mve_v0.c
 *
 *  Created on: Oct 1, 2021
 *      Author: mve
 */
#include "line_recognition_ciam_mve_v0.h"

uint16_t line_recognition_ciam(volatile uint8_t inputSring[]){
	if (inputSring[0] == 's') {                         /*SET BRANCH*/
		if (inputSring[1] == 'c') {						/*CURRENT SET BRANCH*/
			float current = (float)atof(&inputSring[3]);
			return ((uint16_t)(current*100));
		}
		if (inputSring[1] == 'v') {						/*VOLTAGE SET BRANCH*/
			uint16_t voltage = (uint16_t)atoi(&inputSring[3]);
			return (voltage+0x4000);
		}
	}
	if (!strcmp("ch_on", inputSring)) 					/*TURN ON BRANCH*/
		return 0x8001;
	if (!strcmp("ch_off", inputSring))   				/*TURN OFF BRANCH*/
		return 0x8000;
	if (inputSring[0] == 'g') {							/*GET BRANCH*/
		if (!strcmp("get_ch_c", inputSring))			/*CURRENT GET BRANCH*/
			return 0x8002;
		if (!strcmp("get_ch_v", inputSring))			/*VOLTAGE GET BRANCH*/
			return 0x8004;
	}
	return 0xFFFF;
}

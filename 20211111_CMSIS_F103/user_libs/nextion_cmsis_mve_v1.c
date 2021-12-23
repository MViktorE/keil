/*
 * MVE_Nextion.c
 *
 *  Created on: Apr 12, 2021
 * 	latest version 20210930
 *      Author: MVE
 */

#include "nextion_cmsis_mve_v1.h"


void nextion_send (uint8_t *ID, uint8_t *extantion, uint8_t *string){
	char buf[50] = {0};
	uint8_t Cmd_End[3] = {0xFF,0xFF,0xFF};  // command end sequence
	if (ID[0]=='t'){
		sprintf (buf, "%s.%s=\"%s\"", ID, extantion, string);
	}
	else{
		sprintf (buf, "%s.%s=%s", ID, extantion, string);
	}
	uint16_t len = (uint16_t)strlen(buf);
	uart_send((uint8_t *)buf, len);
	uart_send(Cmd_End, 3);
}


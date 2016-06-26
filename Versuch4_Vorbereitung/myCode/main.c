/*
* main.c
*
* Created on: 11.06.2014
* Author: Fabian Alexander Wilms 735162
*
*/
#include <avr/io.h>
#include <libMIT.h>
#include "USART1.h"
#include "adc.h"
#include "timer.h"


int main(void) {
	MIT_initPorts_Ain_Bout();
	init_Timer0(TMODE_NORMAL);
	start_Timer0(1);
	unsigned char i = 1;
	while(1){
		wait_Timer0(TMODE_NORMAL);
		MIT_putByteLED_B(i%2);
		i++;
	}
	return 1;
}



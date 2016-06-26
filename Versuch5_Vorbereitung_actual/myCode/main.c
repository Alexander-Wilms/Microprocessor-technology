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
#include "seg7.h"

void main_V01(void)
{
	MIT_initPorts_Ain_Bout();
	while (1)
	{
		putByte(num2Seg7(2,1), PIO_PORTB);
	}
}

void main_V02(){
	sei(); // erlaube Interrupts
	MIT_initPorts_Ain_Bout();
	init_ADC_INT();
	start_ADC(FREERUN);
	while (1) {
		putByte(gADCres<<2, PIO_PORTB); // schmeisse 2 LSB weg
	}
}

void main_V03(){
	gData[0] = num2Seg7(1,0);
	gData[1] = num2Seg7(2,0);
	gData[2] = num2Seg7(3,0);
	gData[3] = num2Seg7(4,0);
	gOVLcomp = 512;
	MIT_initPorts_Ain_Bout();
	init_Timer0_INT(TMODE_NORMAL);
	start_Timer0(PRESC1024);
	sei();
	while (1) {

	}
}

void main_V04(){
	sei();
	gOcrHI = 1023;
	MIT_initPorts_Ain_Bout();
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC1024);
	while(1){
		// tue nichts
	}
}

int main(void) {
	main_V03();
	return 1;
}

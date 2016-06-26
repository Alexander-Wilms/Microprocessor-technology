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

void main01(){
	init_Timer0(TMODE_NORMAL);
	start_Timer0(PRESC1024);
	unsigned char i = 0b00001000;
	unsigned char a = 0b00000000;
	while(1){
		wait_Timer0(TMODE_NORMAL); // f = 4000000/1024
		MIT_putByteLED_B(i);
		wait_Timer0(TMODE_NORMAL);
		MIT_putByteLED_B(a);
	}
}

void main02(){
	init_Timer0(TMODE_CTC);
	start_Timer0(PRESC1024);
	unsigned char result;
	unsigned char i = 0b00001000;
	unsigned char a = 0b00000000;

	// initialisiere den ADC
	init_ADC();  // Schalte ADC ein

	// starte den ADC im Freerunning-Modus
	start_ADC(FREERUN); // Messung starten

	while(1){
		wait_ADC(); // Warte, bis Messung fertig ist
		result = read_ADC(BIT8);
		setOCRval_Timer0(result);

		wait_Timer0(TMODE_CTC); // f = 4000000/1024
		MIT_putByteLED_B(i);
		wait_Timer0(TMODE_CTC);
		MIT_putByteLED_B(a);
	}
}

void main03(){
	DDRC = 0xff;
	init_Timer0(TMODE_CTC);
	start_Timer0(PRESC128);
	unsigned char result;
	unsigned char highpattern = 0b01000000;
	unsigned char lowpattern = 0b00000000;

	// initialisiere den ADC
	init_ADC();  // Schalte ADC ein

	// starte den ADC im Freerunning-Modus
	start_ADC(FREERUN); // Messung starten

	while(1){
		wait_ADC(); // Warte, bis Messung fertig ist
		result = read_ADC(BIT8);

		int ocrhi=result;
		int ocrlo=255-ocrhi; // Sonderbehandlung

		setOCRval_Timer0(ocrhi);
		MIT_putByteLED_B(highpattern);
		PORTC = highpattern;
		wait_Timer0(TMODE_CTC); // f = 4000000/1024

		setOCRval_Timer0(ocrlo);
		MIT_putByteLED_B(lowpattern);
		PORTC = lowpattern;
		wait_Timer0(TMODE_CTC);
	}
}

void main04(){
	init_Timer0(TMODE_CTC);
	start_Timer0(PRESC1024);
	unsigned char keyport = 255;
	unsigned int tn = 1;
	unsigned char factor;
	unsigned char result;
	unsigned char i = 0b00001000;
	unsigned char a = 0b00000000;

	// initialisiere den ADC
	init_ADC();  // Schalte ADC ein

	// starte den ADC im Freerunning-Modus
	start_ADC(FREERUN); // Messung starten

	while(1){
		// prüfe, ob Taste gedrückt wurde
		keyport = MIT_look4key_A();

		// bestimme Nummer der gedrückten Taste (tn)
		// tn = MIT_getKeyNum(keyport); // Erhalte Nummer der gedrückten Taste aus Binärcode
										// funktionierte nicht
		switch(keyport){
		case 128: tn=7; break;
		case 64: tn=6; break;
		case 32: tn=5; break;
		case 16: tn=4; break;
		case 8: tn=3; break;
		case 4: tn=2; break;
		case 2: tn=1; break;
		case 1: tn=0; break;
		default: break;
		}
		factor = tn;

		wait_ADC(); // Warte, bis Messung fertig ist
		result = read_ADC(BIT8);
		setOCRval_Timer0(result);

		while(factor>0){
			wait_Timer0(TMODE_CTC); // f = 4000000/1024
			factor--;
		}

		MIT_putByteLED_B(i);
		factor = tn;
		if(tn!=0){
			while(factor>0){
				wait_Timer0(TMODE_CTC);
				factor--;
			}
			MIT_putByteLED_B(a);
		}
	}
}

int main(void) {
	MIT_initPorts_Ain_Bout();
	main03();
	return 1;
}

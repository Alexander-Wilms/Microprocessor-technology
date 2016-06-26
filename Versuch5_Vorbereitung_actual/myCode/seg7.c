#include "seg7.h"
#include <avr/io.h>

void initPort(ePORT port, ePORTDIR dir){
	unsigned int* pPort;
	unsigned int* pDDR;
	unsigned int ddr;

	switch (port)
	{
	case PIO_PORTA:
		pPort = (unsigned int*) &PORTA;
		pDDR = (unsigned int*) &DDRA;

		break;
	case PIO_PORTB:
		pPort = (unsigned int*) &PORTB;
		pDDR = (unsigned int*) &DDRB;

		break;
	case PIO_PORTC:
		pPort = (unsigned int*) &PORTC;
		pDDR = (unsigned int*) &DDRC;

		break;
	case PIO_PORTD:
		pPort = (unsigned int*) &PORTD;
		pDDR = (unsigned int*) &DDRD;

		break;
	case PIO_PORTE:
		pPort = (unsigned int*) &PORTE;
		pDDR = (unsigned int*) &DDRE;

		break;
	case PIO_PORTF:
		pPort = (unsigned int*) &PORTF;
		pDDR = (unsigned int*) &DDRF;

		break;
	case PIO_PORTG:
		pPort = (unsigned int*) &PORTG;
		pDDR = (unsigned int*) &DDRG;

		break;
	}

	if(dir==PIO_OUT){
		*pPort=0xff; // Auf Ausgabe initialisieren
		*pDDR=0xff; // Alle Port-Pins auf 1 setzen
	} else if(dir==PIO_IN){
		*pPort=0xff; // Auf Eingabe initialisieren
		*pDDR=0x00; // Alle Pullup-Widerstände einschalten
	}
}

void putByte(unsigned char byte, ePORT port){
	unsigned int* pPort;
	unsigned int* pDDR;
	unsigned int ddr;

	switch (port)
	{
	case PIO_PORTA:
		pPort = (unsigned int*) &PORTA;
		pDDR = (unsigned int*) &DDRA;
		break;
	case PIO_PORTB:
		pPort = (unsigned int*) &PORTB;
		pDDR = (unsigned int*) &DDRB;
		break;
	case PIO_PORTC:
		pPort = (unsigned int*) &PORTC;
		pDDR = (unsigned int*) &DDRC;
		break;
	case PIO_PORTD:
		pPort = (unsigned int*) &PORTD;
		pDDR = (unsigned int*) &DDRD;
		break;
	case PIO_PORTE:
		pPort = (unsigned int*) &PORTE;
		pDDR = (unsigned int*) &DDRE;
		break;
	case PIO_PORTF:
		pPort = (unsigned int*) &PORTF;
		pDDR = (unsigned int*) &DDRF;
		break;
	case PIO_PORTG:
		pPort = (unsigned int*) &PORTG;
		pDDR = (unsigned int*) &DDRG;
		break;
	}
	*pPort = ~byte;
}

unsigned char num2Seg7(unsigned char num, unsigned char dpon){
	num %= 10;
	unsigned char pattern[] = {
			0b00111111, // 0
			0b00000110, // 1
			0b01011011, // 2
			0b01001111, // 3
			0b01100110, // 4
			0b01101101, // 5
			0b01111101, // 6
			0b00000111, // 7
			0b01111111, // 8
			0b01101111, // 9
	};
	unsigned char returnpattern = pattern[num];
	if(dpon){
		returnpattern |= 0b10000000;
	}
	return returnpattern;
}

/*
* main.c
*
* Created on: 19.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/

// Bindet ein h-File ein, in dem alle IO-Adressen und Konstanten
// für den eingestellten Prozessor definiert sind z.B. DDRB, PORTB,
// PIND, PIND3 (3. Bit im IO-Register PIND) etc.
#include <avr/io.h>			// AVR header file for IO ports
#include "adc.h"
#include <stdio.h>

int main_vorbereitung(void)
{
	init_ADC();  // Schalte ADC ein

	// korrekte Parameterwerte
	eADCRUNMODE runmode = SINGLESHOT; // Eine Messung
	start_ADC(runmode); // Messung starten

	eADCRES res = BIT8; // Auflösung des Digitalwertes
	unsigned short result;
	result = read_ADC(res); // 512 bei 50 % bei 10 Bit
							// 128 bei 50 % bei 8 Bit

	stop_ADC();

	unsigned long a = 835;
	unsigned long * p = &a;

	unsigned char b;
	b = ulong2bcd_unpk(p); // b=5 - richtig & a=83 - richtig

	// Sonderfall Parameter = 0
	unsigned long a2 = 0;
	unsigned long * p2 = &a2;
	unsigned char b2;
	b2 = ulong2bcd_unpk(p2);  // b2=0 - richtig & a2=0 - richtig

	unsigned char c;
	c = ulong2bcd_pk(89); // Wird 1000 1001 - richtig

	// inkorrekter Parameterwert
	unsigned char c2;
	c2 = ulong2bcd_pk(5); // Wird 0 - richtig

	unsigned char c3;
	c3 = ulong2bcd_pk(100); // Wird 0 - richtig

	while (1) {
	}
}

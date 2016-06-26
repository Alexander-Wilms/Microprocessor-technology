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
#include "USART1.h"

int main(void)
{
	init_USART1();

	putc_USART1('a');

	unsigned char a = getc_USART1();

	unsigned char b = lookc_USART1();

	unsigned char* c = &b;
	puts_USART1(c);

	unsigned int d = ascii2num('5');

	unsigned char e = num2ascii(5);

	while (1) {
	}
}

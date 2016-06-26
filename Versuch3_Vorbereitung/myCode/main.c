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

	puts_USART1("First string\n\r");
	puts_USART1("First char: ");
	putc_USART1('a');
	puts_USART1("\n\r");

	puts_USART1("Waiting for input...\n\r");
	unsigned char a = getc_USART1();
	putc_USART1('\n');
	putc_USART1('\r');
	puts_USART1("The char you typed is\n\r");
	putc_USART1(a);

	unsigned char b = lookc_USART1();
	puts_USART1("\n\rIf you are too slow this will be ASCII char 255\n\r");
	putc_USART1(b);
	puts_USART1("\n\rThis as well\n\r");
	unsigned char* c = &b;
	puts_USART1(c);

	puts_USART1("\n\r\'5\' converted to an integer\n\r");
	unsigned int d = ascii2num('5');
	for(int i = 1; i<= d; i++)
	putc_USART1('I');

	puts_USART1("\n\rAn ASCII 5\n\r");
	unsigned char e = num2ascii(5);
	putc_USART1(e);

	while (1) {
	}
}

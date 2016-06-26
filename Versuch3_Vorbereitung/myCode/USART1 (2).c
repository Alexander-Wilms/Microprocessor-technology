/*
* USART1.c
*
* Created on: 30.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/
#include <avr/io.h>

// siehe S. 188 im Datenblatt

/* Initialisiert die serielle Schnittstelle
 * Parameter:
 * keine
 * Rückgabewert:
 * keiner
 */
void init_USART1() {
	// siehe S. 193 im Datenblatt
	// Konfiguration der Baud-Rate von 9600 Baud
	UBRR1L = 0;
	UBRR1H = 0;
	// Sender einschalten
	// \/ können nicht geschrieben werden
	UCSR1B |= (1<<TXEN1);
	// Empfänger einschalten
	UCSR1B |= (1<<RXEN1);
	// 8 Datenbits
	UCSR1B |= (1<<UCSZ11)|(1<<UCSZ10);
	// 2 Stopbits
	UCSR1B |= (1<<USBS1);
	// keine Parität
	UCSR1C |= (0<<UPM10)|(0<<UPM11);
	// asynchroner Modus
	UCSR1C |= (0<<UMSEL1);
}

/* Sendet ein Byte (ASCII-Zeichen) über USART1
 * Parameter:
 * data
 * Rückgabewert:
 * keiner
 */
void putc_USART1(unsigned char data) {
	int done = 0;
	while(!done) {
		// Sende-Statusregister des USART1 abfragen
		if(UCSR1A & (1<<TXC1)) {
			// schreibe in Datenregister für Sende-Daten
			UDR1 = data;
			done = 1;
		}
	}
}

/* Wartet so lange, bis ein Byte empfangen wurde
 * Parameter:
 * keine
 * Rückgabewert:
 * empfangenes Zeichen
 */
unsigned char getc_USART1(void) {
	unsigned char a;
	int done = 0;
	while(!done) {
		// Empfangs-Statusregister des USART1 abfragen
		if(UCSR1A & (1<<RXC1)) {
			// lese Datenregister für empfangene Daten
			a = UDR1;
			done = 1;
		}
	}
	return a;
}

/* Schaut nach, ob ein Byte empfangen wurde
 * Parameter:
 * keine
 * Rückgabewert:
 * 255		nichts empfangen
 * sonst	empfangenes Zeichen
 */
unsigned char lookc_USART1(void) {
	unsigned char a;
	// lese Datenregister für empfangene Daten
	if(UCSR1A & (1<<RXC1)) {
		a = UDR1;
		return a;
	} else {
		return 255;
	}
}

/* Gibt eine Zeichenkette aus
 * Parameter:
 * pStr
 * Rückgabewert:
 * keiner
 */
void puts_USART1(unsigned char *pStr) {
	while(*pStr != 0x00) {
		putc_USART1(*pStr);
		pStr++;
	}
}

/* Wandelt eine ASCII-Ziffer in eine Dezimal-Ziffer um
 * Parameter:
 * data
 * Rückgabewert:
 * Dezimal-Ziffer
 */
unsigned int ascii2num(unsigned char data) {
	return (unsigned int) data - 48;
}

/* Wandelt eine Dezimal-Ziffer in eine ASCII-Ziffer um
 * Parameter:
 * data
 * Rückgabewert:
 * ASCII-Code der Ziffer
 */
unsigned char num2ascii(unsigned int data) {
	return (unsigned char) data + 48;
}

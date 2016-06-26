/*
* adc.c
*
* Created on: 19.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/

#include "adc.h"
#include <avr/io.h>
#define ADFR 5
// Hilfreich: http://www.kner.at/home/40.avr/Beispielprogramme/ADC.Theorie.html

/* schaltet den ADC ein und konfiguriert ihn folgendermaßen:
* Wandler-Ergebnis rechtsbündig
* Uref AVCC
* Kanal ADC0, single ended
* Parameter:
* keine
* Rueckgabe:
* keine
*/
void init_ADC() {
	ADCSRA |= (1<<ADEN); // ADC einschalten OK
	ADCSRA |= (1<<ADPS2);// Prescaler auf 16 setzen OK
	ADMUX |= (1<<REFS1)|(1<<REFS0); // Spannungsreferenz Uref intern AVCC mit externer Kapazität
}

/* Setzt den Running-Modus und startet die Wandlung
 * Parameter:
 * mode
 * Rueckgabe:
 * keine
 */
void start_ADC(eADCRUNMODE mode) {
	switch(mode) {
		case FREERUN:
			ADCSRA |= (1<<ADFR); // free-running-mode ein
			break;
		case SINGLESHOT:
			ADCSRA &= (~(1<<ADFR)); // single-shot-mode ein
			break;
		default:				 // Fallback
			ADCSRA &= (~(1<<ADFR)); // single-shot-mode ein
			break;
	}
	ADCSRA |= (1<<ADSC); // Starte Wandlung
}

/* Stoppt die Wandlung
 * Parameter:
 * keine
 * Rueckgabe:
 * keine
 */
void stop_ADC(){
	ADCSRA &= (~(1<<ADFR)); // single shot
}

/* Wartet auf das Ende einer Wandlung
 * Parameter:
 * mode
 * Rueckgabe:
 * keine
 */
void wait_ADC(){
	while(!(ADCSRA & (1<<ADIF))); // Warte, bis Wandlung abgeschlossen ist

	ADCSRA |= (1<<ADIF); // Setze ADIF-Bit zurück
}

/* Liest den gewandelten 10-Bit-Digitalwert aus
 * Parameter:
 * res
 * Rueckgabe:
 * unsigned short
 */
unsigned short read_ADC(eADCRES res){
	ADCSRA |= (1<<ADSC); // Konversion starten
	wait_ADC(); // Warte auf Ende
	uint16_t lb = ADCL; // funktioniert nicht
	uint16_t hb = ADCH; // funktioniert nicht
	hb <<= 8; // Schiebe high Byte um 1 Byte nach links
	hb |= lb; // funktioniert nicht
	if(res == BIT8) // Die zwei LSB wegschmeissen
		hb >>= 2;
	ADCSRA |= (1<<ADSC); // Clear ADIF
	return (unsigned short) hb; // ypecast, damit es passt
}

/* Liefert die niederwertigste Ziffer eines Wertes
 * Parameter:
 * *value
 * Rueckgabe:
 * unsigned char
 */
unsigned char ulong2bcd_unpk(unsigned long* value){
	unsigned long z;
	unsigned long r;
	if(*value == 0){
		// do nothing
		z = 0;
	} else {
		z = *value%10;
		r = (*value - z)/10;
		*value = r;//*10+z;
	}
	return z;
}

/* Wandelt einen zweistelligen Wert vom Typ unsigned_long
 * in eine gepackte BCD-Zahl um
 * Parameter:
 * value
 * Rueckgabe:
 * unsigned char
 */
unsigned char ulong2bcd_pk(unsigned long value){
	if (value > 9 && value < 100){ // Zweistellige Zahl
		unsigned char einser = value % 10;
		unsigned char zehner = value / 10;
		unsigned char bcdzahl;
		bcdzahl = zehner;
		bcdzahl <<= 4;
		bcdzahl |= einser;
		return bcdzahl;
	} else
		return 0;
}

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
	ADMUX |= /*(1<<REFS1)|*/(1<<REFS0); // Spannungsreferenz Uref intern AVCC mit externer Kapazität
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
	uint16_t lb = ADCL;
	uint16_t hb = ADCH;
	hb <<= 8; // Schiebe high Byte um 1 Byte nach links
	hb |= lb;
	if(res == BIT8) // Die zwei LSB wegschmeissen
		hb >>= 2;
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

/* Wandelt einen zweistelligen Wert vom Typ unsgned_long
 * in eine gepackte BCD-Zahl um
 * Parameter:
 * value
 * Rueckgabe:
 * unsigned char
 */
unsigned char ulong2bcd_pk(float value){
	if (value < 100){ // maximal zweistellige Zahl
		unsigned char einser = (unsigned char)value % 10;
		value = value * 10;
		unsigned char zehner = (unsigned char) value % 10;
		unsigned char bcdzahl;
		bcdzahl = einser;
		bcdzahl <<= 4;
		bcdzahl |= zehner;
		return bcdzahl;
	} else
		return 0;
}

/* Wandelt einen Messwert in die entsprechende Spannung
 * Parameter:
 * value, res, uref
 * Rueckgabe:
 * foat
 */
float ushort2Volt(unsigned short value, eADCRES res, float uref){
	float u;
	if(res == BIT10)
	{
		u = value*(uref/1023);
	} else {
		u = value*(uref/255);
	}
	return u;
}

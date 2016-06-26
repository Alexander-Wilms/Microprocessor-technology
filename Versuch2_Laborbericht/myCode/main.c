/*
* main.c
*
* Created on: 21.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/

// Bindet ein h-File ein, in dem alle IO-Adressen und Konstanten
// für den eingestellten Prozessor definiert sind z.B. DDRB, PORTB,
// PIND, PIND3 (3. Bit im IO-Register PIND) etc.
#include <avr/io.h>			// AVR header file for IO ports
#include "adc.h"
#include <libMIT.h>

float ushort2Volt(unsigned short value, eADCRES res, float uref);

void main_01(void){
	// Messung im Free running mode
	init_ADC();  // Schalte ADC ein
	MIT_initPorts_Ain_Bout();

	eADCRUNMODE runmode = FREERUN; // Fortlaufende Messung
	start_ADC(runmode); // Messung starten

	eADCRES res = BIT8; // Auflösung des Digitalwertes
	unsigned short result;
	while(1){
		wait_ADC();
		result = read_ADC(res); // 512 bei 50 % bei 10 Bit
								// 128 bei 50 % bei 8 Bit

		// Messergebnis auf LEDs anzeigen
		MIT_putByteLED_B(result);
	}
	stop_ADC();
}

void main_02(void){
	// Messung im Free running mode
	init_ADC();  // Schalte ADC ein
	MIT_initPorts_Ain_Bout();

	eADCRUNMODE runmode = FREERUN; // Fortlaufende Messung
	start_ADC(runmode); // Messung starten

	eADCRES res = BIT10; // Auflösung des Digitalwertes
	unsigned short result;
	while(1){
		wait_ADC();
		result = read_ADC(res); // 512 bei 50 % bei 10 Bit
								// 128 bei 50 % bei 8 Bit

		// Messergebnis auf LEDs anzeigen
		long min = 0;
		long max = 1023;
		unsigned char bar = MIT_long2bar((long)result,min,max);
		MIT_putByteLED_B(bar);
	}
	stop_ADC();
}

void main_03(void){
	MIT_initPorts_Ain_Bout();
	init_ADC();  // Schalte ADC ein
	while(1){
		if(MIT_wait4key_A()){ // Falls eine Taste gedrückt wurde...
			// Messung im Single shot mode
			eADCRUNMODE runmode = SINGLESHOT; // Fortlaufende Messung
			start_ADC(runmode); // Messung starten

			//eADCRES res = BIT8; // Auflösung des Digitalwertes
			unsigned short result1;
			wait_ADC();
			eADCRES resolution = BIT10;
			result1 = read_ADC(resolution); // 512 bei 50 % bei 10 Bit
									   // 128 bei 50 % bei 8 Bit
			float result2;
			result2 = ushort2Volt(result1,resolution,5);

			unsigned char result3_1;
			result3_1 = ulong2bcd_pk(result2);


			// Messergebnis auf LEDs anzeigen
			MIT_putByteLED_B(result3_1);
			stop_ADC();
		}
	}
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

void wait()
{
	unsigned long cntLoops = 1000;
	unsigned int nwait = 0xffff;
	while(cntLoops != 0)
	{
		while(nwait != 0)
		{
			nwait--;
		}
		cntLoops--;
	}
	return;
}


void main_04(void){
	// initialisiere Anzeige-Modus (dMode) mit 0
	unsigned char dMode = 0;
	// initialisiere Running-Modus (rMode) mit FREERUN
	eADCRUNMODE rMode = FREERUN; // Fortlaufende Messung
	// initialisiere alle weiteren benötigten Variablen
	unsigned char keyport = 255;
	unsigned int tn = 4;
	unsigned char result;

	// initialisiere die Ports für Tasten und LEDs
	MIT_initPorts_Ain_Bout();

	// initialisiere den ADC
	init_ADC();  // Schalte ADC ein

	// starte den ADC im Freerunning-Modus
	start_ADC(rMode); // Messung starten

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

		switch(tn){
		case 0:
			// stop
			// setze rMode auf SINGLESHOT
			rMode = SINGLESHOT;
			// ADC stoppen
			stop_ADC();
			// Messwert auf 0 setzen
			result = 0;
			break;
		case 1:
			// hold
			// setze rMode auf SINGLESHOT
			rMode = SINGLESHOT;
			// ADC stoppen
			stop_ADC();
			break;
		case 2:
			// Free-Running einschalten
			// setze rMode auf FREERUN
			rMode = FREERUN;
			// ADC im Freerunning mode starten
			start_ADC(rMode); // Messung starten
			wait_ADC(); // Warte, bis Messung fertig ist
			result = read_ADC(BIT8);
			break;
		case 3:
			// Single shot-Messung
			// setze rMode auf SINGLESHOT
			rMode = SINGLESHOT;
			// eine Messung im Single-Shot-Modus durchführen und Messwert einlesen
			start_ADC(rMode); // Messung starten
			wait_ADC(); // Warte, bis Messung fertig ist
			result = read_ADC(BIT8);
			break;
		case 4:
			// do nothing
			break;
		default:
			// tn > 4
			// Anzeigemodus wählen
			// setze dMode auf tn
			dMode = tn;
			// schalte zur Taste gehörende LED für 1 s ein
			MIT_putByteLED_B(keyport);
			wait();
			break;
		}
		tn = 4; // Tastendruck zurücksetzen

		if(rMode == FREERUN){
			// eine Messung im Free-Running-Modus durchführen und Messwert speichern
			wait_ADC(); // Warte, bis Messung fertig ist
			result = read_ADC(BIT8);
		}

		switch(dMode) {
		case 5:
			// Messwert binär (8 Bit) anzeigen
			MIT_putByteLED_B(result);
			break;
		case 6: ; // C will das so
			float resultvolt;
			unsigned char resultbcd;
			// Messwert in Volt umrechnen
			resultvolt = ushort2Volt(result,BIT8,5);
			// Messwert als gepackte BCD-Zahl anzeigen
			resultbcd = ulong2bcd_pk(resultvolt);
			// Messergebnis auf LEDs anzeigen
			MIT_putByteLED_B(resultbcd);
			break;
		case 7: ;
			long min = 0;
			long max = 255;
			unsigned char bar;
			// Messwert als Balken anzeigen
			bar = MIT_long2bar(result,min,max);
			MIT_putByteLED_B(bar);
			break;
		default:
			break;
		}
	}
}
/* Aufgabe 4:	Aufgetretene Fehler		Korrektur
 *
 * 				LEDs zeigten nur 1/4	immer 8 Bit Auflösung benutzen
 * 				des Messwertes an
 *
 * 				MIT_getKeyNum schien
 * 				nicht wie erwartet
 * 				zu funktionieren		Mapping von binär -> dezimal von Hand
 *
 * 				Variablendeklaration	erst ein leeres Statement ";" schreiben
 * 				durfte nicht direkt
 * 				hinter Label stehen
 */

int main(void)
{
	main_04();
	return 1;
}


/*
* main.c
*
* Created on: 11.06.2014
* Author: Fabian Alexander Wilms 735162
*
*/
#include <avr/io.h>
#include "USART1.h"
#include "adc.h"
#include <libMIT.h>

// Sendet das Zeichen 'A' ununterbrochen über USART1
void main_01(void) {
	init_USART1(); // !!!
	while(1)
	putc_USART1('A');
}

// Wartet auf Tastatureingabe, empfaengt zeichen
// und schickt es zurueck
void main_02(void) {
	init_USART1();
	unsigned char input;
	while(1) {
		input = getc_USART1();
		putc_USART1('\n');
		putc_USART1('\r');
		putc_USART1(input);
	}
}

// Wartet auf tastendruck und macht entsprechende Ausgabe
void main_03(void) {
	init_USART1();
	unsigned char input;
	while(1) {
		input = getc_USART1();
		switch (input) {
		case 'v':
			puts_USART1("MIT-Digitalvoltmeter : SW-Rev. 0.1\r\n");
			break;

		case 'e':
			puts_USART1("Einzelmessung gestartet\r\n");
			break;

		case 'f':
			puts_USART1("Dauermessung gestartet\r\n");
			break;

		case 'h':
			puts_USART1("Dauermessung Pause\r\n");
			break;

		case 's':
			puts_USART1("Dauermessung angehalten\r\n");
			break;

		case 'b':
			puts_USART1("Displaymodus: Balken\r\n");
			break;

		case 'c':
			puts_USART1("Displaymodus: BCD\r\n");
			break;

		case 'i':
			puts_USART1("Displaymodus: Binaer\r\n");
			break;

		case 'p':
			puts_USART1("Displaymodus: PC\r\n");
			break;

		default:
			puts_USART1("unbekannter Befehl\r\n");
			break;
		}
	}
}

/* rechnet digitalen Messwert in Spannung um und zeigt diesen auf dem Serial Terminal an
 *
 */
void displayVoltage_PC(unsigned long value) {
	float voltage = ushort2Volt(value,BIT8,5);
	unsigned long voltagelong = (long) (voltage*10); // sonst verlieren wir die Nachkommastelle
	unsigned long* voltagePtr= &voltagelong; // ulong2bcd_unpk erwartet Zeigerargument
	unsigned char resultbcd = ulong2bcd_unpk(voltagePtr);
	char nachkomma = num2ascii(resultbcd);
	resultbcd = ulong2bcd_unpk(voltagePtr);
	char vorkomma = num2ascii(resultbcd);

	putc_USART1('\r');
	putc_USART1(vorkomma);
	putc_USART1(',');
	putc_USART1(nachkomma);
	putc_USART1(' ');
	putc_USART1('V');
}

void main_04(void) {
	init_USART1();
	displayVoltage_PC(1023);
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

void main_05(void) {
	// initialisiere Anzeige-Modus (dMode) mit 0
	unsigned char dMode = 0;
	// initialisiere Running-Modus (rMode) mit FREERUN
	eADCRUNMODE rMode = FREERUN; // Fortlaufende Messung
	// initialisiere alle weiteren benötigten Variablen
	unsigned char keyport = 255;
	unsigned int tn = 0;
	unsigned char result;

	// initialisiere die Ports für Tasten und LEDs
	MIT_initPorts_Ain_Bout();

	// initialisiere USART1
	init_USART1();

	// initialisiere den ADC
	init_ADC();  // Schalte ADC ein

	// starte den ADC im Freerunning-Modus
	start_ADC(rMode); // Messung starten

	// Einschaltmeldung auf USART1 ausgeben
	puts_USART1("\rUSART1 eingeschaltet\n\r");

	while(1){
		// prüfe, ob Taste gedrückt wurde
		keyport = MIT_look4key_A();

		// Taste gedrückt
		if(keyport != 255) {
			// bestimme Nummer der gedrückten Taste (tn)
			// tn = MIT_getKeyNum(keyport); // Erhalte Nummer der gedrückten Taste aus Binärcode
			switch(keyport) {
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
		} else if(keyport == 255) {
			// keine Taste gedrückt

			//Taste vom PC einlesen
			unsigned char input = lookc_USART1();

			// gültige Taste gedrückt
			if(	input == 'b' ||
				input == 'c' ||
				input == 'i' ||
				input == 'p' ||
				input == 'e' ||
				input == 'f' ||
				input == 'h' ||
				input == 's' ||
				input == 'v') {
				// v gedrückt
				if(input == 'v') {
					puts_USART1("\rUSART1 eingeschaltet\n\r");
				} else {
					switch(input){
					case 'b': tn=7; break;
					case 'c': tn=6; break;
					case 'i': tn=5; break;
					case 'p': tn=4; break;
					case 'e': tn=3; break;
					case 'f': tn=2; break;
					case 'h': tn=1; break;
					case 's': tn=0; break;
					default: break;
					}
					// Meldung auf USART1 ausgeben
					switch (input) {
					case 'v': puts_USART1("\n\rMIT-Digitalvoltmeter : SW-Rev. 0.1\r\n"); break;
					case 'e': puts_USART1("\n\rEinzelmessung gestartet\r\n"); break;
					case 'f': puts_USART1("\n\rDauermessung gestartet\r\n"); break;
					case 'h': puts_USART1("\n\rDauermessung Pause\r\n"); break;
					case 's': puts_USART1("\n\rDauermessung angehalten\r\n"); break;
					case 'b': puts_USART1("\n\rDisplaymodus: Balken\r\n"); break;
					case 'c': puts_USART1("\n\rDisplaymodus: BCD\r\n"); break;
					case 'i': puts_USART1("\n\rDisplaymodus: Binaer\r\n"); break;
					case 'p': puts_USART1("\n\rDisplaymodus: PC\r\n\n"); break;
					}
				}
			} else {
				// Taste gedrückt, aber ungültig
				if (input != 255) {
					// 'Unbekannter Befehl' auf USART1 ausgeben
					puts_USART1("\n\rUnbekannter Befehl");
				} else {
					// keine Taste gedrückt
					// Tu nichts
				}
				// Tastencode auf 255 setzen
				keyport = 255;
			}
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
				// tn zurücksetzen, sonst würde die Singleshot-Messung immer wieder durchgeführt
				tn = dMode;
				break;
				// Im Singleshot-Modus muss man nach Änderung des dMode eine weitere Messung durchführung
				// Sonst gäbee es keinen Unterschied zum Hold-Modus
				// Ist das korrekt?
			//case 4:
				// do nothing
				//break;
			default:
				// tn > 3
				// Anzeigemodus wählen
				// setze dMode auf tn
				dMode = tn;
				// schalte zur Taste gehörende LED für 1 s ein
				if(keyport != 255)
					MIT_putByteLED_B(keyport);
				wait();
				break;
			}
			//tn = 4; // Tastendruck zurücksetzen


		if(rMode == FREERUN){
			// eine Messung im Free-Running-Modus durchführen und Messwert speichern
			wait_ADC(); // Warte, bis Messung fertig ist
			result = read_ADC(BIT8);
		}

		switch(dMode) {
		case 4:
			puts_USART1("\r");
			displayVoltage_PC(result);
			break;
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

int main(void) {
	main_05();
	return 1;
}


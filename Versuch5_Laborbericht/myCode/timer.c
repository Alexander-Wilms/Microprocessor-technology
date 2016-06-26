#include "timer.h"
#include "seg7.h"
#include <avr/io.h>
unsigned int gOVLcomp = 0;
unsigned char gData[4];
unsigned int gOcrHI = 0;


void init_Timer0_INT(eTIMERMODE mode)
{
	init_Timer0(mode);
	// Setze passendes Interrupt-Enable-Bit
	if(mode==TMODE_NORMAL){
		TIMSK |= (1<<TOIE0);
	} else if (mode==TMODE_CTC){
		TIMSK |= (1<<OCIE0);
	}
}

ISR(TIMER0_OVF_vect){
	// cntISRCalls wird irgendwie auf 0 gesetzt
	static int idx = 0;
	static int cntISRCalls = 0;
	if(gOVLcomp == cntISRCalls){
		//cntISRCalls = 0;
		putByte(gData[idx], PORTB);
		idx++;
		idx %= 4;
	} else {
		cntISRCalls++;
	}
}

ISR(TIMER0_COMP_vect){
	static int CTRLval = 1;
	static int idx = 0;
	if(OCR0 != gOcrHI){
		CTRLval <<= 1;
		if(CTRLval > 0x08){
			CTRLval = 0x01;
		}
		PORTB = ~CTRLval;
		PORTC = CTRLval;
		idx++;
				idx %= 4;
		PORTD=gData[idx];

		//putByte(gData[0], PORTD);
		OCR0 = gOcrHI;
	} else {
		PORTB = 0xff;
		PORTC = 0x00;
		OCR0 = 255-gOcrHI;
	}
}

/*
ISR(TIMER0_COMP_vect){
	static int CTRLval = 1;
	static int idx = 0;
	if(OCR0 != gOcrHI){
		CTRLval <<= 1;
		if(CTRLval > 0x08){
			CTRLval = 0x01;
		}
		PORTC = ~CTRLval;
		putByte(gData[idx], PORTD);
		OCR0 = gOcrHI;
		idx++;
		idx %= 4;
	} else {
		PORTC = 0xff;
		OCR0 = 255-gOcrHI;
	}
}
 */

/*
* Konfiguriert den Waveform Generation Mode des Timer0 in Abh�ngigkeit vom �bergebenen Parameterwert. Der Typ des
* Parameters soll wie im ADC-Versuch als Aufz�hlungstyp (enum) definiert werden (siehe auch entsprechende Hinweise zu
* Versuch 2).
* Hinweis: Die Einstellung des Prescalers soll erst beim Start des Timers erfolgen (siehe unten).
* Parameter:
* mode
* einzustellender Waveform Generation Mode
* TMODE_NORMAL ... Normal-Modus, Timer z�hlt bis 255 im n�chsten Z�hlschritt beginnt er durch
* �berlauf erneut bei 0
* TMODE_CTC ...... Clear-Timer-on-Compare-Match-Modus, Timer z�hlt bis zu dem Wert, der im
* OCR0-Register eingestellt ist und beginnt im n�chsten Schritt erneut bei 0
*/
void init_Timer0(eTIMERMODE mode){
	if(mode == TMODE_NORMAL)
		TCCR0 &= ~((1 << WGM01)|(1 << WGM00));
	else
		TCCR0 |= (1 << WGM01);
}

/*
* Durch Einstellung des Prescalers kann der Timer gestartet oder gestoppt werden (siehe Datenblatt S. 106). Die Funktion
* startet den Timer durch Setzen des Prescalers entsprechend dem �bergebenen Wert. Da der Prescaler nicht auf jeden
* beliebigen Wert gesetzt werden kann, �bernimmt die Funktion einen enum-Wert, anhand dessen die Funktion eindeutig
* feststellen kann, welcher der existierenden Prescaler-Werte gesetzt werden soll.
* Hinweis: Werden die enum-Werte so definiert, dass sie den Bit-Mustern aus der Tabelle im Datenblatt S. 106 entsprechen,
* reduziert sich der Programmieraufwand f�r die Funktion auf eine Zeile Code, z.B. PRESC128 hat den enum-Wert 5.
*/
void start_Timer0(ePRESCALER prescaler){
	TCCR0 &= (~(1<<CS02)) & (~(1<<CS01)) & (~(1<<CS00)); // Ansatz eines Laborbetreuers
	TCCR0 &= 248; // 11111000 // mein Ansatz (beides funktioniert)
	TCCR0 |= prescaler;
}

/*
 * Stoppt den Timer, indem sie den Prescaler auf 0 setzt (siehe Datenblatt S. 106).
 */
void stop_Timer0(){
	TCCR0 &= (~(1<<CS02)) & (~(1<<CS01)) & (~(1<<CS00));
}

/*
 * Setzt den Timer zur�ck, indem sie das TCNT0-Register auf 0 setzt.
 */
void clear_Timer0(){
	TCNT0 = 0;  // Momentaner Wert des Z�hlers // ganzes Register
}

/*
* Wartet durch Polling darauf, dass die eingestellte Zeit abgelaufen ist. Im NORMAL-Modus, setzt der Timer bei Ablauf der
* Zeit das TOV0-Bit, im CTC-Modus das OCF0-Bit. Das jeweilige Bit muss dann wieder zur�ckgesetzt werden.
* Hinweis: Zum R�cksetzen des jeweiligen Bits auf 0 muss eine 1 in das Bit geschrieben werden (siehe auch Datenblatt)!
*/
void wait_Timer0(eTIMERMODE mode){
	switch (mode) {
	case TMODE_NORMAL:
		while (!(TIFR & (1 << TOV0))); // Warte, bis Z�hler �berl�uft
		TIFR = (1 << TOV0); //TOV0 zur�cksetzen
		break;
	case TMODE_CTC:
		while(!(TIFR & (1<<OCF0))); // Warte, bis Vergleichswert erreicht ist
		TIFR = (1 << OCF0); //OCF0 zur�cksetzen
		break;
	}
}

/*
* Setzt das OCR0-Register (Output Compare Register) des Timers auf den �bergebenen Wert. Im CTC-Modus z�hlt der Timer
* bis zu diesem Wert, setzt das OCF0-Bit und beginnt dann das Z�hlen wieder bei 0.
*/
void setOCRval_Timer0(unsigned char ocrval){
	OCR0 = ocrval;   // Vergleichswert setzen // ganzes Register
}

/*
 * Versuch_ASM.S
 *
 *  Created on: 03.04.2012
 *      Author: mit
 */

/*
	Definitionen fuer eingestellten Controller

	s. ProjectProperties - AVR - Target Hardware
*/
#include <avr/io.h>
.file "myCode/Versuch0_ASM.s" // Dateiname muss uebereinstimmen!

; Konstantendefinitionen
/*A = 7				// Variante 1
.set B, 10			// Variante 2
.set C, 200*/
.equ CNT_WAITLOOPS=2

.data
var1:	.byte 1
var2:	.byte 1
var3:	.byte 1

; Code für das Flash (CSEG)
.text
Versuch0:
	; Stackpointer initialisieren
	ldi	r16,LOW(RAMEND)
	sts SPL,r16
	ldi r16,HIGH(RAMEND)
	sts SPH,r16

	; ////////////////////////////////////////////////////////////
	; Berechnung A+B-C
	/*ldi r16, A // A in r16 schreiben
	ldi r17,B // B in r17 schreiben
	ldi r18,C // C in r18 schreiben
	add r16,r17 // r17 zu r16 addieren und in r16 schreiben
	sub r16,r18*/ // r18 von r16 abziehen und in r16 schreiben

	lds r16,var1
	lds r17,var2
	add r16,r17
	sts var1,r16

	lds r17,var3
	sub r16,r17
	sts var1,r16

;//////////////////////////////////////////////////////////////
; Anzeige des Ergebnisses auf der LED-Zeile
	ldi r17, 0xff
	sts DDRB, r17
	com r16
	sts PORTB, r16

;//////////////////////////////////////////////////////////////
 ; der Mikroprozessor wird beschäftigt
//doNothing:
	//jmp doNothing ; Endlosschleife

; Lauflicht

	ldi r24,1
	com r24
	sec // Carry-Flag setzen

loop:
	sts PORTB,r24 // Inhalt
	rol r24 // Rotiere
	call wait
	jmp loop // Wiederhole

;////////////////////////////////////////////////////////////////////////
; Unterprogramm
; wartet, indem der Prozessor 65535 * WAITLOOPS die Schleifen abarbeitet
wait:
	lds r27, SREG
	ldi r26, CNT_WAITLOOPS 	; wie oft soll der 16-Bitwert in r25:r24
						; auf 0 heruntergezählt werden? (Wartezähler laden)
next_wait:
	ldi r24, 0x02 		; lädt den Startwert der inneren Zählschleife
	ldi r25, 0x00

wait_loop:
	sbiw r24,1
	brne wait_loop 		; wenn nicht, springt wieder zu wait_loop
	dec r26 			; wenn ja, dekrementiert den Wartezähler
	brne next_wait 		; wenn nicht 0 => Sprung zum erneuten Herunterzählen
						; des 16-Bit-Wertes
	sts SREG, r27
	ret 				; kehrt zum aufrufenden Programm zurück

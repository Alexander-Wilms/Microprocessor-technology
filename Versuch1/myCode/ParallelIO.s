/*
* ParallelIO.s
*
* Created on: 11.03.2014
* Author: Fabian Alexander Wilms 735162
*
*/
;enth�lt alle Definitionen f�r den eingestellten Prozessor
#include <avr/io.h>
.text ; Programmsegment (ROM)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; Funktionen nach au�en bekannt machen
.global initPorts_Ain_Bout
.global putByteLED_B
.global wait_ms
.global wait4key_A
.global wait
.global next_wait // �berfl�ssig?
.global wait_loop
.global wait_loop_key

.set CNT_WAITLOOPS, 5

; hier je einen weiteren Eintrag f�r die anderen Funktionen
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; Implementierung der Funktionen
; mit Kommentar zum Zweck der Funktion und zur Beschreibung der verwendeten Register (welche
;Register
; enthalten Parameterwerte, welche R�ckgabewerte und welche werden lokal genutzt)
; Beispiel:
/*
* Initialisierung der Ports A und B
* PortA: Eingabe (Anschluss der Tasten)
* PortB: Ausgabe (Anschluss der LEDs)
*
* Register:
* lokal: r16 - Hilfsregister
* Parameter: keine
* R�ckgabe: keine
*/
initPorts_Ain_Bout: ; alles puschn, was kein parameter ist, und verwendet wird
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16

	ldi r16, 0x00	; A IN
	out DDRA, r16
	ldi r16, 0xff	; Pull-Ups
	out PORTA, r16

	ldi r16, 0xff	; B OUT
	out DDRB, r16
	ldi r16, 0xff	; HIGH => LEDs aus
	out PORTB, r16

	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zur�ck

/*
* Gibt ein Byte auf PortB und die daran angeschlossenen LEDs aus.
* An Bit-Positionen mit dem Wert 1 soll die zugeh�rige LED leuchten.
*
* Register:
* lokal: keine
* Parameter: r24
* R�ckgabe: keine
*/
putByteLED_B:
	;push r16 ; Inhalt von r16 retten
	;lds r16, SREG ; Inhalt des Flagregisters retten
	;push r16

	com r24 ; Soll leuchten, wo eine 1 war
	out PORTB, r24

	;pop r16 	; Inhalt des Flagregisters wiederherstellen
	;sts SREG, r16
	;pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zur�ck

/*
* L�sst den Prozessor f�r eine angegebene Zeit im Bereich von etwa 0 bis 255 ms warten
*
* Register:
* lokal: r24,r25,r26,r27
* Parameter: r23
* R�ckgabe: keine
*/
wait_ms:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16
	push r24
	push r25
	push r26
	push r27

	;ldi r23 = 0x64
	call wait

	pop r27
	pop r26
	pop r25
	pop r24
	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zur�ck

wait:
	lds r27, SREG
	mov r26, r23 	; wie oft soll der 16-Bitwert in r25:r24
						; auf 0 heruntergez�hlt werden? (Wartez�hler laden)
next_wait:
	ldi r24, 0xe8 		; l�dt den Startwert der inneren Z�hlschleife -> 1 ms
	ldi r25, 0x03

wait_loop:
	sbiw r24,1			; z�hle 2 Byte-Zahl runter
	brne wait_loop 		; wenn nicht bei 0, springt wieder zu wait_loop
	dec r26 			; wenn ja, dekrementiert den Wartez�hler
	brne next_wait 		; wenn nicht 0 => Sprung zum erneuten Herunterz�hlen
						; des 16-Bit-Wertes
	sts SREG, r27
	ret 				; kehrt zum aufrufenden Programm zur�ck

/*
* Wartet auf eine Eingabe vom Benutzer �ber die an PortA angeschlossenen Tasten
*
* Register:
* lokal: r16, r23 - Hilfsregister
* Parameter: keine
* R�ckgabe: r22
*/
wait4key_A:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16

	wait_loop_key:
		lds r16, PINA
		cpi r16, 0xff ; nicht gedr�ckt?
		breq wait_loop_key

	lds r22, PINA ; Tastencode zur�ckgeben
	ldi r23, 0x0a ; warte 10 ms
	call wait_ms

	wait4keyrelease:
		lds r16, PINA
		cpi r16, 0xff ; nicht gedr�ckt?
		brne wait4keyrelease ; wenn nicht gedr�ckt, wiederhole

	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zur�ck

/*
* Initialisierung der Ports A und B
* PortA: Eingabe (Anschluss der Tasten)
* PortB: Ausgabe (Anschluss der LEDs)
*
* Register:
* lokal:
r16 - Hilfsregister
* Parameter: keine
* R�ckgabe: keine
*/
toggle_bit:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16

	eor r21, r20 // XOR

	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zur�ck

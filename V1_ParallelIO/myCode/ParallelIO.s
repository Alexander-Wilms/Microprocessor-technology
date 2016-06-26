/*
* ParallelIO.s
*
* Created on: 11.03.2014
* Author: Fabian Alexander Wilms 735162
*
*/

;enthält alle Definitionen für den eingestellten Prozessor
#include <avr/io.h>

.file "myCode/ParallelIO.s" ; Muss mit dem Dateinamen uebereinstimmen
.text ; Programmsegment (ROM)

; Funktionen nach außen bekannt machen
.global initPorts_Ain_Bout
.global putByteLED_B
.global wait_ms
.global wait4key_A
.global toggle_bit

/*
* Initialisierung der Ports A und B
* PortA: Eingabe (Anschluss der Tasten)
* PortB: Ausgabe (Anschluss der LEDs)
*
* Register:
* lokal: r16 - Hilfsregister
* Parameter: keine
* Rückgabe: keine
*/
; /\ alles pushen, was kein Parameter ist und verwendet wird
initPorts_Ain_Bout:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16

	ldi r16, 0x00	; A für Eingabe konfigurieren
	sts DDRA, r16
	ldi r16, 0xff	; Pull-Ups anschalten
	sts PORTA, r16

	ldi r16, 0xff	; B für Ausgabe konfigurieren
	sts DDRB, r16
	ldi r16, 0xff	; Ausgang auf HI legen -> alle LEDs aus
	sts PORTB, r16

	pop r16 		; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 		; Inhalt von r16 wiederherstellen
	ret 			; die Funktion kehrt zum aufrufenden Programm zurück

/*
* Gibt ein Byte auf PortB und die daran angeschlossenen LEDs aus.
* An Bit-Positionen mit dem Wert 1 soll die zugehörige LED leuchten.
*
* Register:
* lokal: keine
* Parameter: r24
* Rückgabe: keine
*/
putByteLED_B:

	com r24 		; Soll leuchten, wo eine 1 war -> bitweises invertieren
	sts PORTB, r24 	; In AUsgabe-Register schreiben
	com r24 		; r24 bleibt unverändert, sonst Problem bei Aufgabe 1

	ret ; die Funktion kehrt zum aufrufenden Programm zurück

/*
* Lässt den Prozessor für eine angegebene Zeit im Bereich von etwa 0 bis 255 ms warten
*
* Register:
* lokal: r24,r25,r26,r27
* Parameter: r23
* Rückgabe: keine
*/
wait_ms:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16
	push r24
	push r25
	push r26
	push r27

	lds r27, SREG
	mov r26, r23 		; wie oft soll der 16-Bitwert in r25:r24
						; auf 0 heruntergezählt werden? (Wartezähler laden)
next_wait:
	ldi r24, 0x00 		; lädt den Startwert der inneren Zählschleife -> 1 ms
	ldi r25, 0x32

wait_loop:
	sbiw r24,1			; zähle 2 Byte-Zahl runter
	brne wait_loop 		; wenn nicht bei 0, springt wieder zu wait_loop
	
	dec r26 			; wenn ja, dekrementiert den Wartezähler
	brne next_wait 		; wenn nicht 0 => Sprung zum erneuten Herunterzählen
						; des 16-Bit-Wertes
	sts SREG, r27

	pop r27		; in umgekehrter Weise Register wiederherstellen
	pop r26
	pop r25
	pop r24
	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 	; Inhalt von r16 wiederherstellen
	ret 		; die Funktion kehrt zum aufrufenden Programm zurück

/*
* Wartet auf eine Eingabe vom Benutzer über die an PortA angeschlossenen Tasten
*
* Register:
* lokal: r16, r23 - Hilfsregister
* Parameter: keine
* Rückgabe: r22
*/
wait4key_A:
	push r16 ; Inhalt von r16 retten
	lds r16, SREG ; Inhalt des Flagregisters retten
	push r16

	wait_loop_key:
		lds r16, PINA		; Tastencode in r16 laden
		cpi r16, 0x00 		; nicht gedrückt? ACHTUNG: 00 = nicht gedrückt!!! Unterlagen anscheinend FEHLER
		breq wait_loop_key 	; wiederholen, wenn PINA = 0x00 = nicht gedrückt

	lds r22, PINA ; Tastencode zurückgeben
	ldi r23, 0x0a ; warte 10 ms
	;call wait_ms ; Absturz

	wait4keyrelease:
		lds r16, PINA			; Tastencode in r16 laden
		cpi r16, 0x00 			; gedrückt?
		brne wait4keyrelease 	; wenn gedrückt, wiederhole & Aufgabe 2 blieb hier stecken

	pop r16 	; Inhalt des Flagregisters wiederherstellen
	sts SREG, r16
	pop r16 ; Inhalt von r16 wiederherstellen
	ret ; die Funktion kehrt zum aufrufenden Programm zurück

/*
* Schaltet ein Bit, dessen Position übergeben wird, in einem Byte um
*
* Register:
* lokal: keine
* Parameter: r20, r21
* Rückgabe: r21
*/
; Aufgabe 4
toggle_bit:
	eor r21, r20 ; A XOR 1 = NOT(A)
	ret ; die Funktion kehrt zum aufrufenden Programm zurück

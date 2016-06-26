/*
* Main.s
*
* Created on: 30.04.2014
* Author: Fabian Alexander Wilms 735162
*
*/

#include <avr/io.h>

.file "myCode/Main.s" ; Muss mit dem Dateinamen uebereinstimmen
.text ; Programmsegment (ROM)

main:

	; Initialisierung des Stack-Pointers
	; Code für Initialisierung SP
	
	ldi r16,lo8 (RAMEND)
	sts SPL,r16
	ldi r16,hi8 (RAMEND)
	sts SPH,r16
	
	call main_01	; hier jeweils das Unterprogramm der bearbeiteten Aufgabe aufrufen

	; Zur Sicherheit, falls das main_0x versehentlich keine Endlosschleife enthält
	donothing: ; Endlosschleife
		jmp donothing

; hier folgt für jede der Aufgaben 1 bis 6 ein Unterprogramm nach dem folgenden Muster
; (Retten lokaler Register und des Stack ist in main_0x nicht nötig)

; Aufgabe 1
main_01:
	call initPorts_Ain_Bout 	; Ports initialisieren mit LEDs aus (rote Schrift im Sim)
	ldi r24, 0xff 				; Alle LEDs an  (roter Hintergrund im Sim)
	call putByteLED_B			; LEDs schalten
	ldi r23, 0x64 				; 100 ms warten
	call wait_ms
	loop_01:	
		com r24 				; Bitweises invertieren
		call putByteLED_B		; LEDs schalten
		ldi r23, 0x64 			; 100 ms warten
		call wait_ms			; warte
		jmp loop_01				; wiederhole
	ret							; wird nie erreicht

; Aufgabe 2
main_02:
	call initPorts_Ain_Bout 	; Ports initialisieren mit LEDs aus (rote Schrift im Sim)
	call wait4key_A 			; Auf Tastendruck warten
	mov r24, r22 				; LEDs mit LED-Code beschalten
	call putByteLED_B			; LEDs schalten
	ldi r23, 0xff 				; 100 ms warten
	call wait_ms				; warte
	jmp main_02					; Dann reset & auf nächsten Tastendruck warten
	ret 						; wird nie erreicht

; Aufgabe 3
main_03:
	; Code mit der Lösung der Aufgabe
	call initPorts_Ain_Bout ; Ports initialisieren mit LEDs aus (rote Schrift im Sim)
	start:
	ldi r24, 0x01 ; LED0 an

	loop_3:
		call wait4key_A 		; warte auf Tastendruck
		call putByteLED_B 		; LEDs schalten
		cpi r24, 0x00 			; keine LED leuchtet mehr?
		breq start				; -> r24 resetten
		lsl r24 				; rol funktionierte nicht für das bitweises Verschieben
		jmp loop_3 				; wiederhole
	ret 						; wird nie erreicht

; Aufgabe 5
main_05:
	call initPorts_Ain_Bout ; Ports initialisieren mit LEDs aus (rote Schrift im Sim)
	ldi r24, 0x00 			; Alle LEDs aus
	mov r21, r24			; LED-Code in zu toggelndes Byte schreiben
	ldi r20, 0x08 			; toggle bit setzen
	loop_5:
		call toggle_bit 	; Bit toggeln
		mov r24, r21 		; LED-Beschaltung schreiben
		call putByteLED_B 	; LEDs schalten
		ldi r23, 0x4b 		; 75 ms warten
		call wait_ms		; warte
		jmp loop_5 			; wiederhole
	ret						; wird nie erreicht


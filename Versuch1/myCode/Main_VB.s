#include <avr/io.h>
.file "myCode/Main_VB.s" // Dateiname muss uebereinstimmen!
.file "myCode/ParallelIO.s"

.text ; Programmsegment

main:

	ldi r16,lo8(RAMEND)
	sts SPL, r16
	ldi r16, hi8(RAMEND)
	sts SPH, r16

	call initPorts_Ain_Bout

	call wait4key_A ; warte auf Tastendruck

	ldi r24, 0x01 ; eine LED anschalten
	call putByteLED_B

	ldi r23, 0xe8 ; warte 100 ms
	call wait_ms

	ldi r24, 0x00 ; schalte LED aus
	call putByteLED_B

doNothing: ; tue nichts
	jmp doNothing

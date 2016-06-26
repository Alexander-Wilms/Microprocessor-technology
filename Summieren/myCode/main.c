// Bindet ein h-File ein, in dem alle IO-Adressen und Konstanten
// für den eingestellten Prozessor definiert sind z.B. DDRB, PORTB,
// PIND, PIND3 (3. Bit im IO-Register PIND) etc.
#include <avr/io.h>			// AVR header file for IO ports

int main(void)
{
	int zahl,summe;
	summe=0;
	zahl=0;

	while (zahl<=10){

		summe=summe+zahl;
		zahl+=1;
		//printf("summe ist gleich= %d",summe);



	}
	while (1) {
	}
}





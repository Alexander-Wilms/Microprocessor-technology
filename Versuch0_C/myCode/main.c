// Bindet ein h-File ein, in dem alle IO-Adressen und Konstanten
// f�r den eingestellten Prozessor definiert sind z.B. DDRB, PORTB,
// PIND, PIND3 (3. Bit im IO-Register PIND) etc.
#include <avr/io.h>			// AVR header file for IO ports

#define A 7
#define B 10
#define C 5
#define CNT_WAITLOOPS 2

void wait();

int main(void)
{
	/*char D;
	D = A+B-C;*/

	DDRB=0xff;
	//PORTB= ~D;

	unsigned char lauf=1;
	PORTB = lauf;

	while(1) //Endlosschleife
	{
		if (PORTB == 0) lauf = 1;
		lauf = lauf << 1;
		PORTB = lauf;
		wait();
	}
}

void wait()
{
	unsigned char cntLoops = CNT_WAITLOOPS;
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





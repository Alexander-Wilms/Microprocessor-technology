#include <avr/io.h>

typedef enum {PIO_PORTA,PIO_PORTB,PIO_PORTC,PIO_PORTD,PIO_PORTE,PIO_PORTF,PIO_PORTG} ePORT;
typedef enum {PIO_OUT,PIO_IN} ePORTDIR;

void initPort(ePORT port, ePORTDIR dir);

void putByte(unsigned char byte, ePORT port);

unsigned char num2Seg7(unsigned char num, unsigned char dpon);

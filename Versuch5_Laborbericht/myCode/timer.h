#include <avr/interrupt.h>
typedef enum {TMODE_NORMAL, TMODE_CTC} eTIMERMODE;
typedef enum PRESCALER{PRESC1=1, PRESC8, PRESC32, PRESC64, PRESC128, PRESC256, PRESC1024=0b111} ePRESCALER;
extern unsigned int gOcrHI;
extern unsigned int gOVLcomp;
extern unsigned char gData[4];

void init_Timer0_INT(eTIMERMODE mode);

ISR(TIMER0_OVF_vect);

ISR(TIMER0_COMP_vect);

void init_Timer0(eTIMERMODE mode);

void start_Timer0(ePRESCALER prescaler);

void stop_Timer0();

void clear_Timer0();

void wait_Timer0(eTIMERMODE mode);

void setOCRval_Timer0(unsigned char ocrval);

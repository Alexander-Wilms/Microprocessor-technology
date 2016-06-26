/*
* adc.h
*
* Created on: 19.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/

#include <avr/io.h>

typedef enum {FREERUN, SINGLESHOT} eADCRUNMODE;
typedef enum {BIT10, BIT8} eADCRES;

void init_ADC();

void start_ADC(eADCRUNMODE mode);

void stop_ADC();

void wait_ADC();

unsigned short read_ADC(eADCRES res);

unsigned char ulong2bcd_unpk(unsigned long* value);

unsigned char ulong2bcd_pk(float value);

/*
* main.c
*
* Created on: 11.06.2014
* Author: Fabian Alexander Wilms 735162
*
*/
#include <avr/io.h>
#include <libMIT.h>
#include "USART1.h"
#include "adc.h"
#include "timer.h"
#include "seg7.h"

void main_V01(void)
{
	initPort(PIO_PORTD, PIO_OUT);
	MIT_initPorts_Ain_Bout();
	while (1)
	{
		putByte(num2Seg7(7,0), PIO_PORTD);
	}
}

void main_V02(){
	sei(); // erlaube Interrupts
	initPort(PIO_PORTB, PIO_OUT);  // LEDs als Ausgang
	init_ADC_INT(); // ADC im Interrupt-Betrieb initialisieren
	start_ADC(FREERUN); // ADC im Freerun-Modus starten
	while (1) {
		putByte(gADCres>>2, PIO_PORTB); // schmeisse 2 LSB weg
	}
}

void main_V03(){
	// Fuelle gData mit Bitmustern
	putByte(0xff, PORTB);
	gData[0] = num2Seg7(1,0);
	gData[1] = num2Seg7(2,0);
	gData[2] = num2Seg7(3,0);
	gData[3] = num2Seg7(4,0);
	gOVLcomp = 3; // Schalte alle n ISR-Aufrufe um
	initPort(PIO_PORTB, PIO_OUT);
	init_Timer0_INT(TMODE_NORMAL);
	start_Timer0(PRESC1024);
	sei(); // Erlaube Interrupts global
	while (1) {
		// tu nichts
	}
}

void main_V04(){
	gOcrHI = 1023;
	initPort(PIO_PORTB, PIO_OUT);
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC1024);
	sei();
	while(1){
		// tu nichts
	}
}

void main01(){
	initPort(PIO_PORTB, PIO_OUT);
	initPort(PIO_PORTC, PIO_OUT);
	initPort(PIO_PORTD, PIO_OUT);
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC64);
	gData[0] = num2Seg7(3,1);
	gOcrHI=30;
	sei();
	while(1){

	}
}

void main02(){
	initPort(PIO_PORTC, PIO_OUT);
	initPort(PIO_PORTD, PIO_OUT);
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC64);
	gData[3] = num2Seg7(0,1);
	gData[2] = num2Seg7(1,0);
	gData[1] = num2Seg7(2,0);
	gData[0] = num2Seg7(3,0);
	gOcrHI=32;
	sei();
	while(1){

	}
}

void main03(){
	init_ADC_INT(); // ADC im Interrupt-Betrieb initialisieren
	start_ADC(FREERUN); // ADC im Freerun-Modus starten
	initPort(PIO_PORTB, PIO_OUT);
	initPort(PIO_PORTC, PIO_OUT);
	initPort(PIO_PORTD, PIO_OUT);
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC64);
	gData[0] = num2Seg7(3,1);
	gOcrHI=30;
	sei();
	//int i = 0;
	//float sum = 0;
	while(1){
		//float avg[10];
		int temp[4];
		//avg[i] = ushort2Volt(gADCres,BIT10,5);
		float voltage = ushort2Volt(gADCres,BIT10,5);
		//i = i%10;
		//sum = 0;
		/*for (int a = 0; a<10;a++)
		{
			sum = sum + avg[a];
		}*/
		//float voltage = sum/10;
		unsigned long voltagelong = (long) (voltage*1000);
		unsigned long* voltagePtr= &voltagelong;

		unsigned char bcd = ulong2bcd_unpk(voltagePtr);
		temp[0]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[1]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[2]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[3]=num2Seg7(bcd,0);

		/*
		gData[0] = num2Seg7(0,0); rechts
		gData[1] = num2Seg7(1,0);
		gData[2] = num2Seg7(2,0);
		gData[3] = num2Seg7(3,0); links
		*/

		gData[0] = temp[0];
		gData[1] = temp[1];
		gData[2] = temp[2];
		gData[3] = temp[3];
	}
}

// Konnte nicht mehr ausführlich getestet werden
void main04(){
	init_ADC_INT(); // ADC im Interrupt-Betrieb initialisieren
	start_ADC(FREERUN); // ADC im Freerun-Modus starten
	initPort(PIO_PORTB, PIO_OUT);
	initPort(PIO_PORTC, PIO_OUT);
	initPort(PIO_PORTD, PIO_OUT);
	init_Timer0_INT(TMODE_CTC);
	start_Timer0(PRESC64);
	gData[0] = num2Seg7(3,1);
	gOcrHI=30;
	sei();
	int i = 0;
	float sum = 0;
	while(1){
		float avg[10];
		int temp[4];
		avg[i] = ushort2Volt(gADCres,BIT10,5);
		sum = 0;
		for (int a = 0; a<10;a++)
		{
			sum = sum + avg[a];
		}
		float voltage = sum/10;
		i++;
		i = i%10;
		unsigned long voltagelong = (long) (voltage*1000);
		unsigned long* voltagePtr= &voltagelong;

		unsigned char bcd = ulong2bcd_unpk(voltagePtr);
		temp[0]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[1]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[2]=num2Seg7(bcd,0);
		bcd = ulong2bcd_unpk(voltagePtr);
		temp[3]=num2Seg7(bcd,0);

		/*
		gData[0] = num2Seg7(0,0); rechts
		gData[1] = num2Seg7(1,0);
		gData[2] = num2Seg7(2,0);
		gData[3] = num2Seg7(3,0); links
		*/

		gData[0] = temp[0];
		gData[1] = temp[1];
		gData[2] = temp[2];
		gData[3] = temp[3];
	}
}

int main(void) {
	main03();
	return 1;
}

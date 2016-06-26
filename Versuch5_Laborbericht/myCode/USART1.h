/*
* USART1.h
*
* Created on: 30.05.2014
* Author: Fabian Alexander Wilms 735162
*
*/

void init_USART1();

void putc_USART1(unsigned char data);

unsigned char getc_USART1(void);

unsigned char lookc_USART1(void);

void puts_USART1(unsigned char *pStr);

unsigned int ascii2num(unsigned char data);

unsigned char num2ascii(unsigned int data);

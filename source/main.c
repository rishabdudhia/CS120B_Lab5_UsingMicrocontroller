/*	Author: Rishab Dudhia (rdudh001)
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	Lab 3 exercise 2 on microcontroller
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    //DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char count = 0;
    unsigned char currBit = 0x00;
    //unsigned char i;
    /* Insert your solution below */
    while (1) {
	count = 0;
	currBit = 0x00;
	count = ~PINA & 0x0F;

	if (count >= 1)
	{
	    currBit = currBit | 0x20;
	}
	if (count >= 3)
	{
	    currBit = currBit | 0x10;
	}
	if (count >= 5)
	{
	    currBit = currBit | 0x08;
	}
	if (count >= 7)	
	{
	    currBit = currBit | 0x04;
	}
	if (count >= 10)
	{
	    currBit = currBit | 0x02;
	}
	if (count >= 13)
	{
	    currBit = currBit | 0x01;
	}
	
	if (count <= 4)
	{
	    currBit = currBit | 0x40;
	}
	
	PORTC = currBit;
    }
    return 0;
}

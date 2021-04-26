/*	Author: Rishab Dudhia (rdudh001)
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	Festive lights
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {smstart, begin, Left, Off1, wait1, wait2, wait3, wait4, wait5, wait6, wait7, Right, Off2 } state;
unsigned char cntA0;
unsigned char i;
//unsigned char cntA1;
void Tick()
{
    //unsigned char actualC = PINC ;
    //unsigned char tempC = PORTC & 0x03;
    unsigned char checkA0 = ~PINA & 0x01;
    unsigned char tempB = PORTB;
    switch(state)
    {
	case smstart:
	    state = begin;
	    tempB = 0x30;
	    i = 0;
	    PORTB = tempB;
	    break;
	case begin:
	    if ((checkA0 == 0x01) && (i < 5))
	    {
		state = wait1;
		tempB = tempB >> 1;
		PORTB = tempB;
	    	cntA0 = cntA0 + 1;
	    }
	    else if ((checkA0 == 0x01) && (i == 5))
	    {
		state = wait2;
		PORTB = 0x00;
		cntA0 = cntA0 + 1;
	    }
	    else
	    {
		state = begin;
	    }
	    break;
	case wait1:
	    if(checkA0 == 0x00)
	    {
		state = Right;
	    }
	    else
	    {
		state = wait1;
	    }
	    break;
	case Right:
	    state = begin;
	    break;
	case wait2:
	    if (checkA0 == 0x00)
		    state = Off1;
	    else
		    state = wait2;
	    break;
	case Off1:
	    if (checkA0 == 0x01)
		    state = wait3;
	    else
		    state = Off1;
	    break;
	case wait3:
	    if (checkA0 == 0x00)
	    {
		    state = wait4;
		    PORTB = 0x03;
	    }
	    else
		    state = wait3;
	    break;
	case wait4:
	    if ((checkA0 == 0x01) && (i < 5))
	    {
		    state = wait5;
	    	    tempB = tempB << 1; 
		    PORTB = tempB;
	    	    cntA0 = cntA0 + 1;
	    }
	    else if ((checkA0 == 0x01) && (i == 5))
	    {
		    state = wait6;
	    	    cntA0 = cntA0 + 1;
	    }
	    else
	    {
		    state = wait4;
	    }
	    break;
	case wait5:
	    if (checkA0 == 0x00)
		    state = Left;
	    else 
		    state = wait5;
	    break;
	case Left:
	    state = wait4;
	    break;
	case wait6:
	    if (checkA0 == 0x00)
		    state = Off2;
	    else
		    state = wait6;
	    break;
	case Off2:
	    if (checkA0 == 0x01)
	    {
		    state = wait7;
	    	    cntA0 = cntA0 + 1;
	    }
	    else
		    state = Off2;
	    break;
	case wait7:
	    if (checkA0 == 0x00)
	    {
		    state = begin;
	    	    tempB = 0x30;
		    PORTB = tempB;
		    i = 0;
	    }
	    else
		    state = wait7;
	    break;
        default:
	    state = smstart;
	    break;
    }

    switch(state)
    {
        case smstart:
        case begin:
	case wait1:
	case wait2:
	case wait3:
	case wait4:
	case wait5:
	case wait6:
	case wait7:
	    break;
        case Right:
	    i = i + 1;
	    break;
        case Off1:
	    i = 0;
	    tempB = 0x00;
	    PORTB = tempB;
            break;
	case Left:
	    i = i + 1;
	    break;
	case Off2:
	    i = 0;
	    PORTB = 0x00;
        default:
            break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    cntA0 = 0x00;
    i = 0;
    state = smstart;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 0;
}

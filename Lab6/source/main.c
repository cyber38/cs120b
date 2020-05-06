/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {Start, Zero, One, Two} state;

void OnebyOne() {
	switch (state) {
		case Start:
			state = Zero;
			break;
		case Zero:
			state = One;
			break;
		case One:
			state = Two;
			break;
		case Two:
			state = Zero;
			break;
		default:
			state = Start;
			break;
	}

	switch (state) {
		case Start:
			break;
		case Zero:
			PORTB = 0x01;
			break;
		case One:
			PORTB = 0x02;
			break;
		case Two:
			PORTB = 0x04;
			break;
		default:
			break;
	}
}

int main(void) {
	DDRB = 0xFF;
	PORTB = 0x00;
	state = Start;
	TimerSet(1000);
	TimerOn();
    /* Insert DDR and PORT initializations */
	unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
	OnebyOne();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

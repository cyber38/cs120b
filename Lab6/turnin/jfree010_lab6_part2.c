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

enum state {Start, Zero, One1, Two, One2, Pause} state;
unsigned char hold = 0;
void OnebyOne(unsigned char button) {
	switch (state) {
		case Start:
			state = Zero;
			break;
		case Zero:
			if(button) {
				state = Pause;
			} else {
				state = One1;
			}
			break;
		case One1:
			if(button) {
				state = Pause;
			} else {
				state = Two;
			}
			break;
		case Two:
			if(button) {
				state = Pause;
			} else {
				state = One2;
			}
			break;
		case One2:
			if(button) {
				state = Pause;
			} else {
				state = Zero;
			}
			break;
		case Pause:
			if (button) {
				state = Zero;
			} else {
				state = Pause;
			}
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
			hold = 0x01;
			break;
		case One1:
			PORTB = 0x02;
			hold = 0x02;
			break;
		case Two:
			PORTB = 0x04;
			hold = 0x04;
			break;
		case One2:
			PORTB = 0x02;
			hold = 0x02;
			break;
		case Pause:
			PORTB = hold;
		default:
			break;
	}
}

int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	state = Start;
	TimerSet(300);
	TimerOn();
    /* Insert DDR and PORT initializations */
	unsigned char button;
    /* Insert your solution below */
    while (1) {
	button = ~PINA & 0x01;
	OnebyOne(button);
	while(!TimerFlag) {} ;
	TimerFlag = 0;
    }
    return 1;
}

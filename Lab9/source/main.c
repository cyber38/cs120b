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

void set_PWM(double frequency) {
	static double current_frequency;
	if(frequency != current_frequency) {
		if(!frequency) {
			TCCR3B &= 0x08;
		} else {
			TCCR3B |= 0x03;
		}

		if(frequency < 0.954) {
			OCR3A = 0xFFFF;
		} else if (frequency > 31250) {
			OCR3A = 0x0000;
		} else {
			OCR3A = (short)(8000000 / (128 * frequency)) - 1;
		}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum state {Start, waitp, waitr, offp, offr, upp, upr, downp, downr} state;
double scale[8] = {261.63, 293.66, 329.63, 349.23, 392.0, 440.0, 493.88, 523.25};
unsigned char i = 0;

void Scaling(unsigned char button) {
	switch (state) {
		case Start:
			state = offr;
			break;
		case offr:
			if(button == 0x04) {
				state = offp;
			} else {
				state = offr;
			}
			break;
		case offp:
			if(button == 0x04) {
				state = offp;
			} else {
				state = waitr;
			}
			break;
		case waitr:
			if (button == 0x04) {
				state = waitp;
			} else if (button == 0x02) {
				state = upp;
			} else if (button == 0x01) {
			        state = downp;
		        } else {
				state = waitr;
			}
			break;
		case waitp:
			if(button == 0x04) {
				state = waitp;
			} else { 
				state = offr;
			}
			break;
		case upp:
			if(button == 0x02) {
				state = upp;
			} else {
				state = upr;
			}
			break;
		case upr:
			state = waitr;
			break;
		case downp:
			if(button == 0x01) {
				state = downp;
			} else {
				state = downr;
			}
			break;
		case downr:
			state = waitr;
			break;
		default:
			state = Start;
			break;
	}
	
	switch (state) {
		case Start:
			break;
		case offr:
			if(button == 0x02) {
				if(i < 7) {
					++i;
				}
			}
			if(button == 0x01) {
				if(i > 0) {
					--i;
				}
			}
			set_PWM(0);
			break;
		case offp:
			break;
		case waitr:
			set_PWM(scale[i]);
			break;
		case waitp:
			break;
		case upp:
			break;
		case upr:
			if(i < 7) {
				++i;
			}
			break;
		case downp:
			break;
		case downr:
			if(i > 0) {
				--i;
			}
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
    /* Insert your solution below */
	unsigned char button = 0;
	state = Start;
	TimerSet(100);
	TimerOn();
	PWM_on();
   while(1) {
	button = ~PINA & 0x07;
	Scaling(button);
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

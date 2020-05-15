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

enum state {Start, offp, offr, playc1, playv, playb1, playb2, playb3, playc2} state;
double chorus[] = {0, 392.0, 440.0, 493.88, 0, 493.88, 440.0, 392.0, 0, 392.0, 440.0, 493.88, 440.0, 392.0, 0 ,392.0};
double verse[] = {0, 329.63, 349.23, 392.0, 261.63, 329.63, 349.23, 392.0, 0};
double bridge1[] = {440.0, 392.0, 0, 392.0};
double bridge2[] = {329.63, 349.23, 329.0};
unsigned char k = 0;
unsigned char timer = 0;
void Melody(unsigned char button) {
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
				state = playc1;
			}
			break;
		case playc1:
			if(k == 16) {
				k = 0;
				state = playv;
			} else {
				state = playc1;
			}
			break;
		case playv:
			if(k == 9) {
				k = 0;
				state = playb1;
			} else {
				state = playv;
			}
			break;
		case playb1:
			if(k == 4) {
				k = 0;
				state = playb2;
			} else {
				state = playb1;
			}
			break;
		case playb2:
			if(k == 3) {
				k = 0;
				state = playb3;
			} else {
				state = playb2;
			}
			break;
		case playb3:
			if(k == 4) {
				k = 0;
				state = playc2;
			} else {
				state = playb3;
			}
			break;
		case playc2:
			if(k == 16) {
                                k = 0;
                                state = offr;
                        } else {
                                state = playc2;
                        }
                        break;
		default:
			break;
	}
	
	switch(state) {
		case Start:
			break;
		case offr:
			k = 0;
			set_PWM(0);
			break;
		case offp:
			break;
		case playc1:
			set_PWM(chorus[k]);
			++timer;
			if(timer == 4) {
				++k;
				timer = 0;
			}
			break;
		case playv:
			set_PWM(verse[k]);
			++timer;
			if (timer == 4) {
				++k;
				timer = 0;
			}
			break;
		case playb1:
			set_PWM(bridge1[k]);
			++timer;
			if(k == 1 || k == 2) {
				++timer;
			}
			if(timer == 4) {
				++k;
				timer = 0;
			}
			break;
		case playb2:
			set_PWM(bridge2[k]);
			++timer;
			if(timer == 2) {
                                ++k;
                                timer = 0;
                        }
			break;
		case playb3:
			set_PWM(bridge1[k]);
                        ++timer;
                        if(k == 1 || k == 2) {
                                ++timer;
                        }
                        if(timer == 4) {
                                ++k;
                                timer = 0;
                        }
                        break;
		case playc2:
			set_PWM(chorus[k]);
                        ++timer;
                        if(timer == 4) {
                                ++k;
                                timer = 0;
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
	PWM_on();
	TimerSet(100);
	TimerOn();
   while(1) {
	button = ~PINA & 0x07;
	Melody(button);
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

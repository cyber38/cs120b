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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA  |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	ADC_init();
	unsigned long x = ADC;
	unsigned long max = 0;

    while (1) {
	x = ADC;

	if(x > max) {
		max = x;
	}

	if(x >= ((max * 7) / 8)) {
		PORTB = 0xFF;
	} else if (x > ((max * 6) / 8)) {
		PORTB = 0x7F;
	} else if (x > ((max * 5) / 8)) {
		PORTB = 0x3F;
	} else if (x > ((max * 4) / 8)) {
		PORTB = 0x1F;
	} else if (x > ((max * 3) / 8)) {
		PORTB = 0x0F;
	} else if (x > ((max * 2) / 8)) {
		PORTB = 0x07;
	} else if (x > ((max * 1) / 8)) {
		PORTB = 0x03;
	} else {
		PORTB = 0x01;
	}

    }
    return 1;
}

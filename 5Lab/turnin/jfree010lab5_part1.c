/*	Author: jfree010
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

enum state {Start, Begin, LevelOneTwo, LevelThreeFour, LevelFiveSix, LevelSevenEightNine, LevelTenElevenTwelve, LevelThirteenFourteenFifteen} state;
unsigned char flag = 0;

void Fuel(unsigned char button) {
        switch (state) {
                case Start:
			state = Begin;
                        break;
		case Begin:
			if((button > 0x00) && (button < 0x03)) {
				state = LevelOneTwo;
			} else if ((button > 0x02) && (button < 0x05)) {
				state = LevelThreeFour;
			} else if ((button > 0x04) && (button < 0x07)) {
				state = LevelFiveSix;
			} else if ((button > 0x06) && (button < 0x0A)) {
				state = LevelSevenEightNine;
			} else if ((button > 0x09) && (button < 0x0D)) {
				state = LevelTenElevenTwelve;
			} else if (button > 0x0D) {
				state = LevelThirteenFourteenFifteen;
			} else {
				state = Begin;
			}
			break;
                case LevelOneTwo:
                        if ((button > 0x00) && (button < 0x03)) {
				state = LevelOneTwo;
			} else {
				state = Begin;
			}
                        break;
                case LevelThreeFour:
			if ((button > 0x02) && (button < 0x05)) {
				state = LevelThreeFour;
			} else {
				state = Begin;
			}
                        break;
                case LevelFiveSix:
			if ((button > 0x04) && (button < 0x07)) {
				state = LevelFiveSix;
			} else {
				state = Begin;
			}
                        break;
                case LevelSevenEightNine:
                        if ((button > 0x06) && (button < 0x0A)) {
				state = LevelSevenEightNine;
			} else {
				state = Begin;
			}
                        break;
		case LevelTenElevenTwelve:
			if ((button > 0x09) && (button < 0x0D)) {
				state = LevelTenElevenTwelve;
			} else {
				state = Begin;
			}
			break;
		case LevelThirteenFourteenFifteen:
			if (button > 0x0D) {
				state = LevelThirteenFourteenFifteen;
			} else {
				state = Begin;
			}
			break;
                default:
                        state = Start;
                        break;
        }

        switch (state) {
                case Start:
                        break;
		case Begin:
			PORTC = 0x00;
			break;
                case LevelOneTwo:
                        PORTC = 0x60;
                        break;
                case LevelThreeFour:
			PORTC = 0x70;
                        break;
                case LevelFiveSix:
			PORTC = 0x38;
                        break;
                case LevelSevenEightNine:
                        PORTC = 0x3C;
                        break;
		case LevelTenElevenTwelve:
			PORTC = 0x3E;
			break;
		case LevelThirteenFourteenFifteen:
			PORTC = 0x3F;
			break;
                default:
                        break;
        }
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;

    unsigned char button = 0x00;
    /* Insert your solution below */
    while (1) {
	button = ~PINA & 0x0F;
	Fuel(button);
    }
    return 0;
}

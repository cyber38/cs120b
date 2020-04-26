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

enum state {Start, Begin, P1, R1, P2, R2, P3, R3, P4, R4, P5, R5, P6, R6, P7, R7, P8, R8} state;
unsigned char flip = 0;

void Festive(unsigned char button) {
        switch (state) {
                case Start:
			state = Begin;
                        break;
		case Begin:
			if(button) {
				state = P1;
			} else {
				state = Begin;
			}
			break;
                case P1:
                        if (button) {
				state = P1;
			} else {
				state = R1;
			}
                        break;
                case R1:
			if (button) {
				state = P2;
			} else {
				state = R1;
			}
                        break;
                case P2:
			if (button) {
				state = P2;
			} else {
				state = R2;
			}
                        break;
		case R2:
                        if (button) {
				state = P3;
			} else {
				state = R2;
			}
                        break;
		case P3:
			if (button) {
				state = P3;
			} else {
				state = R3;
			}
			break;
		case R3:
			if (button) {
				state = P4;
			} else {
				state = R3;
			}
			break;
		case P4:
                        if (button) {
                                state = P4;
                        } else {
                                state = R4;
                        }
                        break;
		case R4:
                        if (button) {
                                state = P5;
                        } else {
                                state = R4;
                        }
                        break;
		case P5:
                        if (button) {
                                state = P5;
                        } else {
                                state = R5;
                        }
                        break;
		case R5:
                        if (button) {
                                state = P6;
                        } else {
                                state = R5;
                        }
                        break;
		case P6:
                        if (button) {
                                state = P6;
                        } else {
                                state = R6;
                        }
                        break;
		case R6:
                        if (button) {
                                state = P7;
                        } else {
                                state = R6;
                        }
                        break;
		case P7:
                        if (button) {
                                state = P7;
                        } else {
                                state = R7;
                        }
                        break;
		case R7:
                        if (button) {
                                state = P8;
                        } else {
                                state = R7;
                        }
                        break;
		case P8:
                        if (button) {
                                state = P8;
                        } else {
				state = R8;
			}
                        break;
		case R8:
                        if (button) {
                                state = Begin;
                        } else {
                                state = R8;
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
			PORTB = 0x00;
			break;
                case P1:
                        PORTB = 0x01;
                        break;
		case R1:
			break;
                case P2:
			PORTB = 0x02;
                        break;
		case R2:
                        break;
                case P3:
			PORTB = 0x04;
                        break;
		case R3:
                        break;
                case P4:
                        PORTB = 0x08;
                        break;
		case R4:
                        break;
		case P5:
			PORTB = 0x10;
			break;
		case R5:
                        break;
		case P6:
			PORTB = 0x20;
			break;
		case R6:
                        break;
		case P7:
                        PORTB = 0x15;
                        break;
		case R7:
                        break;
		case P8:
                        PORTB = 0x2A;
                        break;
		case R8:
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

    state = Start;
    unsigned char button = 0x00;
    /* Insert your solution below */
    while (1) {
	button = ~PINA & 0x01;
	Festive(button);
    }
    return 0;
}

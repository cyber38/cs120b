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
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {Start, Begin, OP, OR, ZP, ZR, Reset} state;
unsigned char count = 0;
unsigned char out = 0;
unsigned char flag = 0;

void Counter(unsigned char button) {
	switch (state) {
		case Start:
                        state = Begin;
                        break;
		case Begin:
			if(button == 0x01) {
				state = OP;
				flag = 1;
			} else if(button == 0x02) {
				state = ZP;
				flag = 1;
			} else if(button == 0x03){
				state = Reset;
			} else {
				state = Begin;
			}
			break;
                case OP:
                        if(button == 0x01) {
                                state = OP;
                        } else if (button == 0x02 || button == 0x03) {
                                state = Reset;
                        } else {
				state = OR;
			}
                        break;
                case OR:
                        if(button == 0x01) {
                                state = OP;
				flag = 1;
                        } else if (button == 0x02){
                                state = ZP;
				flag = 1;
                        } else if(button == 0x03){
				state = Reset;
			} else {
				state = OR;
			}
                        break;
                case ZR:
                        if(button == 0x01) {
                                state = OP;
				flag = 1;
                        } else if(button == 0x02){
                                state = ZP;
				flag = 1;
                        } else if (button == 0x03) {
				state = Reset;
			} else {
				state = ZR;
			}
                        break;
                case ZP:
                        if(button == 0x01 || button == 0x03) {
                                state = Reset;
                        } else if(button == 0x02){
                                state = ZP;
                        } else {
				state = ZR;
			}
                        break;
		case Reset:
			if(button == 0x01) {
				state = OP;
				flag = 1;
			} else if (button == 0x02) {
				state = ZP;
				flag = 1;
			} else {
				state = Reset;
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
			count = 0x00;
			if(out == 0) {
				LCD_ClearScreen();
				LCD_WriteData(count + '0');
				out = 1;
			}
			break;
                case OP:
			if(count < 9) {
				++count;
			}
                        if(out == 0) {
				LCD_ClearScreen();
				LCD_WriteData(count + '0');
				out = 1;
			}
                        break;
                case OR:
			out = 0;
			flag = 0;
                        break;
                case ZR:
			out = 0;
			flag = 0;
                        break;
                case ZP:
			if(count > 0) {
				--count;
			}
                        if(out == 0) {
				LCD_ClearScreen();
				LCD_WriteData(count + '0');
				out = 1;
			}
                        break;
		case Reset:
			count = 0;
			if(out == 0) {
				LCD_ClearScreen();
				LCD_WriteData(count + '0');
				out = 1;
			}
			break;
                default:
                        break;
	}
}



int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	state = Start;
	TimerSet(100);
	TimerOn();
	LCD_init();
	unsigned char button = 0x00;
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {
	button = ~PINA & 0x03;
	Counter(button);
	while (!TimerFlag) { };
	TimerFlag = 0;
    }
    return 1;
}

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

enum state {Start, Begin, Zero, One1, Two, One2, Victory} state;
unsigned char count = 0;
unsigned char out = 0;
unsigned char timer = 0;
unsigned char hold = 0;
unsigned char flag = 0;

void StopLightGame(unsigned char button) {
	switch (state) {
		case Start:
                        state = Begin;
                        break;
		case Begin:
			state = Zero;
			break;
		case Zero:
			if (timer == 5) {
				timer = 0;
				state = One1;
			} else if(count == 9) {
				state = Victory;
			} else {
				state = Zero;
			}
			break;
		case One1:
			if (timer == 5) {
				timer = 0;
				state = Two;
			} else if (count == 9) {
				state = Victory;
			} else {
				state = One1;
			}
			break;
		case Two:
			 if (timer == 5) {
				timer = 0;
				state = One2;
			} else if (count == 9) {
				state = Victory;
			} else {
				state = Two;
			}
			break;
		case One2:
			if (timer == 5) {
				timer = 0;
				state = Zero;
			} else if (count == 9) {
				state = Victory;
			} else {
				state = One2;
			}	
			break;
		case Victory:
			state = Victory;
			break;
                default:
                        state = Start;
                        break;
	}

	switch (state) {
		case Start:
			break;
		case Begin:
			count = 5;
			LCD_ClearScreen();
			LCD_WriteData(count + '0');
			break;
		case Zero:
			PORTB = 0x01;
			++timer;
			if(button) {
				if(count > 0) {
					--count;
					LCD_ClearScreen();
					LCD_WriteData(count + '0');
				}
			}
			break;
		case One1:
			PORTB = 0x02;
			++timer;
			if(button) {
				if(count < 9) {
					++count;
					LCD_ClearScreen();
					LCD_WriteData(count + '0');
				}
			}
			break;
		case Two:
			PORTB = 0x04;
			++timer;
			if(button) {
				if(count > 0) {
					--count;
					LCD_ClearScreen();
					LCD_WriteData(count + '0');
				}
			}
			break;
		case One2:
			PORTB = 0x02;
			++timer;
			if(button) {
				if(count < 9) {
					++count;
					LCD_ClearScreen();
					LCD_WriteData(count + '0');
				}
			}
			break;
		case Victory:
			LCD_DisplayString(1, "Victory!!!");
			break;
                default:
                        break;
	}
}



int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
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
	StopLightGame(button);
	while (!TimerFlag) { };
	TimerFlag = 0;
    }
    return 1;
}

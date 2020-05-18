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

unsigned char blinkingLED;
unsigned char threeLEDs;

enum B_State {B_Start, B_On, B_Off} B_State;
void BlinkingLEDSM() {
	switch(B_State) {
		case B_Start:
			B_State = B_On;
			break;
		case B_On:
			B_State = B_Off;
			break;
		case B_Off:
			B_State = B_On;
			break;
		default:
			B_State = B_Start;
			break;
		}
	switch(B_State) {
		case B_Start:
			blinkingLED = 0;
			break;
		case B_On:
			blinkingLED = 0x08;
			break;
		case B_Off:
			blinkingLED = 0;
			break;
		default:
			break;
	}
}

enum T_State {T_Start, T_Zero, T_One, T_Two} T_State;
void ThreeLEDsSM() {
	switch(T_State) {
		case T_Start:
			T_State = T_Zero;
			break;
		case T_Zero:
			T_State = T_One;
			break;
		case T_One:
			T_State = T_Two;
			break;
		case T_Two:
			T_State = T_Zero;
			break;
		default:
			T_State = T_Start;
			break;
	}
	switch(T_State) {
		case T_Start:
			threeLEDs = 0;
			break;
		case T_Zero:
			threeLEDs = 0x01;
			break;
		case T_One:
			threeLEDs = 0x02;
			break;
		case T_Two:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
			
}	

enum D_State {D_Start, D_Output} D_State;
void CombinedLEDsSM() {
	switch(D_State) {
		case D_Start:
			D_State = D_Output;
			break;
		case D_Output:
			D_State = D_Output;
			break;
		default:
			D_State = D_Start;
			break;
	}

	switch(D_State) {
		case D_Start:
			break;
		case D_Output:
			PORTB = blinkingLED | threeLEDs;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
    /* Insert your solution below */
	B_State = B_Start;
	T_State = T_Start;
	D_State = D_Start;
	TimerSet(1000);
	TimerOn();
    while (1) {
	BlinkingLEDSM();
	ThreeLEDsSM();
	CombinedLEDsSM();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
    return 1;
}

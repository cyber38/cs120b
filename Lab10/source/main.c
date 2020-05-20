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
unsigned char audio;
unsigned char frequency;

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

enum R_State {R_Start, R_wait, R_up, R_down} R_State;
void Receive(unsigned char button) {
	switch(R_State) {
		case R_Start:
			R_State = R_wait;
			break;
		case R_wait:
			if(button == 0x04) {
				R_State = R_down;
			} else if (button == 0x02) {
				R_State = R_up;
			} else {
				R_State = R_wait;
			}
			break;
		case R_up:
			R_State = R_wait;
			break;
		case R_down:
			R_State = R_wait;
			break;
		default:
			R_State = R_Start;
			break;
	}
	switch(R_State) {
		case R_Start:
			break;
		case R_wait:
			break;
		case R_up:
			if(frequency < 10) {
				frequency += 2;
			}
			break;
		case R_down:
			if(frequency > 2) {
				frequency -= 2;
			}
			break;
		default:
			break;
	}
}
enum A_State {A_Start, A_off, A_onl, A_onh} A_State;
void Speaker(unsigned char button) {
	switch(A_State) {
		case A_Start:
			A_State = A_off;
			break;
		case A_off:
			if(button == 0x01) {
				A_State = A_onh;
			} else {
				A_State = A_off;
			}
			break;
		case A_onh:
			if(button) {
				A_State = A_onl;
			} else {
				A_State = A_off;
			}
			break;
		case A_onl:
			A_State = A_onh;
			break;
		default:
			A_State = A_Start;
			break;
	}

	switch (A_State) {
		case A_Start:
			break;
		case A_off:
			audio = 0x00;
			break;
		case A_onh:
			audio = 0x10;
			break;
		case A_onl:
			audio = 0x00;
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
			PORTB = blinkingLED | threeLEDs | audio;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
    /* Insert your solution below */
	unsigned long B_elapsedTime = 1000;
	unsigned long T_elapsedTime = 300;
	unsigned long A_elapsedTime = frequency;
	unsigned long R_elapsedTime = 100;
	unsigned long timerPeriod = 1;
	unsigned char button = 0x00;
	B_State = B_Start;
	T_State = T_Start;
	A_State = A_Start;
	D_State = D_Start;
	R_State = R_Start;
	frequency = 2;
	TimerSet(timerPeriod);
	TimerOn();
    while (1) {
	button = ~PINA & 0x07;
	if(B_elapsedTime >= 1000) {
		BlinkingLEDSM();
		B_elapsedTime = 0;
	}
	if(T_elapsedTime >= 300) {
		ThreeLEDsSM();
		T_elapsedTime = 0;
	}
	if(A_elapsedTime >= frequency) {
		Speaker(button);
		A_elapsedTime = 0;
	}
	if(R_elapsedTime >= 100) {
		Receive(button);
		R_elapsedTime = 0;
	}
	CombinedLEDsSM();
	while(!TimerFlag) {};
	TimerFlag = 0;
	B_elapsedTime += timerPeriod;
	T_elapsedTime += timerPeriod;
	A_elapsedTime += timerPeriod;
	R_elapsedTime += timerPeriod;
    }
    return 1;
}

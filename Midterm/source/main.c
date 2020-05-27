/*	Author: <your name>
 *	Lab Section:
 *  Exam #2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

/* SM state declarations --- fill in as needed */
typedef enum ping_states { PInit, PIlow, PIhigh,                            } ping_states;
typedef enum detect_eq_states { DEQInit, DEQCapture                         } detect_eq_states;
typedef enum detect_max_amp_states { DMAInit, DMACheck                      } detect_max_amp_states;
typedef enum detect_zc_states { DZCInit, DZCFirst, DZCSecond,               } detect_zc_states;
typedef enum transmit_states {TInit, TOutput,                               } transmit_states;

/* shared variables --- fill in as needed */
unsigned char direction;
unsigned char amplitude;
unsigned char ping;
unsigned char max = 0;
unsigned char first;
unsigned char zero_crossing;
unsigned char detected;
unsigned char input;
/* state variables --- do not alter */
ping_states ping_state;
detect_eq_states detect_eq_state;
detect_max_amp_states detect_max_amp_state;
detect_zc_states detect_zc_state;
transmit_states transmit_state;

/* SM definitions --- complete each task as a SM in the appropriate file.
 * Alternatively, you can remove the #include statement and insert your
 *   SM implementation directly. 
 */
#include "ping.h"
#include "detect_eq.h"
#include "detect_max_amp.h"
#include "detect_zc.h"
#include "transmit.h"


/* main function --- do not alter */
int main(void) {
    /* DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	
    // Common period for all tasks set to 100ms
    unsigned char timerPeriod = 100;
    TimerSet(timerPeriod);
    TimerOn();
	
    // init state vars
    ping_state = PInit;
    detect_eq_state = DEQInit;
    detect_max_amp_state = DMAInit;
    detect_zc_state = DZCInit;
    transmit_state = TInit;
    
    unsigned long PI_time = 1000;
    while (1) {
	input = ~PINA;
	if(PI_time >= 1000) {
        	Ping();
		PI_time = 0;
	}
        Detect_EQ();
        Detect_Max_Amp();
        Detect_ZC();
        Transmit();
        while (!TimerFlag) { }
        TimerFlag = 0;

	PI_time += timerPeriod;
    }
    return 1;
}

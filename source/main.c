/*	Author: sng055
 *  Partner(s) Name: sunny ng
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempA = 0x00;

enum SM1_STATES {SM1_SMStart, SM1_Init, SM1_PressPound, SM1_PressY, SM1_Wait, SM1_Open } SM1_STATE;

void DOOR_LOCK() {

	switch(SM1_STATE) {

	case SM1_SMStart:
	SM1_STATE = SM1_Init;
	break;

	case SM1_Init:
	if (tempA == 0x04) {
		SM1_STATE = SM1_PressPound;
	}
	else {
		SM1_STATE = SM1_Init;
	}
	break;

	case SM1_PressPound:
	if (tempA == 0x00) {
		SM1_STATE = SM1_PressY;
	}
	else if (tempA == 0x04) {
		SM1_STATE = SM1_PressPound;
	}
	else {
		SM1_STATE = SM1_Init;
	}
	break;

	case SM1_PressY:
	if (tempA == 0x02) {
		SM1_STATE = SM1_Wait;
	}
	else if (tempA == 0x00) {
		SM1_STATE = SM1_PressY;
	}
	else {
		SM1_STATE = SM1_Init;
	}
	break;

	case SM1_Wait:
	if (tempA == 0x00) {
		SM1_STATE = SM1_Open;
	}
	else if (tempA == 0x02) {
		SM1_STATE = SM1_Wait;
	}
	else {
		SM1_STATE = SM1_Init;
	}
	break;

	case SM1_Open:
	if (tempA == 0x80) {
		SM1_STATE = SM1_Init;
	}
	else {
		SM1_STATE = SM1_Open;
	}
	break;

	}	
	switch (SM1_STATE) {
	
	case SM1_SMStart:
	break;

	case SM1_Init:
	PORTB = 0;
	break;
	case SM1_PressPound:
	break;
	case SM1_PressY:
	break;
	case SM1_Wait:
	break;
	case SM1_Open:
	PORTB = 1;
	break;	

	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	DOOR_LOCK();
    }
    return 1;
}

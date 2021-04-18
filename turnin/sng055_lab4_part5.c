/*	Author: sng055
 *  Partner(s) Name: sunny ng
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #5
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
unsigned char array[4] = {0x04,0x01,0x02,0x01};
unsigned char index = 0x00;
enum SM1_STATES {SM1_SMStart, SM1_Init, SM1_Check, SM1_Lock, SM1_Open, SM1_Fails } SM1_STATE;

void DOOR_LOCK() {

	switch(SM1_STATE) {

	case SM1_SMStart:
	SM1_STATE = SM1_Init;
	break;

	case SM1_Init:
	if (tempA == array[index]) {
		SM1_STATE = SM1_Check;
	}
	else if (tempA == 0x00) {
		SM1_STATE = SM1_Init;
	}
	else if (tempA == 0x80) {
		SM1_STATE = SM1_Lock;
	}
	else {
		SM1_STATE = SM1_Fails;
	}
	break;

	case SM1_Check:
	if (tempA == 0x00) {
		index++;
		SM1_STATE = SM1_Init;
	}
	else if (index == 3) {
		SM1_STATE = SM1_Open;
	}
	else if (tempA == 0x80) {
		SM1_STATE = SM1_Lock;
	}
	else {
		SM1_STATE = SM1_Check;
	}
	break;

	case SM1_Open:
	if (tempA == 0x00) {
		index = 0;
		SM1_STATE = SM1_Init;
	}
	else {
		SM1_STATE = SM1_Open;
	}
	break;

	case SM1_Lock:
	if (tempA == 0x80) {
		SM1_STATE = SM1_Lock;
	}
	else {
		index = 0;
		SM1_STATE = SM1_Init;
	}
	break;

	case SM1_Fails:
	index = 0;
	SM1_STATE = SM1_Init;
	break;

	}	
	switch (SM1_STATE) {
	
	case SM1_SMStart:
	PORTB = 0;
	break;
	case SM1_Init:
	break;
	case SM1_Check:
	break;
	case SM1_Open:
	PORTB = 1;
	break;	
	case SM1_Lock:
	PORTB = 0;
	break;
	case SM1_Fails:
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

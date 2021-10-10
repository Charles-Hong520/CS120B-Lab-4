/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: Button switch lights
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State {start, on1, on2, off1, off2} state;
unsigned char tmpA = 0x00;

void Tick() {
	switch (state) {
		case start:
		PORTB=0x01;
		state = on1;
		break;
		case on1:
		if(PINA&0x01) {
			state = off1;
			PORTB = 0x02;
		} else {
			state = on1;
		}
		break;
		case off1:
		if(PINA&0x01) state = off1;
		else state = off2;
		break;
		case off2:
		if(PINA&0x01) {
			state = on2;
			PORTB = 0x01;
		} else {
			state = off2;
		}
		break;
		case on2:
		if(PINA&0x01) state = on2;
		else state = on1;
		break;
	}
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x01; //output
	state = start;
	while(1) {
		Tick();
	}
	return 1;
}
/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: Unlock and Lock with #Y
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define A (PINA&0x87)
enum State {start, init, press, release} state;
unsigned char tmpA = 0x00;

void Tick() {
	switch(state) {
		case start:
		state = init;
		PORTB = 0x00;
		break;
		case init:
		if(A==0x04) {
			state = press;
		} else if(A>=0x80) {
			state = init;
			PORTB = 0;
		} else {
			state = init;
		}
		break;
		case press:
		if(A==0x04) {
			state = press;
		} else if(A==0x00) {
			state = release;
		} else if(A>=0x80) {
			state = init;
			PORTB = 0;
		} else {
			state = init;
		}
		break;
		case release:
		if(A==0x00) {
			state = release;
		} else if(A==0x02) {
			state = init;
			if(PORTB==0) {
				PORTB = 1;
			} else {
				PORTB = 0;
			}
		} else if(A>=0x80) {
			state = init;
			PORTB = 0;
		} else {
			state = init;
		}
		break;
		default:
		state = start;
		printf("something wrong in first switch \n"); break;
	}
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
	state = start;
	while(1) {
		Tick();
	}
	return 1;
}
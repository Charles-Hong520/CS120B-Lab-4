/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: 0-9 Counter
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define A (PINA&0x03)
enum State {start, init, inc, dec} state;
unsigned char tmpA = 0x00;

void Tick() {
	switch(state) {
		case start:
		state = init;
		PORTC = 7;
		break;
		case init:
		if((PINA&0x03)==0x00 || 
			(((PINA&0x03)==0x01) && PORTC==9) ||
			(((PINA&0x03)==0x02) && PORTC==0)) {
			state = init;
		} else if((PINA&0x03)==0x03) {
			state = init;
			PORTC = 0;
		} else if((PINA&0x03)==0x01 && PORTC>=0 && PORTC<=8) {
			state = inc;
			PORTC = PORTC+1;
		} else {
			state = dec;
			PORTC = PORTC-1;
		}
		break;
		case inc:
		if(A==0x00 || (A==0x02 && PORTC==0)) {
			state = init;
		} else if(A==0x03) {
			state = init;
			PORTC = 0;
		} else if(A==0x01) {
			state = inc;
		} else {
			state = dec;
			PORTC = PORTC-1;
		}
		break;
		case dec:
		if(A==0x00 || (A==0x01 && PORTC==9)) {
			state = init;
		} else if(A==0x03) {
			state = init;
			PORTC = 0;
		} else if(A==0x02) {
			state = dec;
		} else {
			state = inc;
			PORTC = PORTC+1;
		}
		break;
		default:
		state = start;
		printf("something wrong in first switch \n"); break;
	}
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x07; //output
	state = start;
	while(1) {
		Tick();
	}
	return 1;
}
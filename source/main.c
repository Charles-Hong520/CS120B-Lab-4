/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: Unlock and Lock with #XYX
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

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
	state = start;
	unsigned char key[] = {0x04, 0x01, 0x02, 0x01};
	unsigned char i = 0;
	const unsigned char KEY_SIZE = 4;
	while(1) {
		switch(state) {
			case start:
			state = init;
			PORTB = 0x00;
			i = 0;
			break;
			case init:
			if(A==key[0]) {
				state = press;
			} else {
				state = init;
			}
			break;
			case press:
			if(A==key[i]) {
				state = press;
			} else if(A==0x00) {
				i++;
				if(i>=KEY_SIZE) {
					if(PORTB==0) PORTB = 1;
					else PORTB = 0;
					state = init;
					i = 0;
				} else {
					state = release;
				}
			} else if(A>=0x80) {
				state = init;
				i = 0;
				PORTB = 0;
			} else {
				state = init;
				i = 0;
			}
			case release:
			if(A==0x00) {
				state = release;
			} else if(A==key[i]) {
				state = press;
			} else if(A>=0x80) {
				state = init;
				i = 0;
				PORTB = 0;
			} else {
				i = 0;
				state = init;
			}
			break;
			default:
			state = start;
			printf("something wrong in first switch \n"); break;
		}
		
	}
	return 1;
}

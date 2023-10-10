/*
 * Mini_Project_2.c
 *
 *  Created on: Sep 15, 2022
 *      Author: Meriam Ehab
 */

#include "Interrupts.h"

int main (void)
{
	SREG |= (1<<7);               // Enable interrupts by setting I-bit
	INT0_INIT_RESET();
	TIMER1_INIT();

	INT1_INIT_PAUSE();
	INT2_INIT_RESUME();

	DDRC |= 0x0F;   //configure first 4 pins in PORTC as output pins to connect to decoder
	PORTC &= 0xF0;  //set initial value 0 to first 4 pins in PORTC

	DDRA |= 0xFF;   //configure first 6 pins in PORTA as output pins to enable/disable 7seg
	PORTA = 0xFF;   //set initial value 1 to first 6 pins in PORTA

	while(1)
	{
		PORTA = (1<<0);    //enable 1th 7seg
		PORTC = (PORTC & 0xF0) | (sec % 10);   //puts first digit of seconds
		_delay_ms (3);
		PORTA = (1<<1);    //enable 2th 7seg
		PORTC = (PORTC & 0xF0) | (sec / 10);   //puts second digit of seconds
		_delay_ms (3);
		PORTA = (1<<2);    //enable 3th 7seg
		PORTC = (PORTC & 0xF0) | (min % 10);   //puts first digit of minutes
		_delay_ms (3);
		PORTA = (1<<3);    //enable 4th 7seg
		PORTC = (PORTC & 0xF0) | (min / 10);   //puts  second digit of minutes
		_delay_ms (3);
		PORTA = (1<<4);    //enable 5th 7seg
		PORTC = (PORTC & 0xF0) | (hour % 10);  //puts first digit of hours
		_delay_ms (3);
		PORTA = (1<<5);    //enable 6th 7seg
		PORTC = (PORTC & 0xF0) | (hour / 10);  //puts second digit of hours
		_delay_ms (3);
	}
}


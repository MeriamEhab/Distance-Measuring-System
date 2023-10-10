/*
 * Interrupts.h
 *
 *  Created on: Sep 16, 2022
 *      Author: Meriam Ehab
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char sec=0;
unsigned char min=0;
unsigned char hour=0;

void TIMER1_INIT(void)
{
	TCNT1 = 0;		                // Set timer1 initial count to zero
	OCR1A = 15625;
	TIMSK |= (1<<OCIE1A);           //Enable Timer1 Compare A Interrupt
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS11);

}

ISR (TIMER1_COMPA_vect)
{
	sec++;
	if (sec==60)
	{
		min++;
		sec=0;
	}
	if (min==60)
	{
		sec=0;
		min=0;
		hour++;
	}
}

void INT0_INIT_RESET(void)
{
	DDRD &=~ (1<<2);               //configure pin 2 in PORTD as input pin
	PORTD |= (1<<PD2);             // For Pull Up
	MCUCR |= (1<<ISC01);           // interrupt 0 sense control with falling edge
	MCUCR &= ~(1<<ISC00);
	GICR  |= (1<<INT0);           // Enable external interrupt pin INT0
}

ISR (INT0_vect)
{
	sec=0;
	min=0;
	hour=0;
}

void INT1_INIT_PAUSE(void)
{
	DDRD &=~ (1<<3);               //configure pin 3 in PORTD as input pin
	MCUCR |= (1<<ISC10);           // interrupt 1 sense control with rising edge
	MCUCR |= (1<<ISC11);
	GICR  |= (1<<INT1);            // Enable external interrupt pin INT1
}

ISR (INT1_vect)
{
	TCCR1B &=~ (1<<CS10) & ~ (1<<CS11);  //stop the timer clk
}

void INT2_INIT_RESUME(void)
{
	DDRB &=~ (1<<2);               //configure pin 2 in PORTB as input pin
	PORTB |= (1<<PB2);             // For Pull Up
	MCUCSR &= ~(1<<ISC2);          //interrupt sense control 2
	GICR  |= (1<<INT2);           // Enable external interrupt pin INT0
}

ISR (INT2_vect)
{
	TCCR1B |= (1<<CS10) | (1<<CS11);  //enable the timer clk
}

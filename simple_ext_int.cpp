#include "stdint.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include <util/delay.h>

#define F_CPU 16000000UL

ISR (INT0_vect) 
{
    PORTC ^= 1<<PC2;
}

int main() 
{
    DDRC = 0xFF;  /// Set PORTD as OUTPUT

    PORTC ^= 1<<PC2;
    _delay_ms(500);
    PORTC ^= 1<<PC2;
    _delay_ms(500);

    DDRD  |=  ( 1 << PD7 );     /// Set PIN7 IN DDRD as INPUT
    PORTD &= ~( 1 << PD7 );     /// Set PIN7 on PORTD to LOW
    DDRD  &= ~( 1 << PD2 );     // Clear the PD2 pin and set PD2 (PCINT0 pin) now as input
    PORTD |= (1 << PD2);        // Set PIN PD2 as INPUT with pull-up enabled

    EICRA |= (1 << ISC00);      // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);       // Turns on INT0
    sei(); 
    while(1) {

    }
}

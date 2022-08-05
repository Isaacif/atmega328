#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>


ISR (TIMER1_OVF_vect) 
{
  TCNT1H = (-31250)>>8;
  TCNT1L = (-31250)&0xFF;
  PORTD ^= 0b11111111;
}

int main()
{
  
  /* Set the LED pin as an output. */
  DDRD = 0xFF;
  DDRB = 0xFF;

  PORTB = 0b11111111;
  
  TCNT1H = (-31250)>>8;
  TCNT1L = (-31250)&0xFF;

  TCCR1A = 0x00;
  TCCR1B = 0X04;

  TIMSK1 = (1<<TOIE1);
  sei();
  while(1);

}

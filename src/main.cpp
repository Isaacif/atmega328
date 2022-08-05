#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

volatile uint8_t ADC_val1, ADC_val2;
volatile uint32_t ADC_total;
uint8_t Threshold = 3;
uint8_t counter = 0;

ISR (TIMER1_OVF_vect) 
{
  DIDR0 = (1<<0);
  /* Conversion takes place*/
  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1 << ADSC));
  /* After successfull conversion displayes value in ADC_val*/
  ADC_val1 = 50000*ADCL;
  ADC_val2 = 50000*ADCH; 

  switch (counter)
  {
  case 0:
        PORTB |= 0b00000001;
        break;
  
  case 1:
        PORTB |= 0b00000010;
        break;
  
  case 2:
        PORTB |= 0b00000100;
        break;

  default:
    break;
  }

  if(counter < 2) {
    counter++;
  }

  else {
    counter = 0;
  }

  ADC_total = 1000*(ADC_val1+ADC_val2);
  TCNT1H = (-312-ADC_total)>>8;
  TCNT1L = (-312-ADC_total)&0xFF;
  PORTB ^= 0b11111111;

}

int main()
{
  
  /* Set the LED pin as an output. */
  DDRD = 0xFF;
  DDRB = 0xFF;

  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
  
  ADMUX |=  (1 << REFS0) | (1 << REFS1);
  
  TCNT1H = (-3125)>>8;
  TCNT1L = (-3125)&0xFF;

  TCCR1A = 0x00;
  TCCR1B = 0X04;

  TIMSK1 = (1<<TOIE1);
  sei();
  while(1) {


  }

}

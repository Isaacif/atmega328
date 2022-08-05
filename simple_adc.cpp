#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

volatile uint8_t ADC_val;
uint8_t Threshold = 3;
int main()
{
  
  /* Set the LED pin as an output. */
  DDRD = 0xFF;
  DDRB = 0xFF;

  PORTB = 0b11111111;
  /* Enabling ADC and Setting Prescaler Division value to 32*/
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
  
  ADMUX |=  (1 << REFS0) | (1 << REFS1);
  while(1)
   {
    /* Setting the ADC5 (i.e) A5 pin in arduino to read the analog value*/
    //ADMUX = (1 << MUX2) | (1 << MUX0);     
    DIDR0 = (1<<0);
    /* Conversion takes place*/
    ADCSRA |= (1 << ADSC);
     
    while(ADCSRA & (1 << ADSC));
     /* After successfull conversion displayes value in ADC_val*/
    ADC_val = ADCL; 
    _delay_ms(1);
   
/* continually check if the ADC value is greater than the
 * defined ADC_THRESHOLD value above.  If it is turn the LED on,
 * if it isn't turn it off. */
     if(ADC_val >= Threshold){
       PORTD = 0b11111111;
     }
     
     else
     {
       PORTD = 0x00;
     }
  }
}
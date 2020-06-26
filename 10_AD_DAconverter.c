// Change brightness of 3 LEDs using PWM

#include <avr/io.h>
#define F_CPU 16000000UL    	//Define CPU clock as 16Mhz
#include <avr/interrupt.h>

int main(void)

{
	cli();
	DDRD = 0xFF; 		// Setting as output mode
	PORTD = 0x00; 		// All pins are low

	// Toggle OC1A on compare match, 
	// not really needed but it is good to check the code
	TCCR1A |= (1<<COM1A0);  

	// Enable CTC mode
	// Prescale of 1
	TCCR1B |= (1<<WGM12)|(1<<CS10); 

	// Compare A match interrupt enable
	TIMSK1 |= (1<<OCIE1A); 

	// clearing bit 7
	ADMUX &= ~(1<<REFS1);
	// Setting REFS0 and ADLAR
	ADMUX |= (1<<REFS0)|(1<<ADLAR);

	// Enable ADC
	// Start single conversion
	// Enable ADC complete interrupt
	// Input clock prescaler, 125 kHz
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

	OCR1A = 1000;  		// arbitrary value for initialization

	sei();  		// enable the interrupt

	while(1){}
	return 0;
}

ISR(TIMER1_COMPA_vect)
{
 	// if it was previously high, setting the low time
	if(PORTD >> 7) 
	{
	 OCR1A = 255; 		// constant counter match for low time
	 PORTD ^= 1<<7; 	// toggling the last three pins
	 PORTD ^= 1<<6;
	 PORTD ^= 1<<5;
	}

	// if it was previously low, setting the high time
	else
	{
	 OCR1A = ADCH;  	// getting the value of ADC and settting it to OCR1A
	 PORTD ^= 1<<7; 	// toggling the last three pins
	 PORTD ^= 1<<6;
	 PORTD ^= 1<<5;
	 ADCSRA |= (1<<ADSC); 	// start the conversion again
	}
}

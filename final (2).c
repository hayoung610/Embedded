#include <avr/io.h>
// #define F_CPU 16000000UL //define CPU clock 16MHz
#include <avr/interrupt.h>
#include <util/delay.h>

int n = 0;
int change = 1;


int main(void)
{
	cli();

	DDRB = 14; // output mode for pin 9, 10, 11 (pwm pins)

	OCR1A = 0; // starting from compare match 0
	OCR1B = 0; // starting from compare match 0

	TCCR1A |= (1<<COM1A1) | (1<<COM1B1); // clear OC1A/OC1B on compare match and set them at BOTTOM (FAST PWM)
	
	TCCR1A |= (1<<WGM11); // settings for fast PWM
	TCCR1B |= (1<<WGM12); // settings for fast PWM

	TCCR1B |= (1<<CS10); // prescaling of 1

	OCR2A = 0; // starting from compare match 0

	TCCR2A |= (1<<COM2A1); // clear OC2A on compare match and set them at BOTTOM (FAST PWM)
	TCCR2A |= (1<<WGM20) | (1<<WGM21); // settings for fast PWM

	TCCR2B |= (1<<CS20);

    //Button interrupt settings
    EICRA |= (1<<ISC01) ;  // falling edge interrupt 0
    EIMSK |= (1<<INT0);   // enable INTO

    //AD converter setting
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0)|(1<<ADLAR);
    ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

    ADCSRA |= (1<<ADSC);

    sei();

	while(1)
	{
		_delay_ms(20);
	
		n += change;

		if (change > 0)
			n %= 50;

		else
			n = (n+50) % 50;

		OCR1A = OCR1B = OCR2A = n;
	}

	return 0;
}

ISR(INT0_vect)
{
	// putting pin 9, 10, 11 in normal mode
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1B1));
	TCCR2A &= ~(1<<COM2A1); 

    int i = 0;
    for(i=0; i<3; i++) //blink three times
    {
        PORTB = 0b1111;
        _delay_ms(250);
        PORTB = 0b0000;
        _delay_ms(250);
    }

    TCCR1A |= (1<<COM1A1) | (1<<COM1B1); // clear OC1A/OC1B on compare match and set them at BOTTOM (FAST PWM)
    TCCR2A |= (1<<COM2A1); // clear OC2A on compare match and set them at BOTTOM (FAST PWM)

}

ISR(ADC_vect)
{
	if (ADCH < 127)
	{
		change = -1;
	}

	else
		change = 1;

	ADCSRA |= (1<<ADSC);
}
#include <avr/io.h>
// #define F_CPU 16000000UL //define CPU clock 16MHz
#include <avr/interrupt.h>
#include <util/delay.h>
 
int n = 0;
 
int main(void)
{
    cli();
    DDRD = 0xF0; //Set portD as output / input
    PORTD = 0x00; //All pins low

    //Button interrupt settings
    EICRA |= (1<<ISC01) ;  // falling edge interrupt 0
    EIMSK |= (1<<INT0);   // enable INTO 

    //CTC settings
    TCCR1A |= (1<<COM1A0); //Fast PWM
    TCCR1B |= (1<<WGM12)|(1<<CS11); // CTC, prescaling 


    TIMSK1 = 0x02; //Timer,Counter1, Output Compare A Match

    OCR1A = 1;

    //AD converter setting
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0)|(1<<ADLAR);
    ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    //The interrupt crashes - remove ad interrupt

    ADCSRA |= (1<<ADSC);

    sei(); // enalbe interrupt
    while (1)
    {
    }
    return 0;
}


ISR(TIMER1_COMPA_vect)
{
    if(ADCH<64) //decrease brightness
    {
        if(PORTD<<7){
            OCR1A = 2047;
            PORTD ^= 1<<7;
            PORTD ^= 1<<6;
            PORTD ^= 1<<5;
        }
        else {
            n -= 1;
            n = (n + 2048) % 2048;
            OCR1A = n;
            PORTD ^= 1<<7;
            PORTD ^= 1<<6;
            PORTD ^= 1<<5;

        }
    }
    else{ //increase brightness
        if(PORTD<<7){
            OCR1A = 2047;
            PORTD ^= 1<<7;
            PORTD ^= 1<<6;
            PORTD ^= 1<<5;
        }
        else {
            n += 1;
            n %= 2048;
            OCR1A = n;
            PORTD ^= 1<<7;
            PORTD ^= 1<<6;
            PORTD ^= 1<<5;
        }
    }
   ADCSRA |=(1<<ADSC);
}

//Button interrupt
ISR(INT0_vect)
{
    int i = 0;
    for(i=0; i<3; i++) //blink three times
    {
        PORTD = 0xF0;
        _delay_ms(250);
        PORTD = 0x00;
        _delay_ms(250);
    }          
}

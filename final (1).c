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

    TIMSK1 = 0x02; //Timer,Counter1, Output Compare A Match

    //AD converter setting
    ADMUX &= ~(1<<REFS1);
    ADMUX |= (1<<REFS0)|(1<<ADLAR);
    ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

    ADCSRA |= (1<<ADSC);

 
    sei(); // enalbe interrupt

    while (1)
    {
        
    }

    return 0;
}

ISR(ADC_vect)
{
    if(ADCH<64)
    {
        int i =0;
        PORTD = 0b00100000;


        for(i=0; i<3 ; i++){
            _delay_ms(500);
            PORTD = PORTD << 1;
        }

    }
    else{ 
        int i =0;
        PORTD = 0b10000000;
        for(i=0; i<3 ; i++){
            _delay_ms(500);
            PORTD = PORTD >> 1;
        }
    }
    ADCSRA |=(1<<ADSC);
}


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
    ADCSRA |=(1<<ADSC);          
}

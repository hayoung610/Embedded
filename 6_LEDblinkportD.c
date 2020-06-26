#include <avr/io.h>
#define F_CPU 16000000UL    //Define CPU clock as 16Mhz
#include <avr/interrupt.h>
int main(void)
{
    cli();
    DDRD = 0xF0;
    OCR1A = 62500;
    TCCR1A = 0b01000000;    //OC1A compare match toggle
    TCCR1B = 0b00001100;    //Enable CTC, clt/256
    TIMSK1 = 0x02;          //enable compare match
    sei();
    while(1){
    }
    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    OCR1A = 62500;
    PORTD ^= 1<<7;           //toggle output(LED on-off)
}

// // LED blinks continuously using CTC mode(clear timer on compare match)
// OC1A used, LED is connected to PB1 pin

#include <avr/io.h>
#define F_CPU 16000000UL        //Define CPU clock as 16Mhz
#include <avr/interrupt.h>

int main(void)
{
    cli();
    DDRB = 0x02;
    OCR1A = 6250;
    TCCR1A = 0b01000000;        //OC1A compare match toggle
    TCCR1B = 0b00001100;        //Enable CTC, clt/256
    TIMSK1 = 0x02;              //enable compare match
    sei();
    while(1){
    }
    return 0;
}

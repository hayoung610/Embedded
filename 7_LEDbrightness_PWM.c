// Change LED brightness using PWM waveform
// The LED brightness changes with time
// The brightness is controlled by how long the LED is on or off

#include <avr/io.h>
#define F_CPU 16000000UL    //Define CPU clock as 16Mhz
#include <avr/interrupt.h>

int n = 0;

int main(void)
{
    cli();
    DDRD = 0xF0;          //Set PORTD pin 4-7 to output
    OCR1A = 62500;
    TCCR1A = 0b01000000;  //OC1A compare match toggle
    TCCR1B = 0b00001001;  //Enable CTC, clt/1 (higher freq)
    TIMSK1 = 0x02;        //enable compare match
    sei();
    while(1){
    }
    return 0;
}
ISR(TIMER1_COMPA_vect)     //Fix on time and changed off time
{
    if(PORTD >> 7)         //When LED ON
    {
         OCR1A = 5000;
         PORTD ^= 1<<7;    //toggle
    }
    else{ \\When LED OFF
         n += 1;           //increase value of OCR1A every time
         n %= 5000;        //to change the off time and
         OCR1A = n;        //set back to 0 when it reaches 5000
         PORTD ^= 1<<7;    //toggle
    }
}

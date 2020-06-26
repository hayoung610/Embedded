// 3 LEDs blinks one after another with period of 0.5s
// When an external interrupt is triggered, all 3 LEDs blink three times simultaneously
// External interrupt is set as a switch connected to INT0 pin


#include <avr/io.h>             //Contains the neccessary definitions for the MCU
#define F_CPU 16000000UL        //Define CPU clock as 16Mhz
#include <util/delay.h>         //Helper functions for delay implementation
#include <avr/interrupt.h>

int main(void)
{
    cli();                      //Turn off the interrupt
    EICRA = 0X02;               //Looking for the falling edge
    EIMSK = 0X01;               //Mask register for INT0
    sei();                      //Turn on the interrupt

    int i;
    DDRD = 0xF0;                //Setting the last four ports as output
                                //Here, only three of them are used
    while(1)
    {
        PORTD = 0x80;           //The first LED is on
        for (i = 0; i < 2; i++)
        {
            _delay_ms(500);     // Delay of 500 ms
            PORTD = PORTD >> 1; // Right shift the ON port, second LED turns on
                                // Repeats..
        }
        _delay_ms(500);
    }
    return 0;
}

ISR(INT0_vect)                  //Interrupt routine for INT0
{
    int i;
    for (i = 0; i < 3; i++)     //Blinking three times
    {
        PORTD = 0XF0;           //Last four ports are on
                                //All LEDs will lighten up
        _delay_ms(250);         //Shorter delay
        PORTD = 0X00;           //All LEDs will turn off
        _delay_ms(250);
    }
}

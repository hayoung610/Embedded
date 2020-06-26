; Continuously blinking LED with period of 1 second
; LED connected to PORTD
; CPU of 16MHz

.include "m328def.inc"
.org 0x0000
RJMP begin; jump to begin  
.org 0x0034
 begin:  CLI			                             ;Clear Interrupt, Set register value to 0
         LDI    R16,  low(RAMEND)           ;load low byte of RAMEND into R16
         OUT    SPL,  R16		                 ;store R16 in stack pointer low
         LDI    R16,  high(RAMEND)          ;load high byte of RAMEND into R16
         OUT    SPH,  R16                   ;store R16 in stack pointer low
         LDI    R16,  0xFF                  ;R16 =0xFF= 0b11111111
         OUT    DDRD, R16 	                 ;Set Port D as output port, all pins as output pins

blink:   LDI    R16,  0xFF                  ;R16 =0xFF= 0b11111111  
         OUT    PORTD, R16	                 ;Write  0b11111111 to Port D –turn on LED
         RCALL  Delay                       ;Call Delay
         LDI    R16,  0x00                  ;R16 =0xFF= 0b00000000  
         OUT    PORTD, R16                  ;Write R16 to Port D – turn off LED  
         RCALL  Delay
         JMP    blink                    
Delay:   LDI    R17,  0x52                  ;set R17 register to decimal 82
         LDI    R18,  0x2B  	               ;set R18 to decimal 43
         LDI    R19,  0x00  	               ;set R19 to decimal 0
loop:    DEC    R19                         ;Decrement R19 
         BRNE   loop                        ;go through loop till R19 reaches 0
         DEC    R18                         ;Decrement R18
         BRNE   loop                        ;go through loop till R18 reaches 0
         DEC    R17                         ;Decrement R17
         BRNE   loop                        ;go through loop till R17 reaches 0
         RET


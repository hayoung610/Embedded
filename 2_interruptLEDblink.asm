; Blink with period 1s continuously
; When there is an interrupt, Blink twice quickly (blink with period 0.5s)
; The interrupt is a switch connected to PIN2 of PORTD
; LED is connected to PIN7 of PORTD

.include "../m328Pdef.inc"
.org 0x0000
  	RJMP begin		; jump to begin
.org 0x0002          		;Initialize the stack pointer, Program address of INT0 interrupt
	RJMP intr		;Jump to interrupt

.org 0x0034
begin:    
	CLI
    	LDI R16,low(RAMEND)
    	OUT SPL,R16
    	LDI R16,high(RAMEND)
    	OUT SPH, R16
 

	LDI R23, 0b00000010
    	STS EICRA, R23  	;Interrupt at falling edge of INT0
    	LDI R23, 0b00000001
    	OUT EIMSK, R23  	;INT0 external interrupt enabled
    	LDI R23, 0xF0
	OUT DDRD, R23  		;set output and input pins in PORTD
	SEI
	     
main:   			;continuous blinking with 1 second period
	LDI R16,0xFF
	OUT PORTD, R16 		;turn on LED
	RCALL Delay
	LDI R16,0x00
	OUT PORTD, R16 		;turn off LED
	RCALL Delay
	JMP main
	
Delay:  			;Gives delay of 1 second
	LDI R17, 0x52
	LDI R18, 0x28
	LDI R19, 0x00
loop:
	DEC R19
	BRNE loop  
	DEC R18
	BRNE loop    
	DEC R17
	BRNE loop        
	RET  

Delay2:  			;Gives delay of 0.5 second
	LDI R20, 0xFF
	LDI	R21, 0xFF
	LDI	R22, 0x14
loop2:
	DEC R20
	BRNE loop2  
	DEC R21
	BRNE loop2    
	DEC R22
	BRNE loop2        
	RET    

intr:                		;When interrupt, quickly blink twice
	LDI R16,0xFF
	OUT PORTD, R16 		;LED on
	RCALL Delay2
	LDI R16,0x00
	OUT PORTD, R16 		;LED off
	RCALL Delay2
	LDI R16,0xFF
	OUT PORTD, R16 		;LED on
	RCALL Delay2
	LDI R16,0x00
	OUT PORTD, R16 		;LED off
	RCALL Delay2
	RETI

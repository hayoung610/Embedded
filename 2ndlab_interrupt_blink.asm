.include "../m328Pdef.inc"

.org 0x0000
  	RJMP begin; jump to begin

.org 0x0002          ;Initialize the stack pointer
   RJMP intr;

.org 0x0034
begin:    
	CLI
    LDI R16,low(RAMEND)
    OUT SPL,R16
    LDI R16,high(RAMEND)
    OUT SPH, R16
 

	LDI R23, 0b00000010
    STS EICRA, R23
    LDI R23, 0b00000001
    OUT EIMSK, R23
    LDI R23, 0xF0
	OUT DDRD, R23
	SEI
             
main: 
	LDI R16,0xFF
	OUT PORTD, R16
	RCALL Delay
	LDI R16,0x00
	OUT PORTD, R16
	RCALL Delay
	JMP main

Delay:
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

Delay2: 
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

intr:                
	LDI R16,0xFF
	OUT PORTD, R16
	RCALL Delay2
	LDI R16,0x00
	OUT PORTD, R16
	RCALL Delay2
	LDI R16,0xFF
	OUT PORTD, R16
	RCALL Delay2
	LDI R16,0x00
	OUT PORTD, R16
	RCALL Delay2
	RETI
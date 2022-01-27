;
; test2.asm
;
; Created: 26.10.2020 19:11:50
; Author : ramenbox
;


; Replace with your application code

//include board datei - wie zB include <iostream>
.include "m328Pdef.inc"

//reset vector - Startet bei Reset hier 
.org 0x000
 rjmp start 

start:
	ldi r16, 0b11111111
	out DDRD, r16		//Alles im Output auf 1 setzen 
	ldi r17,0b00000001	//Laufregister
 
links:
 ldi r21, 7
pnkt:
 lsl r17
 out PORTD, r17
 rcall Delay //Delay Funktion wird über RCALL aufgerufen
 dec r21
 brne pnkt
 rjmp rechts

rechts:
 ldi r22, 7
pnkt1:
 lsr r17
 out PORTD, r17
 rcall Delay //Delay Funktion wird über RCALL aufgerufen
 dec r22
 brne pnkt1
 rjmp links


// Delay 3 200 000 cycles
// Funktion für : 200ms at 16.0 MHz
delay:
    ldi  r18, 17
    ldi  r19, 60
    ldi  r20, 204
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
ret

/*
Die Delay-Funktion habe ich von der Seite " http://darcy.rsgc.on.ca/ACES/TEI4M/AVRdelay.html " < Link allerdings etwas Fischy, also achtet drauf.
*/

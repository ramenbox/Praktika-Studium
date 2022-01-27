/*
 * Created: 12.12.2020 18:34:17
 * Author : ramenbox
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
volatile int32_t systemClock = 0; //Volatile um auf Interrupts zuzugreifen, da sie sich immer anders verhalten könnte


//3 mSekunden - >+10 13ms

//Wartet für millisekunden
void waitFor(int32_t ms)  //10 ms
{
	//Wartet bis die clock das relative ende erreich hat -- systemclock > int -- systemclock == int32bit
	int32_t relEnd = (systemClock + ms); //int relEnd = (systemClock + ms); int nicht (32bit) groß genug, 
	while(systemClock < relEnd){}
}

/*
void waitFor(int32_t ms){
	int relEnd = (systemClock + ms);
	while(systemClock < relEnd){}
}*/


//3ms ->+7 10ms

//Wartet bis der Zähler den Wert ms erreicht hat
void waitUntil(int32_t ms){ //10ms
	while(systemClock < ms){}
}


//jedes mal wenn Timer einen interrupt triggered die clock erhöhen
ISR(TIMER0_OVF_vect)
{
	systemClock++; //32 Bit?
}

int main(void)
{
	DDRD = 0b11111111;
	PORTD = 0b00000000;
	
	//Timer Counter Control Register
    //TCCR0A = 0b00000010;		//Clear OC0A on Compare Match - wenn 250 erreicht wird dann clear
    TCCR0B = 0b00000011;		//clkI/O/64 (From prescaler) - teilt den Takt vor, bei jedem 64ten Signal den Timer erhöhen
    //OCR0A = 250;				//mit CTC -> jedes mal wenn der Timer 250 erreicht reset 
    TIMSK0 = 0b00000001;		//enable interrupts
	//When the TOIE0 bit is written to one, and the I-bit in the Status Register is set, the Timer/Counter0
	//Overflow interrupt is enabled.
	sei();

			PORTD = 0b01;
			waitUntil(500);
	
			PORTD = 0b10;
			waitUntil(1000);

	while(1)
	{
			PORTD = 0b01;
			waitFor(1000);
	
			PORTD = 0b10;
			waitFor(1000);
	}
}

/* 
a)	Wie lange dauert es, bis der Zähler überläuft?
	256 / 8 Bit Timer
	Overflow passiert nachdem 0-255 gezählt wurde.
	Dann wieder reset.

b) Was könnte man tun, um größere Zeiten zu verarbeiten?
	Man könte bspw. eine Größere Zahl nehmen.
	
	
	Notizen:
	
	16000000/ 64 = 250000
	2500000 / 256 = 976.5625
	1 Sekunde / 976.5625 = 0.00124s
	0.00124s = ca. 1ms
*/
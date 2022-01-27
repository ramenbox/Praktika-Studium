/*
 * main.c
 *
 * Created: 07.12.2020 01:42:23
 * Author : ramenbox
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL//Taktfrq
#include <util/delay.h>
#include <avr/interrupt.h>

int speicher = 0;
int boolean = 1;

//SW1 - AVR Interrupt Vectors
ISR(INT0_vect) {
    speicher = 1;
}
//SW2 - AVR Interrupt Vectors
ISR(INT1_vect) {
    speicher = 2;
}

int main(void)
{
    DDRD = 0x00; //eingang taster PortC
    PORTD = 0xFF;  //pullups enable

    DDRB = 0xFF; //ausgang PortB
    PORTB = 0x00; //LEDs aus
    
    //enable und mask INT0, INT1
	EICRA |= (1 << ISC10); // The falling edge of INT0 generates an interrupt request.
	EICRA |= (1 << ISC11); // The rising edge of INT1 generates an interrupt request.
	EICRA |= (1 << ISC00); // The low level of INT0 generates an interrupt request
	EICRA |= (1 << ISC01); // Any logical change generates an interrupt request.
	EIMSK |= (1 << INT1); // interrupt INT1 in PD3
	EIMSK |= (1 << INT0); // interrupt INT0 in PD2
    sei(); //enable interrupts, global
    
    while (boolean == 1) 
    {
		if(speicher == 1)//PINC0
		{
			PORTB = 1;
			_delay_ms(200);
			PORTB = 0;
		}
		else if(speicher == 2)//PINC1
		{
			 PORTB = 2;
			 _delay_ms(200);
			 PORTB = 0;
		}
		_delay_ms(200);
    }
}

/*
Vorteile:

- Reaktionen geschiehen direkt, keine Verzögerung
- Rechenzeit wird nicht verschwendet

Nachteile:

- Die Hardware muss diese Funktionen unterstützen, also z.B. Taster
- Benötigt mehr Speicher und ist auch dem entsprechend aufwändiger zu implementieren
*/
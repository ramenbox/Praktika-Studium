/*
 * main.c
 *
 * Created: 06.12.2020 20:18:37
 * Author : ramenbox
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL//Taktfrq
#include <util/delay.h>

int main(void)
{
  DDRC = 0x00; //eingang taster PortC
  PORTC = 0xFF;  //pullups enable

  DDRB = 0xFF; //ausgang PortB
  PORTB = 0x00; //LEDs aus
    
  int speicher = 0;
  int boolean = 1;

  while(boolean == 1) 
  {
        //taster zu PINC0 betätigt
        if (~PINC & (1<<PINC0))
        {
            //umschalten zu LED D0
            PORTB = 0x00;
            _delay_ms(200);
            speicher = 1;
        }
        //taster zu PINC1 betätigt
        else if (~PINC & (1<<PINC1))
        {
            //umschalten zu LED D9
            PORTB = 0x00;
            _delay_ms(200);
            speicher = 2;
        }

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
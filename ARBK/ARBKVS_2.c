/*
 * main.c
 *
 * Created: 20.11.2020 12:43:23
 * Author : ramenbox
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL //Berechnet Taktfrequenz
#include <util/delay.h>

void rechts(){
    for(int i = 0; i < 8; i++){
        PORTD = (1 << i);
        _delay_ms(200);
        PORTD = 0x00;
    }
    
    for(int i = 0; i < 2; i++){
        PORTB = (1 << i);
        _delay_ms(200);
        PORTB = 0x00;
    }
}

void links(){
    for (int i = 0; i <= 1; i++)
    {
            PORTB = (1 >> i);
            if (i == 0)
            {
                _delay_ms(200);
            }
            PORTB = 0x00;
    }
    
    for(int i = 0; i <= 7; i++)
    {
        PORTD = (0b10000000 >> i);
        _delay_ms(200);
        PORTD = 0x00;
    }
}
    
int main(void)
{
    DDRD = 0b11111111;
    DDRB = 0b11111111;
    PORTD = 0x00;
    PORTB = 0x00;
    
    while(1){
        rechts();
        links();
    }
}

//Aufg e)
//Praktikum 1 : 186 Bytes
//Praktikum 2 : 993 Bytes

//Aufg f)
//-O1) 378 Bytes
//-O2) 328 Bytes
//-03) 320 Bytes
//-0s) 334 Bytes
//-0g) 368 Bytes
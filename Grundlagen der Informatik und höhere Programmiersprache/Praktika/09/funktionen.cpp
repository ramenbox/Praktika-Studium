#include <iostream>
#include "funktionen.h"

using namespace std;

void cstring_einlesen(char* text, bool leer_sein)
{
    
    // To be deleted - Code nicht mehr nötig, da cin.get() es ablöst
    // Sonst kann man nicht nach Leerzeichen im Text suchen
    // Flag
    /*if(not leer_sein) 
    {
        
        // nutze cin.get() um leeren input zu bekommen
        // sonst nutze cin >> buff um den User nach input zu zwingen.
        
        // Überlauf bei mehr als 20 Zeichen
        while(cin >> buff and cstring_len(buff) < 21 and cin.get() != '\n')
        {
            // Text bis zum Leerzeichen wird vom Buffer
            // in char array gespeichert
            cstring_speichern(text, buff, b_cnt);
            
            text[b_cnt++] = ' '; // Danach Leerzeichen setzen
        }
        // Wenn ohne Leerzeichen eingegeben worden ist,
        // ist die Eingabe noch im Buffer und muss ins char array überführt werden
        cstring_speichern(text, buff, b_cnt);
        text[b_cnt] = '\0'; // Terminiere C-String anständig
        
        return;
    }*/
    
    char buff[21];
    unsigned int b_cnt = 0;

    // Überlauf bei mehr als 20 Zeichen
    while(cin.get(buff, 20)) // Sodass Zeichen nicht im Buffer bleiben bei > 20 (Sonst wird der Rest im nächstem gespeichert)
    {
        // Text wird im temporären buffer geladen
        cstring_speichern(text, buff, b_cnt);
    }
    
    // Streambuffer leeren
    cin.clear();
    cin.ignore();
    
    text[b_cnt] = '\0'; // Terminiere C-String anständig
}

void cstring_speichern(char* text, char* buff, unsigned int &pos)
{
    for(unsigned int i = 0; i < cstring_len(buff) and pos < 21; i++) // pos < 21, weil buff größer sein kann
    {
        text[pos++] = buff[i];
    }
}

unsigned int cstring_len(const char* text)
{
    for(int i = 0; i < 21; i++)
    {
        if(text[i] == '\0') return i;
    }
    
    return 20;
}

void cstring_ausgeben(char* text)
{
    for(unsigned int i = 0; i < cstring_len(text); i++)
    {
        cout << text[i];
    }
}

bool cstring_leer(const char* text)
{
    //Zum Testen ob der C-String leer ist
   if (text[0] == '\0') return true;
   else return false;
}